#ifndef __NEWTON_RAPHSON__
#define __NEWTON_RAPHSON__
#include <iostream>
#include "func.h"
using namespace std;

class NewtonRaphsonCalculation {
protected:
    Function& func;
    double epsilon;
    vector<double> xn;

public:
    NewtonRaphsonCalculation(Function& f, const vector<double>& initial_guess, double epsilon_)
        : func(f), xn(initial_guess), epsilon(epsilon_) {}

    vector<double> findRoot();
};
#endif