#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

template<typename T>
using Vec1d = std::vector<T>;
template<typename T>
using Vec2d = std::vector<std::vector<T>>;

// parameters definition
const double PI = std::atan(1.0) * 4.0;
const static double g = 9.81;

const static int NxTot = 103; // grid number including boundary
const static int NX = 101;
const static int NZ = 10;
const static double dt = 0.25;
const static double dx = 10.0;
const static double eps = 0.05;
const static double hmin = 0.01;

const static double Apadle = 1.0;
const double Tpadle = 2.0 * 3600.0; // forcing time 2 hrs

// -----
Vec1d<double> rho   (NZ + 1);
Vec2d<double> eta   (NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<double> dpress(NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<double> hzero (NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<double> h     (NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<double> dhdt  (NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<double> u     (NxTot, Vec1d<double>(NZ + 1, 0.0));
Vec2d<bool>   wet   (NxTot, Vec1d<bool>(NZ + 1, 0.0));

void Init();
void Dynamic();
void Output();

int main()
{
    int ntot = (int)(Tpadle * 10.0 / dt);
    double time = 0.0;


    // initialize data
    Init();

    // main loop
    for(int n = 0; n < ntot; n++)
    {
        // update eta
        for(int kz = 0; kz < NZ; kz++)
            eta[1][kz] = Apadle * std::sin(2.0 * PI * time / Tpadle);
        
        Dynamic();
        
        // update total time
        time += dt;
    }
    return 0;
}

void Init() 
{
    Vec1d<double> h_layer(NZ, 10.0);
    Vec1d<double> htotal(NxTot, 100.0);
    
    htotal[0] = -10.0;
    htotal[NxTot - 1] = -10.0; 

    for(int k = 31; k <= 51; k++)
        htotal[k] = 100.0 - 95.0 * (k - 30) / 21;
    for(int k = 52; k <= 71; k++)
        htotal[k] = 100.0 - 95.0 * (71 - k + 1) / 20;
    
    for(int kx = 0; kx < NxTot; kx++)
    {
        double htot = htotal[kx];
        for(int kz = 0; kz < NZ; kz++)
        {
            hzero[kx][kz] = std::max(std::min(h_layer[kz], htot), 0.0);
            eta[kx][kz] = std::max(0.0, -htot);
            htot = htot - h_layer[kz];
        }
    }

    rho[0] = 0.0;
    rho[1] = 1025.0;
    for(int i = 2; i <= NZ; i++)
        rho[i] = 1026.0 + double(i - 2) / double(NZ - 2) * 0.5;

    for(int kx = 0; kx < NxTot; kx++)
    {
        for(int kz = 1; kz <= NZ; kz++)
        {
            h[kx][kz] = hzero[kx][kz];
            if(h[kz][kz] < hmin) 
                wet[kx][kz] = false;
            else
                wet[kx][kz] = true;
            u[kx][kz] = 0.0;
        }
    }
}

void Dynamic()
{
    double pgradx;
    double beta;
    double hue, huw, hwp, hwn, hen, hep;

    // calculate dynamic pressure
    for(int kx = 0; kx < NxTot; kx++)
    {
        for(int kz = 1; kz <= NZ; kz++)
        {
            dpress[kx][kz] = dpress[kx][kz - 1] + ( rho[kz] - rho[kz - 1] ) * g * eta[kx][kz];
        }
    }
}