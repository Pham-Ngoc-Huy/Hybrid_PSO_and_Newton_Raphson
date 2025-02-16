#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    // Step 1: Initialization
    int m = 3; 
    int n = 5;
    double wmax = 0.9;
    double wmin = 0.4;
    double c1 = 2.0;
    double c2 = 2.0;
    int Maxt = 50;

    vector<double> LB = {0, 0, 0};
    vector<double> UB = {10, 10, 10};
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> rand01(0.0, 1.0);
    
    vector<vector<double>> x0(n, vector<double>(m, 0));
    vector<vector<double>> v0(n, vector<double>(m, 0));
    vector<vector<double>> fitness(n, vector<double>(1, 0));
    vector<double> pBest(n, 0);
    vector<vector<double>> pBestPos = x0;
    double gBest;
    vector<double> gBestPos(m, 0);


    // Initialize positions and velocities
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            uniform_real_distribution<double> dis(LB[j], UB[j]);
            x0[i][j] = dis(gen);
            v0[i][j] = 0.1 * x0[i][j];
        }
    }

    // Evaluate initial fitness
    for (int i = 0; i < n; ++i) {
        fitness[i][0] = 10 * pow((x0[i][0] - 1), 2) +
                        20 * pow((x0[i][1] - 2), 2) +
                        30 * pow((x0[i][2] - 3), 2);
        pBest[i] = fitness[i][0];
        pBestPos[i] = x0[i];
    }
    
    // Determine initial global best
    auto best_it = min_element(fitness.begin(), fitness.end(), [](const vector<double>& a, const vector<double>& b) { return a[0] < b[0]; });
    int best_idx = distance(fitness.begin(), best_it);
    gBest = (*best_it)[0];
    gBestPos = x0[best_idx];

    // PSO Main Loop
    for (int t = 0; t < Maxt; ++t) {
        double w = wmax - (wmax - wmin) * ((double)t / Maxt);
        
        // Update velocity and position
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                double r1 = rand01(gen);
                double r2 = rand01(gen);
                v0[i][j] = w * v0[i][j] +
                           c1 * r1 * (pBestPos[i][j] - x0[i][j]) +
                           c2 * r2 * (gBestPos[j] - x0[i][j]);
                x0[i][j] += v0[i][j];
                x0[i][j] = max(LB[j], min(UB[j], x0[i][j])); // Keep within bounds
            }
        }

        // Evaluate fitness
        for (int i = 0; i < n; ++i) {
            fitness[i][0] = 10 * pow((x0[i][0] - 1), 2) +
                            20 * pow((x0[i][1] - 2), 2) +
                            30 * pow((x0[i][2] - 3), 2);
            
            if (fitness[i][0] < pBest[i]) { // Update personal best
                pBest[i] = fitness[i][0];
                pBestPos[i] = x0[i];
            }
        }

        // Update global best
        auto best_it = min_element(fitness.begin(), fitness.end(), [](const vector<double>& a, const vector<double>& b) { return a[0] < b[0]; });
        int best_idx = distance(fitness.begin(), best_it);
        if ((*best_it)[0] < gBest) {
            gBest = (*best_it)[0];
            gBestPos = x0[best_idx];
        }

        cout << "Iteration " << t << ": Best fitness = " << gBest << endl;
    }

    cout << "Final Global Best: " << gBest << " at position: ";
    for (double val : gBestPos) cout << val << " ";
    cout << endl;
    
    return 0;
}