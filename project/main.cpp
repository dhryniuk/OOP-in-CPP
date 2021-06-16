// Dawid Hryniuk
// Last upadated: 23/05/2021


#include "headers/interface.h"


int main()
{  
    std::string user_input;
    bool exit_flag{false};

    std::cout << "This program can plot and sample various probability "
        "distributions by means of the Metropolis algorithm with "
        "multithreading functionality.\n";
    std::cout << "The available distributions are:\n"
        "-exponential\n-gamma\n-normal\n-student_t\n-uniform\n"
        "-binomial\n-discrete_uniform\n-poisson\n\n";
    std::cout << "Please type in any of the following commands:\n"
        "\"plot\" - to plot a probability density function of a chosen distribution\n"
        "\"sample\" - to sample a chosen distribution\n"
        "\"posterior\" - to sample the posterior distribution of chosen prior "
        "and likelihood distributions\n"
        "\"histogram\" - to histogram a previously sampled distribution\n"
        "\"plot_mc\" - to plot the evolution of the Markov chain from a previously "
        "sampled distribution\n"
        "\"exit\" - to close the program\n\n";

    do {
        try {
            std::cin >> user_input;
            if (user_input=="plot") {
                plot();
            } else if (user_input=="sample") {
                sample();
            } else if (user_input=="posterior") {
                posterior();
            } else if (user_input=="histogram") {
                histogram();
            } else if (user_input=="plot_mc") {
                plot_mc();
            } else if (user_input=="exit") {
                exit_flag=true;
            } else {
                throw "ERROR: Unrecognized command. Please try again.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (exit_flag==false);

    return 0;
}