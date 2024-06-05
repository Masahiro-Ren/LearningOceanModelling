#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T>
using vec1d = vector<T>;

template <typename T>
using vec2d = vector<vector<T>>;

const int Nxtot = 53;
const int Nytot = 53;

const int Nx = 51;
const int Ny = 51;

const double dt = 0.1;
const double dx = 10.0;
const double dy = 10.0;
const double g = 9.81;
const double eps;

const double hmin = 0.05;

vec2d<double> hzero;

int main()
{

}