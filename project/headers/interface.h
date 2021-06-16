#ifndef INTERFACE_H
#define INTERFACE_H

#include <thread>
#include "markov_chain.h"
#include "gnu_pipe.h"


std::tuple<std::string, float, float> set_distribution(std::string message);
std::tuple<std::string, float, float> set_target();
std::tuple<std::string, float, float> set_proposal();
std::tuple<std::string, float, float> set_prior();
std::tuple<std::string, float, float> set_likelihood();
void sample();
void posterior();
void histogram();
void plot();
void plot_mc();

#endif