#include "headers/gammad.h"


bool gammad::positive_support() 
{
    return true;
}
gammad::gammad(double alpha_in, double beta_in) : alpha{alpha_in}, beta{beta_in} 
{
    std::gamma_distribution<double> dis{alpha,beta};
};
gammad::~gammad() {};
double gammad::sample(std::mt19937 generator)
{
    return dis(generator);
}
double gammad::pdf(double x)
{
    if (x>=0) {
        return 1.0/(tgamma(alpha)*pow(beta,alpha)) * pow(x,alpha-1) * exp(-x/beta);
    } else return 0;
}