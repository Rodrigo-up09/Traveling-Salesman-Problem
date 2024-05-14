

#ifndef DAPROJ2_DATAMANAGER_H
#define DAPROJ2_DATAMANAGER_H

#include <string>
#include <fstream>
#include <sstream>
#include "Graph/graph.h"

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
    vector<vector<double>> &getDistMatrix() ;
    void setDistMatrix(const vector<vector<double>> &distMatrix);
    void printGraph(const Graph &g);

private:
Graph g;
vector<vector<double>> distMatrix;
};


#endif //DAPROJ2_DATAMANAGER_H
