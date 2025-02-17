#include "ObjectiveFunction.h"
using namespace std;
ObjectiveFunction::ObjectiveFunction() : Function([](const vector<double>& x) {
    double sum = 0.0;
    for (double val : x) 
        sum += val * val;
    return sum;
}) {}
