#include<iostream>
#include"assignment_5_Hryniuk.hpp" 

int main() 
{
    matrix A(2,2);
    matrix C(2,2);
    matrix D(4,4);
    matrix E(1,1);
    A.element(1,1) = 1;
    A.element(1,2) = 2;
    A.element(2,1) = 3;
    A.element(2,2) = 4;
    std::cout << "Demonstrate copy constructor and copy assignment operator." << std::endl;
    std::cout << "A:\n"<< A << std::endl;
    std::cout << "Perform a deep copy of matrix A using copy constructor." << std::endl;
    matrix B{A};
    std::cout << "B:\n" << B << std::endl;
    std::cout << "Perform a deep copy of matrix A using assignment operator." << std::endl;
    C = A;
    std::cout << "C:\n" << C << std::endl;
    std::cout << "Modify original matrix A." << std::endl;
    A.element(1,1) -= 100;
    A.element(2,2) += 100;
    std::cout << "A:\n" << A << std::endl;
    std::cout << "Copied matrix B remains unchanged." << std::endl;
    std::cout << "B:\n" << B << std::endl;
    std::cout << "Copied matrix C remains unchanged." << std::endl;
    std::cout << "C:\n" << C << std::endl;

    std::cout << "Now, demonstrate move assignment operator. Move values from B to A:" << std::endl;
    A = std::move(B);
    std::cout << "A:\n" << A << std::endl;
    std::cout << "B:\n" << B << std::endl;
    std::cout << "Now, demonstrate move constructor. Declare matrix M and steal values from B to M:" << std::endl;
    matrix M(std::move(B));
    std::cout << "M:\n" << M << std::endl;

    std::cout << "Now, demonstrate overloaded arithmetic operations on matrices." << std::endl;
    std::cout << "A+M: " << A+M << std::endl;
    std::cout << "A-M: " << A-M << std::endl;
    std::cout << "A*M: " << A*M << std::endl;

    // Generate sample 3x3 matrix to demonstrate recursive determinant calculation:
    for (int i{0}; i< D.get_rows()*D.get_columns(); i++){
        D.set_array_element(i,i*(2*i*i-100)/7);
    }

    std::cout << "Now, demonstrate recursive calculation of determinant of square matrix." << std::endl;
    std::cout << "D:\n" << D << std::endl;
    std::cout << "The determinant of D is " << D.determinant() << ".\n" << std::endl;

    std::cout << "Now, demonstrate remove function. Remove row 2 and column 3 from matrix D:" << std::endl;
    std::cout << D.remove(2,3) << std::endl;
    std::cout << "Original matrix D is unchanged and can still be accessed: " << std::endl;
    std::cout << "D:\n" << D << std::endl;

    std::cout << "Now, demonstrate user input of matrix." << std::endl;
    std::cout << "Enter matrix E:\n";
    std::cin >> E;
    std::cout << "E:\n" << E << std::endl;

    return 0;
}