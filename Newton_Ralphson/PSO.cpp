#include <iostream>
#include "pso.h"
using namespace std;

void PSO::initializeSwarm(){
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

vector<double> PSO::optimize(){
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

