#include "headers/distribution.h"

// Calculates the factorial of k:
int factorial (int k)
{
    int product{1};
    for (int i{1}; i<=k; i++) {
        product *= i;
    }
    
    return product;
}

// Recursive calculation of binomial coefficient:
int binom(const double n, const int k)
{
    double sum;

    if (n == 0 || k == 0) {
        sum = 1;
    } else {
        sum = binom(n-1,k-1)+binom(n-1,k);
    }
    if ((n== 1 && k== 0) || (n== 1 && k== 1)) {
        sum = 1;
    }
    if (k > n) {
        sum = 0;
    }

    return sum;
}