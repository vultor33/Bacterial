#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector>

class Integrator
{
public:
    Integrator();

    void advanceEquations(std::vector<double> & point, std::vector<double> & derivative);

private:
    double timeStep;
};

#endif // INTEGRATOR_H
