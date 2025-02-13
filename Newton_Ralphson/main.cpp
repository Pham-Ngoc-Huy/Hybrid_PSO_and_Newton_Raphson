// #include <iostream>
// #include <cstdlib>
// #include <ctime>

// using namespace std;


// class PSO {
//     protected:
//         static const int numParticles = 3;
//         static const int numDimensions = 2;
//         double X[numParticles][numDimensions];
//         double V[numParticles][numDimensions];
//         double R1[numParticles][numDimensions];
//         double R2[numParticles][numDimensions];
//         double b[numParticles];
//         double GBest[1][numDimensions];
//         double Vnew[numParticles][numDimensions];
//         double Xnew[numParticles][numDimensions];
//         int vitriminfitness;
//         double c1 = 2.0;
//         double c2 = 2.0;
//         double wmax = 0.7;
//         double wmin = 0.2;
//     public:
//         //constructor:

//         //deconstruct:
//         double hammuctieu(double x1, double x2) {
//             return 2 * x1 * x2;
//         }

//         void XuatMaTran(double matrix[numParticles][numDimensions]) {
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     cout << matrix[i][j] << "\t";
//                 }
//                 cout << endl;
//             }
//         }
//         void ParticlesPosUpdate(int& Particle, int& Dimension){
//             for (int i = 0; i < Particle; ++i){
//                 for (int j = 0; j < Dimension;++j){
//                     X[i][j + 1] = X[i]
                
//                 }
//             }
//         }
//         void ParticlesVelUpdate(int& Particle, int& Dimension){
//             for (int i = 0; i < Particle; ++i){
//                 for (int j = 0; j < Dimension;++j){
//         }
//         double randomInRange(double minVal, double maxVal){
//             return minVal + (maxVal - minVal) * ((double)rand() / RAND_MAX);
//         }

//         void InitializeMatrices() {
//             srand(time(0));

//             cout << "Khoi tao X:" << endl;
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     X[i][j] = randomInRange(-10, 10);
//                     cout << X[i][j] << "\t";
//                 }
//                 cout << endl;
//             }

//             cout << "\nKhoi tao V:" << endl;
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     V[i][j] = randomInRange(-5, 5);
//                     cout << V[i][j] << "\t";
//                 }
//                 cout << endl;
//             }

//             cout << "\nKhoi tao R1:" << endl;
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     R1[i][j] = randomInRange(0, 1);
//                     cout << R1[i][j] << "\t";
//                 }
//                 cout << endl;
//             }

//             cout << "\nKhoi tao R2:" << endl;
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     R2[i][j] = randomInRange(0, 1);
//                     cout << R2[i][j] << "\t";
//                 }
//                 cout << endl;
//             }
//         }

//         void Fitness() {
//             cout << "\nKet hop ham muc tieu ta co" << endl << "Fitness:" << endl;

//             for (int i = 0; i < numParticles; i++) {
//                 b[i] = hammuctieu(X[i][0], X[i][1]);
//             }

//             for (int i = 0; i < numParticles; i++) {
//                 cout << b[i] << "\t";
//                 cout << endl;
//             }

//             vitriminfitness = 0;
//             double min = b[0];

//             for (int i = 1; i < numParticles; i++) {
//                 if (min > b[i]) {
//                     min = b[i];
//                     vitriminfitness = i;
//                 }
//             }

//             cout << "Minimum Fitness = " << min << endl;
//             cout << "Vi tri min nho nhat la hang thu: " << vitriminfitness + 1 << endl;

//             GBest[0][0] = X[vitriminfitness][0];
//             GBest[0][1] = X[vitriminfitness][1];

//             cout << "GBest la: " << GBest[0][0] << "\t" << GBest[0][1] << endl;
//         }

//         void Tinh_Vnew(int current) {
//             cout << "\nTu cong thuc ta co: ";
//             double w = wmax - ((wmax - wmin) / numParticles) * current;
//             cout << "w = " << w << endl;

//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     Vnew[i][j] = w * V[i][j] +
//                                 c1 * R1[i][j] * (GBest[0][j] - X[i][j]) +
//                                 c2 * R2[i][j] * (GBest[0][j] - X[i][j]);
//                 }
//             }

//             cout << "\nMa tran van toc moi Vnew = " << endl;
//             XuatMaTran(Vnew);
//             cout << "----------------------------" << endl;
//         }

//         void Tinh_Xnew() {
//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     Xnew[i][j] = X[i][j] + Vnew[i][j];
//                 }
//             }

//             cout << "Ma tran vi tri Xnew = " << endl;
//             XuatMaTran(Xnew);
//             cout << "--------------" << endl;

//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     if (Xnew[i][j] > 10) {
//                         Xnew[i][j] = 10;
//                     } else if (Xnew[i][j] < -10) {
//                         Xnew[i][j] = -10;
//                     }
//                 }
//             }

//             cout << "Ket hop voi dieu kien x thuoc [-10, 10], Xnew = " << endl;
//             XuatMaTran(Xnew);
//             cout << "---------------------------" << endl;

//             for (int i = 0; i < numParticles; i++) {
//                 for (int j = 0; j < numDimensions; j++) {
//                     X[i][j] = Xnew[i][j];
//                 }
//             }
//         }
// };
// int main() {
//     InitializeMatrices();
//     Fitness();
//     for (int i = 0; i < 10; i++) {
//         Tinh_Vnew(i);
//         Tinh_Xnew();
//         Fitness();
//     }
//     return 0;
// }


#include <iostream>

using namespace std;

int main(){
    //Step 1 Initialization

    //Initialize parameters
    //Initialize Population
    // https://www.youtube.com/watch?v=HmDjfL3R39M&t=731s
}