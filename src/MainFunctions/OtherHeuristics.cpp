#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include "DataManager/DataManager.h"
#include "OtherHeuristics.h"
#include "TriangularApproximation.h"

using namespace std;


Point computeCentroid(const vector<Vertex*>& cluster) {
    double sumX = 0.0, sumY = 0.0;
    int n = cluster.size();
    for (const auto& vertex : cluster) {
        sumX += vertex->getLatitude();
        sumY += vertex->getLongitude();
    }
    return {sumX / n, sumY / n};
}

double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x, p2.x) + pow(p1.y, p2.y));
}

vector<vector<Vertex*>> sortClustersByCentroidDistance(vector<vector<Vertex*>>& clusters) {
    vector<Point> centroids;
    for (const auto& cluster : clusters) {
        centroids.push_back(computeCentroid(cluster));
    }

    vector<int> indices(clusters.size(), 0);

    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return calculateDistance(centroids[i], centroids[0]) < calculateDistance(centroids[j], centroids[0]);
    });

    vector<vector<Vertex*>> sortedClusters;
    for (int idx : indices) {
        sortedClusters.push_back(clusters[idx]);
    }

    return sortedClusters;
}

vector<int> cluster_graph(DataManager aux, int k) {
    vector<Vertex *> vertexes = aux.getG().getVertexSet();
    vector<int> closures = {};
    for (size_t i = 0; i < vertexes.size(); i = i+k) {
        closures.push_back(i);
    }
    return closures;
}

