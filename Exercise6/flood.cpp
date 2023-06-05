#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

/**
 * MODE 1 for Island scenario
 * MODE 2 for Hillside with depression scenario
*/
const static int MODE = 1;

const static double dt = 0.1;
const static double dx = 10.0;
const static double length = 1000.0;
const static double g = 9.81;
const static double h_min = 0.1;
const static double eps = 0.05; // for shapiro filter

std::vector<double> h_zero;
std::vector<double> h;
std::vector<double> eta;
std::vector<double> _eta;
std::vector<double> u;
std::vector<bool> wet;

bool equal(const double& a, const double& b)
{
    double relative_difference_factor = 0.0001;
    double greater_magnitude = std::max(std::abs(a), std::abs(b));
    return std::abs(a - b) < relative_difference_factor * greater_magnitude;
}

void parse(std::ifstream& infile, std::vector<double>& array)
{
    std::string delimiter = ",";
    std::string values = "";
    while(std::getline(infile, values))
    {
        if(values.empty()) break;
        std::stringstream ss(values);
        std::string tmp;
        while(std::getline(ss, tmp, ','))
        {
            double val = std::stod(tmp);
            array.push_back(val);
        }
    }
}

void Load(const std::string& path)
{
    std::cout << "Load data: " << path << std::endl;
    std::ifstream infile(path);
    std::string name = "";
    while(std::getline(infile, name))
    {
        if(name == "hzero")
        {
            parse(infile, h_zero);
        }
        if (name == "eta")
        {
            parse(infile, eta);
        }
    }
}

void Init()
{
    std::string data_path = "";
    if(MODE == 1)
        data_path = ".\\input\\scenario1.dat";
    if(MODE == 2)
        data_path = ".\\input\\scenario2.dat";
    Load(data_path);

    std::size_t n = h_zero.size();

    for(int k = 0; k < n; k++)
    {
        _eta[k] = eta[k];
        h[k] = h_zero[k] + eta[k];
        // wet = 0 defines dry grid cells
        // wet = 1 defines wet grid cells
        wet[k] = h[k] < h_min ? 0 : 1;
        u[k] = 0.0;
    }
}

void Dynamic(double time, std::vector<std::vector<double>>& Result)
{
    int ntot = static_cast<int>(length / dx);
    double _time = 0.0;
    
    while(!equal(time, _time))
    {
        _time += dt;
        // Predict velocity for wet grid cells
        for(int k = 1; k <= ntot; k++)
        {
            double pgradx = -g * ( eta[k + 1] - eta[k] ) / dx;
            if(wet[k])
            {
                if(wet[k + 1] || pgradx > 0) u[k] += dt * pgradx;
            }
            else
            {
                if(wet[k + 1] && pgradx < 0) u[k] += dt * pgradx;
            }
        }
        // Predict sea level
        for(int k = 1; k <= ntot; k++)
        {
            // TODO
        }
    }
}

int main()
{
    Init();
    return 0;
}