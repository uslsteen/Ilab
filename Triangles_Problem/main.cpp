#include <iostream>
#include "Intersect_algo.h"
#include <vector>
#include <fstream>
#include <string>

void Input_trian_coord()
{
    double a1 = NAN, a2 = NAN, a3 = NAN, b1 = NAN, b2 = NAN, b3 = NAN, c1 = NAN, c2 = NAN, c3 = NAN;

    //! Input coordinate of points
    //! Point №1
    std::cin >> a1 >> b1 >> c1;
    //! Point №2
    std::cin >> a2 >> b2 >> c2;
    //! Point №3
    std::cin >> a3 >> b3 >> c3;
}



int main()
{
    Vec vec1(1, 0, 0), vec2(0, 1, 0), vec3(0, 0, 1), vec4(2, 0, 0.5), vec5(0, 2, 0.5), vec6(0, 0, 0.5);

    Triangle trian1(vec1, vec2, vec3), trian2(vec4, vec5, vec6);

    bool res = trian1.Intersect_algo(trian1, trian2);

    if (res)
        printf("Intersect!\n");

    else
        printf("Doesnt intersect!\n");

    return 0;
}
