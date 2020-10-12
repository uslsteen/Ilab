//
// Created by anon on 11.10.2020.
//

#ifndef TRIANGLES_TRIANGLE_H
#define TRIANGLES_TRIANGLE_H

#include "Plane.h"

class Triangle
{
private:
    Vec vec1, vec2, vec3;

public:

    Triangle(Vec& vec1_, Vec& vec2_, Vec& vec3_) : vec1(vec1_),
                                                vec2(vec2_),
                                                vec3(vec3_)
    {}

    friend bool Intersect_check(Triangle& trian1, Triangle& trian2);

};

void Make_projections(Vec* pnts_buf, Line& line, Vec* prjctions)
{
    for (i = 0; i < 3; ++i)
        prjctions[i] = (line.dir & (pnts_buf[i] - line.r0));

}

void Dist_calculation(Plane& plane, double* points, double* dist)
{
    for (int i = 0; i < 3; ++i)
        dist[i] = plane.Dist_to_vec(points[i]);
}

bool Dist_checker(double* dist)
{
    if ((dist[1] > 0 && dist[2] > 0 && dist[3] > 0) || (dist[1] < 0 && dist[2] < 0 && dist[3] < 0))
        return false;

    else return true;
}

void T_compution(Vec* prjctions, double dist, Vec* t_points)
{
    for (int i = 0; i < 2; ++i)
        t_points[i] = prjctions[i] + (prjctions[2] - prjctions[i])*((dist[i])/(dist[i] - dist[2]));
}


//!
//! \param trian1
//! \param trian2
//! \return
bool Intersect_check(Triangle& trian1, Triangle& trian2)
{
    Plane plane1(trian1.vec1, trian1.vec2, trian1.vec3);
    Vec points1[3] = {trian1.vec1, trian1.vec2, trian1.vec3};
    Vec points2[3] = {trian2.vec1, trian2.vec2, trian2.vec3};
    double dist1[3] = {0, 0, 0};

    Dist_calculation(plane1, points2, dist1)

    //Checking
    if (!Dist_checker(dist1))
        return false;

    else
    {
        Plane plane2(trian2.vec1, trian2.vec2, trian2.vec3);

        if (plane1.normal % plane.normal == 0)
        {
            if ((trian1.point1 - trian2.point2) & plane1.normal == 0)
            {
                bool res = Intersect2D(trian1, trian2);
                return res;
            }
            else if ((trian1.point1 - trian2.point2) & plane1.normal != 0)
                return false;
        }

        double dist2[3] = {0, 0, 0};

        //double dist4 = plane2.Dist_to_vec(trian1.point1), dist5 = plane1.Dist_to_vec(trian1.point2), dist6 = plane1.Dist_to_vec(trian1.point3);
        Dist_calculation(plan2, points1, dist2)

        if (!Dist_checker(dist2))
            return false;

        Line line(plane1, plane2, train1.vec1, train2.vec2);

        Vec t_points1[2], t_points2[2], prjctions1[3], prjctions2[3];

        Make_projection(points1, line, prjctions1);
        Make_projection(points1, line, prjctions2);

        T_compution(prjctions1, dist1, t_points1);
        T_compution(prjctions2, dist2, t_points2);
        
    }
}





#endif //TRIANGLES_TRIANGLE_H
