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
            sum += val * val;  // f(x) = x1^2 + x2^2 + ...
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
            position[d] = minx + ((double)rand() / RAND_MAX) * (maxx - minx);
            velocity[d] = ((double)rand() / RAND_MAX) * (maxx - minx) * 0.1;
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

    void updateSwarm() {
        for (int i = 0; i < N; i++) {
            for (int d = 0; d < DIM; d++) {
                double r1 = (double)rand() / RAND_MAX;
                double r2 = (double)rand() / RAND_MAX;
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
    }

public:
    PSO(int n, int dim, int iter, double minX, double maxX, double inertia, double cognitive, double social, const Function& function)
        : N(n), DIM(dim), max_iter(iter), minx(minX), maxx(maxX), w(inertia), c1(cognitive), c2(social), func(function) {
        bestPosSwarm.resize(DIM);
    }

    vector<double> optimize() {
        initializeSwarm();
        for (int iter = 0; iter < max_iter; iter++) {
            updateSwarm();
            cout << "Iteration: " << iter << " Best fitness: " << bestFitnessSwarm << endl;
        }
        return bestPosSwarm;
    }
};

// Newton-Raphson refinement
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
        bool converged = false;
        int max_iterations = 100;

        for (int iter = 0; iter < max_iterations && !converged; iter++) {
            converged = true;
            for (size_t i = 0; i < xn.size(); i++) {
                double fx = func.evaluate(xn);
                double dfx = func.derivative(xn, i);
                if (abs(dfx) < 1e-6) continue;
                double new_xi = xn[i] - fx / dfx;
                if (abs(new_xi - xn[i]) > epsilon)
                    converged = false;
                xn1[i] = new_xi;
            }
            xn = xn1;
        }
        return xn1;
    }
};

// **HYBRID PSO-NEWTONRAPHSON CLASS**
class HybridPSO_NewtonRaphson {
private:
    PSO pso;
    bool apply_newton;
    Function& func;
    double epsilon;

public:
    HybridPSO_NewtonRaphson(PSO pso_, Function& func_, bool use_newton, double eps)
        : pso(pso_), func(func_), apply_newton(use_newton), epsilon(eps) {}

    vector<double> optimize() {
        // Step 1: Run PSO
        vector<double> best_position = pso.optimize();
        double best_value = func.evaluate(best_position);

        // Step 2: Apply Newton-Raphson if enabled
        if (apply_newton) {
            NewtonRaphsonCalculation newton(func, best_position, epsilon);
            best_position = newton.findRoot();
            best_value = func.evaluate(best_position);
        }

        // Print final optimized values
        cout << "Optimized Value: " << best_value << " at Position: ";
        for (double val : best_position) cout << val << " ";
        cout << endl;

        return best_position;
    }
};

// **TEST IN MAIN FUNCTION**
int main() {
    ObjectiveFunction func;

    // PSO settings
    int N = 30;
    int DIM = 2;
    int max_iter = 100;
    double minx = -10.0, maxx = 10.0;
    double w = 0.5, c1 = 1.5, c2 = 1.5;

    // Create PSO object
    PSO pso(N, DIM, max_iter, minx, maxx, w, c1, c2, func);

    // Hybrid PSO-NewtonRaphson
    bool apply_newton = true;
    HybridPSO_NewtonRaphson hybrid_optimizer(pso, func, apply_newton, 1e-6);

    // Run optimization
    hybrid_optimizer.optimize();

    return 0;
}
