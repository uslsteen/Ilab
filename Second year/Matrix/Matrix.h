//
// Created by anon on 10.11.2020.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <vector>
#include <cassert>



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

        public:

            //! Constructors for class Matrix

            //! Constructor of matrix class of zeros
            Matrix(uint rows_, uint clmns_) : rows(rows_),
                                              clmns(clmns_)
            {
                if (rows * clmns == 0)
                    return;

                matrix = new Data* [rows];
                for (size_t i = 0; i < rows; ++i)
                {
                    matrix = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = 0;
                }
            }

            //! Constructor of matrix class of value
            Matrix(uint rows_, uint clmns_, Data val = Data{}) : rows(rows_),
                                                                 clmns(clmns_)
            {
                if (rows * clmns == 0)
                    return;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    matrix[i] = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                        matrix[i][j] = val;
                }
            }

            //! Constructor class matrix of vector
            Matrix(uint rows_, uint clmns_, Data beg, Data end) : rows(rows_),
                                                                  clmns(clmns_)
            {
                if (rows * clmns == 0)
                    return;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                {
                    if (beg == end)
                        break;

                    matrix = new Data [clmns];

                    for (size_t j = 0; j < clmns; ++j)
                    {
                        matrix[i][j] = beg;
                        ++beg;
                    }
                }
            }

            Matrix eye(uint rows_, uint clmns_)
            {
                Matrix matr(rows_, clmns_);

                for (int i = 0; i < rows_; ++i)
                {
                    for (int j = 0; j < clmns; ++j)
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

            /*
            const Data& operator[](int i)
            {
                return
            }
             */

            void dump(std::ostream& os) const
            {
                for (size_t i = 0; i < rows; ++i)
                {
                    os << "|| ";

                    for (size_t j = 0; j < clmns; ++j)
                        os << matrix[i][j] << " ";

                    os << "||" << std::endl;
                }
            }


            //! Reloading of operators for class matrix

            //! Make it more smart
            Matrix<Data>& operator =(const Matrix<Data>& rhs)
            {
                if (rows != rhs.rows || clmns != rhs.clmns)
                    Resize(rhs);

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

            void Resize(const Matrix& mtr)
            {
                for (size_t i = 0; i < clmns; ++i)
                    delete[] matrix[i];

                delete[] matrix;

                matrix = new Data* [rows];

                for (size_t i = 0; i < rows; ++i)
                    matrix[i] = new Data[clmns];
            }


            // Meyers rules of [][];
            //For writing const ???
            Data* operator [](int i) const
            {
                return matrix[i];
            }

    };
}




#endif //MATRIX_MATRIX_H
