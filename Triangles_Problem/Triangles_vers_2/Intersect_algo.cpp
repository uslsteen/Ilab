//
// Created by anon on 15.10.2020.
//

#include "Intersect_algo.h"


int Get_mid_index(int i0, int i1, int N)
{
    if (i0 < i1)
        return (i0 + i1) / 2;
    else
        return (i0 + i1 + N) / 2 % N;
}

int Get_extreme_index(const Triangle& trian, const Vec& pt)
{
    int i0 = 0, i1 = 0;

    while (true)
    {
        int mid = Get_mid_index(i0, i1, 3);
        int next = (mid + 1) % 3;

        Vec E(trian[next] - trian[mid]);

        if ((E & pt) > 0)
        {
            if (mid != i0)
                i0 = mid;
            else
                return i1;
        }
        else
        {
            int prev = (mid + 3 - 1) % 3;

            E = trian[mid] - trian[prev];

            if ((E & pt) < 0)
                i1 = mid;
            else
                return mid;
        }
    }
}


int Find_max_ind(double a, double b, double c)
{
    int ind = 0;
    double max = 0;

    if (a > b)
    {
        ind = 0;
        max = a;
    }
    else
    {
        ind = 1;
        max = b;
    }

    if (max < c)
        ind = 2;

    return ind;
}


bool Test_intersection(const Triangle& trian1, const Triangle& trian2)
{
    for (int i0 = 0, i1 = 2; i0 < 3; i1 = i0, ++i0)
    {
        Vec D1((trian1[i0] - trian1[i1]).perp_2D()), D2((trian2[i0] - trian2[i1]).perp_2D());

        int min1 = Get_extreme_index(trian1, -D1), min2 = Get_extreme_index(trian2, -D2);

        Vec diff1(trian2[min1] - trian2[i0]), diff2(trian1[min2] - trian2[i0]);

        if ((D1 & diff1) > 0 || (D2 & diff2) > 0)
            return false;
    }

    return true;
}



bool Intersect_2D(const Triangle &trian1, const Triangle &trian2, const Vec& normal)
{
    double  Oxy = std::abs(normal & Vec(0, 0, 1)),
            Oxz = std::abs(normal & Vec(0, 1, 0)),
            Oyz = std::abs(normal & Vec(1, 0, 0));

    size_t j = 0;

    size_t max_ind = Find_max_ind(Oyz, Oxz, Oxy);

    Vec new_trian1[3], new_trian2[3];

    for (size_t i = 0; i < 2; ++i)
    {
        if (i == max_ind)
            continue;

        for (size_t k = 0; k < 3; ++k)
        {
            new_trian1[k][j] = trian1[k][i];
            new_trian2[k][j] = trian2[k][i];
        }

        ++j;
    }

    return Test_intersection(Triangle(new_trian1[0], new_trian1[1], new_trian1[2]),
                             Triangle(new_trian2[0], new_trian2[1], new_trian2[2]));
}



bool Dist_checker(double* dist)
{
    if ((dist[1] > 0 && dist[2] > 0 && dist[3] > 0) || (dist[1] < 0 && dist[2] < 0 && dist[3] < 0))
        return false;

    else
        return true;
}


void T_compution(double* prjctions, double* dist, double* t_points)
{
    for (int i = 0; i < 2; ++i)
        t_points[i] = prjctions[i] + (prjctions[2] - prjctions[i])*((dist[i])/(dist[i] - dist[2]));
}


void swap(double* x, double* y)
{
    double temp = *y;
    *y = *x;
    *x = temp;
}


bool Interval_checking(double* t_points1, double* t_points2)
{
    if (t_points1[0] > t_points1[1])
        swap(&t_points1[0], &t_points1[1]);

    if (t_points2[0] > t_points2[1])
        swap(&t_points2[0], &t_points2[1]);

    if (t_points1[0] >= t_points2[1] || t_points1[1] <= t_points2[0])
        return false;

    else
        return true;
}



void Dist_calculation(Plane& plane, Vec* points, double* dist)
{
    for (int i = 0; i < 3; ++i)
        dist[i] = plane.Dist_to_vec(points[i]);
}


void Line::Make_projection(Vec* pnts_buf, Line& line, double* prjctions)
{
    for (int i = 0; i < 3; ++i)
        prjctions[i] = (line.dir & (pnts_buf[i] - line.r0));

}


Line Plane::Plane_intersection(Plane& plane1, Plane& plane2)
{
    Vec n1 = plane1.normal, n2 = plane2.normal;
    Vec dir = n1 % n2;

    double D1 = plane1.D, D2 = plane2.D;
    double n1_scl_n2 = n1 & n2, n1_scl_n1 = n1 & n1, n2_scl_n2 = n2 & n2;

    double a = (D2 * n1_scl_n2 - D1 * n2_scl_n2) / (n1_scl_n2*n1_scl_n2 - n1_scl_n1 * n2_scl_n2);
    double b = (D1 * n1_scl_n2 - D2 * n1_scl_n1) / (n1_scl_n2 * n1_scl_n2 - n1_scl_n1 * n2_scl_n2);

    Vec r0 = (n1*a + n2*b);

    return Line(r0, dir);
}

bool Intersect_3D(Plane& plane1, Plane& plane2, Vec* points1, Vec* points2, double* dist1)
{
    double dist2[3] = {0, 0, 0};

    Dist_calculation(plane2, points1, dist2);

    if (!Dist_checker(dist2))
        return false;

    Line line_intsct = plane1.Plane_intersection(plane1, plane2);

    double t_points1[2], t_points2[2], prjctions1[3], prjctions2[3];

    line_intsct.Make_projection(points1, line_intsct, prjctions1);
    line_intsct.Make_projection(points1, line_intsct, prjctions2);

    T_compution(prjctions1, dist1, t_points1);
    T_compution(prjctions2, dist2, t_points2);

    bool res = Interval_checking(t_points1, t_points2);

    return res;
}




bool Triangle::Intersect_algo(const Triangle& trian1, const Triangle& trian2)
{
    Plane plane1(trian1.vec1, trian1.vec2, trian1.vec3);
    Vec n1 = plane1.Get_normal();

    Vec points1[3] = {trian1.vec1, trian1.vec2, trian1.vec3};
    Vec points2[3] = {trian2.vec1, trian2.vec2, trian2.vec3};

    double dist1[3] = {0, 0, 0};

    bool res = false;

    Dist_calculation(plane1, points2, dist1);

    if (!Dist_checker(dist1))
        return false;

    else
    {
        Plane plane2(trian2.vec1, trian2.vec2, trian2.vec3);
        Vec n2 = plane2.Get_normal();

        if ((n1 % n2) == Vec(0, 0, 0))
        {
            if (((trian1.vec1 - trian2.vec1) & n1) == 0)
            {
                res = Intersect_2D(trian1, trian2, plane1.Get_normal());
                return res;
            }
            else if (((trian1.vec1 - trian2.vec1) & n1) != 0)
                return false;
        }

        res = Intersect_3D(plane1, plane2, points1, points2, dist1);
    }

    return res;
}
