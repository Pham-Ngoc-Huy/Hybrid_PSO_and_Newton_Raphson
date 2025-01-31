#include <iostream>
#include "differentiate.h"
#include <cmath>
using namespace std;

//global variable
//declare function
double function(double x) {
    return x*x*x*x*x*x;
};
int main() {
    double val = 2;
    double h = 10e-10;
    int n = 3;
    double x;
    double y = 2*x + 1;
    double result = dev(function,n,val);
    cout<<result<<endl;
}
