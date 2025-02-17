#include "pso.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;
PSO::PSO(int n, int dim, int iter, double minX, double maxX, double inertia, double cognitive, double social, const Function& function)
    : N(n), DIM(dim), max_iter(iter), minx(minX), maxx(maxX), w(inertia), c1(cognitive), c2(social), func(function) {
    bestPosSwarm.resize(DIM);
}

void PSO::initializeSwarm() {
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

vector<double> PSO::optimize() {
    initializeSwarm();
    for (int iter = 0; iter < max_iter; iter++) {
        for (auto& particle : swarm) {
            for (size_t d = 0; d < particle.position.size(); d++) {
                double r1 = (double) rand() / RAND_MAX;
                double r2 = (double) rand() / RAND_MAX;
                particle.velocity[d] = w * particle.velocity[d] +
                                       c1 * r1 * (particle.bestPos[d] - particle.position[d]) +
                                       c2 * r2 * (bestPosSwarm[d] - particle.position[d]);
                particle.position[d] += particle.velocity[d];
            }
            particle.fitness = func.evaluate(particle.position);
            if (particle.fitness < particle.bestFitness) {
                particle.bestFitness = particle.fitness;
                particle.bestPos = particle.position;
            }
            if (particle.fitness < bestFitnessSwarm) {
                bestFitnessSwarm = particle.fitness;
                bestPosSwarm = particle.position;
            }
        }
        cout << "Iteration: " << iter << " Best fitness: " << bestFitnessSwarm << endl;
    }
    return bestPosSwarm;
}
