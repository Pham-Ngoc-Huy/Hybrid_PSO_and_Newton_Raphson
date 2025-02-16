#ifndef __OBJECTIVE_FUNCTION__
#define __OBJECTIVE_FUNCTION__
#include <iostream>
#include <vector>
#include <cmath>
#include "func.h"
#include "pso.h"

using namespace std;

class ObjectiveFunction: public Function{
    public:
        ObjectiveFunction() : Function([](const vector<double>& x) {
        double sum = 0.0;
        for (double val : x){
            sum += val * val;
        }
        return  - 10 + sum;
    }) {}
};
// Hàm mục tiêu 1: Sphere function
class SphereFunction : public Function {
public:
    SphereFunction() : Function([](const vector<double>& x) {
        double sum = 0.0;
        for (double val : x) sum += val * val;
        return sum;
    }) {}
};

// Hàm mục tiêu 2: Rosenbrock function
class RosenbrockFunction : public Function {
public:
    RosenbrockFunction() : Function([](const vector<double>& x) {
        double sum = 0.0;
        for (size_t i = 0; i < x.size() - 1; i++) {
            sum += 100 * pow(x[i + 1] - x[i] * x[i], 2) + pow(1 - x[i], 2);
        }
        return sum;
    }) {}
};

// Hàm mục tiêu 3: Rastrigin function
class RastriginFunction : public Function {
public:
    RastriginFunction() : Function([](const vector<double>& x) {
        double sum = 10 * x.size();
        for (double val : x) {
            sum += val * val - 10 * cos(2 * M_PI * val);
        }
        return -sum;
    }) {}
};

// USE for test case: provide by CHATGPT

void runTest(const string& testName, Function& func) {
        cout << "Running test: " << testName << endl;
        PSO pso(30, 2, 1000, -5.0, 5.0, 0.7, 1.5, 1.5, func);
        vector<double> result = pso.optimize();
        cout << "Result for " << testName << ": ";
        for (double val : result) cout << val << " ";
        cout << "\n--------------------------\n";
    };
#endif