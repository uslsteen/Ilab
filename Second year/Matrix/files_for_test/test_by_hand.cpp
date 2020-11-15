#include "Matrix.h"

using namespace AdamR;

#define OUT std::cout

int main()
{
    std::cout << "Add testing with matrix\n";

    Matrix<int> mtr1 = {2, 2, 1}, mtr2 = {2, 2, 2}, mtr3{};
    std::cout << mtr1 << "+\n" << mtr2 << "=? " << std::endl;

    mtr3 = mtr1 + mtr2;


    std::cout << "Mul testing №1 with matrix\n";

    std::vector<int> buffer4 = {1, 1, 2, 2, 3, 5, 6, 7}, buffer5 = {2, 2, 3, 5, 6, 7, 1, 1};
    Matrix<int> mtr4 = {4, 2, buffer4}, mtr5 = {2, 4, buffer5}, mtr6_1{}, mtr6_2{};
    std::cout << mtr4 << "*\n" << mtr5 << "=? " << std::endl;

    mtr6_1 = mtr4 * mtr5;

    std::cout << mtr6_1 << std::endl;

    std::cout << "And also\n" << mtr5 << "*\n" << mtr4 << "=? " << std::endl;

    mtr6_2 = mtr5 * mtr4;
    std::cout << mtr6_2 << std::endl;

    std::cout << "Mul testing №2 with matrix\n";

    std::vector<int> buffer7 = {27, 97, 83, 24, 17, 61, 39, 21, 85, 58, 6, 92}, buffer8 = {1, 3, 4, 6, 21, 30, 34, 39, 44, 50, 53, 59, 65, 79, 84, 87, 88, 89, 92, 95};
    Matrix<int> mtr7 = {3, 4, buffer7}, mtr8{4, 5, buffer8}, mtr9{};

    std::cout << mtr7 << " * \n" << mtr8 << "= " << std::endl;
    mtr9 = mtr7 * mtr8;
    std::cout << mtr9 << std::endl;

    std::cout << "Testing mul with scalar\n";

    mtr3 *= 6;
    std::cout << mtr3 << std::endl;

    mtr3 /= 4;
    std::cout << mtr3 << std::endl;

    std::vector<int> buffer10 = {1, 2, 5, 55, 89, 2, 1, 555, 5}, buffer0 = {111, 2, 3, 4};
    Matrix<int> mtr10 = {3, 3, buffer10}, mtr0 = {2, 2, buffer0};
    std::cout << mtr10 << std::endl;

    std::cout << "Testing determinant\n";


    std::cout << "det(mtr0) = " << mtr0.detemrinant() << std::endl;
    std::cout << "det(mtr1) = " << mtr1.detemrinant() << std::endl;
    std::cout << "det(mtr2) = " << mtr2.detemrinant() << std::endl;
    std::cout << "det(mtr3) = " << mtr3.detemrinant() << std::endl;
    std::cout << "det(mtr6_1) = " << mtr6_1.detemrinant() << std::endl;
    std::cout << "det(mtr6_2) = " << mtr6_2.detemrinant() << std::endl;
    std::cout << "det(mtr10) = " << mtr10.detemrinant() << std::endl;

    return 0;

}
