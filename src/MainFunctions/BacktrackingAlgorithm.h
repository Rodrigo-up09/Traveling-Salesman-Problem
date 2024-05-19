
#ifndef PROJETDA2_BACKTRACKINGALGORITHM_H
#define PROJETDA2_BACKTRACKINGALGORITHM_H

#include "../DataManager/DataManager.h"

using namespace std;

/**
 * @brief Recursive helper function for the Backtracking algorithm in the Traveling Salesman Problem (TSP).
 * @param distMatrix The distance matrix of the graph.
 * @param actualDist The current distance of the path.
 * @param minDist The minimum distance found so far.
 * @param n The total number of vertices in the graph.
 * @param currI The current index in the path.
 * @param path An array to store the best path found so far.
 * @param currPath An array to store the current path.
 */
void tspBackTrackR(double **distMatrix, double actualDist, double &minDist, int n, int pos, unsigned int  path[], unsigned int currPath[]);

/**
 * @brief Executes the Backtracking algorithm for the Traveling Salesman Problem (TSP).
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @return The minimum distance of the path.
 */
double tspBackTrack(DataManager dataManager);

#endif
