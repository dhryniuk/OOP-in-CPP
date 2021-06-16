#include "headers/uniform.h"


bool uniform::positive_support() 
{
    return false;
}
uniform::uniform(double a, double b) : min{a}, max{b} 
{
    std::uniform_real_distribution<double> dis{min,max};
};
uniform::~uniform() {};
double uniform::sample(std::mt19937 generator)
{
    return dis(generator);
}
double uniform::pdf(double x)
{
    if (x>min && x<max) {
        return 1/(max-min);
    } else return 0;
}