

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

private:
Graph g;
};


#endif //DAPROJ2_DATAMANAGER_H
