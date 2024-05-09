

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
    void readMid();
    void readReal(int type);
    void readEdges(string filePath);
    Graph getG();
    vector<vector<double>> &getDistMatrix() ;
    void setDistMatrix(const vector<vector<double>> &distMatrix);

private:
Graph g;
vector<vector<double>> distMatrix;
};


#endif //DAPROJ2_DATAMANAGER_H
