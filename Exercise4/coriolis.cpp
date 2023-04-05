#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double pi = std::atan(1.0) * 4.0;
double freq = 2.0 * pi / ( 24.0 * 3600.0 );
double f = -2.0 * freq;
double dt = 24.0 * 3600.0 / 200.0;

double alpha = dt * f;
double beta = 0.25 * alpha * alpha;


void Coriolis(  double u,
                double v,
                std::vector<double>& x,
                std::vector<double>& y)
{
    double un, vn;
    double xn, yn;
    for(int n = 1; n <= 200; n++)
    {
        un = ( ( 1 - beta ) * u + alpha * v ) / ( 1 + beta );
        vn = ( ( 1 - beta ) * v - alpha * u ) / ( 1 + beta );
        xn = x[n-1] + dt * un / 1000;
        yn = y[n-1] + dt * vn / 1000;
        u = un;
        v = vn;
        x.push_back(xn);
        y.push_back(yn);
    }
}

int main()
{
    double u = 0.5;
    double v = 0.5;
    std::vector<double> x{0.0};
    std::vector<double> y{5.0};

    Coriolis(u, v, x, y);
    std::cout << "done.. \n";
    std::ofstream file("coriolis1.dat");
    if(file.is_open())
    {
        std::cout << "storing result.. \n";
        for(int i = 0; i < x.size(); i++)
        {
            file << x[i] << "," << y[i] << std::endl;
        }
        file.close();
    }

    return 0;
}