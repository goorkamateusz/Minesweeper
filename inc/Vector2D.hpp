#pragma once
#include <iostream>

/**
 * \brief 2 dimension vector
 * \tparam T - type of number
 */
template< typename T >
class Vector2D_t {
public:
    T x;        //< X coordinate of vectior
    T y;        //< Y coordinate of vectior

public:
    /**
     * \brief Construct a new Vector 2 D object
     * \param xx - x
     * \param yy - y
     */
    Vector2D_t( const T& xx, const T& yy ): x(xx), y(yy){}

    /**
     * \brief Construct a new Vector 2 D object
     */
    Vector2D_t(): x(0), y(0){}

    /**
     * \brief Construct a new Vector 2 D object
     * \param vec -
     */
    Vector2D_t( const Vector2D_t& vec ): x(vec.x), y(vec.y){}

    /**
     * \brief Destroy the Vector 2 D object
     */
    ~Vector2D_t() = default;

////---------------------------------------------------------------
public:
    /**
     * \brief Operator +=
     * \param vec -
     * \return Vector2D_t& -
     */
    inline Vector2D_t& operator += ( const Vector2D_t& vec )
    { this->x += vec.x;   this->y += vec.y; }

    /**
     * \brief Operator -=
     * \param vec -
     * \return Vector2D_t& -
     */
    inline Vector2D_t& operator -= ( const Vector2D_t& vec )
    { this->x -= vec.x;   this->y -= vec.y; }

////---------------------------------------------------------------
public:
    /**
     * \brief operator +
     * \param vec -
     * \return Vector2D_t -
     */
    inline Vector2D_t operator + ( Vector2D_t vec )
    { vec += *this; return vec; }

    /**
     * \brief operator + v2
     * \param vec -
     * \return Vector2D_t -
     */
    inline Vector2D_t operator + ( const Vector2D_t& vec ){
        Vector2D_t tmp = vec;
        tmp += *this;
        return tmp;
    }

    /**
     * \brief Operator -
     * \param vec -
     * \return Vector2D_t -
     */
    inline Vector2D_t operator - ( const Vector2D_t& vec ){
        Vector2D_t tmp = *this;
        tmp -= vec;
        return tmp;
    }

};


/**
 * \brief Display operator.
 * Only for debug!
 * \param strm -
 * \param vec -
 * \return std::ostream& -
 */
template< typename T >
std::ostream& operator << ( std::ostream& strm, const Vector2D_t<T>& vec ){
    strm << "[" << vec.x << "; " << vec.y << "]";
    return strm;
}