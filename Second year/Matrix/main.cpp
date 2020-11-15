#include "Matrix.h"

using namespace AdamR;

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

    std::cout << "Matrix det: " << mtr.detemrinant() << std::endl;

    return 0;
}
