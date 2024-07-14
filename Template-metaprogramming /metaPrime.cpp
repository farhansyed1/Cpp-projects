/*
* Template meta programming - Prime numbers 
* 
* Author: Farhan Syed
* Year: 2024

  Prime numbers using meta template programming

  Compile: g++ -o metaPrime metaPrime.cpp

*/

#include <iostream>

// Helper function that checks if a number p is prime by testing divisibility from i down to 2
template <unsigned int p, unsigned int i>
struct check_if_prime {
    static const bool isPrime = (p % i != 0) && check_if_prime<p, i - 1>::isPrime;
};

// Base case - if i reaches 1, p is prime because no divisors were found
template <unsigned int p>
struct check_if_prime<p, 1> {
    static const bool isPrime = true;
};

// Specific cases for when p < 2
template <unsigned int i>
struct check_if_prime<0, i> {
    static const bool isPrime = false;
};

template <unsigned int i>
struct check_if_prime<1, i> {
    static const bool isPrime = false;
};

// Checks if a number is prime using the helper function
template <unsigned int X>
struct is_prime {
    static const bool isPrime = check_if_prime<X, X - 1>::isPrime;
};

int main() {
    std::cout << "Number | Prime? \n";  
    std::cout << "0      |  " << is_prime<0>::isPrime << std::endl;  
    std::cout << "1      |  " << is_prime<1>::isPrime << std::endl;  
    std::cout << "2      |  " << is_prime<2>::isPrime << std::endl;  
    std::cout << "3      |  " << is_prime<3>::isPrime << std::endl;  
    std::cout << "4      |  " << is_prime<4>::isPrime << std::endl;  
    std::cout << "5      |  " << is_prime<5>::isPrime << std::endl;  
    std::cout << "6      |  " << is_prime<6>::isPrime << std::endl;  
    std::cout << "7      |  " << is_prime<7>::isPrime << std::endl;  
    std::cout << "97     |  " << is_prime<97>::isPrime << std::endl;  

    return 0;
}