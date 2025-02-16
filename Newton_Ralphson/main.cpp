#include <iostream>
#include <vector>
#include <cmath>
#include "pso.h"
#include "objective.h"
#include "func.h"
#include "newtonraphson.h"

using namespace std;


int main() {
    // uncomment for testing - those provide by chatgpt
    // SphereFunction sphere;
    // RosenbrockFunction rosenbrock;
    // RastriginFunction rastrigin;
    
    // runTest("Sphere Function", sphere);
    // runTest("Rosenbrock Function", rosenbrock);
    // runTest("Rastrigin Function", rastrigin);
    
    // return 0;



    // Khởi tạo hàm mục tiêu
    ObjectiveFunction objFunc;

    // Khởi tạo PSO
    PSO pso(
        30,   // Số lượng hạt
        1,    // Số chiều
        100,  // Số vòng lặp tối đa
        -5.0, // Giới hạn dưới của biến
        5.0,  // Giới hạn trên của biến
        0.7,  // Hệ số quán tính
        1.5,  // Hệ số nhận thức cá nhân
        1.5,  // Hệ số nhận thức xã hội
        objFunc
    );

    // Tìm kiếm nghiệm tối ưu
    vector<double> best_solution = pso.optimize();

    // In kết quả cuối cùng
    cout << "Best solution found: ";
    for (double val : best_solution) cout << val << " ";
    cout << endl;

    NewtonRaphsonCalculation find_1(objFunc, best_solution,1e-6);
    find_1.findRoot();

    return 0;
}
