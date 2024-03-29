#include "Matrix.h"

using namespace AdamR;

#define OUT std::cout

void Test_for_eq(uint rows1, uint clmns1, uint rows2, uint clmns2, size_t num_of_test)
{
    OUT << "Start of the " << num_of_test <<" test" << std::endl;
    std::vector<double> buffer1, buffer2;
    buffer1.resize(rows1*clmns1), buffer2.resize(rows2*clmns2);

    for (size_t i = 0; i < rows1*clmns1; ++i)
        buffer1[i] = i/4;

    for (size_t i = 0; i < rows2*clmns2; ++i)
        buffer2[i] = (i*i)/3;


    Matrix<double> mtr1{rows1, clmns1, buffer1}, mtr2{rows2, clmns2, buffer2};

    OUT << "mtr1:\n";
    mtr1.dump(OUT);

    OUT << "mtr2:\n";
    mtr2.dump(OUT);

    OUT << "Lets do mtr1 = mtr2\n\n";
    mtr1 = mtr2;

    OUT << "mtr1:\n";
    mtr1.dump(OUT);

    OUT << "mtr2:\n";
    mtr2.dump(OUT);

    OUT << "End ot the " << num_of_test  <<" test!\n\n";
}

int main()
{
    srand(clock());
    OUT << "Test for memory leaks in operator =\n";
    uint rows1 = 2, clmns1 = 3, rows2 = 3, clmns2 = 2, num_of_tests = 10;
    //Test_by_hand(rows1, clmns1, rows2, clmns2, 1);

    for (size_t i = 1; i != num_of_tests; ++i)
    {
        rows1 = 1 + rand() % 10; clmns1 = 1 + rand() % 10;
        rows2 = 1 + rand() % 10; clmns2 = 1 + rand() % 10;

        Test_for_eq(rows1, clmns1, rows2, clmns2, i);
    }


    return 0;
}
