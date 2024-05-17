

#ifndef PROJETDA2_TSPINTHEREALWORLD_H
#define PROJETDA2_TSPINTHEREALWORLD_H
#include "../Graph/graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataManager/DataManager.h"
using namespace std;


Vertex* findNearestNeighbor(Vertex* vertex, const vector<Vertex*>& unvisited);
pair<vector<Vertex*>, double> nearestNeighborTSP(Graph graph, const string& origin);
pair<vector<Vertex*>, double> greedyTSP(Graph graph, const string& origin);
pair<vector<Vertex*>, double> greedyTSP(Graph graph, const string& origin);
void GetTour(Vertex* origin, vector<Vertex*>& tour);
void printTour(const vector<Vertex*>& tour, double totalDistance);
pair<vector<Vertex*>, double> greedyTSP2(Graph graph, const string& origin,double** distMatrix);
pair<vector<Vertex*>, double> greedyTSP3(Graph graph, const string& origin,double** distMatrix);

#endif
