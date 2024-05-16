#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include "DataManager/DataManager.h"
#include "OtherHeuristics.h"
#include "TriangularApproximation.h"

using namespace std;

vector<int> cluster_graph(DataManager aux, int k) {
    vector<Vertex *> vertexes = aux.getG().getVertexSet();
    vector<int> closures;
    int j = 0;
    for (size_t i = 0; i < vertexes.size(); i+k) {
        closures[j] = i;
        j++;
    }
    return closures;
}

pair<int,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int,Vertex *>>> path) {
    int allVisited = (1 << k) - 1;
    if (mask == allVisited) {
        return path;
    }

    pair<int,vector<pair<int,Vertex*>>> best_path;
    double min_length = std::numeric_limits<double>::infinity();

    for (int i = 0; i < k; ++i) {
        if (!(mask & (1 << i))) {
            pair<int, vector<pair<int, Vertex*>>> new_path = path;
            new_path.second.push_back(vertices[i]);
            int new_mask = mask | (1 << i);

            pair<int,vector<pair<int,Vertex*>>> result = tsp_dynamic_programming(distances, vertices, i, new_mask, k, new_path);

            double tour_length = 0.0;
            for (int j = 0; j < result.second.size() - 1; ++j) {
                tour_length += distances[result.second[j].first][result.second[j+1].first];
            }

            if (tour_length < min_length) {
                min_length = tour_length;
                best_path = result;
                best_path.first = min_length;
            }
        }
    }
    return best_path;
}

pair<int,vector<pair<int, Vertex *>>> joinSets(pair<int,vector<pair<int, Vertex *>>> set1, pair<int,vector<pair<int, Vertex *>>> set2, bool toy) {
    pair<int,vector<pair<int, Vertex *>>> merged;
    Vertex * single1 = set1.second.back().second;
    Vertex * single2 = set2.second[0].second;
    double distance = 0;
    if (toy) {
        Edge * connection;
        for (auto i : single1->getAdj()) {
            if (i->getDest()->getInfo() == single2->getInfo()) {
                connection = i;
            }
        }
        distance = set1.first + set2.first + connection->getdistance();
    }
    else {
        distance = haversine(single1->getLatitude(), single1->getLongitude(), single2->getLatitude(), single2->getLongitude());
    }
    vector<pair<int, Vertex*>> joinedPath;
    joinedPath.insert(joinedPath.end(), set1.second.begin(), set1.second.end());
    joinedPath.insert(joinedPath.end(), set2.second.begin(), set2.second.end());
    return {distance, joinedPath};
}

vector<vector<double>> getDistances(vector<pair<int, Vertex*>> vertices, bool toy) {
    vector<vector<double>> distances(vertices.size(), vector<double>(vertices.size(), 0.0));
    for (auto col: vertices) {
        for (auto row: vertices) {
            if (col.first != row.first) {
                if (toy) {
                    for (auto y : col.second->getAdj()) {
                        if (y->getDest()->getInfo() == row.second->getInfo()) {
                            distances[col.first][row.first] = y->getdistance();
                        }
                    }
                }
                else {
                    distances[col.first][row.first] = haversine(col.second->getLatitude(), col.second->getLongitude(), row.second->getLatitude(), row.second->getLongitude());
                }
            }
        }
    }
    return distances;
}

int OtherHeuristic(DataManager aux, int k, bool toy) {
   vector<Vertex *> vertices = aux.getG().getVertexSet();
   vector<pair<int,Vertex *>> workingVertices = {};
   pair<int,vector<pair<int, Vertex *>>> finalPath;
   finalPath.first = 0;
   finalPath.second = {};
   vector<int> clusters = cluster_graph(aux, k);
   int i = 0;
   for (int y : clusters) {
        for (int w = 0; w < k; w++) {
           workingVertices.push_back({i, vertices[y + w]});
        }
        vector<vector<double>> distances = getDistances(workingVertices, toy);
        joinSets(finalPath, tsp_dynamic_programming(distances, workingVertices, 0, 0, k, {0, {}}), toy);
    }
    if (toy) {
        int x;
        for (auto y: finalPath.second.back().second->getAdj()) {
            if (y->getDest()->getInfo() == finalPath.second[0].second->getInfo()) {
                x = y->getdistance();
            }
        }
        finalPath.first += x;
    }
    else {
        int x;
        Vertex* v1 = finalPath.second[0].second;
        Vertex* v2 = finalPath.second.back().second;
        x = haversine(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
        finalPath.first += x;
    }
    return finalPath.first;
}