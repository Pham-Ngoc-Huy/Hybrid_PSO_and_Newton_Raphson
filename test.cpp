#include <iostream>
#include <cmath>
using namespace std;
class Number {
public:
    double value;

    // Constructor
    Number(double val) : value(val) {}

    // Overload the ^ operator for exponentiation
    Number operator^(int exp) const {
        return Number(std::pow(value, exp));
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Number& num) {
        os << num.value;
        return os;
    }
};

int main() {
    Number x = 5;
    int exp = 3;
    Number result = x ^ exp;
    cout << result <<endl;
    return 0;
}
