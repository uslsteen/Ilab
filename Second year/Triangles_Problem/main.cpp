
/*
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
    Vec vec1(0, 1, 0), vec2(1, 0, 0), vec3(0, 0, 1), vec4(0, 2, 0), vec5(2, 0, 0), vec6(0, 0, 0);

    Triangle trian1(vec1, vec2, vec3), trian2(vec4, vec5, vec6);

    bool res = trian1.Intersect_algo(trian1, trian2);

    if (res)
        printf("Intersect!\n");

    else
        printf("Doesnt intersect!\n");

    return 0;
}


*/




#include <iostream>
#include "Intersect_algo.h"
#include <vector>
#include <fstream>
#include <string>

void Input_triangles(std::vector<Triangle>& buf_of_trians, std::vector<Vec> buf_of_points, size_t num_of_triangles)
{
    double x = NAN, y = NAN, z = NAN;

    for (size_t i = 0; i < num_of_triangles; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            std:: cin >> x >> y >> z;
            buf_of_points[j] = Vec(x, y, z);
        }

        buf_of_trians[i] = Triangle(buf_of_points[0], buf_of_points[1], buf_of_points[2]);
    }
}

void Intersection_checking(std::vector<Triangle> buf_of_trians, size_t num_of_triangles)
{
    for (size_t i = 0; i < num_of_triangles; ++i)
    {
        for (size_t j = i + 1; j < num_of_triangles; ++j)
        {
            Intersect_algo(buf_of_trians[i], buf_of_trians[j]);
        }
    }
}


int main()
{
    /*
    Vec vec1(1, 0, 0), vec2(0, 1, 0), vec3(0, 0, 0), vec4(0, 2, 0), vec5(0.5, 0, 0), vec6(0, 0, 0);

    Triangle trian1(vec1, vec2, vec3), trian2(vec4, vec5, vec6);

    bool res = trian1.Intersect_algo(trian1, trian2);

    if (res)
        printf("Intersect!\n");

    else
        printf("Doesnt intersect!\n");

    return 0;
*/

    size_t num_of_triangles = 0;
    std::vector <Triangle> buf_of_trians;
    std::vector <Vec> buf_of_points;

    std::cin >> num_of_triangles;

    buf_of_trians.resize(num_of_triangles);
    buf_of_points.resize(3);

    Input_triangles(buf_of_trians,buf_of_points, num_of_triangles);

    Intersection_checking(buf_of_trians, num_of_triangles);

}