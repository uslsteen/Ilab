//
// Created by anon on 10.11.2020.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>



namespace AdamR
{
    template <typename Data>
    class Matrix final
    {
        private:

            //! Num of rows and columns of my matrix
            int rows, clmns;

            //! Perfomance of my matrix
            Data** matrix;

            //! using for special data type of my matrix
            using DataIt = typename std::vector<Data>::iterator;

            const int EPSILON = 1e-6;

        public:

            Matrix() : rows(0),
                       clmns(0),
                       matrix(nullptr)
            {
            }

            Matrix(int rows_, int clmns_) : rows(rows_),
                                              clmns(clmns_)
            {
                assert(rows_*clmns_ != 0);

                matrix = new Data* [rows];
                for (size_t i = 0; i < rows; ++i)
                {
                    matrix[i] = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = 0;
                }
            }
            //! Constructors for class Matrix

            //! Constructor of matrix class of zeros

            //! Constructor of matrix class of value
            Matrix(uint rows_, uint clmns_, Data val = Data{}) : rows(rows_),
                                                                 clmns(clmns_)
            {
                if (rows * clmns == 0)
                    return;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    matrix[i] = new Data[clmns];

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = val;
                }

            }

            //! Constructor class matrix of vector
            Matrix(uint rows_, uint clmns_, const DataIt& beg, const DataIt& end) : rows(rows_),
                                                                                    clmns(clmns_)
            {
                assert(rows_ * clmns_ != 0);

                DataIt current = beg;
                int num_of_elem = rows_*clmns_, cnter = 0;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    if (cnter == num_of_elem - 1)
                        return;

                    matrix[i] = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                    {
                        matrix[i][j] = *current;
                        ++current;
                    }
                }
            }

            static Matrix eye(uint num)
            {
                Matrix matr(num, num);

                for (int i = 0; i < num; ++i)
                {
                    for (int j = 0; j < num; ++j)
                    {
                        if (i = j)
                            matr.matrix[i][j] = 1;
                    }
                }
                return matr;
            }

            //! Copy constructor for class Matrix
            Matrix(const Matrix<Data>& rhs) : rows(rhs.rows),
                                              clmns(rhs.clmns),
                                              matrix(rhs.matrix)
            {
                // ??????????????????????????????????
            }


            ~Matrix()
            {
                for (size_t i = 0; i < rows; ++i)
                    delete[] matrix[i];

                delete[] matrix;

                matrix = nullptr;
            }

            //Getters of class matrix

            int nrows()
            {
                return rows;
            }

            int nclmns()
            {
                return clmns;
            }


            //! Reloading of operators for class matrix

            Matrix<Data>& operator =(const Matrix<Data>& rhs)
            {
                if (rows != rhs.rows || clmns != rhs.clmns)
                    Resize(rhs.rows, rhs.clmns);

                rows = rhs.rows;
                clmns = rhs.clmns;

                for (size_t i = 0; i < rows; ++i)
                {
                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = rhs.matrix[i][j];
                }

                return (*this);
            }

            Matrix<Data> operator -() const
            {
                Matrix<Data> res_mtr{(*this)};

                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < clmns; ++j)
                        res_mtr.matrix[i][j] *= -1;
                }

                return res_mtr;
            }


            Matrix<Data>& operator +=(const Matrix<Data>& mtr)
            {
                assert((rows == mtr.rows) && (clmns == mtr.clmns));

                rows = mtr.rows;
                clmns = mtr.clmns;

                for (size_t i = 0; i < rows; ++i)
                {
                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] += mtr.matrix[i][j];
                }

                return (*this);
            }

            Matrix<Data>& operator -=(const Matrix<Data>& mtr)
            {
                assert((rows == mtr.rows) && (clmns == mtr.clmns));

                rows = mtr.rows;
                clmns = mtr.clmns;

                for (size_t i = 0; i < rows; ++i)
                {
                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] -= mtr.matrix[i][j];
                }

                return (*this);
            }

            Matrix<Data>& operator *=(const Matrix<Data>& mtr)
            {
                assert(clmns == mtr.clmns);

                Matrix tmp_mtr{rows, mtr.clmns, 0};

                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < mtr.clmns; ++j)
                    {
                        for (int k = 0; k < mtr.clmns; ++k)
                            tmp_mtr[i][j] += matrix[i][k]*mtr[k][j];
                    }
                }

                *this = tmp_mtr;

                return (*this);
            }

            Matrix<Data>& operator *=(Data value)
            {
                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < clmns; ++j)
                        matrix[i][j] *= value;
                }

                return (*this);
            }

            Matrix<Data>& operator /=(Data value)
            {
                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < clmns; ++j)
                        matrix[i][j] /= value;
                }

                return (*this);
            }


            bool operator ==(const Matrix<Data>& mtr)
            {
                if (rows != mtr.rows && clmns != mtr.clmns)
                    return false;

                for (size_t i = 0; i < rows; ++i)
                {
                    for (size_t j = 0; j < clmns; ++j)
                    {
                        if (std::abs(mtr.matrix[i][j] - matrix[i][j]) > EPSILON)
                            return false;
                    }
                }

                return true;
            }


            // Meyers rules of [][];
            //For writing const ???
            Data* operator [](int i) const
            {
                return matrix[i];
            }


            bool operator !=(const Matrix<Data>& mtr)
            {
                return !(operator==(mtr));
            }


    private:
            //! Function for resing matrix
            //! \param mtr
            void Resize(uint rows_, uint clmns_)
            {
                assert(rows_ * clmns_ != 0);

                for (size_t i = 0; i < clmns; ++i)
                    delete[] matrix[i];

                delete[] matrix;

                matrix = new Data* [rows_];

                for (size_t i = 0; i < rows_; ++i)
                    matrix[i] = new Data[clmns_];
            }



    public:

        /*
            //! Function for trannsposing matrix
            void transposition()
            {
                Resize(*this);


            }
            */


            void dump(std::ostream& os) const
            {
                std::cout << std::endl;

                for (size_t i = 0; i < rows; ++i)
                {
                    os << "|| ";

                    for (size_t j = 0; j < clmns; ++j)
                        os << matrix[i][j] << " ";

                    os << "||" << std::endl;
                }

                std::cout << std::endl;
            }



    };

    template <typename Data>
    Matrix<Data> operator +(const Matrix<Data>& lhs, const Matrix<Data> rhs)
    {

    }

    template <typename Data>
    Matrix<Data> operator -(const Matrix<Data>& lhs, const Matrix<Data> rhs)
    {

    }

    template <typename Data>
    Matrix<Data> operator *(const Matrix<Data>& lhs, const Matrix<Data>& rhs)
    {

    }


}




#endif //MATRIX_MATRIX_H
