#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>
#include <algorithm>

using namespace std;
class Function{
    protected:
        double h = 1e-10;
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
        virtual ~Function(){};
};

//PSO - Particle Swarm Optimization Algorithm
class PSO : public Function {
    protected:
        int num_particles;
        int dimensions;
        int max_iter;
        double w;
        double c1;
        double c2;
        double LB;
        double UB;
        vector<vector<double>> positions;
        vector<vector<double>> velocities;
        vector<vector<double>> fitness;
        vector<double> pBest;
        double gBest = 0;
        function<double(vector<double>)> objective;
        double gBest_value;
    
    public:
        //constructor (initialization)
        PSO (int num_particles_
            , int dimensions_
            , int max_iter_
            , double w_
            , double c1_
            , double c2_
            , double LB_
            , double UB_
            , function<double(vector<double>)> obj)
                : num_particles(num_particles_)
                    ,dimensions(dimensions_)
                    , max_iter(max_iter_)
                    , w(w_)
                    , c1(c1_)
                    , c2(c2_)
                    , LB(LB_)
                    , UB(UB_)
                    , objective(obj) 
            {
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<double> dis(LB, UB);
                positions.resize(num_particles, vector<double>(dimensions,0));
                velocities.resize(num_particles, vector<double>(dimensions,0));
                fitness.resize(num_particles);
                pBest.resize(num_particles);


                // intialization positions and velocities
                for (int i = 0; i < num_particles; ++i) {
                    for (int j = 0; j<dimensions; ++j){
                        positions[i][j] = dis(gen);
                        velocities[i][j] = 0.1*positions[i][j];
                    }
                }
                // Evaluate intial fitness
                for (int i = 0; i < num_particles; ++i) {
                    for (int j = 0; j < dimensions; ++j)
                        fitness[i][0] = objective(positions[i][j]);
                }       
                
                // Determine intial global best and best pos

            }

        double PSO_optimize() {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<double> rand(0.0, 1.0);
    
            for (int iter = 0; iter < max_iter; ++iter) {
                // Update the positions and velocities
                for (int i = 0; i < num_particles; ++i) {
                    for (int j = 0; j < dimensions; ++j) {
                        double r1 = rand(gen);
                        double r2 = rand(gen);
        
                        velocities[i][j] = w * velocities[i][0] +
                                        c1 * r1 * (pBest[i] - positions[i][j]) +
                                        c2 * r2 * (gBest - positions[i][j]);
        
                        positions[i][j] =  positions[i][j] + velocities[i][j];
                    }
                }
                // Evaluate Fitness
                for (int i = 0; i < num_particles; ++i) {
                    for (int j = 0; j < dimensions; ++j)
                        fitness[i][0] = objective(positions[i][j]);
                }      

                // find the new gBest and pBest

                for (int i = 0; i < num_particles; ++i) {
                    for (int j = 0; j < dimensions; ++j) {
                        
                    }
                }
                cout << "Iteration " << iter << ": Best fitness = " << gBest << endl;
            }
            return gBest;
        }
};

//Newton Raphson
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

// Newton-Raphson with PSO hybrid
class HybridPSO_Newton : public PSO , public NewtonRaphsonCalculation{
    protected:
        double epsilon;
    public:
        HybridPSO_Newton(int num_particles_, int max_iter_, double w_, double c1_, double c2_, function<double(vector<double>)> obj, double epsilon_)
            : PSO(num_particles_, max_iter_, w_, c1_, c2_, obj), epsilon(epsilon_) {}

        double refineSolution() {
            double root = gBest;
            double xn1 = root - objective({root}) / (derivative(root));
            while (abs(xn1 - root) >= epsilon) {
                root = xn1;
                xn1 = root - objective({root}) / (derivative(root));
            }
            return xn1;
        }
};
class IRR : public HybridPSO_Newton{
    protected:
        vector <double> cashFlows;
        double initial_Investment;
    public:
        // constructor
        IRR(const vector<double>& cashFlows_, double initialInvestment_, double guess = 0.1, double epsilon_ = 1e-6)
                : HybridPSO_Newton(nullptr, guess, epsilon_), cashFlows(cashFlows_), initial_Investment(initialInvestment_) {
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
            return refineSolution();
        }
};


int main() {
    vector<double> cashFlows = {100, 200, 300}; 
    double initialInvestment = 500;

    PSO pso_solver(10, 100, 0.5, 1.5, 1.5, [](vector<double> x) { return pow(x[0] - 2, 2); });
    double best_solution = pso_solver.PSO_optimize();

    HybridPSO_Newton hybrid_solver(10, 100, 0.5, 1.5, 1.5, [](vector<double> x) { return pow(x[0] - 2, 2); }, 1e-6);
    double refined_solution = hybrid_solver.refineSolution();

    cout << "Best solution found by PSO: " << best_solution << endl;
    cout << "Refined solution using Newton-Raphson: " << refined_solution << endl;

    return 0;
}