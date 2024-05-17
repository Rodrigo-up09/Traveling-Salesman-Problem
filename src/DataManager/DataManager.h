

#ifndef DAPROJ2_DATAMANAGER_H
#define DAPROJ2_DATAMANAGER_H

#include <string>
#include <fstream>
#include <sstream>
#include "Graph/graph.h"
#include <limits>

#define INF std::numeric_limits<double>::infinity()
using namespace std;
class DataManager {

public:
    DataManager();
    void start(int dataSet,int type);
    void readSmall(int type);
    void readMid(int n);
    void readReal(int type);
    void readEdges(string filePath, bool flag);
    Graph getG();
    Graph& getGC();
    double** &getDistMatrix() ;
    void setDistMatrix(double **&distMatrix);
    void printGraph(const Graph &g);

private:
Graph g;
double **distMatrix;
};



#endif //DAPROJ2_DATAMANAGER_H
