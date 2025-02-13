#include <iostream>
#include "differentiate.h"
#include <cmath>
using namespace std;

AutoDiffVar::AutoDiffVar(double v){
    val = v;
    der = 0;
}
AutoDiffVar::AutoDiffVar(double v, double d){
    val = v;
    der = d;
}
AutoDiffVar AutoDiffVar::getValue() const{
    return val;
}
AutoDiffVar AutoDiffVar::getDerivative() const{
    return der;
}
AutoDiffVar AutoDiffVar::derivativeOnce() const {
    return AutoDiffVar(0, 1);
}

AutoDiffVar AutoDiffVar::Derivative(int& n) const{
    AutoDiffVar temp = *this;
    for (int i = 0; i < n; i++){
        temp = temp.derivativeOnce();
    }
    return temp;
}

AutoDiffVar AutoDiffVar::operator+(const AutoDiffVar& other) const {
    return AutoDiffVar(
        val + other.val
        , der + other.der
        );
}
AutoDiffVar AutoDiffVar::operator-(const AutoDiffVar& other) const {
    return AutoDiffVar(
        val - other.val
        , der - other.der
        );
}
AutoDiffVar AutoDiffVar::operator*(const AutoDiffVar& other) const {
    return AutoDiffVar(
        val * other.val
        , val * other.der + der * other.val
        );
}
AutoDiffVar AutoDiffVar::operator/(const AutoDiffVar& other) const {
    return AutoDiffVar(
        val / other.val, 
        (der * other.val - val * other.der) / (other.val * other.val)
    );
}

double dev(double (*func)(double), double& val) {
    double h = 10e-10;
    return (func(val + h) - func(val - h)) / (2 * h);
}

double operator^(double base, int exp) {
    return std::pow(base, exp);
}


