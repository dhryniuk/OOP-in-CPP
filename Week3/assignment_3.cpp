#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
    std::string hubble_type;
    double redshift;
    double total_mass;
    double stellar_mass_fraction;
    std::vector<galaxy> satellites;

public:
    galaxy() 
    {
        hubble_type = "SBb";
        redshift = 0.000368;
        total_mass = 450e6;
        stellar_mass_fraction = 0.01;
    }

    galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction) :
    hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass}, stellar_mass_fraction{galaxy_stellar_mass_fraction}
    {}

    ~galaxy() {}

    double stellar_mass() 
    { 
        return stellar_mass_fraction * total_mass;
    }

    void change_type(std::string new_type) 
    { 
        hubble_type = new_type;
        return;
    }

    void print_data();

    void add_satellite(std::string hubble_type, double redshift, double total_mass, double stellar_mass_fraction) 
    {
        satellites.push_back(galaxy(hubble_type, redshift, total_mass, stellar_mass_fraction));
        return;
    }
};

void galaxy::print_data ()
{
    std::cout << "Galaxy: [Hubble type, redshift, total mass, stellar mass fraction, number of satellites] = [" << hubble_type << "," 
    << redshift << "," << total_mass << "," << stellar_mass_fraction << "," << satellites.size() << "]" <<std::endl;
    if (satellites.size() != 0) {
        for (int i = 0; i < satellites.size(); i++) {
            std::cout << "Satellite: [Hubble type, redshift, total mass, stellar mass fraction] = [" << satellites[i].hubble_type << "," 
            << satellites[i].redshift << "," << satellites[i].total_mass << "," << satellites[i].stellar_mass_fraction << "]" <<std::endl;       
        }
    }
    return;
}


int main()
{
    std::vector<galaxy> galaxy_data;

    galaxy_data.push_back(galaxy());
    galaxy_data.push_back(galaxy("SBb", -0.001001, 1.5e12, 0.01));
    galaxy_data[0].add_satellite("E2", -0.000670, 3e9, 0.01);
    galaxy_data[0].add_satellite("E6", -0.000804, 9.3e9, 0.01);

    for(auto it = galaxy_data.begin(); it < galaxy_data.end(); ++it) {
        it->print_data();
        std::cout << "The stellar mass of the galaxy is " << it->stellar_mass() << " solar masses." << std::endl;
    }
    galaxy_data[1].change_type("SBc");
    galaxy_data[1].print_data();

    return 0;
}