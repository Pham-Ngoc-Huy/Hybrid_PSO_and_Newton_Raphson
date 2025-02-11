#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <functional>
#include <cmath>

using namespace std;

class Differentiator {
    protected:
        // Eg of the struct : (coefficient,x,exponent) -> 3x^2 -> (3,x,2)
        struct Term {
            double coefficient;
            int exponent;
        };

        // Parses a single term (e.g., "3x^2" → {3,2}, "x" → {1,1}, "5" → {5,0})
        Term parseTerm(const string& term) {
            regex termPattern(R"(([-+]?\d*)(x?)(\^(\d+))?)");
            smatch matches;
            Term result = {0, 0};

            if (regex_match(term, matches, termPattern)) {
                string coefStr = matches[1].str();
                string varStr = matches[2].str();
                string expStr = matches[4].str();

                // Handle coefficient
                if (coefStr.empty() || coefStr == "+" || coefStr == "-") {
                    result.coefficient = (coefStr == "-") ? -1 : 1;
                } else {
                    result.coefficient = stod(coefStr);
                }

                // Handle exponent
                if (!varStr.empty()) {
                    result.exponent = expStr.empty() ? 1 : stoi(expStr);
                }
            }
            return result;
        }

        string differentiateTerm(const Term& term) {
            if (term.exponent == 0) return "";  

            double newCoef = term.coefficient * term.exponent;
            int newExp = term.exponent - 1;

            if (newExp == 0) 
                return to_string((int)newCoef); 
            if (newExp == 1) 
                return to_string((int)newCoef) + "x"; 

            return to_string((int)newCoef) + "x^" + to_string(newExp);
        }

    public:
        // Constructor
        Differentiator() {
            cout << "Differentiator object created.\n";
        }

        // Destructor
        ~Differentiator() {
            cout << "Differentiator object destroyed.\n";
        }

        // Differentiates a full expression
        string differentiate(const string& expression) {
            istringstream stream(expression);
            string term;
            vector<string> derivatives;

            while (stream >> term) {
                if (term == "+" || term == "-") {
                    derivatives.push_back(term);
                    continue;
                }

                Term parsedTerm = parseTerm(term);
                string diffTerm = differentiateTerm(parsedTerm);
                if (!diffTerm.empty()) derivatives.push_back(diffTerm);
            }

            string result;
            for (const auto& part : derivatives) {
                result += part + " ";
            }
            return result.empty() ? "0" : result;
        }
    };
class NewtonRalpson_Calculation : public Differentiator{
    protected:
        double epsilon;
        double evaluateFunction(const string& expression, double x){
            if(expression == "x^2 - 4") return x*x - 4
            if(expression == "x^3 -2x + 1") return x*x*x - 2*x + 1;
            return 0;
        }
    public:
        // constructor:
        NewtonRalpson_Calculation(double tol = 1e-6) : epsilon(tol){}

        //Newton Ralphson Iteration
        double findRoot(const string& function, double x0, int maxIterations = 100) {
            string derivative = differentiate(function);

            cout<< "Derivative: " << derivative <<endl;

            for (int i = 0; i < maxIterations; i++){

                }
                double x1 = x0 - (f_x / f_prime_x);
                cout << "Iteration" << i + 1<<": x = "<<x1<<endl;

                if (fabs(x1-x0) < epsilon) 
                    return x1; // convergence check            
                x0 = x1;
        }
        cout << "Max iterations reached, returning las approximation.\n"
        return x0;
    };
int main() {
    NewtonRaphson_Calculation newtonSolver;
    
    string function = "x^2 - 4";
    double initialGuess = 3.0;

    double root = newtonSolver.findRoot(function, initialGuess);
    cout << "Root found: " << root << endl;
    return 0;
}
