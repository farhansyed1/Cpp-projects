#include "Matrix.h"
#include <gtest/gtest.h>

// To compile: g++ -o tests tests.cpp Matrix.h -lgtest -lgtest_main -pthread
// Running valgrind: valgrind --leak-check=full --show-leak-kinds=all ./tests

// Default constructor - Check size
TEST(MatrixConstructors, DefaultCorrectSize) {
    Matrix<int> m;
    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.cols());
}

// Square matrix constructor - Check size
TEST(MatrixConstructors, SquareCorrectSize) {
    Matrix<int> m(5);
    EXPECT_EQ(5, m.rows());
    EXPECT_EQ(5, m.cols());
    EXPECT_EQ(0, m(1,1));
}

// Defined row and column size constructor - Check size
TEST(MatrixConstructors, RowColCorrectSize) {
    Matrix<int> m(3,5);
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(5, m.cols());
    EXPECT_EQ(0, m(2,1));
}

// Square matrix using list constructor - List is perfect square
TEST(MatrixConstructors, ListCorrectSize) {
    Matrix<int> m({1,2,3,4});
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(2, m.cols());
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(1,0));
    EXPECT_EQ(4, m(1,1));
}

// Square matrix using list constructor - List is not perfect square and throws error
TEST(MatrixConstructors, ListWrongSize) {
    EXPECT_THROW({Matrix<int> m({2,2});}, std::out_of_range);
}

// Copy constructor - Copies correctly
TEST(MatrixConstructors, CopyConstructorCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2(m); // Using an lvalue

    EXPECT_EQ(2, m2.rows());
    EXPECT_EQ(2, m2.cols());
    EXPECT_EQ(1, m2(0,0));
    EXPECT_EQ(2, m2(0,1));
    EXPECT_EQ(3, m2(1,0));
    EXPECT_EQ(4, m2(1,1));
}

// Move constructor - Moves correctly
TEST(MatrixConstructors, MoveConstructorCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2(std::move(m)); // Using an rvalue

    EXPECT_EQ(2, m2.rows());
    EXPECT_EQ(2, m2.cols());
    EXPECT_EQ(1, m2(0,0));
    EXPECT_EQ(2, m2(0,1));
    EXPECT_EQ(3, m2(1,0));
    EXPECT_EQ(4, m2(1,1));
}

// Copy assignment operator - Copies correctly
TEST(AssignmentOperators, CopyAssignmentCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2 = m; // Using an lvalue

    EXPECT_EQ(2, m2.rows());
    EXPECT_EQ(2, m2.cols());
    EXPECT_EQ(1, m2(0,0));
    EXPECT_EQ(2, m2(0,1));
    EXPECT_EQ(3, m2(1,0));
    EXPECT_EQ(4, m2(1,1));
}

// Moves assignment operator - Moves correctly
TEST(AssignmentOperators, MoveAssignmentCorrect ) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2 = std::move(m); // Using an rvalue

    EXPECT_EQ(2, m2.rows());
    EXPECT_EQ(2, m2.cols());
    EXPECT_EQ(1, m2(0,0));
    EXPECT_EQ(2, m2(0,1));
    EXPECT_EQ(3, m2(1,0));
    EXPECT_EQ(4, m2(1,1));
}

// Rows accessor - Check correct number of rows
TEST(MatrixAccessors, CorrectNumOfRows) {
    Matrix<int> m({1,2,3,4,5,6,7,8,9});
    EXPECT_EQ(3, m.rows());
}

// Columns accessor - Check correct number of columns
TEST(MatrixAccessors, CorrectNumOfCols) {
    Matrix<int> m({1,2,3,4,5,6,7,8,9});
    EXPECT_EQ(3, m.cols());
}

// Access operator () - Returns correct element
TEST(MatrixOperators, ElementAccessCorrect) {
    Matrix<int> m({1,2,3,4,5,6,7,8,9});
    EXPECT_EQ(3, m(0,2));
}

// Const access operator () - Returns correct element
TEST(MatrixOperators, ConstElementAccessCorrect) {
    const Matrix<int> m({1,2,3,4,5,6,7,8,9});
    EXPECT_EQ(3, m(0,2));
}

// Mulitplication operator * - Product matrix is correct
TEST(MatrixOperators, MultiplicationIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2(2,1);
    m2(0,0) = 2;
    m2(1,0) = 2;
    Matrix<int> product = m*m2;

    EXPECT_EQ(6, product(0,0));
    EXPECT_EQ(14, product(1,0));
}

// Addition operator + - Sum matrix is correct
TEST(MatrixOperators, AdditionIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2({1,2,3,4});
    Matrix<int> sum = m+m2;

    EXPECT_EQ(2, sum(0,0));
    EXPECT_EQ(4, sum(0,1));
    EXPECT_EQ(6, sum(1,0));
    EXPECT_EQ(8, sum(1,1));
}

// Subtraction operator - - Difference matrix is correct
TEST(MatrixOperators, SubtractionIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2({1,1,1,1});
    Matrix<int> diff = m-m2;

    EXPECT_EQ(0, diff(0,0));
    EXPECT_EQ(1, diff(0,1));
    EXPECT_EQ(2, diff(1,0));
    EXPECT_EQ(3, diff(1,1));
}