pair<double,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int,Vertex *>>> path) {
    int allVisited = (1 << k) - 1;
    if (mask == allVisited) {
        return path;
    }

    pair<double,vector<pair<int,Vertex*>>> best_path;
    double min_length = std::numeric_limits<double>::infinity();

    for (int i = 0; i < k; ++i) {
        if (!(mask & (1 << i))) {
            pair<double, vector<pair<int, Vertex*>>> new_path = path;
            new_path.second.push_back(vertices[i]);
            int new_mask = mask | (1 << i);

            pair<double,vector<pair<int,Vertex*>>> result = tsp_dynamic_programming(distances, vertices, i, new_mask, k, new_path);

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

pair<double,vector<pair<int, Vertex *>>> joinSets(pair<double,vector<pair<int, Vertex *>>> set1, pair<double,vector<pair<int, Vertex *>>> set2, bool toy) {
    pair<int,vector<pair<int, Vertex *>>> merged;
    if (set1.second.empty()) {
        set1 = set2;
        return set1;
    }
    else {
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
            distance = set1.first + set2.first + haversine(single1->getLatitude(), single1->getLongitude(), single2->getLatitude(), single2->getLongitude());
        }
        vector<pair<int, Vertex*>> joinedPath;
        joinedPath.insert(joinedPath.end(), set1.second.begin(), set1.second.end());
        joinedPath.insert(joinedPath.end(), set2.second.begin(), set2.second.end());
        return {distance, joinedPath};
    } 
}

vector<vector<double>> getDistances(vector<pair<int, Vertex *>> vertices, bool toy) {
    vector<vector<double>> distances(vertices.size(), vector<double>(vertices.size(), 0.0));
    for (auto col: vertices) {
        for (auto row: vertices) {
            if (col.first != row.first) {
                if (toy) {
                    for (auto y: col.second->getAdj()) {
                        if (y->getDest()->getInfo() == row.second->getInfo()) {
                            distances[col.first][row.first] = y->getdistance();
                            break;
                        }
                    }
                } else {
                    distances[col.first][row.first] = haversine(col.second->getLatitude(),
                                                                col.second->getLongitude(),
                                                                row.second->getLatitude(),
                                                                row.second->getLongitude());
                }
            }
        }
    }
    return distances;
}

double OtherHeuristic(DataManager aux, int k, bool toy) {
   vector<Vertex *> vertices = aux.getG().getVertexSet();
   vector<pair<int,Vertex *>> workingVertices = {};
   pair<int,vector<pair<int, Vertex *>>> finalPath;
   finalPath.first = 0;
   finalPath.second = {};
   vector<int> clusters = cluster_graph(aux, k);
   int i = 0;
   for (int y : clusters) {
        for (int w = 0; w < k; w++) {
            if (y + w > vertices.size() - 1) {
                break;
            }
            workingVertices.push_back({i, vertices[y + w]});
            i++;
        }
        vector<vector<double>> distances = getDistances(workingVertices, toy);
        finalPath = joinSets(finalPath, tsp_dynamic_programming(distances, workingVertices, 0, 0, k, {0, {}}), toy);
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

double OtherHeuristic2(DataManager aux, int k, bool toy) {
    vector<Vertex *> vertices = aux.getG().getVertexSet();
    vector<vector<Vertex*>> divisions;
    pair<int,vector<Vertex *>> finalPath;
    finalPath.first = 0;
    finalPath.second = {};
    vector<int> clusters = cluster_graph(aux, k);
    for (int y : clusters) {
        vector<Vertex *> workingVertices = {};
        for (int w = 0; w < k; w++) {
            if (y + w > vertices.size() - 1) {
                break;
            }
            workingVertices.push_back( vertices[y + w]);
        }
        vector<Vertex*> path1;
        if (toy) {
            double distance = adaptedTspTriangular(workingVertices, path1);
            finalPath = joinSets2(finalPath, {distance, workingVertices}, toy);
        }
        else {
            divisions.push_back(workingVertices);
        }
    }
    if (toy) {
        int x;
        for (auto y: finalPath.second.back()->getAdj()) {
            if (y->getDest()->getInfo() == finalPath.second[0]->getInfo()) {
                x = y->getdistance();
            }
        }
        finalPath.first += x;
    }
    else {
        vector<Vertex*> path1;
        sortClustersByCentroidDistance(divisions);
        finalPath.first = adaptedTspTriangular(divisions[0], path1);
        finalPath.second = divisions[0];
        for (auto i = 1; i < divisions.size(); i++) {
            finalPath = joinClustersWithPaths(finalPath, {adaptedTspTriangular(divisions[i], path1), divisions[i]});
        }
    }
    return finalPath.first;
}

double adaptedTspTriangular(vector<Vertex*> vertices, vector<Vertex*>& path) {
    double finalDistance = 0;
    vector<Edge*> mst = adaptedPrim(vertices);
    preorderTraversal(mst, vertices[0], path);
    path.push_back(vertices[0]);
    for(int i=0; i < path.size()-1; i++) {
        finalDistance += calculateDistance(path[i], path[i+1]);
    }

    return finalDistance;
}

vector<Edge*> adaptedPrim(vector<Vertex*> vertices) {
    vector<Edge*> mst;
    if(vertices.empty()) {
        return mst;
    }
    for(auto v : vertices) {
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    auto source = vertices[0];
    source->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(source);

    while(!q.empty()){
        auto v = q.extractMin();
        if(v->getPath() != nullptr) {
            mst.push_back(v->getPath());
        }
        v->setVisited(true);
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            if(!w->isVisited()){
                double old_dist = w->getDist();
                if(old_dist > e->getdistance()) {
                    w->setDist(e->getdistance());
                    w->setPath(e);
                    if(old_dist == DBL_MAX) {
                        q.insert(w);
                    }else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return mst;
}


pair<double,vector< Vertex*>> joinSets2(pair<double,vector< Vertex*>> set1, pair<double,vector< Vertex*>> set2, bool toy) {
    pair<int,vector<pair<int, Vertex *>>> merged;
    if (set1.second.empty()) {
        set1 = set2;
        return set1;
    }
    else {
        Vertex * single1 = set1.second.back();
        Vertex * single2 = set2.second[0];
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
            distance = set1.first + set2.first + haversine(single1->getLatitude(), single1->getLongitude(), single2->getLatitude(), single2->getLongitude());
        }
        vector< Vertex*> joinedPath;
        joinedPath.insert(joinedPath.end(), set1.second.begin(), set1.second.end());
        joinedPath.insert(joinedPath.end(), set2.second.begin(), set2.second.end());
        return {distance, joinedPath};
    }
}

pair<double, std::vector<Vertex*>> joinClustersWithPaths(
        const std::pair<double, std::vector<Vertex*>>& cluster1,
        const std::pair<double, std::vector<Vertex*>>& cluster2) {

    double minTotalDistance = std::numeric_limits<double>::infinity();
    vector<Vertex*> bestJoinedPath;

    double originalDistance1 = cluster1.first;
    double originalDistance2 = cluster2.first;
    const std::vector<Vertex*>& path1 = cluster1.second;
    const std::vector<Vertex*>& path2 = cluster2.second;

    for (size_t i = 0; i < path1.size() - 1; ++i) {
        for (size_t j = 0; j < path2.size() - 1; ++j) {
            double distRemoved1 = calculateDistanceVer(path1[i], path1[i + 1]);
            double distRemoved2 = calculateDistanceVer(path2[j], path2[j + 1]);
            double distAdded1 = calculateDistanceVer(path1[i], path2[j]);
            double distAdded2 = calculateDistanceVer(path1[i + 1], path2[j + 1]);
            double newTotalDistance = originalDistance1 + originalDistance2
                                      - distRemoved1 - distRemoved2
                                      + distAdded1 + distAdded2;

            if (newTotalDistance < minTotalDistance) {
                minTotalDistance = newTotalDistance;

                std::vector<Vertex*> newPath;
                newPath.insert(newPath.end(), path1.begin(), path1.begin() + i + 1);
                newPath.insert(newPath.end(), path2.begin() + j + 1, path2.end());
                newPath.insert(newPath.end(), path2.begin(), path2.begin() + j + 1);
                newPath.insert(newPath.end(), path1.begin() + i + 1, path1.end());

                bestJoinedPath = newPath;
            }
        }
    }

    return {minTotalDistance, bestJoinedPath};
}

double calculateDistanceVer(Vertex* a, Vertex* b) {
    return haversine(a->getLatitude(), a->getLongitude(), b->getLatitude(), b->getLongitude());
}



