#ifndef PSO_H
#define PSO_H

#include <vector>
#include "Particle.h"
using namespace std;
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
    PSO(int n, int dim, int iter, double minX, double maxX, double inertia, double cognitive, double social, const Function& function);
    vector<double> optimize();
};

#endif
