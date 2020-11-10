#include "Matrix.h"

using namespace AdamR;

int main()
{
    //Matrix<int> mtr1 = {2,2};

    Matrix<int> mtr2 = {2, 2, 1};
    Matrix<int> mtr3 = {2, 2, 1};
    mtr3 *= mtr2;

    mtr3.dump(std::cout);
}
