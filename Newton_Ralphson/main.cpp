#include <iostream>
#include "ObjectiveFunction.h"
#include "pso.h"
#include "newtonraphson.h"
#include "hybridPSONewtonRaphson.h"
using namespace std;
int main() {
    // Define objective function
    ObjectiveFunction objFunc;

    // Test PSO Only
    cout << "=== Running PSO Only ===" << endl;
    PSO pso(10, 2, 100, -5, 5, 0.5, 1.5, 1.5, objFunc);
    vector<double> pso_result = pso.optimize();

    // Test Newton-Raphson Only (with random initial guess)
    cout << "\n=== Running Newton-Raphson Only ===" << endl;
    vector<double> initial_guess = {2.0, -3.0}; // Example starting point
    NewtonRaphsonCalculation newtonSolver(objFunc, initial_guess, 1e-6);
    vector<double> newton_result = newtonSolver.findRoot();

    // Test Hybrid PSO + Newton-Raphson
    cout << "\n=== Running Hybrid PSO + Newton-Raphson ===" << endl;
    HybridPSONewton hybrid(10, 2, 100, -5, 5, 0.5, 1.5, 1.5, objFunc, 1e-6);
    vector<double> hybrid_result = hybrid.optimize();

    return 0;
}
