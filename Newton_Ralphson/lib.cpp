#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <regex>
#include <stdexcept>

using namespace std;

// Abstract class: DifferentiatorBase
class DifferentiatorBase {
public:
    virtual ~DifferentiatorBase() = default;
    virtual string differentiate(const string& expression) = 0;
};

// Concrete class: Differentiator
class Differentiator : public DifferentiatorBase {
protected:
    struct Term {
        double coefficient;
        int exponent;
    };

    Term parseTerm(const string& term) {
        regex termPattern(R"(([-+]?\d*)(x?)(\^(\d+))?)");
        smatch matches;
        Term result = {0, 0};

        if (regex_match(term, matches, termPattern)) {
            string coefStr = matches[1].str();
            string varStr = matches[2].str();
            string expStr = matches[4].str();

            result.coefficient = coefStr.empty() || coefStr == "+" || coefStr == "-" ? 
                                (coefStr == "-" ? -1 : 1) : stod(coefStr);
            result.exponent = varStr.empty() ? 0 : (expStr.empty() ? 1 : stoi(expStr));
        }
        return result;
    }

    string differentiateTerm(const Term& term) {
        if (term.exponent == 0) return "";  
        double newCoef = term.coefficient * term.exponent;
        int newExp = term.exponent - 1;
        if (newExp == 0) return to_string((int)newCoef); 
        if (newExp == 1) return to_string((int)newCoef) + "x"; 
        return to_string((int)newCoef) + "x^" + to_string(newExp);
    }

public:
    string differentiate(const string& expression) override {
        istringstream stream(expression);
        string term;
        vector<string> derivatives;

        while (stream >> term) {
            if (term == "+" || term == "-") derivatives.push_back(term);
            Term parsedTerm = parseTerm(term);
            string diffTerm = differentiateTerm(parsedTerm);
            if (!diffTerm.empty()) derivatives.push_back(diffTerm);
        }

        string result;
        for (const auto& part : derivatives) result += part + " ";
        return result.empty() ? "0" : result;
    }
};

// Abstract class: ExpressionEvaluatorBase
class ExpressionEvaluatorBase {
public:
    virtual ~ExpressionEvaluatorBase() = default;
    virtual double evaluate(const string& expression, double x) = 0;
};

// Concrete class: ExpressionEvaluator
class ExpressionEvaluator : public ExpressionEvaluatorBase {
public:
    double evaluate(const string& expression, double x) override {
        if (expression == "x^2 - 4") return x * x - 4;
        if (expression == "x^3 - 2x + 1") return x * x * x - 2 * x + 1;
        throw invalid_argument("Unsupported expression");
    }
};

// Abstract class: NewtonRaphsonBase
class NewtonRaphsonBase {
protected:
    double epsilon;
public:
    NewtonRaphsonBase(double tol = 1e-6) : epsilon(tol) {}
    virtual ~NewtonRaphsonBase() = default;
    virtual double findRoot(const string& function, double x0, int maxIterations = 100) = 0;
};

// Concrete class: NewtonRaphsonSolver
class NewtonRaphsonSolver : public NewtonRaphsonBase {
protected:
    ExpressionEvaluator evaluator;
    Differentiator differentiator;

public:
    NewtonRaphsonSolver(double tol = 1e-6) : NewtonRaphsonBase(tol) {}

    double findRoot(const string& function, double x0, int maxIterations = 100) override {
        string derivative = differentiator.differentiate(function);
        cout << "Derivative: " << derivative << endl;

        for (int i = 0; i < maxIterations; i++) {
            double f_x = evaluator.evaluate(function, x0);
            double f_prime_x = evaluator.evaluate(derivative, x0);

            if (fabs(f_prime_x) < 1e-10) {
                throw runtime_error("Derivative near zero, Newton-Raphson failed.");
            }

            double x1 = x0 - (f_x / f_prime_x);
            cout << "Iteration " << i + 1 << ": x = " << x1 << endl;

            if (fabs(x1 - x0) < epsilon) return x1;
            x0 = x1;
        }
        cout << "Max iterations reached, returning last approximation.\n";
        return x0;
    }
};

// IRR Calculator
class IRRCalculator : public NewtonRaphsonSolver {
protected:
    double cash_out;
    double tenor;
    double instalment;
    double last_instalment;
    double precision = 1e-8;
    int max_iterations = 100;
    double initial_guess = 0.1;

public:
    IRRCalculator(double co, double t, double inst, double inst_last, double tol = 1e-8) 
        : NewtonRaphsonSolver(tol), cash_out(co), tenor(t), instalment(inst), last_instalment(inst_last) {}

    double calculateIRR() {
        double r = initial_guess;
        for (int i = 0; i < max_iterations; i++) {
            double npv = -cash_out;
            double npv_derivative = 0;

            for (int j = 1; j <= tenor; j++) {
                npv += instalment / pow(1 + r, j);
                npv_derivative -= j * instalment / pow(1 + r, j + 1);
            }

            npv += last_instalment / pow(1 + r, tenor);
            npv_derivative -= tenor * last_instalment / pow(1 + r, tenor + 1);

            if (fabs(npv) < precision) return r;
            r -= npv / npv_derivative;
        }
        throw runtime_error("IRR calculation did not converge.");
    }
};

// EIR Calculator
class EIRCalculator : public NewtonRaphsonSolver {
public:
    double calculateEIR() {
        return findRoot("x^2 - 4", 3.0);
    }
};

// Main function
int main() {
    NewtonRaphsonSolver newtonSolver;
    string function = "x^2 - 4";
    double initialGuess = 3.0;

    try {
        double root = newtonSolver.findRoot(function, initialGuess);
        cout << "Root found: " << root << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
