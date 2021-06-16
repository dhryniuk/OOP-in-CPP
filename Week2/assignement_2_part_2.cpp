#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


float calculate_mean(std::vector<float> marks) 
{
    float sum{0};
    unsigned int i{0};
    for (int i = 0; i <= marks.size()-1; i++) {
        sum += marks[i];
    }  
    return sum/marks.size();
}

float calculate_standard_deviation(std::vector<float> marks, float mean) 
{
    float sum{0};
    unsigned int i{0};
    for (int i = 0; i <= marks.size()-1; i++) {
        sum += (marks[i]-mean) * (marks[i]-mean);
    }
    return sqrt(sum/(marks.size()-1));
}

int find_first_digit(int n) 
{ 
    while (n >= 10)  
        n /= 10; 
    return n; 
}

bool sort_by_second(const std::tuple<float, int, std::string>& a, const std::tuple<float, int, std::string>& b) 
{ 
    return (std::get<1>(a) < std::get<1>(b)); 
}

bool sort_by_third(const std::tuple<float, int, std::string>& a, const std::tuple<float, int, std::string>& b) 
{ 
    return (std::get<2>(a) < std::get<2>(b)); 
}


int main()
{
    char user_input;
    unsigned int lines_count{0}, code, year_group;
    float mark, mean, standard_deviation;
    std::string line, expression, mark_string, name, stringstream_string;
    std::stringstream undelimited_stringstream, delimited_stringstream;
    std::vector<float> marks_vector;
    std::vector<std::tuple<float, int, std::string>> data_vector;

    std::ifstream file;
    file.open("courselist.dat");
    while (std::getline(file, line)) {
        ++lines_count;
    }
    file.clear();
    file.seekg(0);

    while (getline(file, line)) {
        std::stringstream undelimited_stringstream(line);
        while (getline(undelimited_stringstream, expression, ' ')) {
            if (expression.find('.') != std::string::npos) {
                mark_string = expression;
            }
            else if (isdigit(expression[0])) {
                code = std::stoi(expression);
                delimited_stringstream << code << ' ';
            }
            else delimited_stringstream << expression << ' ';
        }
        mark = std::stof(mark_string);
        delimited_stringstream >> code;
        stringstream_string = delimited_stringstream.str();
        name = stringstream_string.substr(5);

        data_vector.push_back(std::make_tuple(mark, code, name));

        delimited_stringstream.str("");
        delimited_stringstream.clear();
    }
    file.close();

    for (std::vector<std::tuple<float, int, std::string>>::iterator i = data_vector.begin(); i != data_vector.end(); ++i) {
        std::cout << std::get<0>(*i) << ' ' << std::get<1>(*i) << std::get<2>(*i) << std::endl;
    }

    std::cout << "Filter the courses by year group? [y/n] ";
    std::cin >> user_input;
    if (user_input == 'y') {
        std::cout << "Specify year group [1/2/3/4] ";
        std::cin >> user_input;
        year_group = user_input - '0';

        for (std::vector<std::tuple<float, int, std::string>>::iterator it = data_vector.begin(); it != data_vector.end(); ++it) {
            if (find_first_digit(std::get<1>(*it)) == year_group) {
                std::cout << std::get<0>(*it) << ' ' << std::get<1>(*it) << std::get<2>(*it) << std::endl;
                mark = std::get<0>(*it);
                marks_vector.push_back(mark);
            }
        }
        mean = calculate_mean(marks_vector);
        standard_deviation = calculate_standard_deviation(marks_vector, mean);

        std::cout << "The mean mark is " << std::setprecision(3) << mean << " with standard deviation " 
        << std::setprecision(2) << standard_deviation << '.' << std::endl;
    }

    std::cout << "Sort the courses? [y/n] ";
    std::cin >> user_input;
    if (user_input == 'y') {
        std::cout << "Sort by grade/code/name? [g/c/n] ";
        std::cin >> user_input;

        if (user_input == 'g') {
            std::sort(std::begin(data_vector), std::end(data_vector));
            for (std::vector<std::tuple<float, int, std::string>>::iterator it = data_vector.begin(); it != data_vector.end(); ++it) {
                std::cout << std::setprecision(3) << std::get<0>(*it) << ' ' << std::get<1>(*it) << std::get<2>(*it) << std::endl;
            }
        }
        
        if (user_input == 'c') {
            std::sort(std::begin(data_vector), std::end(data_vector), sort_by_second);
            for (std::vector<std::tuple<float, int, std::string>>::iterator it = data_vector.begin(); it != data_vector.end(); ++it) {
                std::cout << std::setprecision(3) << std::get<0>(*it) << ' ' << std::get<1>(*it) << std::get<2>(*it) << std::endl;
            }
        }
        
        if (user_input == 'n') {
            std::sort(std::begin(data_vector), std::end(data_vector), sort_by_third);
            for (std::vector<std::tuple<float, int, std::string>>::iterator it = data_vector.begin(); it != data_vector.end(); ++it) {
                std::cout << std::setprecision(3) << std::get<0>(*it) << ' ' << std::get<1>(*it) << std::get<2>(*it) << std::endl;
            }
        }
    }

    return 0;
}