//
// Created by anon on 11.10.2020.
//
#ifndef TRIANGLES_PLANE_H
#define TRIANGLES_PLANE_H

#include "Line.h"

class Triangle;

class Plane {
private:
    //! Plane equation in form (r - r0, n) = 0 <=> (r, n) = (r0, n) = D
    //! Normal vector of the plane
    Vec normal;
    double D;

public:

    //! Plane constructor with help three points(vectors)
    Plane(Vec& vec1, Vec& vec2, Vec& vec3)
    {
        normal = (vec3 - vec1) % (vec2 - vec1);
        normal.Normalize();

        D = normal & vec1;
    }

    //! Calculating distance from point(vector) to plane (without abs)
    //! dist = (r, n) - (r0, n)
    //!
    //! \param vec
    //! \return
    double Dist_to_vec(Vec& vec)
    {
        double dist = (vec & normal) - D;

        return dist;
    }

    void dump(std::ostream& os) const
    {
        os << "normal vec = " << normal << ", D = " << D << std::endl;
    }

    friend bool Intersect_algos(Triangle& trian1, Triangle& trian2);
    friend Line& Line::Plane_intersection(Plane& plane1, Plane& plane2, Vec& r01, Vec& r02)
};

#endif //TRIANGLES_PLANE_H
