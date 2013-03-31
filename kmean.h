#ifndef KMEAN_H
#define KMEAN_H
#include <Eigen/Dense>
#include <vector>
using namespace Eigen;
using namespace std;

VectorXd init(int groupNum, int pointNum);
VectorXd calCenter(vector<VectorXd> group);
double calDistance(VectorXd v, VectorXd center);
vector<VectorXd> kmean(MatrixXd mat, int groupNum);

#endif // KMEAN_H
