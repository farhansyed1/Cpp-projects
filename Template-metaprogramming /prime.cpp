/*
* Simple prime numbers functions
* 
* Author: Farhan Syed
* Year: 2024

  Compile: g++ -o prime prime.cpp

*/

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>


// Function that returns a string of c++ code that initializes a vector or array with prime numbers.
std::string hard_coded_primes() {
    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    std::stringstream ss;

    ss << "std::vector<int> primes = {";

    for (int i = 0; i < primes.size(); i++) {
        ss << primes[i];
        if (i < primes.size() - 1){
            ss << ", ";
        } 
    }
    ss << "};";

    return ss.str();
}

// Function to find all primes up to N and prints them.
void find_primes(int N) {
    if (N < 2) {
        std::cout << "No prime numbers less than 2. \n";
        return;
    }
    std::vector<int> primeNums;

    for (int i = 2; i <= N; i++) {
        bool isPrime = true;
        for (int prime : primeNums) {
            if (prime > std::sqrt(i)) break;  
            if (i % prime == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primeNums.push_back(i);  
        }
    }
    for (int prime : primeNums) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
}

int main() {
    find_primes(30);
    std::string s = hard_coded_primes();
    std::cout << s << std::endl;
    return 0;
}