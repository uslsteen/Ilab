
#ifndef TRIANGLES_VEC_HPP
#define TRIANGLES_VEC_HPP

#include <iostream>
#include <cmath>

class Trian;

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

  /* Vector constructor method */
  Vec(double a, double b, double c) : x_(a),
                                      y_(b),
                                      z_(c)
  {}

  /* Vector constructor method with similar coordinates */
  explicit Vec(double a = 0) : x_(a),
                               y_(a),
                               z_(a)
  {}

  /* Vector copy constructor */
  Vec(const Vec& V) : x_(V.x_),
                      y_(V.y_),
                      z_(V.z_)
  {}


  //! Reloading operators for vector

  /**
   * @brief Vector add vector (reload +) function
   * @param[in] V - link to vector.
   * @return result vector;
   */
  Vec operator +(const Vec& V) const
  {
    return Vec(x_ + V.x_, y_ + V.y_, z_ + V.z_);
  } /* End of 'operator+' function */

  /**
   * @brief Vector subtraction vector (reload -) function
   * @param - link to vector:
   * @return result vector;
   */
  Vec operator -(const Vec& V) const
  {
    return Vec(x_ - V.x_, y_ - V.y_, z_ - V.z_);
  } /* End of 'operator-' function */

  /**
   * @brief Vector negate (reload -) function
   * @return result vector;
   */
  Vec operator -() const
  {
    return Vec(-x_, -y_, -z_);
  } /* End of 'operator-' function */

  /**
   * @brief Reload assignment operator.
   * @param[in] V - link to vector
   * @return link to vector. (for multiple '=')
   */
  Vec & operator =(const Vec& V)
  {
    x_ = V.x_;
    y_ = V.y_;
    z_ = V.z_;

    return *this;
  } /* End of 'operator=' function */

  /**
   * @brief Vector add and assign vector (reload +=)
   * @param V - link to vector
   * @return link to result vector.
   */
  Vec& operator +=(const Vec& V)
  {
    x_ += V.x_;
    y_ += V.y_;
    z_ += V.z_;
    return *this;
  } /* End of 'operator+=' function */

  /**
   * @brief Get x coordinate function.
   * @return x - coordinate
   */
  double getX() const
  {
    return x_;
  }

  /**
   * @brief Get y coordinate function.
   * @return y - coordinate
   */
  double getY() const
  {
    return y_;
  }

  /**
   * @brief Get z coordinate function.
   * @return z - coordinate
   */
  double getZ() const
  {
    return z_;
  }

  /**
   * @brief Vector substract and assign function (reload -=)
   * @param V - link to vector
   * @return  link to vector result.
   */
  Vec & operator -=(const Vec& V)
  {
    x_ -= V.x_;
    y_ -= V.y_;
    z_ -= V.z_;

    return *this;
  } /* End of 'operator -=' function */

  /**
   * @brief Calculate the length of a vector function
   * @return length of a vector
   */
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

  friend bool Is2DIntersect( const Trian &trian1, const Vec &Norm, const Trian &trian2 );

  double operator []( size_t index ) const
  {
    return *(&x_ + Clamp(index, (size_t)0, (size_t)2));
  }

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

#endif
