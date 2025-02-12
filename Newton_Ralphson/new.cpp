#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

using namespace std;

class Function{
    protected:
        double h = 10e-10;
        function<double(double)>func;
    public:
        //constructor
        //default:
        Function(): func(nullptr), h(0) {}
        Function(double (*f)(double)):func(f) {}

        void setFunction(double (*f)(double)){
            func = f;
        } 

        double evaluate(double x) const{
            if (func) 
                return func(x);
            throw runtime_error("No function assigned!");
        }
        //member method
        double derivative(double x) const {
            if (!func) 
                throw runtime_error("No function assigned!");
            return (func(x + h) - func(x)) / h;
        }
};
class NewtonRaphsonCalculation : public Function{
    protected:
        double epsilon;
        double xn;
    public:
        //constructor
        NewtonRaphsonCalculation(double (*f)(double), const double& xn_, const double&epsilon_) : Function(f), xn(xn_), epsilon(epsilon_){}
        double Findroot(){
            double xn1 = xn - evaluate(xn)/derivative(xn);
            while(abs(xn1-xn) >= epsilon){
                xn=xn1;
                xn1 = xn - evaluate(xn)/derivative(xn);
            }
            return xn1;
            cout<<"Root Find" << xn1<<endl;
        }
};
class IRR : public NewtonRaphsonCalculation{
    protected:
        vector <double> cashFlows;
        double initial_Investment;
    public:
        // constructor
        IRR(const vector<double>& cashFlows_, double initialInvestment_, double guess = 0.1, double epsilon_ = 1e-6)
                : NewtonRaphsonCalculation(nullptr, guess, epsilon_), cashFlows(cashFlows_), initial_Investment(initialInvestment_) {
                func = [this](double r) { return NPV(r); };
            }
        double NPV(double& r){
            double npv = - initial_Investment;
            for (size_t t = 0; t < cashFlows.size(); t++){
                npv += cashFlows[t]/pow(1+r, t+1);
            }
            return npv;
        }
        double findIRR(){
            return Findroot();
        }
};

int main() {
    vector<double> cashFlows = {100, 200, 300}; 
    double initialInvestment = 500;

    IRR irrCalculator(cashFlows, initialInvestment);
    double irr = irrCalculator.findIRR();

    cout << "Tỷ suất hoàn vốn nội bộ (IRR): " << irr * 100 << "%" << endl;

    return 0;
}