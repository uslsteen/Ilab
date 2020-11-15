//
// Created by anon on 10.11.2020.
//
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include <fstream>
#include <ctime>


namespace AdamR
{
    template <typename Data>
    class Matrix final
    {
        private:

            //! Num of rows and columns of my matrix
            uint rows, clmns;

            //! Perfomance of my matrix
            Data** matrix;

            //! using for special data type of my matrix
            using DataIt = typename std::vector<Data>::iterator;

            //! Constant for copmaring
            const int EPSILON = 1e-6;

        public:

            //! Constructors for class Matrix


            //! Empy consturctor for matrix
            Matrix() : rows(0),
                       clmns(0),
                       matrix(nullptr)
            {
            }

            //! Constructor for matrix of zeros
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


            //! Constructor for matrix class of value
            Matrix(uint rows_, uint clmns_, Data val = Data{}) : rows(rows_),
                                                                 clmns(clmns_)
            {
                assert(rows_ * clmns_ != 0);
                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    matrix[i] = new Data[clmns];

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = val;
                }

            }

            //! Constructor for matrix class from buffer
            Matrix(uint rows_, uint clmns_,const std::vector<Data>& buffer) : rows(rows_),
                                                                         clmns(clmns_)
            {
                assert(rows_ * clmns_ != 0);

                size_t num_of_elems = buffer.size(), cnter = 0;
                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    if (cnter == num_of_elems - 1)
                        return;

                    matrix[i] = new Data[clmns];

                    for (size_t j = 0; j < clmns; ++j)
                    {
                        matrix[i][j] = buffer[cnter];
                        ++cnter;
                    }
                }
            }

            //! Constructor class matrix of two iterators to the vector
            Matrix(uint rows_, uint clmns_, const DataIt& beg, const DataIt& end) : rows(rows_),
                                                                                    clmns(clmns_)
            {
                assert(rows_ * clmns_ != 0);

                DataIt current = beg;
                int num_of_elems = rows_*clmns_, cnter = 0;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    if (cnter == num_of_elems - 1)
                        return;

                    matrix[i] = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                    {
                        matrix[i][j] = *current;
                        ++current;
                        ++cnter;
                    }
                }
            }


            //! Function returns a matrix of the upper triangular type
            static Matrix U_matr(uint num, Data elem)
            {
                Matrix matr{num, num};

                for (int i = 0; i < num; ++i)
                    for (int j = 0; j < num; ++j)

                        if (j >= i)
                            matr.matrix[i][j] = elem;


                return matr;
            }


            //! The function returns the identity matrix
            static Matrix eye(uint num)
            {
                Matrix matr(num, num);

                for (int i = 0; i < num; ++i)

                    for (int j = 0; j < num; ++j)

                        if (i == j)
                            matr.matrix[i][j] = 1;


                return matr;
            }

            //! Copy constructor for class Matrix
            Matrix(const Matrix<Data>& rhs) : rows(rhs.rows),
                                              clmns(rhs.clmns)
            {
                matrix = new Data* [rhs.rows];

                for (int i = 0; i < rhs.rows; ++i)
                {
                    matrix[i] = new Data [rhs.clmns];

                    for (int j = 0; j < rhs.clmns; ++j)
                        matrix[i][j] = rhs.matrix[i][j];
                }
            }

            //! Destructor for matrix class
            ~Matrix()
            {
                for (size_t i = 0; i < rows; ++i)
                    delete[] matrix[i];

                delete[] matrix;
                matrix = nullptr;
            }

            //Getters of class matrix
            uint nrows()
            {
                return rows;
            }

            uint nclmns()
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

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = rhs.matrix[i][j];


                return (*this);
            }

            Matrix<Data> operator -() const
            {
                Matrix<Data> res_mtr{(*this)};

                for (int i = 0; i < rows; ++i)

                    for (int j = 0; j < clmns; ++j)
                        res_mtr.matrix[i][j] *= -1;

                return res_mtr;
            }


            Matrix<Data>& operator +=(const Matrix<Data>& mtr)
            {
                assert((rows == mtr.rows) && (clmns == mtr.clmns));

                rows = mtr.rows;
                clmns = mtr.clmns;

                for (size_t i = 0; i < rows; ++i)

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] += mtr.matrix[i][j];

                return (*this);
            }

            Matrix<Data>& operator -=(const Matrix<Data>& mtr)
            {
                assert((rows == mtr.rows) && (clmns == mtr.clmns));

                rows = mtr.rows;
                clmns = mtr.clmns;

                for (size_t i = 0; i < rows; ++i)

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] -= mtr.matrix[i][j];

                return (*this);
            }

            Matrix<Data>& operator *=(const Matrix<Data>& mtr)
            {
                assert(clmns == mtr.rows);

                Matrix tmp_mtr{rows, mtr.clmns, 0};

                for (int i = 0; i < rows; ++i)

                    for (int j = 0; j < mtr.clmns; ++j)

                        for (int k = 0; k < mtr.rows; ++k)
                            tmp_mtr[i][j] += matrix[i][k] * mtr.matrix[k][j];

                *this = tmp_mtr;
                return (*this);
            }

            Matrix<Data>& operator *=(Data value)
            {
                assert((((*this).rows) * ((*this).clmns)) != 0);

                for (int i = 0; i < rows; ++i)

                    for (int j = 0; j < clmns; ++j)
                        matrix[i][j] *= value;

                return (*this);
            }

            Matrix<Data>& operator /=(Data value)
            {
                for (int i = 0; i < rows; ++i)

                    for (int j = 0; j < clmns; ++j)
                        matrix[i][j] /= value;

                return (*this);
            }


            bool operator ==(const Matrix<Data>& mtr)
            {
                if (rows != mtr.rows && clmns != mtr.clmns)
                    return false;

                for (size_t i = 0; i < rows; ++i)
                    for (size_t j = 0; j < clmns; ++j)

                        if (std::abs(mtr.matrix[i][j] - matrix[i][j]) > EPSILON)
                            return false;

                return true;
            }


            Data* operator [](int i) const
            {
                return matrix[i];
            }

