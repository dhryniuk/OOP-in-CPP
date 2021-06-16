#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include "utils.h"


class markov_chain 
{
public:
    std::string name;
    // decorrelation sets the period between sampled Markov chain states being recorded
    unsigned int length{0}, decorrelation{0}, acceptance{0};
    static unsigned short int number_of_chains;
    float min{0}, max{0};

    markov_chain(unsigned int length, unsigned int d, std::string name);
    ~markov_chain();

    void sort();
    void save_markov_chain(std::string file_name);
    // Constructs the Markov chain using the Metropolis algorithm:
    void run_sampling(int thread_number,
    std::tuple<std::string, float, float> target_tuple,
    std::tuple<std::string, float, float> proposal_tuple);
    // Constructs the Markov chain using the Metropolis algorithm for a posterior distribution:
    void run_posterior(int thread_number,
    std::tuple<std::string, float, float> prior_tuple,
    std::tuple<std::string, float, float> likelihood_tuple,
    std::tuple<std::string, float, float> proposal_tuple);
};

void find_total_acceptance_rate(std::vector<markov_chain> chains, int number_of_threads);

#endif