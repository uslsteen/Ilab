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
    Plane(const Vec& vec1, const Vec& vec2, const Vec& vec3) : normal(((vec3 - vec1) % (vec2 - vec1)).normalize()),
                                                               D(vec1 & normal)
    {
    }

    //! Copy constructor of class plane
    Plane(const Plane& plane) : normal(plane.normal),
                                D(plane.D)
    {
    }

    //! Empty constructor of class plane
    Plane() : normal(Vec()),
              D(0)
    {
    }

    //! Calculating distance from point(vector) to plane (without abs)
    //! dist = (r, n) - (r0, n)
    //! \param vec
    //! \return distance
    double Dist_to_vec(const Vec& vec)
    {
        double dist = (vec & normal) - D;

        return dist;
    }


    //! Getters for class plane
    Vec Get_normal()
    {
        return normal;
    }

    double Get_D()
    {
        return D;
    }

    void dump(std::ostream& os) const
    {
        os << "normal vec = " << normal << ", D = " << D << std::endl;
    }


    Line Plane_intersection(const Plane& plane1, const Plane& plane2);
};

#endif //TRIANGLES_PLANE_H
