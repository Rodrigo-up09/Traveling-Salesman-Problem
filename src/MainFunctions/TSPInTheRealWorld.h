

#ifndef PROJETDA2_TSPINTHEREALWORLD_H
#define PROJETDA2_TSPINTHEREALWORLD_H
#include "../Graph/graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;


Vertex* findNearestNeighbor(Vertex* vertex, const vector<Vertex*>& unvisited);
pair<vector<Vertex*>, double> nearestNeighborTSP(Graph graph, const string& origin);
#endif
