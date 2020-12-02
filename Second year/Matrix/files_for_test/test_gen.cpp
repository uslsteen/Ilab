#include "Matrix.hpp"


using namespace AdamR;

#define OUT std::cout

int main()
{
    uint size_of_mtr = 0;
    double real_det = 0;
    int swp_cnter = 1;
    size_t num_of_str = 0;

    OUT << "Input size of you matrix\n";
    std::cin >> size_of_mtr;

    OUT << "Input expected det of your matrix\n";
    std::cin >> real_det;

    double copy_det = real_det;

    Matrix<double> matr{size_of_mtr, size_of_mtr};
    matr = Matrix<double>::U_matr(size_of_mtr, 1);
    matr[0][0] *= real_det;


    OUT << matr;

    srand(clock());

    for (size_t i = 0; i < size_of_mtr; ++i)
    {
        int j = rand() % (size_of_mtr - 1);
        matr.swap_rows(i, j);
        swp_cnter = -swp_cnter;
    }

    copy_det *= swp_cnter;

    for (size_t i = 0; i < size_of_mtr/2; ++i)
    {
        num_of_str = (rand() % (size_of_mtr - 1)) + 1;
        double value = rand() % 10 + 1;

        matr.mul_rows_to_sclr(num_of_str, value);
        copy_det *= value;
    }

    double value = (rand() % 3) + 1;
    value = 1/value;
    std::cout << "value = " << value << std::endl;


    num_of_str = (rand() % (size_of_mtr - 1)) + 1;
    matr.mul_rows_to_sclr(num_of_str, value);
    copy_det *= value;


    matr.transposition();
    std::cout << "Calculated matr determiannt = " << matr.determ() << std::endl;
    std::cout << matr << std::endl;
    std::cout << "Start det = " << real_det << std::endl;
    std::cout << "Copy det = " << copy_det << std::endl;


    return 0;
}
