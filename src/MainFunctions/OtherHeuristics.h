#ifndef PROJETDA2_OTHERHEURISTICS_H
#define PROJETDA2_OTHERHEURISTICS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

#include "DataManager/DataManager.h"
#include "TriangularApproximation.h"

using namespace std;

struct Point {
    double x, y;
};

/**
 * @brief Computes the centroid of a cluster of vertices.
 * @param cluster A vector of pointers to the vertices in the cluster.
 * @return A Point object representing the centroid of the cluster.
 */
Point computeCentroid(const vector<Vertex*>& cluster);

/**
 * @brief Joins two clusters of vertices into a single cluster.
 * @param cluster1 A pair consisting of the total distance of the first cluster's path and a vector of vertices representing the first cluster's path.
 * @param cluster2 A pair consisting of the total distance of the second cluster's path and a vector of vertices representing the second cluster's path.
 * @return A pair consisting of the total distance of the joined path and a vector of vertices representing the joined path.
 */
pair<double, std::vector<Vertex*>> joinClustersWithPaths (const std::pair<double, std::vector<Vertex*>>& cluster1,const std::pair<double, std::vector<Vertex*>>& cluster2);

/**
 * @brief Calculates the distance between two vertices using the Haversine formula.
 * @param a A pointer to the first vertex.
 * @param b A pointer to the second vertex.
 * @return The distance between the two vertices.
 */
double calculateDistanceVer(Vertex* a, Vertex* b);

/**
 * @brief Calculates the distance between two points.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Euclidean distance between the two points.
 */
double calculateDistance(const Point& p1, const Point& p2);

/**
 * @brief Sorts a vector of clusters based on the distance of their centroids from the origin.
 * @param clusters A reference to a vector of clusters, where each cluster is represented as a vector of Vertex pointers.
 * @return A vector of clusters sorted by the distance of their centroids from the origin.
 */
vector<vector<Vertex*>> sortClustersByCentroidDistance(vector<vector<Vertex*>>& clusters);

/**
 * @brief Divides the graph into clusters.
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @return A vector of integers, where each integer represents the index of the first vertex in each cluster.
 */
vector<int> cluster_graph(DataManager aux, int k);

/**
 * @brief Executes the dynamic programming algorithm for the Traveling Salesman Problem (TSP).
 * @param distances A 2D vector representing the distances between each pair of vertices.
 * @param vertices A vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param pos The current position in the path.
 * @param mask A bitmask representing the set of visited vertices.
 * @param k The total number of vertices in the graph.
 * @param path A pair consisting of the current total distance and a vector of pairs representing the current path.
 * @return A pair consisting of the minimum total distance and a vector of pairs representing the optimal path.
 */
pair<double,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int, Vertex *>>> path);

/**
 * @brief Joins two sets of vertices into a single set.
 * @param set1 A pair consisting of the total distance of the first set's path and a vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param set2 A pair consisting of the total distance of the second set's path and a vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A pair consisting of the total distance of the joined path and a vector of pairs representing the joined path.
 */
pair<double,vector<pair<int, Vertex *>>> joinSets(pair<double,vector<pair<int, Vertex *>>> set1, pair<double,vector<pair<int, Vertex *>>> set2, bool toy);

/**
 * @brief Executes a heuristic algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return The minimum total distance of the path.
 */
double OtherHeuristic(DataManager aux, int k, bool toy);

/**
 * @brief Calculates the distance between each pair of vertices.
 * @param vertices A vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A 2D vector representing the distances between each pair of vertices.
 */
vector<vector<double>> getDistances(vector<pair<int, Vertex*>> vertices, bool toy);

/**
 * @brief Executes a heuristic algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return The minimum total distance of the path.
 */
pair<int, vector<Vertex*>> OtherHeuristic2(DataManager aux, int k, bool toy);

/**
 * @brief Executes the Prim's algorithm to find the Minimum Spanning Tree (MST) of a graph.
 * @param vertices A vector of pointers to the vertices of the graph.
 * @return A vector of pointers to the edges that form the MST.
 */
vector<Edge*> adaptedPrim(vector<Vertex*> vertices);

/**
 * @brief Executes a modified version of the TSP algorithm using a triangular inequality.
 * @param vertices A vector of pointers to the vertices of the graph.
 * @param path A reference to a vector of vertices where the path will be stored.
 * @return The minimum total distance of the path.
 * @details This function implements a heuristic algorithm for the TSP. It starts by finding the Minimum Spanning Tree (MST) of the graph using the Prim's algorithm.
 */
double adaptedTspTriangular(vector<Vertex*> vertices, vector<Vertex*>& path);

/**
 * @brief Joins two sets of vertices into a single set.
 * @param set1 A pair consisting of the total distance of the first set's path and a vector of vertices representing the first set's path.
 * @param set2 A pair consisting of the total distance of the second set's path and a vector of vertices representing the second set's path.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A pair consisting of the total distance of the joined path and a vector of vertices representing the joined path.
 */
pair<double,vector< Vertex*>> joinSets2(pair<double,vector< Vertex*>> set1, pair<double,vector< Vertex*>> set2, bool toy);

void printOtherHeuristic(pair<int, vector<Vertex*>> path);

#endif
