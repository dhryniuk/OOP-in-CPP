#include "headers\interface.h"


std::tuple<std::string, float, float> set_distribution(std::string message) {
    std::string input;
    float alpha{}, beta{};
    bool recognized_input{true};
    
    do {
        std::cout << message;
        try {
            std::cin >> input;
            if (input=="gamma") {
                recognized_input = true;
                while (alpha<=0) {
                    std::cout << "Set shape parameter: ";
                    try {
                        std::cin >> alpha;
                        if (alpha<=0) {
                            throw "ERROR: Shape parameter must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
                while (beta<=0) {
                    std::cout << "Set rate parameter: ";
                    try {
                        std::cin >> beta;
                        if (beta<=0) {
                            throw "ERROR: Rate parameter must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="normal") {
                recognized_input = true;
                std::cout << "Set mean: ";
                std::cin >> alpha;
                while (beta<=0) {
                    std::cout << "Set standard deviation: ";
                    try {
                        std::cin >> beta;
                        if (beta<=0) {
                            throw "ERROR: Standard deviation must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="exponential") {
                recognized_input = true;
                while (alpha<=0) {
                    std::cout << "Set rate parameter: ";
                    try {
                        std::cin >> alpha;
                        if (alpha<=0) {
                            throw "ERROR: Rate parameter must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="uniform") {
                recognized_input = true;
                while (beta<=alpha) {
                    std::cout << "Set minimum bound: ";
                    std::cin >> alpha;
                    std::cout << "Set maximum bound: ";
                    try {
                        std::cin >> beta;
                        if (beta<=alpha) {
                            throw "ERROR: The maximum bound must be greater than the minimum bound.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="student_t") {
                recognized_input = true;
                do {
                    try {
                        std::cout << "Set number of degrees of freedom: ";
                        std::cin >> alpha;
                        if (alpha<=0 || ceil(alpha)!=alpha) {
                            throw "ERROR: the number of degrees of freedom must be a positive integer.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                } while (alpha<=0 || ceil(alpha)!=alpha);
            } else if (input=="cauchy") {
                recognized_input = true;
                std::cout << "Set location: ";
                std::cin >> alpha;
                while (beta<=0) {
                    std::cout << "Set scale parameter: ";
                    try {
                        std::cin >> beta;
                        if (beta<=0) {
                            throw "ERROR: Scale parameter must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="poisson") {
                recognized_input = true;
                while (alpha<=0) {
                    std::cout << "Set rate parameter: ";
                    try {
                        std::cin >> alpha;
                        if (alpha<=0) {
                            throw "ERROR: Rate parameter must be positive.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="discrete_uniform") {
                recognized_input = true;
                while (beta<=alpha) {
                    std::cout << "Set minimum bound: ";
                    std::cin >> alpha;
                    std::cout << "Set maximum bound: ";
                    try {
                        std::cin >> beta;
                        if (beta<=alpha) {
                            throw "ERROR: The maximum bound must be greater than the minimum bound.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else if (input=="binomial") {
                recognized_input = true;
                while (alpha<=0) {
                    std::cout << "Set number of trials: ";
                    try {
                        std::cin >> alpha;
                        if (alpha<=0 || std::floor(alpha)!=alpha) {
                            throw "ERROR: The number of trials must be a positive integer.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
                while (beta<=0 || beta>1) {
                    std::cout << "Set success rate of each trial: ";
                    try {
                        std::cin >> beta;
                        if (beta<=0 || beta>1) {
                            throw "ERROR: The success rate must be a number between 0 and 1.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << msg << std::endl;
                    }
                }
            } else {
                throw "ERROR: Unrecognized distribution, please try again.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
            recognized_input=false;
        }
    } while (recognized_input==false);
    return std::make_tuple(input, alpha, beta);
}

std::tuple<std::string, float, float> set_target() {
    return set_distribution("Set target distribution: ");
}

std::tuple<std::string, float, float> set_proposal() {
    return set_distribution("Set proposal distribution: ");
}

std::tuple<std::string, float, float> set_prior() {
    return set_distribution("Set prior distribution: ");
}

std::tuple<std::string, float, float> set_likelihood() {
    return set_distribution("Set likelihood distribution: ");
}

void sample() 
{
    std::tuple<std::string, float, float> target, proposal;
    int number_of_samples{1}, decorrelation{1};
    short int number_of_threads{0}, thread_number{0};
    std::string file_name;
    std::vector<markov_chain> chains;
    std::vector<std::thread> workers;

    target = set_target();
    proposal = set_proposal();

    do {
        std::cout << "Set number of trials: ";
        try {
            std::cin >> number_of_samples;
            if (number_of_samples <= 0) {
                throw "ERROR: The number of samples must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (number_of_samples <= 0);

    do {
        std::cout << "Set decorrelation: ";
        try {
            std::cin >> decorrelation;
            if (decorrelation <= 0) {
                throw "ERROR: The decorrelation must be a positive integer.";
            }
            if (number_of_samples%decorrelation != 0) {
                throw "ERROR: The decorrelation must be a divisor of the number of samples.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (decorrelation <= 0 || number_of_samples%decorrelation != 0);

    do {
        std::cout << "Set number of threads: ";
        try {
            std::cin >> number_of_threads;
            if (number_of_threads <= 0) {
                throw "ERROR: The number of threads must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (number_of_threads <= 0);

    std::cout << "Set file name (w/o extension): ";
    std::cin >> file_name;

    chains.resize(number_of_threads, markov_chain(number_of_samples, decorrelation, file_name));

    for (int i = 0; i < number_of_threads; i++) { 
        workers.push_back(std::thread(&markov_chain::run_sampling, &chains[i], 
        i, target, proposal));
    }
    // Join threads via lambda expression:
    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });

    find_total_acceptance_rate(chains, number_of_threads);
    concatenate_data(file_name, number_of_threads);
    std::cout << "Done\n" << std::endl;
}

void posterior() 
{
    std::tuple<std::string, float, float> prior, likelihood, proposal;
    unsigned int number_of_samples{1}, decorrelation{1}, number_of_threads{0}, thread_number{0};
    std::string file_name;
    std::vector<std::thread> workers;
    std::vector<markov_chain> chains;

    prior = set_prior();
    likelihood = set_likelihood();
    proposal = set_proposal();

    do {
        std::cout << "Set number of trials: ";
        try {
            std::cin >> number_of_samples;
            if (number_of_samples <= 0) {
                throw "ERROR: The number of samples must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (number_of_samples <= 0);

    do {
        std::cout << "Set decorrelation: ";
        try {
            std::cin >> decorrelation;
            if (decorrelation <= 0) {
                throw "ERROR: The decorrelation must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (decorrelation <= 0);

    do {
        std::cout << "Set number of threads: ";
        try {
            std::cin >> number_of_threads;
            if (number_of_threads <= 0) {
                throw "ERROR: The number of threads must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (number_of_threads <= 0);

    std::cout << "Set file name (w/o extension): ";
    std::cin >> file_name;

    chains.resize(number_of_threads, markov_chain(number_of_samples, decorrelation, file_name));
    for (int i = 0; i < number_of_threads; i++) { 
        workers.push_back(std::thread(&markov_chain::run_posterior, &chains[i], 
        i, prior, likelihood, proposal));
    }
    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });

    find_total_acceptance_rate(chains, number_of_threads);
    concatenate_data(file_name, number_of_threads);
    std::cout << "Done\n" << std::endl;
}

void histogram()
{
    int number_of_bins{1};
    float min{0}, max{0};
    std::string name, range;

    std::cout << "Select file name (w/o extension): ";
    std::cin >> name;

    do {
        try {
            std::cout << "Set number of bins: ";
            std::cin >> number_of_bins;
            if (number_of_bins<=0) {
                throw "ERROR: The number of bins must be a positive integer.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (number_of_bins<=0);
    save_histogram(name, number_of_bins);

    do {
        try{
            std::cout << "Set x-range [auto/custom]: ";
            std::cin >> range;
            if (range != "auto" && range != "custom") {
                throw "ERROR: Unrecognized command. Please try again.";
            }
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    } while (range != "auto" && range != "custom");

    if (range=="auto") {
        plot_histogram((char*)name.c_str(), 0, 0);
    } else {
        do {
            std::cout << "Set minimum bound: ";
            std::cin >> min;
            std::cout << "Set maximum bound: ";
            try {
                std::cin >> max;
                if (max<=min) {
                    throw "ERROR: The maximum bound must be greater than the minimum bound.";
                }
            }
            catch (const char* msg) {
                std::cout << msg << std::endl;
            }
        } while (max<=min);
        plot_histogram((char*)name.c_str(), min, max);
    }
    std::cout << "Done\n" << std::endl;
}

void plot()
{
    float min{}, max{};
    int fineness{10000}; // determines how fine/coarse the plot will be
    std::string file_name;

    std::tuple<std::string, float, float> dist = set_distribution( "Set distribution: ");
    std::cout << "Set file name (w/o extension): ";
    std::cin >> file_name;
    std::cout << "Set minimum x: ";
    std::cin >> min;
    std::cout << "Set maximum x: ";
    std::cin >> max;
    std::shared_ptr<distribution> base_dist = make_distribution(dist);
    if (is_continuous[std::get<0>(dist)] == true) {
        auto dist = std::dynamic_pointer_cast<continuous_distribution>(base_dist);
        save_data(file_name, dist, min, max, fineness);
    } else {
        auto dist = std::dynamic_pointer_cast<discrete_distribution>(base_dist);
        save_data(file_name, dist, min, max, fineness);
    }
    plot_function((char*)file_name.c_str());
    std::cout << "Done\n" << std::endl;
}

void plot_mc()
{
    std::string file_name;

    std::cout << "Select file name (w/o extension): ";
    std::cin >> file_name;
    plot_function((char*)file_name.c_str());
    std::cout << "Done\n" << std::endl;
}