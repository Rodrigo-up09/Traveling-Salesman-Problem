#ifndef PROJETDA2_TSPINTHEREALWORLD_H
#define PROJETDA2_TSPINTHEREALWORLD_H

#include "../Graph/graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataManager/DataManager.h"

using namespace std;

/**
 * @brief Finds the nearest unvisited neighbor of a given vertex.
 * @param vertex The vertex for which the nearest neighbor is to be found.
 * @param unvisited A vector of vertices that have not been visited yet.
 * @return A pointer to the nearest unvisited neighbor. If no unvisited neighbor is found, returns nullptr.
 */
Vertex* findNearestNeighbor(Vertex* vertex, const vector<Vertex*>& unvisited);

/**
 * @brief Executes the Nearest Neighbor algorithm for the Traveling Salesman Problem (TSP).
 * @param graph The graph on which the TSP is to be solved.
 * @param origin The starting vertex for the TSP.
 * @return A pair consisting of a vector of vertices representing the path of the tour and the total distance of the tour.
 */
pair<vector<Vertex*>, double> nearestNeighborTSP(Graph graph, const string& origin);

/**
 * @brief Constructs the tour from the origin vertex.
 * @param origin A pointer to the origin vertex.
 * @param tour A reference to a vector of Vertex pointers where the tour will be stored.
 */
void GetTour(Vertex* origin, vector<Vertex*>& tour);

/**
 * @brief Executes the Greedy algorithm for the Traveling Salesman Problem (TSP).
 * @param graph The graph on which the TSP is to be solved.
 * @param origin The starting vertex for the TSP.
 * @return A pair consisting of a vector of vertices representing the path of the tour and the total distance of the tour.
 */
pair<vector<Vertex*>, double> greedyTSP(Graph graph, const string& origin);

/**
 * @brief Prints the tour path and total distance of the Traveling Salesman Problem (TSP).
 * @param tour A vector of Vertex pointers representing the path taken by the algorithm.
 * @param totalDistance The total distance covered by the path.
 */
void printTour(const vector<Vertex*>& tour, double totalDistance);

/**
 * @brief Executes the Greedy algorithm for the Traveling Salesman Problem (TSP) with a priority queue.
 * @param graph The graph on which the TSP is to be solved.
 * @param origin The starting vertex for the TSP.
 * @param distMatrix The distance matrix of the graph.
 * @return A pair consisting of a vector of vertices representing the path of the tour and the total distance of the tour.
 */
pair<vector<Vertex*>, double> greedyTSP3(Graph graph, const string& origin,double** distMatrix);

#endif
