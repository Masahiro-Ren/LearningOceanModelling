#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

/**
 * MODE 1 : Dam break;
 * MODE 2 : Wave paddle;
*/
const static int MODE = 2;

// parameters for calculation
const static double dt = 0.1;
const static double dx = 10.;
const static double g = 9.81;
const static double length = 1000;
const static double h_zero = 10.0;
const static double eps = 0.05; // for filter

// parameters for MODE 2
const static double T = 20.;
static double pi = std::atan(1.0) * 4.0;

std::vector<double> h;
std::vector<double> _eta;
std::vector<double> eta;
std::vector<double> u;


bool checkCFL()
{
    double h_max = 0.0;
    for(const auto& val : h)
        h_max = std::max(val, h_max);
    return dt <= dx / ( std::sqrt( g * h_max ) );
}
bool equal(double a, double b)
{
    double relative_difference_factor = 0.0001;
    double greater_magnitude = std::max(std::abs(a), std::abs(b));
    return std::abs(a - b) < relative_difference_factor * greater_magnitude;
}

void Init()
{
    int k = length / dx + 2;
    h = std::vector<double>(k, h_zero);
    _eta = std::vector<double>(k, 0.0);
    eta = std::vector<double>(k, 0.0);
    u = std::vector<double>(k, 0.0);

    int pivot = k / 2 - 1;
    std::cout << "k is " << k << std::endl;
    std::cout << "pivot is " << pivot << std::endl;
    if(MODE == 1)
    {
        std::cout << "Init Dam Break... \n";
        for(int i = pivot; i >= pivot - 5; i--)
        {
            h[i] = 11.0;
            _eta[i] = 1.0;
            eta[i] = 1.0;
        }
        for(int i = pivot + 1; i <= pivot + 5; i++)
        {
            h[i] = 11.0;
            _eta[i] = 1.0;
            eta[i] = 1.0;
        }
    }
    else if(MODE == 2)
    {
        std::cout << "Init Wave paddle... \n";
    }
}

void Dynamic(double time, std::vector<std::vector<double>>& Result)
{
    double _time = 0.0;
    int ntot = length / dx;
    while(!equal(time, _time))
    {
        if(MODE == 2)
        {
            int pivot = (ntot + 2) / 2;
            eta[pivot] = std::sin(2 * pi * _time / T);
        }   
        _time += dt;
        
        for(int k = 1; k <= ntot; k++)
        {
            u[k] = u[k] - dt * g * ( eta[k + 1] - eta[k] ) / dx;
        }
        for(int k = 1; k <= ntot; k++)
        {
            double uk_plus = 0.5 * ( u[k] + std::fabs(u[k]) );
            double uk_minus = 0.5 * ( u[k] - std::fabs(u[k]) );
            double ukk_plus = 0.5 * ( u[k - 1] + std::fabs(u[k - 1]) );
            double ukk_minus = 0.5 * ( u[k - 1] - std::fabs(u[k - 1]) );
            _eta[k] = eta[k] - dt * ( uk_plus * h[k] + uk_minus * h[k + 1] - 
                                        ukk_plus * h[k - 1] - ukk_minus * h[k]);
        }
        // first-order shapiro filter
        for(int k = 1; k <= ntot; k++)
        {
            eta[k] = ( 1 - eps ) * _eta[k] + 0.5 * eps * ( _eta[k - 1] + _eta[k + 1] );
        }
        Result.push_back(eta);
        std::cout << "Time step: " << _time << std::endl;
    }
}

void Output(std::vector<std::vector<double>>& Result)
{
    std::string filename = "Unknown_mode.dat";
    if(MODE == 1)
        filename = "dam_break.dat";
    else if(MODE == 2)
        filename = "wave_paddle.dat";
    std::ofstream file(filename);
    if(file.is_open())
    {
        for(auto& line : Result)
        {
            for(int k = 0; k < line.size(); k++)
            {
                file << h_zero + line[k];
                if(k != line.size() - 1) file << ",";
            }
            file << std::endl;
        }
        file.close();
    }
}

int main()
{
    Init();
    if(checkCFL())
    {
        std::cout << "check CFL condition... OK. \n";
        std::vector<std::vector<double>> Result;
        Dynamic(20, Result);
        Output(Result);
    }
    else
    {
        std::cout << "check CFL condition... failed. \n";
    }
    return 0;
}
