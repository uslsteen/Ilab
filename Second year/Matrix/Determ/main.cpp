#include "Matrix.hpp"

using namespace Linear_space;

#define OUT std::cout

int main()
{
    uint size_of_mtr = 0;
    std::vector<double> buffer;

    std::cin >> size_of_mtr;
    buffer.resize(size_of_mtr*size_of_mtr);

    for (size_t i = 0; i < size_of_mtr*size_of_mtr; ++i)
        std::cin >> buffer[i];

    Matrix<double> mtr{size_of_mtr, size_of_mtr, buffer};

    OUT << mtr;
    double det = mtr.determ();
    std::cout << "Matrix det: " << det << std::endl;


    return 0;
}
