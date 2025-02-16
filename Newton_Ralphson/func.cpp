#include <iostream>
#include "func.h"
#include <vector>
#include <functional>

using namespace std;

double Function::evaluate(const vector<double>& x) const {
        return func(x);
    }

double Function::derivative(const vector<double>& x, int dim) const {
        vector<double> xh = x;
        xh[dim] += h;
        return (func(xh) - func(x)) / h;
    }