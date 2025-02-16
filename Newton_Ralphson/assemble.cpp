#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <functional>

using namespace std;

class Function {
protected:
    function<double(const vector<double>&)> func;
    double h;
public:
    Function(function<double(const vector<double>&)> f, double step_size = 1e-6) 
        : func(f), h(step_size) {}

    virtual double evaluate(const vector<double>& x) const {
        return func(x);
    }

    virtual double derivative(const vector<double>& x, int dim) const {
        vector<double> xh = x;
        xh[dim] += h;
        return (func(xh) - func(x)) / h;
    }

    virtual ~Function() {}
};

class ObjectiveFunction : public Function {
public:
    ObjectiveFunction() : Function([](const vector<double>& x) {
        double sum = 0.0;
        for (double val : x) 
            sum += val * val;
        return sum;
    }) {}
};

class Particle {
public:
    vector<double> position;
    vector<double> velocity;
    vector<double> bestPos;
    double fitness;
    double bestFitness;

    Particle(int dim, double minx, double maxx, const Function& func) {
        position.resize(dim);
        velocity.resize(dim);
        bestPos.resize(dim);
        for (int d = 0; d < dim; d++) {
            position[d] = minx + ((double) rand() / RAND_MAX) * (maxx - minx);
            velocity[d] = ((double) rand() / RAND_MAX) * (maxx - minx) * 0.1;
            bestPos[d] = position[d];
        }
        fitness = func.evaluate(position);
        bestFitness = fitness;
    }
};

class PSO {
protected:
    int N, DIM, max_iter;
    double minx, maxx, w, c1, c2;
    vector<Particle> swarm;
    vector<double> bestPosSwarm;
    double bestFitnessSwarm;
    const Function& func;

    void initializeSwarm() {
        srand(time(0));
        bestFitnessSwarm = numeric_limits<double>::max();
        for (int i = 0; i < N; i++) {
            Particle p(DIM, minx, maxx, func);
            if (p.fitness < bestFitnessSwarm) {
                bestPosSwarm = p.position;
                bestFitnessSwarm = p.fitness;
            }
            swarm.push_back(p);
        }
    }

public:
    PSO(int n, int dim, int iter, double minX, double maxX, double inertia, double cognitive, double social, const Function& function)
        : N(n), DIM(dim), max_iter(iter), minx(minX), maxx(maxX), w(inertia), c1(cognitive), c2(social), func(function) {
        bestPosSwarm.resize(DIM);
    }

    vector<double> optimize() {
        initializeSwarm();
        for (int iter = 0; iter < max_iter; iter++) {
            for (int i = 0; i < N; i++) {
                for (int d = 0; d < DIM; d++) {
                    double r1 = (double) rand() / RAND_MAX;
                    double r2 = (double) rand() / RAND_MAX;
                    swarm[i].velocity[d] = w * swarm[i].velocity[d] +
                                           c1 * r1 * (swarm[i].bestPos[d] - swarm[i].position[d]) +
                                           c2 * r2 * (bestPosSwarm[d] - swarm[i].position[d]);
                    swarm[i].position[d] += swarm[i].velocity[d];
                    if (swarm[i].position[d] < minx) swarm[i].position[d] = minx;
                    if (swarm[i].position[d] > maxx) swarm[i].position[d] = maxx;
                }
                swarm[i].fitness = func.evaluate(swarm[i].position);
                if (swarm[i].fitness < swarm[i].bestFitness) {
                    swarm[i].bestFitness = swarm[i].fitness;
                    swarm[i].bestPos = swarm[i].position;
                }
                if (swarm[i].fitness < bestFitnessSwarm) {
                    bestFitnessSwarm = swarm[i].fitness;
                    bestPosSwarm = swarm[i].position;
                }
            }
            cout << "Iteration: " << iter << " Best fitness: " << bestFitnessSwarm << endl;
        }
        cout << "Best solution found by PSO: ";
        for (double val : bestPosSwarm) cout << val << " ";
        cout << endl;
        return bestPosSwarm;
    }
};

class NewtonRaphsonCalculation {
protected:
    Function& func;
    double epsilon;
    vector<double> xn;

public:
    NewtonRaphsonCalculation(Function& f, const vector<double>& initial_guess, double epsilon_)
        : func(f), xn(initial_guess), epsilon(epsilon_) {}

    vector<double> findRoot() {
        vector<double> xn1 = xn;
        for (size_t i = 0; i < xn.size(); i++) {
            do {
                double fx = func.evaluate(xn);
                double dfx = func.derivative(xn, i);
                if (dfx == 0.0) break;
                xn1[i] = xn[i] - fx / dfx;
            } while (abs(xn1[i] - xn[i]) >= epsilon);
        }
        cout << "Refined solution using Newton-Raphson: ";
        for (double val : xn1) cout << val << " ";
        cout << endl;
        return xn1;
    }
};

class HybridPSO_NewtonRaphson : public PSO, public NewtonRaphsonCalculation {
public:
    HybridPSO_NewtonRaphson(int n, int dim, int iter, double minX, double maxX, double inertia, double cognitive, double social, Function& function, double epsilon)
        : PSO(n, dim, iter, minX, maxX, inertia, cognitive, social, function), NewtonRaphsonCalculation(function, vector<double>(dim, 0.0), epsilon) {}

    vector<double> optimizeAndRefine() {
        vector<double> best_solution = PSO::optimize();
        return NewtonRaphsonCalculation::findRoot();
    }
};

int main() {
    ObjectiveFunction objFunc;
    HybridPSO_NewtonRaphson hybrid(30, 2, 1000, -10.0, 10.0, 0.7, 1.5, 1.5, objFunc, 1e-6);
    vector<double> final_solution = hybrid.optimizeAndRefine();
    return 0;
}
