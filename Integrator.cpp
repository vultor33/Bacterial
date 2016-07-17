#include "Integrator.h"

using namespace std;

Integrator::Integrator()
{
    timeStep = 1.0e-2;
}

void Integrator::advanceEquations(vector<double> & point, vector<double> & derivative)
{
    for(size_t i = 0; i < point.size(); i++)
    {
        point[i] = point[i] + timeStep * derivative[i];
    }
}

double Integrator::advanceEquations(double point, double derivative)
{
    return point + timeStep * derivative;
}



