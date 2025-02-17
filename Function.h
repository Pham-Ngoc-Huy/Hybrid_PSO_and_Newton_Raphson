#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <functional>
using namespace std;
class Function {
protected:
    function<double(const vector<double>&)> func;
    double h;

public:
    Function(function<double(const vector<double>&)> f, double step_size = 1e-6);
    virtual double evaluate(const vector<double>& x) const;
    virtual double derivative(const vector<double>& x, int dim) const;
    virtual ~Function() {}
};

#endif
