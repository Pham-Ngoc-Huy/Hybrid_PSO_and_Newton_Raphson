#include "hybridPSONewtonRaphson.h"
#include <iostream>
using namespace std;
HybridPSONewton::HybridPSONewton(int psoParticles, int dimensions, int psoIterations, double minX, double maxX, 
                                 double inertia, double cognitive, double social, Function& function, double newtonEpsilon)
    : pso(psoParticles, dimensions, psoIterations, minX, maxX, inertia, cognitive, social, function),
      func(function), epsilon(newtonEpsilon) {}

vector<double> HybridPSONewton::optimize() {
    vector<double> bestPosition = pso.optimize();
    double bestValue = func.evaluate(bestPosition);

    cout << "PSO Best Fitness: " << bestValue << " at Position: ";
    for (double val : bestPosition) cout << val << " ";
    cout << endl;

    NewtonRaphsonCalculation newtonSolver(func, bestPosition, epsilon);
    vector<double> refinedPosition = newtonSolver.findRoot();
    double refinedValue = func.evaluate(refinedPosition);

    cout << "Newton-Raphson Refined Value: " << refinedValue << " at Position: ";
    for (double val : refinedPosition) cout << val << " ";
    cout << endl;

    return refinedPosition;
}
