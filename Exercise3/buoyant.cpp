#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double N2 = 1e-4;
const double g = 9.81f;
const double dt = 1.0f;
const double rho_surf = 1025.0f;
const double R = 0.002;

void Buoyant(double init_loc, double rho_obj, int time, std::vector<double>& trace)
{
    trace.push_back(init_loc);
    double w = 0.0f;
    double z = init_loc;
    double rho_amb = 0.0f;

    for(int t = 1; t < time; t += (int)dt)
    {
        // calculate rho
        rho_amb = rho_surf * ( 1.0 + N2 / g * std::abs(z) );
        // predict vectical speed
        w = w - dt * g * ( 1.0  - rho_amb / rho_obj );
        // predict vertical location
        z = z + dt * w;
        // location was constrained between [0, -100]
        z = std::max(z, -100.0);
        z = std::min(z, 0.0);
        
        trace.push_back(z);
    }
    std::ofstream file("buoyant.dat");
    if(file.is_open())
    {
        for(auto val : trace)
            file << val << "\n";
        file.close();
    }
}

void Buoyant_Fric(double init_loc, double rho_obj, int time, std::vector<double>& trace)
{
    trace.push_back(init_loc);
    double w = 0.0f;
    double z = init_loc;
    double rho_amb = 0.0f;

    for(int t = 1; t < time; t += (int)dt)
    {
        // calculate rho
        rho_amb = rho_surf * ( 1.0 + N2 / g * std::abs(z) );
        // predict vertical speed
        w = ( w - dt * g * ( 1.0 - rho_amb / rho_obj ) ) / ( 1.0 + R * dt );
        // predict vertical location
        z = z + dt * w;
        z = std::max( z, -100.0 );
        z = std::min( z, 0.0 );

        trace.push_back(z);
    }
    std::ofstream file("buoyant-fric.dat");
    if(file.is_open())
    {
        for(auto val : trace)
            file << val << "\n";
        file.close();
    }
}

int main()
{
    std::vector<double> trace;
    std::vector<double> trace_fric;
    Buoyant(-80.0, 1025.5, 1800, trace);
    Buoyant_Fric(-80.0, 1025.5, 1800, trace_fric);
    return 0;
}