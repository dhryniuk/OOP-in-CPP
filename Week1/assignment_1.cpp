#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>

float energy_level (int atomic_number, int quantum_number) 
{
    float energy;
    energy = -13.6 * pow(atomic_number,2) * 1/pow(quantum_number,2);
    return  energy;
}

int main()
{
    bool correct_input;
    std::string redo_calculation, units;
    float atomic_number, initial_quantum_number, final_quantum_number, energy_of_transition;

    do {
        do {
            std::cout << "Enter atomic number Z: ";
            std::cin >> atomic_number;
            if (floor(atomic_number) != atomic_number || atomic_number <= 0) {
                correct_input = false;
                std::cout << "Atomic number must be a positive integer number." << std::endl;
            }
            else {
                correct_input = true;
            }
        } while (correct_input == false);

        do {
            std::cout << "Enter initial quantum number n_i: ";
            std::cin >> initial_quantum_number;
            if (floor(initial_quantum_number) != initial_quantum_number || initial_quantum_number <= 1) {
                correct_input = false;
                std::cout << "Quantum number must be a positive integer number greater than 1." << std::endl;
            }
            else {
                correct_input = true;
            }
        } while (correct_input == false);   

        do {
            std::cout << "Enter final quantum number n_f: ";
            std::cin >> final_quantum_number;
            if (floor(final_quantum_number) != final_quantum_number || final_quantum_number < 1) {
                correct_input = false;
                std::cout << "Initial quantum number must be a positive integer number." << std::endl;
            }   
            else if (final_quantum_number >= initial_quantum_number) {
                correct_input = false;
                std::cout << "Final quantum number must be smaller than initial quantum number." << std::endl;
            }
            else {
                correct_input = true;
            }
        } while (correct_input == false);  

        energy_of_transition = energy_level(atomic_number,initial_quantum_number) - energy_level(atomic_number,final_quantum_number);
        
        do {
            std::cout << "Should the energy of the transition be printed out in J or eV? [J/eV] ";
            std::cin >> units;
            if (units == "eV") {
                correct_input = true;
            }
            else if (units == "J") {
                correct_input = true;
                energy_of_transition = energy_of_transition * 1.602176634e-19;
                continue;
            }
            else {
                correct_input = false;
                std::cout << "Incorrect input." << std::endl;    
            }
        } while (correct_input == false);

        std::cout << "The energy of the transition for Z = " << atomic_number << " from n_i = " << initial_quantum_number << " to n_f = " 
        << final_quantum_number << " is " << std::setprecision(3) << energy_of_transition << " " << units << "." << std::endl;     
        
        do {
            std::cout << "Do you want to perform another calculation? [y/n] "; 
            std::cin >> redo_calculation;
            if (redo_calculation == "y" || redo_calculation == "n") {
                correct_input = true;
            }
            else {
                correct_input = false;
                std::cout << "Incorrect input." << std::endl; 
            }
        } while (redo_calculation != "y" && redo_calculation != "n");
    } while (redo_calculation == "y");
}