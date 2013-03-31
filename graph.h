#ifndef GRAPH_H
#define GRAPH_H


#include <Eigen/Dense>
#include <vector>
#include <stdio.h>

#include "boost/graph/adjacency_matrix.hpp"
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/simple_point.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>

using namespace Eigen;
using namespace std;

struct Vertex{
    string name; // or whatever, maybe nothing
};
struct Edge{
    // nothing, probably. Or a weight, a distance, a direction, ...
};

struct vect{
    int index;
    complex<double> data;
};

//typedef boost::adjacency_list< boost::listS, boost::vecS, boost::directedS, Vertex, Edge> UGraph;
//typedef UGraph::vertex_descriptor VertexID;
//typedef UGraph::edge_descriptor   EdgeID;

class Graph
{
public:
    Graph(MatrixXd mat);
    MatrixXd mcl(int e,int r);
    MatrixXd spectral(MatrixXd mat,int k);
    vector<vector<double> > classify(MatrixXd mat);

private:
    MatrixXd adj;
    MatrixXd inflate(MatrixXd grap,int r);
    MatrixXd expand(MatrixXd inf, int e);
    double error(MatrixXd ex, MatrixXd inf);

};

#endif // GRAPH_H
