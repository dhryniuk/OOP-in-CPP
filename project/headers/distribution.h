#ifndef DISTRIBUTION_H 
#define DISTRIBUTION_H

#include<iostream>
#include<string>
#include<random>
#include<algorithm>


const double pi = 3.14159265358979323846;

int factorial(int k);
int binom(const double n, const int k);

class distribution
{
public:
    virtual bool positive_support()=0; //Checks if distribution is positively supported
    virtual ~distribution() {};
};

#endif