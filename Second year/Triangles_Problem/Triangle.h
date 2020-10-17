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

    Triangle(const Vec& vec1_, const Vec& vec2_, const Vec& vec3_) : vec1(vec1_),
                                                   vec2(vec2_),
                                                   vec3(vec3_)
    {}

    void dump(std::ostream& os) const
    {
        os << "vec1 = " << vec1 << ", vec2 = " << vec2 << ", vec3 = " << vec3 << std::endl;
    }

    const Vec& operator [](int ind) const
    {
        return *(&vec1 + ind % 3);
    }


    bool Intersect_algo(const Triangle& trian1, const Triangle& trian2);

    friend bool Intersect_2D(const Triangle &trian1, const Triangle &trian2, const Vec& normal);

};


#endif //TRIANGLES_TRIANGLE_H
