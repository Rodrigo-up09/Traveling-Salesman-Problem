#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"

int main() {
    DataManager dataManager=DataManager();
    dataManager.readSmall(1);
    cout<<tspBackTrack(dataManager);


    return 0;
}