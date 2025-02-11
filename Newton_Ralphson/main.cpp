// #include <iostream>
// #include <cmath>
// #include <functional>

// using namespace std;

// // Base class Function
// class Function {
// protected:
//     function<double(double)> func;
//     string functionStr; 
// public:
//     // Default constructor
//     Function() : functionStr(" "), func([](double x) { return 0; }) {}

//     // Constructor with function
//     Function(const string& function_, function<double(double)> func_) 
//         : functionStr(function_), func(func_) {}

//     // Print function
//     virtual void print() const {
//         cout << "The function is: " << functionStr << endl;
//     }

//     // Evaluate function at a point
//     virtual double evaluate(double x) const {
//         return func(x);
//     }
// };

// // Derived class Differentiation
// class Differentiation : public Function {
// private:
//     double h = 1e-5;  // Small step for numerical differentiation
// public:
//     // Constructor using base class constructor
//     Differentiation(const string& function_, function<double(double)> func_) 
//         : Function(function_, func_) {}

//     // Compute numerical derivative using central difference method
//     double diff(double x) const {
//         return (evaluate(x + h) - evaluate(x - h)) / (2 * h);
//     }
// };

// int main() {
//     // Define a lambda for the function x^2 + x^3
//     auto myFunc = [](double x) { return x * x + x * x * x; };

//     // Create objects
//     Function f1("x^2 + x^3", myFunc);
//     Differentiation df("x^2 + x^3", myFunc);

//     // Print function
//     f1.print();

//     // Test differentiation
//     double x = 2.0;
//     cout << "f(" << x << ") = " << f1.evaluate(x) << endl;
//     cout << "f'(" << x << ") ≈ " << df.diff(x) << endl;

//     return 0;
// }