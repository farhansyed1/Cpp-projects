/*
* Prime number using constexpr 
* 
* Author: Farhan Syed
* Year: 2024

  Compile: g++ -o constexprPrime constexprPrime.cpp

  Must compile with c++20

*/

#include <array>
#include <iostream>

// Helper function to check if a number p is prime by testing divisibility from i down to 2
constexpr bool is_prime(int p, int i) {
    if (p < 2) {
        return false;  
    } else if (i == 1) {
        return true;   // Base case - if i reaches 1, p is prime because no divisors were found
    } else if (p % i == 0) {
        return false;  
    } else {
        return is_prime(p, i - 1);  
    }
}

// Generates an array of the first 10 prime numbers
constexpr std::array<int, 10> generate_primes() {
    std::array<int, 10> primes{};
    int count = 0;
    for (int p = 2; count < 10; p++) { // Find 10 first prime numbers
        if (is_prime(p, p - 1)) {
            primes[count++] = p;
        }
    }
    return primes;
}

int main() {
    constexpr auto prime_numbers = generate_primes();  
    for (int prime : prime_numbers) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
    return 0;
}