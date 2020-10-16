//
// Created by anon on 14.10.2020.
//

#ifndef __INTERSECT_ALGO_H__
#define __INTERSECT_ALGO_H__

#include "Triangle.h"


/*
bool Intersect2D(Triangle& trian1, Triangle& trian2);

//!
//! \param pnts_buf
//! \param line
//! \param prjctions
void Make_projection(Vec* pnts_buf, Line& line, Vec* prjctions);

//!
//! \param plane
//! \param points
//! \param dist
void Dist_calculation(Plane& plane, double* points, double* dist);


//! Function for checking sign of distance
//! \param dist
//! \return
bool Dist_checker(double* dist);


//! Function for checking interval of t_vectors
//! \param t_points1
//! \param t_points2
//! \return
bool Interval_checking(Vec* t_points1, Vec* t_points2);

bool Intersect_algos(Triangle& trian1, Triangle& trian2);
*/


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

    if (t_points1[0] > t_points2[1] || t_points1[1] < t_points2[0])
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



bool Intersect_2D(Triangle& trian1, Triangle& trian2)
{
    return false;
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




bool Triangle::Intersect_algo(Triangle& trian1, Triangle& trian2)
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
                res = Intersect_2D(trian1, trian2);
                return res;
            }
            else if (((trian1.vec1 - trian2.vec1) & n1) != 0)
                return false;
        }

        res = Intersect_3D(plane1, plane2, points1, points2, dist1);
    }

    return res;
}





#endif //TRIANGLES_INTERSECT_ALGO_H
