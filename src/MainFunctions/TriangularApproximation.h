#ifndef PROJETDA2_TRIANGULARAPPROXIMATION_H
#define PROJETDA2_TRIANGULARAPPROXIMATION_H

#include "../DataManager/DataManager.h"
#include "../DataStructure/MutablePriorityQueue.h"
#include <cmath>
#include <cfloat>
#include <limits>
#include <set>

using namespace std;

double haversine(double lat1, double lon1, double lat2, double lon2);
double calculateDistance(Vertex* v1, Vertex* v2);
vector<Edge*> prim(DataManager aux);
void preorderTraversal(vector<Edge*> mst, Vertex* v, vector<Vertex*>& path);
double tspTriangular(DataManager aux, vector<Vertex*>& path);
void printTSPTriangular(const vector<Vertex*>& path, double finalDistance);

#endif