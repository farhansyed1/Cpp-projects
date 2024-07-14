/*
* Complex numbers
* 
* Author: Farhan Syed
* Year: 2024
*/

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

class Complex{

    public:
        // Constructors
        Complex();
        Complex(double real); 
        constexpr Complex(double real,double imaginary);
        
        Complex(const Complex &rhs);
        Complex &operator=(const Complex &other);
        
        // Accessors
        double real() const;
        double imag() const;

        // Operators
        Complex& operator+=(const Complex &other);
        Complex& operator-=(const Complex &other);
        Complex& operator*=(const Complex &other); 
        Complex& operator/=(const Complex &other); 

    private:
        double re;
        double im;

};

// Non-member functions 
Complex operator+(const Complex &lhs, const Complex &rhs);
Complex operator-(const Complex &lhs, const Complex &rhs);
Complex operator*(const Complex &lhs, const Complex &rhs);
Complex operator/(const Complex &lhs, const Complex &rhs);

bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);

double real(const Complex &number);
double imag(const Complex &number);
double abs(const Complex &number);

bool operator<(const Complex &lhs, const Complex &rhs);

std::istream & operator>>(std::istream & is, Complex &number);
std::ostream & operator<<(std::ostream & os, const Complex &number);

constexpr Complex operator""_i(long double arg);
constexpr Complex operator""_i(unsigned long long arg);

/* Implementations of member functions */

// CONSTRUCTORS
// Standard constructors
Complex::Complex() : re(0.0), im(0.0){}
Complex::Complex(double real) : re(real), im(0.0){}
constexpr Complex::Complex(double real, double imaginary) : re(real), im(imaginary){};

// Copy constructor
Complex::Complex(const Complex &rhs) : re{rhs.re}, im{rhs.im} {};

// Copy assignment operator
Complex &Complex::operator=(const Complex &other){
    if(this != &other){
        re = other.re;
        im = other.im;
    }
    return *this;
};

// ACCESSORS
// Access real component
double Complex::real() const{
    return re;
};

// Access imaginary component
double Complex::imag() const{
    return im;
};

// OPERATORS
// These operators are chainable

// += operator
Complex& Complex::operator+=(const Complex &other){
    *this = *this + other;
    return *this;
};

// -= operator
Complex& Complex::operator-=(const Complex &other){
    *this = *this - other;
    return *this;
};

// *= operator
Complex& Complex::operator*=(const Complex &other){
    *this = *this * other;
    return *this;
};

// /= operator
Complex& Complex::operator/=(const Complex &other){
    *this = *this / other;
    return *this;
};

/* Implementations of non-member functions */

// ACCESSORS

// Access real component
double real(const Complex &number){
    return number.real();
};

// Access imaginary component
double imag(const Complex &number){
    return number.imag();
};

// Get the absolute value with formula sqrt(a^2+b^2)
double abs(const Complex &number){
    return sqrt(pow(number.real(),2) + pow(number.imag(),2)); 
};

// OPERATORS

// Unary + for one complex number
Complex operator+(const Complex &number){
    return number;
}

// Unary - for one complex number
Complex operator-(const Complex &number){
    return Complex(-number.real(), -number.imag());
}

// Addition of two complex numbers
Complex operator+(const Complex &lhs, const Complex &rhs){
    double realSum = lhs.real() + rhs.real();
    double imagSum = lhs.imag() + rhs.imag();
    return Complex(realSum,imagSum);
};

// Subtraction of two complex numbers
Complex operator-(const Complex &lhs, const Complex &rhs){
    double realDiff = lhs.real() - rhs.real();
    double imagDiff = lhs.imag() - rhs.imag();
    return Complex(realDiff,imagDiff);
};

// Multiplication of two complex numbers, with formula (a+bi)*(c+di) = (ac−bd)+(ad+bc)i
Complex operator*(const Complex &lhs, const Complex &rhs){
    double realPart = (lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag());
    double imagPart = (lhs.real() * rhs.imag()) + (lhs.imag() * rhs.real());
    return Complex(realPart,imagPart);
};

// Division of two complex numbers, with formula (a+bi)/(c+di) = (ac+bd)/(c^2 + d^2) + (bc-ad)i/(c^2 + d^2)   
Complex operator/(const Complex &lhs, const Complex &rhs){ 
    double denominator = rhs.real()*rhs.real() + rhs.imag()*rhs.imag();
    if(denominator != 0){
        double realPart = (lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag());
        double imagPart = (lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag());
        return Complex(realPart/denominator,imagPart/denominator);
    }
    throw std::out_of_range("Invalid arguments. Cannot divide with 0!");    
};

// Equality operator
bool operator==(const Complex &lhs, const Complex &rhs){
    if(lhs.real() == rhs.real() && lhs.imag() == rhs.imag()){
        return true;
    } 
    return false;
};

// Not equal operator
bool operator!=(const Complex &lhs, const Complex &rhs){
    return !(lhs == rhs);
};

// Less than operator
bool operator<(const Complex &lhs, const Complex &rhs){
    if(abs(lhs) < abs(rhs)){
        return true;
    }
    return false;
};

// Output operator
std::ostream & operator<<(std::ostream & os, const Complex &number){
    os << "(" << number.real() << "," << number.imag() << ")";
    return os;
};

// Input operator
std::istream & operator>>(std::istream & is, Complex &number){
    std::string line;
    double realPart = 0.0;
    double imagPart = 0.0;
    std::getline(is,line);  

    line.erase(std::remove(line.begin(), line.end(), '('), line.end()); // Parentheses are removed
    line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
    
    std::istringstream numberIS(line); // convert line string to input stream

    numberIS >> realPart;

    if (numberIS.peek() == ',') {
        numberIS.ignore();  // Comma in (real,imaginary) is ignored
        numberIS >> imagPart; 
    }
    number = Complex(realPart, imagPart);

    return is;
};

// double_i  literal form
constexpr Complex operator""_i(long double arg) {
    return Complex(0.0, static_cast<double>(arg));
}

// wholeNumber_i  literal form
constexpr Complex operator""_i(unsigned long long arg) {
    return Complex(0.0, static_cast<double>(arg));
}

#endif //COMPLEX_H
