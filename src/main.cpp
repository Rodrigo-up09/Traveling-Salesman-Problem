#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TriangularApproximation.h"

int main() {
    DataManager dataManager=DataManager();
    dataManager.readSmall(0);
    cout<<tspBackTrack(dataManager) << endl;
    cout<<tspTriangular(dataManager,true) <<endl;

    return 0;
}