// Mulitplication equals operator *= - Product matrix is correct
TEST(MatrixOperators, MultiplicationEqualIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2(2,1);
    m2(0,0) = 2;
    m2(1,0) = 2;
    m *= m2;

    EXPECT_EQ(6, m(0,0));
    EXPECT_EQ(14, m(1,0));
}

// Addition equals operator += - Sum matrix is correct
TEST(MatrixOperators, AdditionEqualsIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2({1,2,3,4});
    m += m2;

    EXPECT_EQ(2, m(0,0));
    EXPECT_EQ(4, m(0,1));
    EXPECT_EQ(6, m(1,0));
    EXPECT_EQ(8, m(1,1));
}

// Subtraction operator - - Difference matrix is correct
TEST(MatrixOperators, SubtractionEqualsIsCorrect) {
    Matrix<int> m({1,2,3,4});
    Matrix<int> m2({1,1,1,1});
    m -= m2;

    EXPECT_EQ(0, m(0,0));
    EXPECT_EQ(1, m(0,1));
    EXPECT_EQ(2, m(1,0));
    EXPECT_EQ(3, m(1,1));
}

// Reset matrix - Rows and columns are 0 
TEST(Reset, ResetSetsDimToZero) {
    Matrix<int> m({1,2,3,4});
    m.reset();

    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.cols());
}

// Insert row - New row of zeroes in correct place 
TEST(RowOperations, InsertRowIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.insert_row(1);
   
    EXPECT_EQ(3, m.rows());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(0, m(1,0));
    EXPECT_EQ(0, m(1,1));
    EXPECT_EQ(3, m(2,0));
    EXPECT_EQ(4, m(2,1));
}

// Append row - New row of zeroes in correct place 
TEST(RowOperations, AppendRowIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.append_row(1);
   
    EXPECT_EQ(3, m.rows());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(1,0));
    EXPECT_EQ(4, m(1,1));
    EXPECT_EQ(0, m(2,0));
    EXPECT_EQ(0, m(2,1));
}

// Remove row - row is removed 
TEST(RowOperations, RemoveRowIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.remove_row(1);
   
    EXPECT_EQ(1, m.rows());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
}

// Insert column - New column of zeroes in correct place 
TEST(ColOperations, InsertColumnIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.insert_column(1);
   
    EXPECT_EQ(3, m.cols());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(0, m(0,1));
    EXPECT_EQ(2, m(0,2));

    EXPECT_EQ(3, m(1,0));
    EXPECT_EQ(0, m(1,1));
    EXPECT_EQ(4, m(1,2));
}

// Append column - New column of zeroes in correct place 
TEST(ColOperations, AppendColumnIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.append_column(1);
   
    EXPECT_EQ(3, m.cols());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(0, m(0,2));

    EXPECT_EQ(3, m(1,0));
    EXPECT_EQ(4, m(1,1));
    EXPECT_EQ(0, m(1,2));
}

// Remove column - column is removed 
TEST(ColOperations, RemoveColumnIsCorrect) {
    Matrix<int> m({1,2,3,4});
    m.remove_column(1);
   
    EXPECT_EQ(1, m.cols());

    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(3, m(1,0));
}

// Begin() - points to first element 
TEST(Iterators, BeginPointsToFirstElem) {
    Matrix<int> m({1,2,3,4});
    int* p = m.begin();

    EXPECT_EQ(1, *p);
}

// End() - points to last element 
TEST(Iterators, EndPointsToLastElem) {
    Matrix<int> m({1,2,3,4});
    int* p = m.end()-1;

    EXPECT_EQ(4, *p);
}

// Input operator >> 
TEST(IO, InputIsCorrect) { 
    std::string input = "1 2\n3 4"; 
    std::istringstream is(input);

    Matrix<int> expected(2, 2); 
    is >> expected;

    EXPECT_EQ(1, expected(0,0));
    EXPECT_EQ(2, expected(0,1));
    EXPECT_EQ(3, expected(1,0));
    EXPECT_EQ(4, expected(1,1));

}

// Output operator << 
TEST(IO, OutputIsCorrect) {
    Matrix<int> m({1,2,3,4});

    std::stringstream os;
    os << m;

    std::string expected = "[ 1 2\n  3 4 ]"; 
    EXPECT_EQ(os.str(), expected);
}

// Input and output are consistent
TEST(IO, InputOutputConsistency) {
    Matrix<int> m({1,2,3,4,5,6,7,8,9});

    std::stringstream ss;
    ss << m;
    Matrix<int> n(3, 3); 
    ss >> n;

    // Verify the elements are the same
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.cols(); j++) {
            EXPECT_EQ(m(i, j), n(i, j));
        }
    }
}

// Identity matrix
TEST(Identity, IdentityIsCorrect) {
    Matrix<int> m = identity<int>(2);
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(0, m(0,1));
    EXPECT_EQ(0, m(1,0));
    EXPECT_EQ(1, m(1,1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}