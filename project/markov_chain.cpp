#include "headers/markov_chain.h"


unsigned short int markov_chain::number_of_chains{0};

markov_chain::markov_chain(unsigned int l, unsigned int d, std::string n)
{
    length = l;
    decorrelation = d;
    name = n;
    number_of_chains++;
}

markov_chain::~markov_chain() 
{
    number_of_chains--;
}

void markov_chain::run_sampling(int thread_number,
    std::tuple<std::string, float, float> target_tuple,
    std::tuple<std::string, float, float> proposal_tuple) 
{
    std::string file_path = "./data/" + name + std::to_string(thread_number) + ".dat";
    std::ofstream file;
    file.open(file_path);
    file << '#' << length/decorrelation << std::endl;

    double x{}, x_candidate{};
    double alpha{}, beta{};

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Mersenne twister random number engine
    std::unique_ptr<continuous_distribution> random_uniform(new uniform{0.0,1.0}); 

    // Set base pointers to chosen probability distributions:
    auto base_pointer_target = make_distribution(target_tuple); 
    auto base_pointer_proposal = make_distribution(proposal_tuple);

    // Check if positively supported:
    bool positive_support = base_pointer_target->positive_support();

    std::string message = "thread " + std::to_string(thread_number+1) + " started...\n";
    std::cout << message;

    if (is_continuous[std::get<0>(target_tuple)] == true) {
        // Specialise pointers: 
        auto derived_pointer_target = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_target);
        auto derived_pointer_proposal = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_proposal);

        x = derived_pointer_target->sample(gen); //sample initial state from target distribution
        if (positive_support) {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (x_candidate>0  &&  (random_uniform->sample(gen) <= 
                Metropolis_sampling(x, x_candidate, derived_pointer_target)) ) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                }
            } 
        } else {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen); 
                if (random_uniform->sample(gen) <= 
                Metropolis_sampling(x, x_candidate, derived_pointer_target)) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                } 
            }
        }
    } else {
        // Specialise pointers: 
        auto derived_pointer_target = 
        std::dynamic_pointer_cast<discrete_distribution>(base_pointer_target);
        auto derived_pointer_proposal = 
        std::dynamic_pointer_cast<discrete_distribution>(base_pointer_proposal);

        x = derived_pointer_target->sample(gen); //sample initial state from target distribution
        if (positive_support) {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (x_candidate>=0 && x_candidate<=4*std::get<1>(target_tuple) 
                && (random_uniform->sample(gen) <= 
                Metropolis_sampling(x, x_candidate, derived_pointer_target)) ) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                }
            } 
        } else {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (x_candidate<=4*std::get<1>(target_tuple) && 
                random_uniform->sample(gen) <= 
                Metropolis_sampling(x, x_candidate, derived_pointer_target)) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                } 
            }
        }
    }
    file.close();
}

void markov_chain::run_posterior(int thread_number,
    std::tuple<std::string, float, float> prior_tuple,
    std::tuple<std::string, float, float> likelihood_tuple,
    std::tuple<std::string, float, float> proposal_tuple) 
{
    std::string file_path = "./data/" + name + std::to_string(thread_number) + ".dat";
    std::ofstream file;
    file.open(file_path);
    file << '#' << length/decorrelation << std::endl;

    double x{}, x_candidate{};
    double alpha{}, beta{};

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Mersenne twister random number engine
    std::unique_ptr<continuous_distribution> random_uniform(new uniform{0.0,1.0}); 

    // Set base pointers to chosen probability distributions:
    auto base_pointer_prior = make_distribution(prior_tuple); 
    auto base_pointer_likelihood = make_distribution(likelihood_tuple); 
    auto base_pointer_proposal = make_distribution(proposal_tuple);

    // Check if positively supported:
    bool positive_support = base_pointer_likelihood->positive_support();

    std::string message = "thread " + std::to_string(thread_number+1) + " started...\n";
    std::cout << message;

    if (is_continuous[std::get<0>(likelihood_tuple)] == true) {
        // Specialise pointers: 
        auto derived_pointer_prior = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_prior);
        auto derived_pointer_likelihood = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_likelihood);
        auto derived_pointer_proposal = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_proposal);

        x = derived_pointer_prior->sample(gen); //sample initial state from prior distribution
        if (positive_support) {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (x_candidate>0  &&  (random_uniform->sample(gen) <= 
                Metropolis_posterior(x, x_candidate, derived_pointer_prior, 
                derived_pointer_likelihood)) ) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                }
            } 
        } else {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen); 
                if (random_uniform->sample(gen) <= 
                Metropolis_posterior(x, x_candidate, derived_pointer_prior, 
                derived_pointer_likelihood)) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                } 
            }
        }
    } else {
        // Specialise pointers: 
        auto derived_pointer_prior = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_prior);
        auto derived_pointer_likelihood = 
        std::dynamic_pointer_cast<continuous_distribution>(base_pointer_likelihood);
        auto derived_pointer_proposal = 
        std::dynamic_pointer_cast<discrete_distribution>(base_pointer_proposal);

        x = derived_pointer_prior->sample(gen); //sample initial state from prior distribution
        if (positive_support) {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (x_candidate>0  &&  (random_uniform->sample(gen) <= 
                Metropolis_posterior(x, x_candidate, derived_pointer_prior, 
                derived_pointer_likelihood)) ) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                }
            } 
        } else {
            for (int i{0}; i<length; i++) {
                std::mt19937 gen(rd());
                x_candidate = x+derived_pointer_proposal->sample(gen);
                if (random_uniform->sample(gen) <= 
                Metropolis_posterior(x, x_candidate, derived_pointer_prior, 
                derived_pointer_likelihood)) {
                    x = x_candidate;
                    acceptance++;
                }
                if (i%decorrelation==0) {
                    file << i/decorrelation << ' ' << x << std::endl;
                } 
            }
        }
    }
    file.close();
}

// Claculates total acceptance rate across seperate Markov chains:
void find_total_acceptance_rate(std::vector<markov_chain> chains, int number_of_threads)
{
    int length{0}, acceptance{0};
    for (int i = 0; i < number_of_threads; i++) {
        length += chains[i].length;
        acceptance += chains[i].acceptance;
    }
    std::cout << "Metropolis acceptance: " << acceptance << '/' << length 
    << " [" << (float)acceptance/length*100 << "%]" << std::endl;
    if ((float)acceptance/length > 0.8) {
        std::cout << "WARNING: Metropolis acceptance rate is too high. Consider adjusting proposal distribution." << std::endl;
    }
    if ((float)acceptance/length < 0.2) {
        std::cout << "WARNING: Metropolis acceptance rate is too low. Consider adjusting proposal distribution." << std::endl;
    }
}