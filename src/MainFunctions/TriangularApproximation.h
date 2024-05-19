#ifndef PROJETDA2_TRIANGULARAPPROXIMATION_H
#define PROJETDA2_TRIANGULARAPPROXIMATION_H

#include "../DataManager/DataManager.h"
#include "../DataStructure/MutablePriorityQueue.h"
#include <cmath>
#include <cfloat>
#include <limits>
#include <set>

using namespace std;

/**
 * @brief Calculates the Haversine distance between two points on the Earth's surface.
 * @param lat1 Latitude of the first point in degrees.
 * @param lon1 Longitude of the first point in degrees.
 * @param lat2 Latitude of the second point in degrees.
 * @param lon2 Longitude of the second point in degrees.
 * @return The Haversine distance between the two points in meters.
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Calculates the distance between two vertices.
 * @param v1 Pointer to the first vertex.
 * @param v2 Pointer to the second vertex.
 * @return The distance between the two vertices. If there is an edge between the vertices,
 * the distance of the edge is returned. Otherwise, the haversine distance is calculated and returned.
 */
double calculateDistance(Vertex* v1, Vertex* v2);

/**
 * @brief Executes the Prim's algorithm on the given graph.
 * @param aux The DataManager instance containing the graph and other related data.
 * @return A vector of edges representing the Minimum Spanning Tree (MST) of the graph.
 */
vector<Edge*> prim(DataManager aux);

/**
 * @brief Performs a preorder traversal on the minimum spanning tree (MST).
 * @param mst A vector of edges representing the MST.
 * @param v The starting vertex for the traversal.
 * @param path A reference to a vector of vertices where the path of the traversal will be stored.
 */
void preorderTraversal(vector<Edge*> mst, Vertex* v, vector<Vertex*>& path);

/**
 * @brief Executes the Triangular Approximation algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param path A reference to a vector where the path of the traversal will be stored.
 * @return The total distance of the path.
 */
double tspTriangular(DataManager aux, vector<Vertex*>& path);

/**
 * @brief Prints the path and total distance of the Triangular Approximation algorithm.
 * @param path A vector of Vertex pointers representing the path taken by the algorithm.
 * @param finalDistance The total distance covered by the path.
 */
void printTSPTriangular(const vector<Vertex*>& path, double finalDistance);

#endif