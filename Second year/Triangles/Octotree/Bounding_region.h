//
// Created by anon on 03.11.2020.
//

#ifndef TRIANGLES_UPD_BOUNDING_REGION_H
#define TRIANGLES_UPD_BOUNDING_REGION_H

#include "Geom_lib/Vec.h"


enum Obj_cond
{
    BELNG = 0,
    PARTLY_BELNG,
    DSNT_BELNG,
};

class Bounding_region {
private:

    Vec bot_vec, top_vec;


public:

    Bounding_region(const Vec &bot_, const Vec &top_) : bot(bot_),
                                                        top(top_)
    {
    }

    Bounding_region(const Vec& reg) : bot(reg.bot),
                                      top(reg.top)
    {
    }

    bool does_it_belong(const Vec& vec)
    {
        int cnter = 0;

        for (int i = 0; i < 3; ++i)
        {
            if (abs(bot_vec.get_val(i) - vec.get_val(i)) + abs(top_vec.get_val(i) - vec.get_val(i)) == abs(top_vec.get_val(i) - abs(bot_vec.get_val(i))))
                cnter++
        }

        if (cnter == 3)
            return true;
        else
            return false;

    }


    enum Obj_cond does_it_belong(const Triangle& trian)
    {
        int cnter = 0;

        for (int i = 0; i < 3; ++i)
        {
            if (does_it_belong(trian[i]))
               cnter++;
        }

        if (cnter == 3)
            return BELNG;

        else if (cnter == 1 || cnter == 2)
            return PARTLY_BELNG;

        else if (cnter == 0)
            return DSNT_BELNG;
    }

    Vec& get_bot()
    {
        return bot_vec;
    }

    Vec& get_top()
    {
        return top_vec;
    }

    Vec& get_diag()
    {
        return Vec(top_vec - bot_vec);
    }
};

#endif //TRIANGLES_UPD_BOUNDING_REGION_H
