#include <iostream>
#include <functional>

double dev(std::function<double(double)> func, int n, double val) {
    double h = 1e-10;  // Small step size
    double derivative;
    for (int i = 0; i < n; i++) {
        // Apply central difference for the first derivative
        derivative = (func(val + h) - func(val - h)) / (2 * h);
        
        // Update func to be the derivative function for the next iteration
        func = [func, h](double x) {
            return (func(x + h) - func(x - h)) / (2 * h);
        };
    }

    return derivative;
}

// Example usage
double exampleFunction(double x) {
    return x * x * x * x;  // Example function: f(x) = x^4
}

int main() {
    int n = 2;  // We want the second derivative
    double val = 2.0;  // Point at which to evaluate the derivative
    double result = dev(exampleFunction, n, val);
    std::cout << "The " << n << "th derivative at " << val << " is: " << result << std::endl;
    return 0;
}