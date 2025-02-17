#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "Function.h"
using namespace std;
class Particle {
public:
    vector<double> position;
    vector<double> velocity;
    vector<double> bestPos;
    double fitness;
    double bestFitness;

    Particle(int dim, double minx, double maxx, const Function& func);
};

#endif
