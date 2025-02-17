#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include "Function.h"
using namespace std;
class NewtonRaphsonCalculation {
protected:
    Function& func;
    double epsilon;
    vector<double> xn;

public:
    NewtonRaphsonCalculation(Function& f, const vector<double>& initial_guess, double epsilon_);
    vector<double> findRoot();
};

#endif
