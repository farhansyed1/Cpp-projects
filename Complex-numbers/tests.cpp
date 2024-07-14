#include "Complex.h"
#include <gtest/gtest.h>

// To compile: g++ -o tests tests.cpp Complex.h -lgtest -lgtest_main -pthread
// Running valgrind: valgrind --leak-check=full --show-leak-kinds=all ./tests

// MEMBER FUNCTIONS

// Default constructor - Real and imag should be 0
TEST(ComplexConstructors, DefaultCorrectValue) {
    Complex c;
    EXPECT_EQ(0, c.real());
    EXPECT_EQ(0, c.imag());
}

// Only real part constructor - Real should get value while imag should be 0
TEST(ComplexConstructors, RealCorrectValue) {
    Complex c(5);
    EXPECT_EQ(5, c.real());
    EXPECT_EQ(0, c.imag());

    Complex c2(-5.9999);
    EXPECT_EQ(-5.9999, c2.real());
    EXPECT_EQ(0, c2.imag());
}

// Both real and imag constructor - Real and imag should get their defined values
TEST(ComplexConstructors, RealImagCorrectValues) {
    Complex c(5, 10);
    EXPECT_EQ(5, c.real());
    EXPECT_EQ(10, c.imag());

    Complex c2(-5.40, -10);
    EXPECT_EQ(-5.4, c2.real());
    EXPECT_EQ(-10, c2.imag());
}

// Copy constructor - Copies correctly
TEST(ComplexConstructors, CopyCopiesCorrectly) {
    Complex c(5.0, 10.0);
    Complex c2(c);

    EXPECT_EQ(5.0, c2.real());
    EXPECT_EQ(10.0, c2.imag());

    Complex c3;
    Complex c4(c3);

    EXPECT_EQ(0, c4.real());
    EXPECT_EQ(0, c4.imag());
}

// Copy assignment operator - Copies correctly
TEST(AssignmentOperators, CopyAssignmentCorrect) {
    Complex c(5, -10);
    Complex c2 = c;
    EXPECT_EQ(5, c2.real());
    EXPECT_EQ(-10, c2.imag());

    Complex c3 = 5.9;
    EXPECT_EQ(5.9, c3.real());
    EXPECT_EQ(0, c3.imag());
}

// Real part accessor - Check if real() gets correct value
TEST(ComplexMemberAccessors, MemberAccessRealPart) {
    Complex c(-5, 10);
    EXPECT_EQ(-5, c.real());
}

// Imaginary part accessor - Check if imag() gets correct value
TEST(MatrixAccessors, CorrectNumOfCols) {
    Complex c(5.3, 10.1);
    EXPECT_EQ(10.1, c.imag());
}

// Addition equals operator += 
TEST(MemberOperators, AdditionEqualsIsCorrect) {
    Complex c(5, 10);
    Complex c2(2, 2);
    c += c2;
    EXPECT_EQ(7, c.real());
    EXPECT_EQ(12, c.imag());

    Complex c3(-1, -1);
    Complex c4(2, 2);
    c += c3 += c4;
    EXPECT_EQ(8, c.real());
    EXPECT_EQ(13, c.imag());

}

// Subtraction operator -= 
TEST(MatrixOperators, SubtractionEqualsIsCorrect) {
    Complex c(5, 10);
    Complex c2(2.5, 2.4);
    c -= c2;
    EXPECT_EQ(2.5, c.real());
    EXPECT_EQ(7.6, c.imag());

    Complex c3(-1, -1);
    Complex c4(2, 2);
    c -= c3 -= c4; //c3 -= c4 becomes (-3,-3)
    EXPECT_EQ(5.5, c.real());
    EXPECT_EQ(10.6, c.imag());
}

// Mulitplication equals operator *=  
TEST(MemberOperators, MultiplicationEqualsIsCorrect) {
    Complex c(5.0, 10.0);
    Complex c2(2.0, 2.0);
    c *= c2;
    EXPECT_EQ(-10.0, c.real());
    EXPECT_EQ(30.0, c.imag());

    Complex c3(-1, -1);
    Complex c4(2, 2);
    c *= c3 *= c4; //c3 *= c4 becomes (0,-4)
    EXPECT_EQ(120, c.real());
    EXPECT_EQ(40, c.imag()); 
}

// Division equals operator /=  
TEST(MemberOperators, DivisionEqualsIsCorrect) {
    Complex c(6.0, 8.0);
    Complex c2(2.0, 2.0);
    c /= c2;
    EXPECT_EQ(3.5, c.real());
    EXPECT_EQ(0.5, c.imag());

    Complex c3(-1, -1);
    Complex c4(2, 2);
    c /= c3 /= c4; // c3 /= c4 becomes (-0.5,0)
    EXPECT_EQ(-7, c.real());
    EXPECT_EQ(-1, c.imag()); 
}

// NON-MEMBER FUNCTIONS

// Real part accessor - Check if real(c) gets correct value
TEST(NonMemberAccessors, NonMemberAccessRealPart) {
    Complex c(5.2, -110);
    EXPECT_EQ(5.2, real(c));
}

// Imaginary part accessor - Check if imag(c) gets correct value
TEST(NonMemberAccessors, NonMemberAccessImagPart) {
    Complex c(5, 10);
    EXPECT_EQ(10, imag(c));
}

// Absolute value calculation
TEST(AbsCalculation, AbsCorrectValue) {
    Complex c(-3.0, 4);
    EXPECT_EQ(5, abs(c));

    Complex c2(0, 4);
    EXPECT_EQ(4, abs(c2));

    Complex c3(0, 0);
    EXPECT_EQ(0, abs(c3));

    Complex c4(-3, -4);
    EXPECT_EQ(5, abs(c4));

    Complex c5(3, 4);
    EXPECT_EQ(5, abs(c5));
}

