
#include <iostream>
#include "Intersect_algo.h"
#include <vector>
#include <fstream>
#include <string>


void Input_triangles(std::vector<Triangle>& buf_of_trians, std::vector<Vec>& buf_of_points, size_t num_of_triangles)
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
            if (Intersect_algo(buf_of_trians[i], buf_of_trians[j]))
            {
                std::cout << "\n" << i << " " << j << std::endl;
            }
        }
    }
}



int main()
{
    size_t num_of_triangles = 0;
    std::vector <Triangle> buf_of_trians;
    std::vector <Vec> buf_of_points;

    std::cin >> num_of_triangles;

    buf_of_trians.resize(num_of_triangles);
    buf_of_points.resize(3);

    Input_triangles(buf_of_trians,buf_of_points, num_of_triangles);

    Intersection_checking(buf_of_trians, num_of_triangles);

    std::cout << "End of working program!\n";
}
