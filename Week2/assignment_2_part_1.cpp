#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>


float calculate_mean(float *marks, int lines_count) 
{
    float sum{0};
    unsigned int i{0};
    for (int i = 0; i <= lines_count-1; i++) {
        sum += marks[i];
    }  
    return sum/lines_count;
}

float calculate_standard_deviation(float *marks, float mean, int lines_count) 
{
    float sum{0};
    unsigned int i{0};
    for (int i = 0; i <= lines_count-1; i++) {
        sum += (marks[i]-mean) * (marks[i]-mean);
    }
    return sqrt(sum/(lines_count-1));
}

float calculate_standard_error_in_the_mean(float standard_deviation, int lines_count) 
{
    return standard_deviation/sqrt(lines_count);
}


int main()
{
    unsigned int i{0}, lines_count{0};
    std::string line, mark_string, code, name;
    float mark, sum, mean, standard_deviation, standard_error_in_the_mean;
    float *marks;

    std::ifstream file;
    file.open("courselist.dat");

    while (std::getline(file , line)) {
        ++lines_count;
    }
    file.clear();
    file.seekg(0);

    marks = new float[lines_count];

    while (std::getline(file , line)) {
        mark_string = line.substr(0, 4);
        float mark = std::stof(mark_string);
        marks[i] = mark;
        code = line.substr(5, 5);
        name = line.substr(13);
        i++;
    }

    file.close();

    mean = calculate_mean(marks, lines_count);
    standard_deviation = calculate_standard_deviation(marks, mean, lines_count);
    standard_error_in_the_mean = calculate_standard_error_in_the_mean(standard_deviation, lines_count);

    std::cout << "The total number of courses is " << lines_count << std::endl; 
    std::cout << "The mean is " << mean << std::endl; 
    std::cout << "The standard deviation is " << standard_deviation << std::endl; 
    std::cout << "The standard error in the mean is " << standard_error_in_the_mean << std::endl; 

    delete[] marks;

    return 0;
}