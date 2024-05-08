

#ifndef PROJETDA2_BACKTRACKINGALGORITHM_H
#define PROJETDA2_BACKTRACKINGALGORITHM_H

#include "../DataManager/DataManager.h"

using namespace std;




void tspBackTrackR(Graph graph,double actualDist, double &minDist,int n,int currI,vector<int>path,vector<int>currPath);

double tspBackTrack(DataManager dataManager);
#endif
