#ifndef UTILS_BACKUP_H
#define UTILS_BACKUP_H

#include <fstream>
#include <unordered_map>
#include <memory>
#include "distribution.h"
#include "continuous_distribution.h"
#include "discrete_distribution.h"
#include "exponential.h"
#include "gammad.h"
#include "normal.h"
#include "student_t.h"
#include "uniform.h"
#include "binomial.h"
#include "discrete_uniform.h"
#include "poisson.h"


// Concatenates data obtained from different threads:
inline void concatenate_data(std::string file_name, int number_of_threads)
{
    unsigned int number_of_data{0};

    std::string combined_file_path = "./data/" + file_name + ".dat";
    std::cout << "Concatenating data..." << std::endl;
    std::ofstream combined_file;
    combined_file.open(combined_file_path);
    for (int i{0}; i<number_of_threads; i++) {
        std::string file_path = "./data/" + file_name + std::to_string(i) + ".dat";
        std::ifstream file;
        file.open(file_path);
        std::string line;
        std::getline(file, line);
        if (i==0) {
            number_of_data = std::stoi(line.substr(1));
            number_of_data *= number_of_threads;
            combined_file << "#" << std::to_string(number_of_data) << '\n';
        }
        while (std::getline(file, line)) {
            combined_file << line << '\n';
        }
        file.close();
        remove(file_path.c_str()); //Remove file as it's now redundant
    }
    combined_file.close();
}

template<class type>
double Metropolis_sampling(double x, double x_candidate, std::shared_ptr<type> &dist1)
{
    return std::min(1.0,(dist1->pdf(x_candidate))/(dist1->pdf(x)));
}

template<class type>
double Metropolis_posterior(double x, double x_candidate, std::shared_ptr<type> &dist1, std::shared_ptr<type> &dist2)
{
    return std::min(1.0,(dist1->pdf(x_candidate)*dist2->pdf(x_candidate))/(dist1->pdf(x)*dist2->pdf(x)));
}

// Saves the pdf of a distribution to a file:
template<class type>
void save_data(std::string name, std::shared_ptr<type> &dist, double min, double max, int fineness)
{
    std::string file_path = "./data/" + name + ".dat";
    std::ofstream file;
    file.open(file_path);
    for (double i{min*fineness}; i<=max*fineness; i++) {
        file << i/fineness << ' ' << dist->pdf(i/fineness) << std::endl;
    }
    file.close();
}

inline std::shared_ptr<distribution> make_distribution(std::tuple<std::string, float, float> dist) 
{
    std::string name = std::get<0>(dist);
    float a = std::get<1>(dist);
    float b = std::get<2>(dist);
    
    std::unordered_map<std::string,std::shared_ptr<distribution>> map = {
        std::make_pair("exponential", std::make_shared<exponential>(a)),
        std::make_pair("gamma", std::make_shared<gammad>(a, b)),
        std::make_pair("normal", std::make_shared<normal>(a, b)),
        std::make_pair("student_t", std::make_shared<student_t>(a)),
        std::make_pair("uniform", std::make_shared<uniform>(a, b)),

        std::make_pair("binomial", std::make_shared<binomial>(a, b)),
        std::make_pair("discrete_uniform", std::make_shared<discrete_uniform>(a, b)),
        std::make_pair("poisson", std::make_shared<poisson>(a))
    };

    return map[name];
}

inline std::unordered_map<std::string,bool> is_continuous = {
    {"exponential", true},
    {"gamma", true},
    {"normal", true},
    {"student_t", true},
    {"uniform", true},

    {"binomial", false},
    {"discrete_uniform", false},
    {"poisson", false}
};

// Generates histogram from Markov chain data saved to a file
inline void save_histogram(std::string name, int number_of_bins)
{
    std::string file_path = "./data/" + name + ".dat";
    std::ifstream file;
    file.open(file_path);

    int bins[(int)number_of_bins];
    for (int bin{0}; bin<=number_of_bins; bin++) bins[bin]=0;
    float bin_width{0.0};

    // Find minimum and maximum value in file:
    unsigned int a{0}, j{1};
    float b{0}, min{0}, max{0};
    std::string line;

    file >> line;
    unsigned int length = std::stoi(line.substr(1));

    double chain[length+1];
    file >> a >> b;
    min=b; max=b; chain[0]=b;
    while (file >> a >> b) {
        chain[j]=b;
        if (b<min) {min=b;}
        else if (b>max) {max=b;}
        j++;
    }

    bin_width = (max-min)/number_of_bins;
    std::sort(chain, chain+length+1);

    int bin{0};
    int i{0}; 
    while (i<=length) {
        if (chain[i] <= bin*bin_width+min) {
            bins[bin]++;
            i++;
        } else {bin++;};
    }
    file.close();

    std::string histogram_path = "./data/" + name + "_histogram.dat";
    std::ofstream histogram;
    histogram.open(histogram_path);

    for (int bin{0}; bin<=number_of_bins; bin++) { 
        histogram << bin*bin_width+min << ' ' << (float)bins[bin]/length << std::endl;
	}
    histogram.close();
}

#endif