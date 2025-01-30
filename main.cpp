#include <iostream>
using namespace std;


double function(double x) {
    return x * x; 
}

// Numerical derivative using central difference method
double derivative(double (*func)(double), double x, double h) {
    return (func(x + h) - func(x - h)) / (2 * h);
}

int main() {
    double x = 3.0; // Point where we compute the derivative
    double h = 0.00001; // Small step size
    double result = derivative(function, x, h);

    cout << "Derivative at x = " << x << " is approximately " << result << std::endl;
    return 0;
}
