#include <fstream>
#include <cmath>
#include <vector>
#include <functional>

const double kappa = 0.0001f;
const double alpha = 0.5f;
const double dt = 3600;

auto explicit_scheme = [](double conc)->double{ return (1 - dt * kappa) * conc; };
auto implicit_scheme = [](double conc)->double{ return conc / (1 + dt * kappa); };
auto hybrid_scheme = [](double conc)->double{ return (1 - (1 - alpha) * kappa * dt) * conc / (1 + alpha * kappa * dt); };

void Decay( double concentrarion,
            int steps,
            const std::function<double(double)>& scheme,
            const char* result_path )
{
    std::vector<double> res{concentrarion};
    for(int i = 0; i < steps; i++)
    {
        double conc = scheme(res[i]);
        res.push_back(conc);
    }
    std::ofstream file(result_path);
    if(file.is_open())
    {
        for(auto val : res)
            file << val << "\n";
        file.close();
    }
}

void AnalyticalSolution(double concentration,
                        int steps)
{
    std::vector<double> res{concentration};
    double t = 0;
    for(int i = 1; i <= steps; i++)
    {
        t += dt;
        double ct = std::exp(-kappa * t) * concentration;
        res.push_back(ct);
    }

    std::ofstream file("res_analytical.txt");
    if(file.is_open())
    {
        for(auto val : res)
            file << val << "\n";
        file.close();
    }
}

int main()
{
    double concentration = 100;
    int steps = 15;

    Decay(concentration, steps, explicit_scheme, "res_explicit.txt");
    Decay(concentration, steps, implicit_scheme, "res_implicit.txt");
    Decay(concentration, steps, hybrid_scheme, "res_hybrid.txt");
    AnalyticalSolution(concentration, steps);

    return 0;
}