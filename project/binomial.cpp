#include "headers/binomial.h"


bool binomial::positive_support() 
{
    return true;
}
binomial::binomial(int number, float success) : n{number}, p{success} 
{
    std::binomial_distribution<int> dis{n,p};
};
binomial::~binomial() {};
int binomial::sample(std::mt19937 generator)
{
    return dis(generator);
}
double binomial::pdf(int x)
{
    return binom(n,x)*pow(p,x)*pow(1-p,n-x);
}