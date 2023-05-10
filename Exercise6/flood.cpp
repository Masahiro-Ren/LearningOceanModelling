#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

/**
 * MODE 1 for Island scenario
 * MODE 2 for Hillside with depressio9n scenario
*/
const static int MODE = 1;

const static double dt = 0.1;
const static double dx = 10.0;
const static double g = 9.81;
const static double h_min = 0.1;
const static double eps = 0.05; // for shapiro filter

std::vector<double> h_zero;
std::vector<double> h;
std::vector<double> eta;
std::vector<double> _eta;
std::vector<double> u;
std::vector<bool> wet;

void parse(std::ifstream& infile, std::vector<double>& array)
{
    std::string delimiter = ",";
    std::string values = "";
    while(std::getline(infile, values))
    {
        if(values.empty()) break;
        size_t pos = 0;
        while((pos = values.find(delimiter)) != std::string::npos)
        {
            double val = std::stod(values.substr(0, pos));
            array.push_back(val);
            values.erase(0, pos + delimiter.length());
        }
        array.push_back(std::stod(values));
    }
}

void Load(const std::string& path)
{
    std::cout << "Load data: " << path << std::endl;
    std::ifstream infile(path);
    std::string name = "";
    while(std::getline(infile, name))
    {
        if(name == "h_zero")
        {
            parse(infile, h_zero);
        }
        if(name == "eta")
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

}

void Calculate()
{

}

int main()
{
    Init();
    for(const auto& val : h_zero)
        std::cout << val << " ";
    std::cout << std::endl;
    for(const auto& val : eta)
        std::cout << val << " ";
    std::cout << std::endl;
    return 0;
}