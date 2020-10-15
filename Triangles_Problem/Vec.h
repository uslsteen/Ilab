// Created by anon on 15.10.2020.
//


#ifndef TRIANGLES_VEC_H
#define TRIANGLES_VEC_H

#include <iostream>
#include <cmath>


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
        if ((std::fabs(vec.x - x) < epsilon) && (std::fabs(vec.x - x) < epsilon) && (std::fabs(vec.x - x) < epsilon))
            return true;
        else
            return false;
    }


    //! There is u can find public methods of class vector for working with vector.

    /*
    const double& get_val(int ind)
    {
        return *(&x + ind % 3);
    }
     */

    double operator [](int index) const
    {
        return *(&x + index % 3);
    }


    Vec perp2D()
    {
        return Vec(y, -x, 0);
    }

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


/*

#ifndef TRIANGLES_VERS_2_VEC_H
#define TRIANGLES_VERS_2_VEC_H


#include <iostream>
#include <cmath>


class Plane;
class Line;

template <typename T>
T Clamp( T val, T a, T b )
{
    return val < a ? a : (a > b ? b : val);
}

const double VEC_THRESHOLD = 1e-11;

class Vec
{
private:

    double x_, y_, z_;

    static double threshold;

public:
    //friend class Plane;


    Vec(double x, double y, double z) : x_(x),
                                        y_(y),
                                        z_(z)
    {}


    explicit Vec(double a = 0) : x_(a),
                                 y_(a),
                                 z_(a)
    {}


    Vec(const Vec& V) : x_(V.x_),
                        y_(V.y_),
                        z_(V.z_)
    {}




    Vec operator +(const Vec& V) const
    {
        return Vec(x_ + V.x_, y_ + V.y_, z_ + V.z_);
    }

    Vec operator -(const Vec& V) const
    {
        return Vec(x_ - V.x_, y_ - V.y_, z_ - V.z_);
    }

    Vec operator -() const
    {
        return Vec(-x_, -y_, -z_);
    }

    Vec & operator =(const Vec& V)
    {
        x_ = V.x_;
        y_ = V.y_;
        z_ = V.z_;

        return *this;
    }


    Vec& operator +=(const Vec& V)
    {
        x_ += V.x_;
        y_ += V.y_;
        z_ += V.z_;
        return *this;
    }



    double getX() const
    {
        return x_;
    }





    double getY() const
    {
        return y_;
    }


    double getZ() const
    {
        return z_;
    }


    Vec & operator -=(const Vec& V)
    {
        x_ -= V.x_;
        y_ -= V.y_;
        z_ -= V.z_;

        return *this;
    }

    double operator!( void ) const
    {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    double operator &(const Vec& V) const
    {
        return x_ * V.x_ + y_ * V.y_ + z_ * V.z_;
    }

    Vec operator %( const Vec&V ) const
    {
        return Vec(y_ * V.z_ - z_ * V.y_, z_ * V.x_ - x_ * V.z_, x_ * V.y_ - y_ * V.x_);
    }

    Vec operator *( double number ) const
    {
        return Vec(x_ * number, y_ * number, z_ * number);
    }

    Vec operator *(double number)
    {
        return Vec(number * x_, number* y_, number* z_);
    }


    Vec operator /( double number ) const
    {
        return Vec(x_ / number, y_ / number, z_ / number);
    }

    Vec & operator *=( double number )
    {
        x_ *= number;
        y_ *= number;
        z_ *= number;

        return *this;
    }

    Vec & operator /=( double number )
    {
        x_ /= number;
        y_ /= number;
        z_ /= number;

        return *this;
    }

    Vec Normalizing() const
    {
        double len= !(*this);

        Vec V = *this;

        if (len == 0 || len == 1)
            return V;

        V /= len;

        return V;
    }

    Vec& Normalize()
    {
        double len = !(*this);

        if (len == 0 || len == 1)
            return *this;

        *this /= len;

        return *this;
    }

    double Length2() const
    {
        return *this & *this;
    }

    double Distance(const Vec& V) const
    {
        return !(*this - V);
    }

    friend bool operator ==(const Vec &V1, const Vec &V2)
    {
        return (std::abs(V1.x_ - V2.x_) < threshold &&
                std::abs(V1.y_ - V2.y_) < threshold &&
                std::abs(V1.z_ - V2.z_) < threshold);
    }

    static void SetThreshold(double new_threshold)
    {
        threshold = new_threshold;
    }

    static void SetDefThres()
    {
        threshold = VEC_THRESHOLD;
    }

    static double GetThreshold()
    {
        return threshold;
    }

    Vec Perp2D() const
    {
        return Vec(y_, -x_, 0);
    }

    //friend bool Is2DIntersect( const Trian &trian1, const Vec &Norm, const Trian &trian2 );

    double operator []( size_t index ) const
    {
        return *(&x_ + Clamp(index, (size_t)0, (size_t)2));
    }

    friend bool Intersect_3D(Plane& plane1, Plane& plane2, Vec* points1, Vec* points2, double* dist1);

private:
    double & operator []( size_t index )
    {
        return *(&x_ + Clamp(index, (size_t)0, (size_t)2));
    }


};

double Vec::threshold = VEC_THRESHOLD;

// FOR DEBUG
std::ostream & operator <<( std::ostream &ost, const Vec &vec )
{
    ost << "x = " << vec.getX() << "\n";
    ost << "y = " << vec.getY() << "\n";
    ost << "z = " << vec.getZ() << "\n";

    return ost;
}

#endif //TRIANGLES_VERS_2_VEC_H

*/