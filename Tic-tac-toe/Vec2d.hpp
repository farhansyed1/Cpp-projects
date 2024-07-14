/*
* Tic tac toe
* 
* Author: Farhan Syed
* Year: 2024

*/

#ifndef VEC2D_HPP
#define VEC2D_HPP

template <class T>
struct Vec2d {
    T x;
    T y;
    Vec2d() : x{}, y{} {}
    Vec2d(T xx, T yy) : x(xx), y(yy) {}

    Vec2d<T> operator+(const Vec2d<T> & o) const;
    Vec2d<T> operator-(const Vec2d<T> & o) const;
    Vec2d<T> operator*(const Vec2d<T> & o) const;

    template <class S>
    Vec2d<T> operator*(const S & i ) const ;
  
    Vec2d<bool> operator==(const Vec2d<T> & o) const ;
    bool operator==(const bool & o) const ;
    Vec2d<bool> operator<(const Vec2d<T> & o) const ;
    Vec2d<bool> operator<=(const Vec2d<T> & o) const ;
    Vec2d<bool> operator&&(const Vec2d<T> & o) const ;

    operator bool() const ;
};

//---------------------------------------------------------

template <class T>
Vec2d<T> Vec2d<T>::operator+(const Vec2d<T> & o) const {
    return { x + o.x, y + o.y };
}
template <class T>
Vec2d<T> Vec2d<T>::operator-(const Vec2d<T> & o) const {
    return { x - o.x, y - o.y };
}
template <class T>
Vec2d<T> Vec2d<T>::operator*(const Vec2d<T> & o) const {
    return { x * o.x, y * o.y };
}
template <class T>
template <class S>
Vec2d<T> Vec2d<T>::operator*(const S & i ) const {
    return { x * i, y * i };
}
template <class T>
Vec2d<bool> Vec2d<T>::operator==(const Vec2d<T> & o) const {
    return { x == o.x, y == o.y };
}
template <class T>
bool Vec2d<T>::operator==(const bool & o) const {
    return (x == o) && (y == o);
}
template <class T>
Vec2d<bool> Vec2d<T>::operator<(const Vec2d<T> & o) const {
    return { x < o.x , y < o.y };
}
template <class T>
Vec2d<bool> Vec2d<T>::operator<=(const Vec2d<T> & o) const {
    return { x <= o.x , y <= o.y };
}
template <class T>
Vec2d<bool> Vec2d<T>::operator&&(const Vec2d<T> & o) const {
    return { x && o.x , y && o.y };
}

template <class T>
Vec2d<T>::operator bool() const { return !( x == T{} || y == T{} ); }

#endif  // VEC2D_HPP