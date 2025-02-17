#include "newtonraphson.h"
#include <cmath>
using namespace std;
NewtonRaphsonCalculation::NewtonRaphsonCalculation(Function& f, const vector<double>& initial_guess, double epsilon_)
    : func(f), xn(initial_guess), epsilon(epsilon_) {}

vector<double> NewtonRaphsonCalculation::findRoot() {
    vector<double> xn1 = xn;
    bool converged = false;
    int max_iterations = 100;

    for (int iter = 0; iter < max_iterations && !converged; iter++) {
        converged = true;
        for (size_t i = 0; i < xn.size(); i++) {
            double fx = func.evaluate(xn);
            double dfx = func.derivative(xn, i);
            if (abs(dfx) < 1e-6) continue;
            double new_xi = xn[i] - fx / dfx;
            if (abs(new_xi - xn[i]) > epsilon)
                converged = false;
            xn1[i] = new_xi;
        }
        xn = xn1;
    }
    return xn1;
}
