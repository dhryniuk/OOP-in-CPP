#include <iostream>
#include <string>
#include <math.h>


const double pi = 3.141592;

class shape 
{
public:
    virtual ~shape() {};
    virtual void info()=0;
    virtual double area()=0;
};

class shape2D: public shape 
{
protected:
    int dimension{2};
public:
    virtual ~shape2D() {};
    virtual void info()=0;
    virtual double area()=0;
};

class shape3D: public shape 
{
protected:
    int dimension{3};
public:
    virtual ~shape3D() {};
    virtual void info()=0;
    virtual double area()=0;
    virtual double volume()=0;
};

class ellipse: public shape2D 
{
private:
    double semi_minor{}, semi_major{};
    std::string name{"ellipse"};
public:
    ellipse() {};
    ellipse(double min, double maj) : semi_minor{min}, semi_major{maj} {};
    ~ellipse() {};
    double area() 
    {
        return pi*semi_minor*semi_major;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << std::endl;
    }
};

class circle: public ellipse 
{
private:
    double radius{};
    std::string name{"circle"};
public:
    circle() {};
    circle(double r) : radius{r} {}
    ~circle() {};
    double area() 
    {
        return pi*radius*radius;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << std::endl;
    }
};

class rectangle: public shape2D 
{
private:
    double length{}, width{};
    std::string name{"rectangle"};
public:
    rectangle() {};
    rectangle(double l, double w) : length{l}, width{w} {};
    ~rectangle() {};
    double area() 
    {
        return length*width;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << std::endl;
    }
};

class square: public rectangle 
{
private:
    double length{};
    std::string name{"square"};
public:
    square() {};
    square(double l) : length{l} {};
    ~square() {};
    double area() 
    {
        return length*length;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << std::endl;
    }
};

class cuboid: public shape3D 
{
private:
    double length{}, width{}, height{};
    std::string name{"cuboid"};
public:
    cuboid() {};
    cuboid(double l, double w, double h) : length{l}, width{w}, height{h} {};
    ~cuboid() {};
    double area() 
    {
        return 2*length*width + 2*width*height + 2*height*length;
    }
    double volume() 
    {
        return length*width*height;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << "\t volume=" << volume() << std::endl;
    }
};

class cube: public cuboid 
{
private:
    double length{};
    std::string name{"cube"};
public:
    cube() {};
    cube(double l) : length{l} {};
    ~cube() {};
    double area() 
    {
        return 6*length*length;
    }
    double volume() 
    {
        return length*length*length; 
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << "\t volume=" << volume() << std::endl;
    }
};

class ellipsoid: public shape3D 
{
private:
    std::string name{"ellipsoid"};
    double a{}, b{}, c{};
public:
    ellipsoid() {};
    ellipsoid(double A, double B, double C) : a{A}, b{B}, c{C} {};
    ~ellipsoid() {};
    double area() 
    {
        //Use Knud Thomsen’s Formula:
        const double p = 1.6075;
        return 4.0*pi*pow((pow(a,p)*pow(b,p)+pow(a,p)*pow(c,p)+pow(b,p)*pow(c,p))/3.0,1.0/p);
    }
    double volume() 
    {
        return 4.0/3.0*pi*a*b*c;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << "\t volume=" << volume() << std::endl;
    }
};

class sphere: public ellipsoid 
{
private:
    double radius{};
    std::string name{"sphere"};
public:
    sphere() {};
    sphere(double r) : radius{r} {};
    ~sphere() {};
    double area() 
    {
        return 4.0*pi*radius*radius;
    }
    double volume() 
    {
        return 4.0/3.0*pi*radius*radius*radius;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t area=" 
        << area() << "\t volume=" << volume() << std::endl;
    }
};

class prism: public shape3D 
{
private:
    double height{};
    shape2D *shape2D_pointer;
    std::string name{"prism"};
public:
    prism() {};
    prism(double h, shape2D *sh) : height{h}, shape2D_pointer{sh} {};
    ~prism() {};
    double area() 
    {
        return 0;
    }
    double volume() 
    {
        return shape2D_pointer->area()*height;
    }
    void info() 
    {
        std::cout<<"shape: name=" << name << "\t dimensions=" << dimension << "\t volume=" 
        << volume() << std::endl;
    }
};



int main()
{
    //Demonstrate polymorphism using array of pointers:
    shape **shape_array = new shape*[9];

    shape_array[0] = new circle{1};
    shape_array[1] = new ellipse{1,1};
    shape_array[2] = new rectangle{1,1};
    shape_array[3] = new square{3};
    
    shape_array[4] = new cube{1.2};
    shape_array[5] = new cuboid{1,3,7};
    shape_array[6] = new ellipsoid{1,2,3};
    shape_array[7] = new sphere{2};

    shape_array[8] = new prism{1, new circle{3}};

    for (int i{0}; i<=8; i++) {
        shape_array[i]->info();
        delete shape_array[i];
    }
    delete[] shape_array;

    return 0;
}