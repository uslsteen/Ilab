#include "Matrix.h"

using namespace AdamR;

#define OUT std::cout

int main()
{
    //Matrix<int> mtr1 = {2,2};

    //Matrix<int> mtr2 = {2, 2, 1};
    //Matrix<int> mtr3 = {2, 2, 1};
    //mtr3 *= mtr2;

    std::vector<int> buffer = {1, 1, 1, 2, 2, 2, 3, 3, 3};
    Matrix<int> mtr4 = {3, 3, buffer.begin(), buffer.end()};

    Matrix<int> mtr2 = {2, 2, 1};

    mtr2.dump(OUT);
    mtr4.dump(OUT);

    Matrix<int> mtr5 = Matrix<int>::eye(3);

    mtr5.dump(OUT);

    mtr2 = mtr4;

    mtr2 *= mtr2;



    Matrix<int> mtr1 = {2,2};
    mtr1.dump(OUT);

    mtr2.dump(OUT);

    //mtr3.dump(std::cout);
}
