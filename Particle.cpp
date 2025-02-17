#include "Particle.h"
#include <cstdlib>

Particle::Particle(int dim, double minx, double maxx, const Function& func) {
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
