#include<iostream>
#include<string>
#include<cmath>
#include<math.h>

class complex
{
    friend std::ostream & operator<<(std::ostream &os, const complex &z);
    friend std::istream & operator>>(std::istream &is, complex &z);
private:
    double re, im;
public:
    complex() : re{}, im{} {}
    complex(double real_part, double im_part) : re{real_part}, im{im_part} {}

    double real_part()
    {
        return re;
    }
    double imag_part()
    {
        return im;
    }

    double modulus()
    {
        return sqrt(re*re + im*im);
    }

    double argument()
    {
        return atan2(im,re) * (180.0/3.141592653589793238463);
    }

    complex conjugate()
    {
        complex conjugate;
        conjugate.re = re;
        conjugate.im = -im;
        return conjugate;
    }

    complex operator+(const complex &z) const
    {
        complex temp{re+z.re,im+z.im};
        return temp;
    }

    complex operator-(const complex &z) const
    {
        complex temp{re-z.re,im-z.im};
        return temp;
    }

    complex operator*(const complex &z) const
    {
        complex temp{re*z.re - im*z.im, re*z.im + im*z.re};
        return temp;
    }

    complex operator/(const complex &z) const
    {
        complex temp{(re*z.re + im*z.im)/(z.re*z.re + z.im*z.im),
         (-re*z.im + im*z.re)/(z.re*z.re + z.im*z.im)};
        return temp;
    }

};

std::ostream & operator<<(std::ostream &os, const complex &z)
{
    if (z.im>=0){
        os<<z.re<<'+'<<z.im <<'i';
    }
    else{
        os<<z.re<<z.im <<'i';
    }
    return os;
}

std::istream & operator>>(std::istream &is, complex &z)
{
    char sign, i;
    is >> z.re >> sign >> i >> z.im;
    if (sign == '-') {
        z.im = -z.im;
    }
    return is;
}


int main()
{  
    std::cout.precision(3);

    complex a{3,4};
    complex b{1,-2};
    complex input;

    std::cout << "Real part of a is " << a.real_part() << std::endl
              << "Imaginary part of a is " << a.imag_part() << std::endl
              << "Modulus of a is " << a.modulus() << std::endl
              << "Argument of a is " << a.argument() << "\370" << std::endl;

    std::cout << "Real part of b is " << b.real_part() << std::endl
              << "Imaginary part of b is " << b.imag_part() << std::endl
              << "Modulus of b is " << b.modulus() << std::endl
              << "Argument of b is " << b.argument() << "\370" << std::endl;

    std::cout << "Conjugate of a is " << a.conjugate() << std::endl
              << "Conjugate of b is " << b.conjugate() << std::endl;

    std::cout << "Sum of a and b is " << a+b << std::endl
              << "Difference of a and b is " << a-b << std::endl
              << "Product of a and b is " << a*b << std::endl
              << "Quotient of a and b is " << a/b << std::endl;

    std::cout << "Input complex number: [a+/-ib] ";
    std::cin >> input;
    std::cout << "The complex number is " << input;

  return 0;
}