// Unary operator +
TEST(NonMemberOperators, UnaryPositiveIsCorrect) {
    Complex c(-5.0, -10.0);
    Complex c2 = +c;
    EXPECT_EQ(-5.0, real(c2));
    EXPECT_EQ(-10.0, imag(c2));
}

// Unary operator -
TEST(NonMemberOperators, UnaryNegativeIsCorrect) {
    Complex c(5.0, 10.0);
    Complex c2 = -c;
    EXPECT_EQ(-5.0, real(c2));
    EXPECT_EQ(-10.0, imag(c2));
}

// Addition operator + 
TEST(NonMemberOperators, AdditionIsCorrect) {
    Complex c(5, 10);
    Complex c2(-2, -2);
    EXPECT_EQ(3, real(c+c2));
    EXPECT_EQ(8, imag(c+c2));
}

// Subtraction operator - 
TEST(NonMemberOperators, SubtractionIsCorrect) {
    Complex c(5.0, 10.0);
    Complex c2(2.0, 2.0);
    EXPECT_EQ(3.0, real(c-c2));
    EXPECT_EQ(8.0, imag(c-c2));
}

// Multiplication operator * 
TEST(NonMemberOperators, MultiplicationIsCorrect) {
    Complex c(5.0, 10.0);
    Complex c2(2.0, 2.0);
    EXPECT_EQ(-10.0, real(c*c2));
    EXPECT_EQ(30.0, imag(c*c2));
}

// Division operator / 
TEST(NonMemberOperators, DivisionIsCorrect) {
    Complex c(6.0, 8.0);
    Complex c2(2.0, 2.0);
    EXPECT_EQ(3.5, real(c/c2));
    EXPECT_EQ(0.5, imag(c/c2));
}

// Equality operator == 
TEST(NonMemberOperators, EqualityIsCorrect) {
    Complex c(5, 10);
    Complex c2(c);
    EXPECT_EQ(true, c==c2);

    Complex c3(5, 11);
    EXPECT_EQ(false, c==c3);
}

// Inequality operator != 
TEST(NonMemberOperators, InequalityIsCorrect) {
    Complex c(5, 10);
    Complex c2(5.1, 10);
    EXPECT_EQ(true, c!=c2);

    Complex c3(5, 10);
    EXPECT_EQ(false, c!=c3);
}

// Less than operator < 
TEST(NonMemberOperators, LessThanIsCorrect) {
    Complex c(5.0, 10);
    Complex c2(5.1, 10);
    EXPECT_EQ(true, c<c2);

    Complex c3(5, 10);
    EXPECT_EQ(false, c<c3);

    Complex c4(0, 0);
    EXPECT_EQ(false, c<c4);
}

// Output operator << 
TEST(IO, OutputIsCorrect) {
    Complex c(5.2, 10.1);
    std::stringstream os;
    os << c;

    std::string expected = "(5.2,10.1)"; 
    EXPECT_EQ(os.str(), expected);

    std::stringstream os2;
    os2 << Complex(6, 6) / 6;

    std::string expected2 = "(1,1)"; 
    EXPECT_EQ(os2.str(), expected2);

    std::stringstream os3;
    os3 << Complex();

    std::string expected3 = "(0,0)"; 
    EXPECT_EQ(os3.str(), expected3);

    std::stringstream os4;
    os4 << Complex(-1);

    std::string expected4 = "(-1,0)"; 
    EXPECT_EQ(os4.str(), expected4);

}

// Input operator >> 
TEST(IO, InputIsCorrect) { 
    std::istringstream is("(5.0,10.0)");
    Complex expected(1);
    is >> expected;
    EXPECT_EQ(5.0, real(expected));
    EXPECT_EQ(10.0, imag(expected));
 
    std::istringstream is2("(5)");
    Complex expected2(10,-1);
    is2 >> expected2;
    EXPECT_EQ(5, real(expected2));
    EXPECT_EQ(0, imag(expected2));

    std::istringstream is3("5");
    Complex expected3(0);
    is3 >> expected3;
    EXPECT_EQ(5, real(expected3));
    EXPECT_EQ(0, imag(expected3));
}

// Input and output are consistent
TEST(IO, InputOutputConsistency) {
    Complex c(5.0, 10.0);
    
    std::stringstream ss;
    ss << c;
    Complex expected(1);
    ss >> expected;

    EXPECT_EQ(real(c), real(expected));
    EXPECT_EQ(imag(c), imag(expected));
}

// Literal form for doubles 
TEST(LiteralForm, DoubleLiteralFormIsCorrect) {
    Complex c = 10.4_i;
    EXPECT_EQ(0, real(c));
    EXPECT_EQ(10.4, imag(c));

    Complex c2 = -2.5 + 10.4_i;
    EXPECT_EQ(-2.5, real(c2));
    EXPECT_EQ(10.4, imag(c2));
}

// Literal form for whole numbers 
TEST(LiteralForm, WholeNumberLiteralFormIsCorrect) {
    Complex c = 10_i;
    EXPECT_EQ(0, real(c));
    EXPECT_EQ(10, imag(c));

    Complex c2 = -2 + 10_i;
    EXPECT_EQ(-2, real(c2));
    EXPECT_EQ(10, imag(c2));

    Complex c3 = 5 + 1_i * Complex(5, 3);
    EXPECT_EQ(2, real(c3));
    EXPECT_EQ(5, imag(c3));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}