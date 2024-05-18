

#ifndef PROJETDA2_OTHERHEURISTICS_H
#define PROJETDA2_OTHERHEURISTICS_H

using namespace std;
    vector<int> cluster_graph(DataManager aux, int k);
    pair<double,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int, Vertex *>>> path);
    pair<double,vector<pair<int, Vertex *>>> joinSets(pair<double,vector<pair<int, Vertex *>>> set1, pair<double,vector<pair<int, Vertex *>>> set2, bool toy);
    double OtherHeuristic(DataManager aux, int k, bool toy);
    vector<vector<double>> getDistances(vector<pair<double, Vertex*>> vertices, bool toy);
#endif
