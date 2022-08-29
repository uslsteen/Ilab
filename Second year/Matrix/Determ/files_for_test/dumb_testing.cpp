#include "Matrix.h"

using namespace AdamR;

#define OUT std::cout

int main()
{
    std::vector<int> buffer = {1, 0, 0, 0, 1, 0, 0, 0, 4};
    Matrix<int> mtr4 = {3, 3, buffer.begin(), buffer.end()};

    mtr4.dump(OUT);
    int res = mtr4.detemrinant();

    printf("%d\n", res);

    Matrix<int> mtr2 = {2, 2, 1};

    mtr2.dump(OUT);

    Matrix<int> mtr5 = Matrix<int>::eye(3);

    mtr5.dump(OUT);

    mtr2 = mtr4;

    mtr2 *= mtr2;

    mtr2.dump(OUT);

    mtr2.transposition();

    mtr2.dump(OUT);

    Matrix<int> mtr1 = {2,2};
    mtr1.dump(OUT);

    mtr2.dump(OUT);

    buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> buffer1 = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    mtr4 = {3, 3, buffer.begin(), buffer.end()};
    mtr5 = {3, 3, buffer1.begin(), buffer1.end()};

    std::cout << "Add testing:\n";

    Matrix<int> mtr6 = mtr4 + mtr5;

    mtr6.dump(OUT);

    std::vector<int> buffer3 = {1, 1, 2, 3, 4, 5, 6, 9, 100};

    Matrix<int> mtr7 = {3, 3, buffer3};

    mtr7.dump(OUT);



    //mtr3.dump(std::cout);
}
