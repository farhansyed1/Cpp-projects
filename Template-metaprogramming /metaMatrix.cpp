/*
* Template meta programming 
* 
* Author: Farhan Syed
* Year: 2024

  N-dimensional matrix using template meta programming

  Compile: g++ -o metaMatrix metaMatrix.cpp

*/

#include <vector>
#include <iostream>

// Recursion for N-dimensional matrix
template<int N, typename T = int>
struct NdimMatrix {
    std::vector<NdimMatrix<N-1, T>> m_vec;
    NdimMatrix(int size) : m_vec(size, NdimMatrix<N-1, T>(size)) {}

    NdimMatrix<N-1, T>& operator[](int index) { // return reference to the lower dimension matrix
        return m_vec[index];
    }
};

// Base case for 1-dimensional matrix
template<typename T>
struct NdimMatrix<1, T> {
    std::vector<T> m_vec;
    NdimMatrix(int size) : m_vec(size) {}

    T& operator[](int index) { // return a reference to the element at the specific index
        return m_vec[index];
    }
};

int main() {
    NdimMatrix<3> n(9); // a cube with 9 * 9 * 9 elements
    NdimMatrix<6> m(5); // a matrix in six dimensions with 5 * 5 * 5 * 5 * 5 * 5 elements
    m[1][3][2][1][4][0] = 7;
    NdimMatrix<3> t(5);
    t = m[1][3][2]; // assign part (slice) of m to t, the dimensions and element size matches
    t[1][4][0] = 2; // changes t but not m
    std::cout << m[1][3][2][1][4][0] << std::endl; // 7
    std::cout << t[1][4][0] << std::endl;          // 2
}
