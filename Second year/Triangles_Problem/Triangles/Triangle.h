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

    //! Constructor for triange with help three vectors

    Triangle(Vec& vec1_, Vec& vec2_, Vec& vec3_) : vec1(vec1_),
                                                   vec2(vec2_),
                                                   vec3(vec3_)
    {}

    void dump(std::ostream& os) const
    {
        os << "vec1 = " << vec1 << ", vec2 = " << vec2 << ", vec3 = " << vec3 << std::endl;
    }

    friend bool Intersect_algos(Triangle& trian1, Triangle& trian2);
};


#endif //TRIANGLES_TRIANGLE_H
