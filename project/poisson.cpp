#include "headers/poisson.h"


bool poisson::positive_support() 
{
    return true;
}
poisson::poisson(double lambda_in) : lambda{lambda_in} 
{
    std::poisson_distribution<int> dis{lambda};
};
poisson::~poisson() {};
int poisson::sample(std::mt19937 generator)
{
    return dis(generator);
}
double poisson::pdf(int k)
{
    if (k>=0) return pow(lambda,k)*exp(-lambda)/factorial(k);
    else return 0;
}