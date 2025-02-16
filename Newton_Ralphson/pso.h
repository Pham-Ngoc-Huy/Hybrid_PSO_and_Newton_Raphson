#ifndef __PSO_ALGORITHM__
#define __PSO_ALGORITHM__
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include "func.h"

using namespace std;
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

        void initializeSwarm();

    public:
        //constructor
        PSO(int n
            , int dim
            , int iter
            , double minX
            , double maxX
            , double inertia
            , double cognitive
            , double social
            , const Function& function)
                : N(n)
                    , DIM(dim)
                    , max_iter(iter)
                    , minx(minX)
                    , maxx(maxX)
                    , w(inertia)
                    , c1(cognitive)
                    , c2(social)
                    , func(function) {
                        bestPosSwarm.resize(DIM);
                        }
        vector<double> optimize();
};



#endif