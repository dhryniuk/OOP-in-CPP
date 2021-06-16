#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>



int main()
{
    unsigned int i{0}, lines_count{0};
    std::string line, grade, code, name;
    float mark, sum, mean, standard_deviation, standard_error_in_the_mean;

    std::ifstream file;
    file.open("courselist.dat");

    while (std::getline(file , line)) {
        ++lines_count;
    }

    // Reset getline pointer:
    file.clear();
    file.seekg(0);

    std::stringstream ss;
    std::vector<std::string> list;
    while (std::getline(file , line)) {
        ss << line;
        list.push_back(ss.str());
        ss.str("");
        ss.clear();
    }

    file.close();

    std::cout << ss.str();

    std::cout << list[2] << std::endl;

    std::vector<std::string>::iterator vector_iterator;
    std::vector<std::string>::iterator vector_begin{list.begin()};
    std::vector<std::string>::iterator vector_end{list.end()};
    for( vector_iterator = vector_begin ;vector_iterator < vector_end ;++ vector_iterator )
        std::cout << *vector_iterator <<std::endl;


    std::vector<float> marks;
    for( vector_iterator = vector_begin ;vector_iterator < vector_end ;++ vector_iterator ) {
        std::string expectsString(*vector_iterator);
        if (expectsString.substr(5,1) == "2") {
            std::cout << *vector_iterator <<std::endl;
            grade = expectsString.substr (0, 4);
            float mark = std::stof(grade);
            marks.push_back(mark);
            std::cout << mark << " " << marks.size() << std::endl;
            i++;
        }
    }
    
    sum = 0;
    for (int i = 0; i <= marks.size(); i++) {
        sum += marks[i];
        std::cout << sum << std::endl;
    }  
    mean = sum/marks.size();

    sum = 0;
    for (int i = 0; i <= marks.size(); i++) {
        sum += (marks[i]-mean) * (marks[i]-mean);
    }
    standard_deviation = sqrt(sum/marks.size());
    standard_error_in_the_mean = standard_deviation/marks.size();

    printf("The mean is %f \nThe standard deviation is %f \nThe standard error in the mean is %f", 
    mean, standard_deviation, standard_error_in_the_mean);

    std::sort(list.begin(), list.end());
    for( vector_iterator = vector_begin ;vector_iterator < vector_end ;++ vector_iterator )
        std::cout << *vector_iterator <<std::endl;

    std::sort(std::begin(list), std::end(list), [](std::string const& a, std::string const& b){
        return std::lexicographical_compare(std::begin(a) + 5, std::end(a), std::begin(b) + 5, std::end(b));
    }
    );

    for( vector_iterator = vector_begin ;vector_iterator < vector_end ;++ vector_iterator )
        std::cout << *vector_iterator <<std::endl;

    std::sort(std::begin(list), std::end(list), [](std::string const& a, std::string const& b){
        return std::lexicographical_compare(std::begin(a) + 13, std::end(a), std::begin(b) + 13, std::end(b));
    }
    );

    for( vector_iterator = vector_begin ;vector_iterator < vector_end ;++ vector_iterator )
        std::cout << *vector_iterator <<std::endl;


return 0;
}