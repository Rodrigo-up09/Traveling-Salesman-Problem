

#ifndef PROJETDA2_OTHERHEURISTICS_H
#define PROJETDA2_OTHERHEURISTICS_H

using namespace std;

class OtherHeuristics {
public:
    vector<int> cluster_graph(DataManager aux, int k);
    pair<int,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int, Vertex *>>> path);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    pair<int,vector<pair<int, Vertex *>>> joinSets(pair<int,vector<pair<int, Vertex *>>> set1, pair<int,vector<pair<int, Vertex *>>> set2, bool toy);
    int OtherHeuristic(DataManager aux, int k, bool toy);
    vector<vector<double>> getDistances(vector<pair<int, Vertex*>> vertices, bool toy);
};


#endif
