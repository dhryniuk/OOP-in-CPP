#include "headers/discrete_uniform.h"


bool discrete_uniform::positive_support() 
{
    return false;
}
discrete_uniform::discrete_uniform(int a, int b) : min{a}, max{b} 
{
    std::uniform_int_distribution<int> dis{min,max};
};
discrete_uniform::~discrete_uniform() {};
int discrete_uniform::sample(std::mt19937 generator)
{
    return dis(generator);
}
double discrete_uniform::pdf(int x)
{
    if (x>=min && x<=max) {
        return 1/(max-min+1);
    } else return 0;
}