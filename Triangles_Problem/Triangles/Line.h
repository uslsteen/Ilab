//
// Created by anon on 12.10.2020.
//

#ifndef TRIANGLES_LINE_H
#define TRIANGLES_LINE_H

#include "Vector.h"

//! Canon form of line : r = r0 + a*t

class Plane;

class Line
{
private:

    Vec r0;
    Vec dir; // <=> a

public:

    //! Constructor of line by two points
/*
    Line (Vec& vec1, Vec& vec2): dir(vec2 - vec1),
                                 r0(vec1)
    {
    }
    */

    Line(): r0(0, 0, 0),
            dir(0, 0, 0)
    {}

    Line(Vec& r0_, Vec& dir_) : r0(r0_),
                                dir(dir_)
    {}
    //! Constructor of line by main din vector and point on the this line

    //! Constructor of line as the intersection of two plan
    //!
    //! \param plane1
    //! \param plane2
    //! \param vec1
    //! \param vec2
    /*
    Line(Plane& plane1, Plane& plane2, Vec& r01, Vec& r02)
    {
        double r0x = NAN, r0y = NAN, r0z = NAN;
        Vec n1 = plane1.normal, n2 = plane2.normal;

        dir = (n1 % n2);

        r0x = (n1.x*r01.x_ - n2.x_*r02.x_)/(n1.x_ - n2.x_);
        r0y = (n1.y*r01.y_ - n2.y_*r02.y_)/(n1.y_ - n2.y_);
        r0z = (n1.z*r01.z_ - n2.z_*r02.z_)/(n1.z_ - n2.z_);

        r0(r0x, r0y, r0z);
    }
     */

    void dump(std::ostream& os) const
    {
        os << "r0 = " <<  r0 << ", dir = " << dir << std::endl;
    }

    Line& Plane_intersection(Plane& plane1, Plane& plane2, Vec& r01, Vec& r02);

    void Make_projection(Vec* pnts_buf, Line& line, double* prjctions);
};


#endif //TRIANGLES_LINE_H
