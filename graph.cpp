
#include "graph.h"
#include <Eigen/Dense>
#include <iostream>
#include "kmean.h"
#include <fstream>

using namespace Eigen;
using namespace std;
using namespace boost;

//typedef boost::adjacency_matrix<boost::undirectedS> UGraph;


Graph::Graph(MatrixXd mat)
{
    int size = mat.rows();
    adj.resize(size,size);
    adj = mat;
    std::cout <<mat<<std::endl;
}

/*Graph::Graph(string fileName)
{
    ifstream inFile;
    inFile.open("airlines.graphml");
    boost::dynamic_properties dp;

    boost::read_graphml(inFile, ug,dp);

    boost::print_graph(ug);
}
*/

MatrixXd Graph::mcl(int e,int r)
{
        int size = adj.rows();
        MatrixXd inf(size,size);
        MatrixXd ex(size,size);
        adj = adj + MatrixXd::Identity(size,size);
        inf = inflate(adj,1);
      //  cout<<inf<<endl;
        double err = 1;

        while(err>0.001)
        {
            ex = expand(inf,e);
            inf = inflate(ex,r);
            err = error(ex,inf);
          //  cout<<err<<endl;

        }

        return inf;
}

// inflate
MatrixXd Graph::inflate(MatrixXd grap,int r)
{
    int size = grap.rows();
    MatrixXd sumM(1,size);
    MatrixXd xPower(size,size);
    MatrixXd result(size,size);

    for(int col=0; col<size; col++)
        for(int row=0; row<size; row++)
        {
            xPower(row,col) = pow(grap(row,col),r);
        }

    for(int col=0; col<size; col++)
    {
        double sum = 0;
        for(int row=0; row<size; row++)
        {
            sum = sum + xPower(row,col);
        }
        sumM(0,col) = sum;
    }

    for(int col=0; col<size; col++)
        for(int row=0; row<size; row++)
        {
            result(row,col) = xPower(row,col)/sumM(0,col);
        }

    return result;

}

MatrixXd Graph::expand(MatrixXd inf, int e)
{
    MatrixXd ex = inf;
    while(e > 1)
    {
        ex = ex*inf;
        e--;
    }

    return ex;
}

double Graph::error(MatrixXd ex, MatrixXd inf)
{
    int size = ex.rows();
    double err;
    for(int row=0; row<size; row++)
        for(int col=0; col<size; col++)
        {
            err = err + pow(ex(row,col) - inf(row,col),2);
        }

    return err;
}

vector<vector<double> > Graph::classify(MatrixXd mat)
{
    int size = mat.rows();
    vector<vector<double> > result;
    vector<double> temp;
    for(int row=0; row<size; row++)
    {

        for(int col=0; col<size; col++)
        {
            if(mat(row,col)>0.001)
                temp.push_back(col+1);
        }
        if(temp.size()!=0)
            result.push_back(temp);
        temp.clear();
    }

    return result;
}

bool complex_less_pred(vect const& x, vect const& y)
{
    return x.data.real() < y.data.real();
}




MatrixXd Graph::spectral(MatrixXd mat,int k)
{
    int size = mat.rows();

    UGraph ug(size);
   // enum { A, B, C, D, E, F, G,H,I,J,K,L };
    //  const char* name = "ABCDEFGHIJKL";
  /*  for(int i=0; i<size; i++)
    {
        VertexID vID = boost::add_vertex(ug);
        ug[vID].name = i;
    }
    */

    for(int row=0; row<size; row++)
    {
        for(int col=row; col<size; col++)
        {
            if(mat(row,col)!=0)
            add_edge(row,col,ug);
        }
    }


    boost::print_graph(ug);

    MatrixXd deg = MatrixXd::Zero(size,size);
    MatrixXd lap(size,size);


    for(int col=0; col<size; col++)
    {

        deg(col,col) = boost::degree(col,ug);
    }

    lap = deg - adj;
    EigenSolver<MatrixXd> es(lap);
   // complex<double> lambda = es.eigenvalues()[0];

    VectorXcd D = es.eigenvalues();
    MatrixXcd V = es.eigenvectors();
    vector<vect > vd;
    MatrixXd vt(size,k);
    for(int i=0; i<D.rows(); i++)
    {
        vect temp;
        temp.index = i;
        temp.data = D[i];
        vd.push_back(temp);
    }

    std::sort(vd.begin(),vd.end(),complex_less_pred);

 /*   for(int i=0; i<D.rows(); i++)
    {
        cout<<vd[i].index<<":";
        cout<<vd[i].data<<endl;
    }
    */

    for(int col=0; col<k; col++)
        for(int row=0; row<size; row++)
    {
            vt(row,col) = V(row,vd[col].index).real();
    }

   cout<<"vector = "<<endl<<vt<<endl;

 //  cout<<V<<endl;
    vector<VectorXd> center = kmean(vt,k);
    cout<<"center = " <<endl;
    for(int i=0; i<center.size();i++)
    {
        cout<<center[i]<<endl;
    }
}
