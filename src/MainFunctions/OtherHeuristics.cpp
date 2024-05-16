#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <math.h>
#include "DataManager/DataManager.h"
#include "OtherHeuristics.h"
//#include <corecrt_math_defines.h>

using namespace std;

vector<int> OtherHeuristics::cluster_graph(DataManager aux, int k) {
    vector<Vertex *> vertexes = aux.getG().getVertexSet();
    vector<int> closures;
    int j = 0;
    for (size_t i = 0; i < vertexes.size(); i+k) {
        closures[j] = i;
        j++;
    }
    return closures;
}

pair<int,vector<pair<int,Vertex *>>> OtherHeuristics::tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int,Vertex *>>> path) {
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

pair<int,vector<pair<int, Vertex *>>> OtherHeuristics::joinSets(pair<int,vector<pair<int, Vertex *>>> set1, pair<int,vector<pair<int, Vertex *>>> set2, bool toy) {
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

double OtherHeuristics::haversine(double lat1, double lon1, double lat2, double lon2) {
    double rad_lat1 = lat1 * M_PI / 180;
    double rad_lon1 = lon1 * M_PI / 180;
    double rad_lat2 = lat2 * M_PI / 180;
    double rad_lon2 = lon2 * M_PI / 180;

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double aux = pow(sin(delta_lat/2),2) + cos(rad_lat1) * cos(rad_lat2) * pow(sin(delta_lon/2),2);
    double c = 2 * atan2(sqrt(aux), sqrt(1 - aux));

    return c * 6371000;
}

int OtherHeuristics::OtherHeuristic(DataManager aux, int k, bool toy) {
   pair<int,vector<pair<int, Vertex *>>> path;
   vector<int> clusters = cluster_graph(aux, k);
   int i = 0;

}

vector<vector<double>> OtherHeuristics::getDistances(vector<pair<int, Vertex*>> vertices, bool toy) {
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