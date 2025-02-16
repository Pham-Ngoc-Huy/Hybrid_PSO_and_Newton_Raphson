#include <iostream>
#include "newtonraphson.h"
using namespace std;

vector<double> NewtonRaphsonCalculation::findRoot() {
        vector<double> xn1 = xn;
        for (size_t i = 0; i < xn.size(); i++) {
            do {
                double fx = func.evaluate(xn);
                double dfx = func.derivative(xn, i);
                if (dfx == 0.0) break;
                xn1[i] = xn[i] - fx / dfx;
            } while (abs(xn1[i] - xn[i]) >= epsilon);
        }
        cout << "Refined solution using Newton-Raphson: ";
        for (double val : xn1){ 
            cout << val << " ";
        }
        cout << endl;
        return xn1;
}