/*
 *
 * Read Scott Mayers book (55 effective...)
            bool operator !=(const Matrix<Data>& mtr)
            {
                return !(operator==(mtr));
            }
*/


    private:
            //! Function for resing matrix
            void Resize(uint rows_, uint clmns_)
            {
                assert(rows_ * clmns_ != 0);

                for (size_t i = 0; i < rows; ++i)
                    delete[] matrix[i];

                delete[] matrix;

                matrix = new Data* [rows_];

                for (size_t i = 0; i < rows_; ++i)
                    matrix[i] = new Data[clmns_];
            }



    public:

            //! Function for mul diagonal elements
            Data Diag_mul(const Matrix& mtr)
            {
                assert(mtr.rows == mtr.clmns);
                assert(mtr.matrix);
                Data res = 1;

                for (int i = 0; i < mtr.rows; ++i)
                    res *= static_cast<double>(mtr.matrix[i][i]);

                return res;
            }

            //! Function - realisation Gauss algorithm
            void Gauss_algo(Matrix& mtr, int* swap_counter)
            {
                bool need_swap = false;

                for (size_t i = 0; i < clmns; ++i)
                {
                    size_t max_ind = i;

                    //! Finding row with the biggest first elem
                    for (size_t j = i + 1; j < rows; ++j)
                    {
                        if (abs(mtr.matrix[j][i]) > abs(mtr.matrix[max_ind][i]))
                        {
                            max_ind = j;
                            need_swap = true;
                        }
                    }

                    //! Swap the lines [i] and [max_ind]
                    if (need_swap)
                    {
                        std::swap(mtr.matrix[i], mtr.matrix[max_ind]);
                        *swap_counter = -*swap_counter;
                    }


                    for (size_t j = i + 1; j < rows; ++j)
                    {
                        double q = ( static_cast<double>(mtr.matrix[j][i]) ) / ( static_cast<double>(mtr.matrix[i][i]) );

                        for (size_t k = 0; k < mtr.clmns; k++)
                            mtr[j][k] -= q * static_cast<double>(mtr[i][k]);
                    }
                }
            }

            //! Function for calculating determinant
            Data detemrinant()
            {
                assert((*this).clmns == (*this).rows);
                assert((*this).matrix);

                int swap_counter = 1;
                uint rows = (*this).rows, clmns = (*this).clmns;
                Matrix<Data> tmp_mtr{(*this)};

                Gauss_algo(tmp_mtr, &swap_counter);

                Data res = swap_counter*Diag_mul(tmp_mtr);

                return res;
            }


            //! Function for trannsposing matrix
            void transposition()
            {
                Matrix<Data> tmp_mtr{(*this)};
                Resize(clmns, rows);

                for (int i = 0; i < clmns; ++i)

                    for(int j = 0; j < rows; ++j)
                        matrix[i][j] = tmp_mtr[j][i];
            }

            //! Dump for matrix
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
                std::cout << "Num of rows = " << rows;
                std::cout << "Num of clmns = " << clmns;

                std::cout << std::endl;
            }

            //! Functions for working with matrix rows

            //! Function for swapping matrix rows
            void swap_rows(uint i, uint j)
            {
                assert(i >= 0 && j >= 0);
                assert(i < (*this).rows && j < (*this).rows);

                std::swap((*this).matrix[i], (*this).matrix[j]);
            }

            //! Function for add matrix rows
            void sum_rows(uint i, uint j)
            {
                assert(i >= 0 && j >= 0);
                assert(i < (*this).rows && j < (*this).rows);

                for (int k = 0; k < (*this).clmns; ++k)
                    (*this).matrix[k][i] += (*this).matrix[k][j];
            }

            //! Function for mul matrix rows
            void mul_rows_to_sclr(uint i, Data value)
            {
                assert(i >= 0);
                assert(i < (*this).rows);

                for (int k = 0; k < (*this).clmns; ++k)
                    (*this).matrix[k][i] *= static_cast<double>(value);
            }
    };

    //! Also binary reloaded operators for working with matrix

    template <typename Data>
    std::ostream& operator <<(std::ostream &os, Matrix<Data>& matr)
    {
        for (size_t i = 0; i < matr.nrows(); ++i)
        {
           // os << "|| ";

            for (size_t j = 0; j < matr.nclmns(); ++j)
                os << matr[i][j] << " ";

            os << std::endl;
        }

        return os;
    }

    template <typename Data>
    Matrix<Data> operator +(const Matrix<Data>& lhs, const Matrix<Data>& rhs)
    {
        Matrix<Data> res{lhs};

        res += rhs;
        return res;
    }

    template <typename Data>
    Matrix<Data> operator -(const Matrix<Data>& lhs, const Matrix<Data>& rhs)
    {
        Matrix<Data> res{lhs};

        res -= rhs;
        return res;
    }

    template <typename Data>
    Matrix<Data> operator *(const Matrix<Data>& lhs, const Matrix<Data>& rhs)
    {
        Matrix<Data> res{lhs};

        res *= rhs;
        return res;
    }

}

#endif //MATRIX_MATRIX_H
