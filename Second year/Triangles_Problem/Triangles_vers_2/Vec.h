// Created by anon on 15.10.2020.
//


#ifndef TRIANGLES_VEC_H
#define TRIANGLES_VEC_H

#include <iostream>
#include <cmath>


class Triangle;

class Vec
{
private:
    double x, y, z;

    const double epsilon = 0.000001;

public:


    //! Constructor of class vector
    Vec(double x_, double y_, double z_): x(x_),
                                          y(y_),
                                          z(z_)
    {}

    //! Copy constructor of class vector
    Vec(const Vec& vec) : x(vec.x),
                          y(vec.y),
                          z(vec.z)
    {}

    Vec() : x(0),
            y(0),
            z(0)
    {}



    //! Getters of class vector

    double Get_x() const
    {
        return x;
    }

    double Get_y() const
    {
        return y;
    }

    double Get_z() const
    {
        return z;
    }

public:

    //!Operators reloading for class vector

    //! Operator mul to scalar value
    Vec operator *(const double value)
    {
        return Vec(value*x, value*y, value*z);
    }

    //! Operator div to scalar value
    Vec operator /(const double value)
    {
        return Vec(x/value, y/value, z/value);
    }

    //! Operator plus - equal for vector
    Vec& operator +=(const Vec& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return (*this);
    }

    //! Operator minus - equal for vector
    Vec& operator -=(const Vec& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return (*this);
    }

    //! Operator mul - equal for vector
    Vec& operator *=(double value)
    {
        x *= value;
        y *= value;
        z *= value;

        return (*this);
    }

    //! Operator div - equal for vector


    Vec & operator /=(double value)
    {
        x /= value;
        y /= value;
        z /= value;

        return (*this);
    }

    //! Operator unary minus for vector
    Vec operator -()
    {
        return Vec(-x, -y, -z);
    }

    //! Operator of equallity for vector


    Vec& operator =(const Vec& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;

        return (*this);
    }



    bool operator ==(const Vec& vec)
    {
        if ((std::fabs(vec.x - x) < epsilon) && (std::fabs(vec.y - y) < epsilon) && (std::fabs(vec.z - z) < epsilon))
            return true;
        else
            return false;
    }


    //! There is u can find public methods of class vector for working with vector.

    Vec perp_2D()
    {
        return Vec(y, -x, 0);
    }


    double& get_val(int ind)
    {
        return *(&x + ind % 3);
    }


    double operator []( int index ) const
    {
        return *(&x + index % 3);
    }


    friend std::istream & operator >>( std::istream &ist, Vec &vec );

private:

    double & operator []( int index )
    {
        return *(&x + index % 3);
    }


public:

//! Function for getting norma of the vector
    double norma()
    {
        return std::sqrt(x*x + y*y + z*z);
    }


    //! Function for normalizing vector
    Vec& normalize()
    {
        double norma = (*this).norma();

        if (norma == 0)
            return *this;
        else
            (*this /= norma);

        return (*this);
    }

    friend bool Intersect_2D(const Triangle &trian1, const Triangle &trian2, const Vec& normal);


};




//! Reloading binary opearators as: binary plus, minus, scalar mul and cross mul and output to ostream

//! Operator for output vector to ostream
std::ostream& operator <<(std::ostream &os, const Vec& vec)
{
    os << "(" << vec.Get_x() << ", " << vec.Get_y() << ", " << vec.Get_z() << ")" << std::endl;

    return os;
}


//! Operator binary plus for vector
//! \param vec_lhs
//! \param vec_rhs
//! \return res of sum
Vec operator +(const Vec& vec_lhs, const Vec& vec_rhs)
{
    Vec res(vec_lhs);

    res += vec_rhs;
    return res;
}

//! Operator bintary minus for vector
//! \param vec_lhs
//! \param vec_rhs
//! \return res of sub

Vec operator -(const Vec& vec_lhs, const Vec& vec_rhs)
{
    return Vec(vec_lhs.Get_x() - vec_rhs.Get_x(), vec_lhs.Get_y() - vec_rhs.Get_y(), vec_lhs.Get_z() - vec_rhs.Get_z());
}

//!
double operator &(const Vec& lhs, const Vec& rhs)
{
    return lhs.Get_x()*rhs.Get_x() + lhs.Get_y()*rhs.Get_y() + lhs.Get_z()*rhs.Get_z();
}

//!
Vec operator %(const Vec& lhs, const Vec& rhs)
{
    double x1 = lhs.Get_x(), y1 = lhs.Get_y(), z1 = lhs.Get_z(), x2 = rhs.Get_x(), y2 = rhs.Get_y(), z2 = rhs.Get_z();

    return Vec(y1*z2 - y2*z1, x1*z2 - x2*z1, x1*y2 - x2*y1);
}


#endif //TRIANGLES_VEC_H

