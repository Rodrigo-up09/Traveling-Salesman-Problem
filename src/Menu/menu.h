/**
 * @file Menu.h
 * @brief Declaration of the Menu functions.
 */

#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TSPInTheRealWorld.h"
#include "MainFunctions/TriangularApproximation.h"
#include "MainFunctions/OtherHeuristics.h"
#include <chrono>

/**
 * @brief Displays the main menu for user interaction.
 */
void displayMenu();

/**
 * @brief Displays the results of a single algorithm.
 * @param dataManager Instance containing the graph and other related data.
 */
void displaySingleAlgorithm(DataManager dataManager, bool shipping);

/**
 * @brief Displays the results of Backtrack Algorithm.
 * @param dataManager Instance containing the graph and other related data.
 */
void displayBackTrac(DataManager dataManager);

/**
 * @brief Displays the results of Triangular Approximation Algorithm.
 * @param dataManager Instance containing the graph and other related data.
 */
void displayTriangular(DataManager dataManager, bool shipping);

/**
 * @brief Displays the results of TSP in Real World Algorithm.
 * @param dataManager Instance containing the graph and other related data.
 */
void displayReal(DataManager dataManager,const string& origin);

/**
 * @brief Displays the results of multiple algorithms for comparison.
 * @param dataManager Instance containing the graph and other related data.
 */
void displayMultiple(DataManager dataManager, bool shipping);

void displayOtherHeuristic(DataManager dataManager, bool shipping, int k);



void displayReal2(DataManager dataManager,const string& origin);

