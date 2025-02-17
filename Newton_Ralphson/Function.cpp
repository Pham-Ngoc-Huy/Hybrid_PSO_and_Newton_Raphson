#include "Function.h"
using namespace std;
Function::Function(function<double(const vector<double>&)> f, double step_size) 
    : func(f), h(step_size) {}

double Function::evaluate(const vector<double>& x) const {
    return func(x);
}

double Function::derivative(const vector<double>& x, int dim) const {
    vector<double> xh = x;
    xh[dim] += h;
    return (func(xh) - func(x)) / h;
}
