//
// Created by anon on 14.10.2020.
//

#ifndef TRIANGLES_VEC_H
#define TRIANGLES_VEC_H

#include <iostream>
#include <cmath>

class Vec
{
private:
    double x, y, z;

public:

    //! Constructor of class vector
    Vec(double x_, double y_, double z_): x(x_),
                                          y(y_),
                                          z(z_)
    {}

    //! Copy constructor of class vector

    Vec(Vec& vec): x(vec.x),
                   y(vec.y),
                   z(vec.z)
    {}

    //!Operators reloading for class vector

    //! Operator binary plus for vector
    Vec& operator +(const Vec& vec)
    {
        return Vec(x + vec.x, y + vec.y, z + vec.z);
    }

    //! Operator binary minus for vector
    Vec& operator -(const Vec& vec)
    {
        return Vec(x - vec.x, y - vec.y, z - vec.z);
    }

    //! Operator mul to scalar value
    Vec& operator *(const double value)
    {
        return Vec(value*x, value*y, value*z);
    }

    //! Operator div to scalar value
    Vec& operator /(const double value)
    {
        return Vec(x/value, y/value, z/value)
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
    Vec& operator *=(const Vec& vec)
    {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;

        return (*this);
    }

    //! Operator div - equal for vector
    Vec& operator /=(const Vec& vec)
    {
        x /= vec.x;
        y /= vec.y;
        z /= vec.z;

        return (*this);
    }

    //! Operator unary minus for vector
    Vec& operator -()
    {
        return Vec(-x, -y, -z);
    }

    //! Operator of equallity for vector
    Vec& operator =(Vec& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;

        return (*this)
    }

    //! Operator of scalar mul of the vector
    Vec& operator &(Vec& vec)
    {
        return (vec.x * x, vec.y * y, vec.z * z);
    }


    //! Operator of cross mul of the vector
    Vec& operator %(Vec& vec)
    {
        return Vec(y * vec.z - vec.y * z, x * vec.z - vec.x * z, x * vec.y - vec.x * y);
    }


    //! There is u can find public methods of class vector for working with vector.

    //! Function for getting norma of the vector
    double norma()
    {
        return sqrt(x^2 + y^2 + z^2);
    }


    // Function for normalizing vector
    Vec& normalize()
    {
        double norma = (*this).norma();
        normalized_vec = {0, 0, 0};

        if (norma == 0)
            return normalized_vec;
        else
        {
            normalized_vec = (*this) / norma;
            return normalized_vec;
        }
    }

    std::ostream & operator <<(std::ostream & os, const Vec& vec)
    {
        os << "(" << vec.x << ", " <<  vec.x << ", " << vec.x << ")" << std::endl;
        return os;
    }

};

#endif //TRIANGLES_VEC_H
