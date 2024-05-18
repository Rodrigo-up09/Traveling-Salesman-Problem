#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TSPInTheRealWorld.h"
#include "MainFunctions/TriangularApproximation.h"
#include "MainFunctions/OtherHeuristics.h"
void displayMenu();
void displaySingleAlgoritm( DataManager dataManager);
void displayBackTrac(DataManager dataManager);
void displayTriangular(DataManager dataManager);
void displayReal(DataManager dataManager,const string& origin);