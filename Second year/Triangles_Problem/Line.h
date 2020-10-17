//
// Created by anon on 12.10.2020.
//

#ifndef TRIANGLES_LINE_H
#define TRIANGLES_LINE_H

#include "Vec.h"

//! Canon form of line : r = r0 + a*t

class Plane;

class Line
{
private:

    Vec r0;
    Vec dir; // <=> a

public:

    //! Constructor of line by main dir and origin point(vec)
    Line(Vec& r0_, Vec& dir_) : r0(r0_),
                                dir(dir_)
    {}

    //! Empty constructor of line
    Line(): r0(0, 0, 0),
            dir(0, 0, 0)
    {}


    void Make_projection(Vec* pnts_buf, Line& line, double* prjctions);


    void dump(std::ostream& os) const
    {
        os << "r0 = " <<  r0 << ", dir = " << dir << std::endl;
    }

};


#endif //TRIANGLES_LINE_H
