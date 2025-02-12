// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <regex>

// using namespace std;

// // Abstract base class
// class DifferentiatorBase {
// public:
//     virtual ~DifferentiatorBase() = default;
//     virtual string differentiate(const string& expression) = 0;
// };

// // Concrete class for differentiating general expressions
// class GeneralDifferentiator : public DifferentiatorBase {
// protected:
//     struct Term {
//         double coefficient = 0;
//         int exponent = 0;
//         string type = ""; // "polynomial", "ln", "sqrt", "logn()", "a^x", "cos", "sin", "tan"
//     };

//     // Parses a single term (e.g., "3x^2" → {3,2}, "ln(x)" → ln, "sqrt(x)" → sqrt)
//     Term parseTerm(const string& term) {
//         Term result;
        
//         if (term.find("ln(x)") != string::npos) {
//             result.type = "ln";
//         } 
//         else if (term.find("sqrt(x)") != string::npos) {
//             result.type = "sqrt";
//         }
//         else if (term.find("cos(x)") != string::npos) {
//             result.type = "cos";
//         }
//         else if (term.find("sin(x)") != string:: npos){
//             result.type = "sin";
//         }
//         else if (term.find("tan(x)") != string:: npos){
//             result.type = "tan";
//         }
//         else if (term.find("log(x)") != string:: npos){
//             result.type = "log";
//         }
//         else {
//             // Polynomial pattern (e.g., "3x^2", "-x", "4")
//             regex termPattern(R"(([-+]?\d*\.?\d*)(x?)(\^(\d+))?)");
//             smatch matches;

//             if (regex_match(term, matches, termPattern)) {
//                 string coefStr = matches[1].str();
//                 string varStr = matches[2].str();
//                 string expStr = matches[4].str();

//                 // Handle coefficient
//                 if (coefStr.empty() || coefStr == "+" || coefStr == "-") {
//                     result.coefficient = (coefStr == "-") ? -1 : 1;
//                 } else {
//                     result.coefficient = stod(coefStr);
//                 }

//                 // Handle exponent
//                 if (!varStr.empty()) {
//                     result.exponent = expStr.empty() ? 1 : stoi(expStr);
//                 }
//                 result.type = "polynomial";
//             }
//         }
//         return result;
//     }

//     // Computes the derivative of a polynomial term
//     string differentiatePolynomial(const Term& term) {
//         if (term.exponent == 0) return "";  // Constant terms disappear

//         double newCoef = term.coefficient * term.exponent;
//         int newExp = term.exponent - 1;

//         if (newExp == 0) return to_string((int)newCoef);
//         if (newExp == 1) return to_string((int)newCoef) + "x";

//         return to_string((int)newCoef) + "x^" + to_string(newExp);
//     }

//     // Computes the derivative of ln(x) and sqrt(x)
//     string differentiateSpecial(const Term& term) {
//         if (term.type == "ln") return "1/x";
//         if (term.type == "sqrt") return "1/(2sqrt(x))";
//         return "";
//     }
//     // Computes the derivative of 

// public:
//     string differentiate(const string& expression) override {
//         regex termPattern(R"(([-+]?\s*\d*\.?\d*x?\^?\d*|ln\(x\)|sqrt\(x\)))");
//         sregex_iterator it(expression.begin(), expression.end(), termPattern);
//         sregex_iterator end;

//         vector<string> derivatives;
//         string lastOp = "+";

//         while (it != end) {
//             string term = it->str();
//             term.erase(remove(term.begin(), term.end(), ' '), term.end()); 

//             if (term == "+" || term == "-") {
//                 lastOp = term;
//             } else {
//                 Term parsedTerm = parseTerm(term);
//                 string diffTerm;

//                 if (parsedTerm.type == "polynomial") {
//                     diffTerm = differentiatePolynomial(parsedTerm);
//                 } else {
//                     diffTerm = differentiateSpecial(parsedTerm);
//                 }

//                 if (!diffTerm.empty()) {
//                     derivatives.push_back((lastOp == "-" ? "-" : "") + diffTerm);
//                 }
//             }
//             ++it;
//         }

//         string result;
//         for (const auto& part : derivatives) {
//             result += part + " ";
//         }
//         return result.empty() ? "0" : result;
//     }
// };

// int main() {
//     DifferentiatorBase* diff = new GeneralDifferentiator();
//     cout << "Derivative: " << diff->differentiate("x^2 + ln(x) + sqrt(x)") << endl;

//     delete diff;
//     return 0;
// }
#include <iostream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <stdexcept>

class ExpressionParser {
    std::string expr;
    size_t pos = 0;
    double x_value;

public:
    ExpressionParser(const std::string& expression, double x) : expr(expression), x_value(x) {}

    double parse() {
        pos = 0;
        return parseExpression();
    }

private:
    char peek() {
        while (pos < expr.size() && isspace(expr[pos])) pos++; // Bỏ qua khoảng trắng
        return pos < expr.size() ? expr[pos] : '\0';
    }

    char get() {
        return pos < expr.size() ? expr[pos++] : '\0';
    }

    double parseNumber() {
        std::string num;
        while (isdigit(peek()) || peek() == '.' || peek() == 'x') {
            if (peek() == 'x') {
                get();
                return x_value;
            }
            num += get();
        }
        return std::stod(num);
    }

    double parseFactor() {
        if (peek() == '(') {  // Xử lý dấu ngoặc
            get();
            double result = parseExpression();
            if (get() != ')') throw std::runtime_error("Lỗi: Dấu ngoặc không hợp lệ");
            return result;
        } else {
            return parseNumber();
        }
    }

    double parsePower() {
        double base = parseFactor();
        while (peek() == '^') {
            get();
            double exponent = parseFactor();
            base = std::pow(base, exponent);
        }
        return base;
    }

    double parseTerm() {
        double result = parsePower();
        while (peek() == '*' || peek() == '/') {
            char op = get();
            double next = parsePower();
            if (op == '*') result *= next;
            else if (op == '/') result /= next;
        }
        return result;
    }

    double parseExpression() {
        double result = parseTerm();
        while (peek() == '+' || peek() == '-') {
            char op = get();
            double next = parseTerm();
            if (op == '+') result += next;
            else if (op == '-') result -= next;
        }
        return result;
    }
};

// Hàm đánh giá biểu thức với giá trị x
double evaluateFunction(const std::string& expression, double x) {
    ExpressionParser parser(expression, x);
    return parser.parse();
}

// Chạy thử chương trình
int main() {
    std::string expression = "x^2 + 4";
    double x = 2.0;
    std::cout << "f(" << x << ") = " << evaluateFunction(expression, x) << expression << std::endl;
    return 0;
}
