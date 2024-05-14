#include <cfloat>
#include "BacktrackingAlgorithm.h"

void tspBackTrackR(const vector<vector<double>>& distMatrix, double actualDist, double &minDist, int n, int currI, unsigned int  path[], unsigned int currPath[]) {
    //break case
    if(currI==n){
        actualDist+=distMatrix[currPath[n-1]][0];
        if(actualDist<minDist){
            minDist=actualDist;
            for(int i=0;i<n;i++){
                path[i]=currPath[i];
            }
        }
        return;
    }
for(int i=1;i<n;i++){
    if((actualDist+distMatrix[currPath[currI-1]][i]<minDist) && distMatrix[currPath[currI-1]][i]>0){//If this dont happen is a non minDist  path,so backTrack
        bool isNew= true;
        for(int j=1;j<currI;j++){//check if the value was already process
            if(currPath[j]==i){
                isNew= false;
                break;
            }

        }
        if(isNew){//add the new vertex,and recursive call the next index
            currPath[currI]=i;
            tspBackTrackR(distMatrix,actualDist+distMatrix[currPath[currI-1]][currPath[currI]],minDist,n,currI+1,path,currPath);
        }

    }
}

}

double tspBackTrack(DataManager dataManager) {
    int n = dataManager.getG().getVertexSet().size();
    if(n>1000){
        cout<< "to big for me";
        return  0.0;}
     unsigned int path[1000];
    unsigned int currPath[1000];
    currPath[0] = 0;
    double minDist = DBL_MAX;
    tspBackTrackR(dataManager.getDistMatrix(), 0, minDist, n/2, 1, path, currPath);
    return minDist;
}


