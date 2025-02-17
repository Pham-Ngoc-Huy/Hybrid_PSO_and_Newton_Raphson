#ifndef HYBRID_PSO_NEWTON_H
#define HYBRID_PSO_NEWTON_H

#include "pso.h"
#include "newtonraphson.h"
using namespace std;
class HybridPSONewton {
private:
    PSO pso;
    Function& func;
    double epsilon;

public:
    HybridPSONewton(int psoParticles, int dimensions, int psoIterations, double minX, double maxX, 
                    double inertia, double cognitive, double social, Function& function, double newtonEpsilon);

    vector<double> optimize();
};

#endif
