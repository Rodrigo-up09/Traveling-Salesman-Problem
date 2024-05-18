

#ifndef PROJETDA2_BACKTRACKINGALGORITHM_H
#define PROJETDA2_BACKTRACKINGALGORITHM_H

#include "../DataManager/DataManager.h"

using namespace std;


void tspBackTrackR(double **distMatrix, double actualDist, double &minDist, int n, int pos, unsigned int  path[], unsigned int currPath[]);

double tspBackTrack(DataManager dataManager);
#endif
