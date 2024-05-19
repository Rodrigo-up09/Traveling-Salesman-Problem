

#ifndef PROJETDA2_OTHERHEURISTICS_H
#define PROJETDA2_OTHERHEURISTICS_H

using namespace std;
    struct Point {
        double x, y;
    };
    Point computeCentroid(const vector<Vertex*>& cluster);
    pair<double, std::vector<Vertex*>> joinClustersWithPaths (const std::pair<double, std::vector<Vertex*>>& cluster1,const std::pair<double, std::vector<Vertex*>>& cluster2);
    double calculateDistanceVer(Vertex* a, Vertex* b);
    double calculateDistance(const Point& p1, const Point& p2);
    vector<vector<Vertex*>> sortClustersByCentroidDistance(vector<vector<Vertex*>>& clusters);
    vector<int> cluster_graph(DataManager aux, int k);
    pair<double,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int, Vertex *>>> path);
    pair<double,vector<pair<int, Vertex *>>> joinSets(pair<double,vector<pair<int, Vertex *>>> set1, pair<double,vector<pair<int, Vertex *>>> set2, bool toy);
    double OtherHeuristic(DataManager aux, int k, bool toy);
    vector<vector<double>> getDistances(vector<pair<double, Vertex*>> vertices, bool toy);
    double OtherHeuristic2(DataManager aux, int k, bool toy);
    vector<Edge*> adaptedPrim(vector<Vertex*> vertices);
    double adaptedTspTriangular(vector<Vertex*> vertices, vector<Vertex*>& path);
    pair<double,vector< Vertex*>> joinSets2(pair<double,vector< Vertex*>> set1, pair<double,vector< Vertex*>> set2, bool toy);
#endif
