#ifndef AUTODIFF_VARIABLE_H
#define AUTODIFF_VARIABLE_H

#include <iostream>
using namespace std;
class AutoDiffVar {
    private:
        double der; //derivative/gradient
        AutoDiffVar derivativeOnce() const;
    protected:
    public:
        double val;  //value
        double h = 10e-10; // error 

        // Constructor:
        //==== just for replacement value into function - no derivative
        AutoDiffVar(double v);
        //==== for replacement value and derivative
        AutoDiffVar(double v, double d);
        //==== for derivative with higher Degree
        AutoDiffVar Derivative(int& n) const;
        // Accessors
        AutoDiffVar getValue() const;
        AutoDiffVar getDerivative() const;
        // Overload basic operators
        AutoDiffVar operator+(const AutoDiffVar& other) const;
        AutoDiffVar operator-(const AutoDiffVar& other) const;
        AutoDiffVar operator*(const AutoDiffVar& other) const;
        AutoDiffVar operator/(const AutoDiffVar& other) const;
};
#endif;

#ifndef CAL_H
#define CAL_H

class cal {
    double dev(double (*func)(double),double& val);
    //constructor
    d
    public:
        double value;

        cal(double val):value(val) {}

        cal operator^(int exp) const;
        cal sqrt() const;
};
#endif;

