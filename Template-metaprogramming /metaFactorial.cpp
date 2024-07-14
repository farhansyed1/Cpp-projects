/*
* Template meta programming - Factorial  
* 
* Author: Farhan Syed
* Year: 2024

  Compile: g++ -o metaFactorial metaFactorial.cpp

*/

#include <iostream>

template <int x>
struct Factorial
{
  static const int nr = x * Factorial<x - 1>::nr;
};

template <>
struct Factorial<1>
{
  static const int nr = 1;
};
int main()
{
  std::cout << Factorial<5>::nr << std::endl;
}