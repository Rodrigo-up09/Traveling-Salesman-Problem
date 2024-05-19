#include <cfloat>
#include "BacktrackingAlgorithm.h"
#include <chrono>

/**
 * @brief Recursive helper function for the Backtracking algorithm in the Traveling Salesman Problem (TSP).
 * @param distMatrix The distance matrix of the graph.
 * @param actualDist The current distance of the path.
 * @param minDist The minimum distance found so far.
 * @param n The total number of vertices in the graph.
 * @param currI The current index in the path.
 * @param path An array to store the best path found so far.
 * @param currPath An array to store the current path.
 * @details This function is a part of the Backtracking algorithm for the TSP. It recursively explores all possible paths in the graph,
 * updating the minimum distance and the best path whenever a shorter path is found. The function uses a pruning condition to avoid
 * exploring paths that are guaranteed to be longer than the best path found so far. This significantly reduces the search space and
 * improves the efficiency of the algorithm.
 * @complexity O(n!), where n is the number of vertices in the graph.
 */
void tspBackTrackR(double **distMatrix, double actualDist, double &minDist, int n, int currI, unsigned int  path[], unsigned int currPath[]) {
    //break case
    if(currI==n && distMatrix[currPath[n-1]][0]!=INF){

        actualDist+=distMatrix[currPath[n-1]][0];
        if(actualDist<minDist){
            minDist=actualDist;
            for(int i=0;i<n;i++){
                path[i]=currPath[i];
            }


        }
        path[n]=0;

        return;
    }
    for(int i=1;i<n;i++){

        if((actualDist+distMatrix[currPath[currI-1]][i]<minDist) && distMatrix[currPath[currI-1]][i]!=INF){

            //If this dont happen is a non minDist  path,so backTrack
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

/**
 * @brief Executes the Backtracking algorithm for the Traveling Salesman Problem (TSP).
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @return The minimum distance of the path.
 * @details This function first checks if the number of vertices in the graph is greater than 1000. If it is, the function prints a message and returns 0.0.
 * Otherwise, it initializes the path and currPath arrays, sets the first element of currPath to 0, and sets minDist to the maximum possible double value.
 * It then calls the recursive helper function tspBackTrackR, passing the distance matrix, the current distance (0), the minimum distance, the number of vertices,
 * the current index (1), the path, and the currPath.
 * After the recursive function returns, it calculates the execution time, prints the path and the execution time, and returns the minimum distance.
 * @complexity O(n!), where n is the number of vertices in the graph.
 */
double tspBackTrack(DataManager dataManager) {
    int n = dataManager.getG().getVertexSet().size();
    if(n>1000){
        cout<< "to big for me";
        return  0.0;}
     unsigned int path[1000];
    unsigned int currPath[1000];
    currPath[0] = 0;
    double minDist = DBL_MAX;
    auto start = std::chrono::high_resolution_clock::now();

    tspBackTrackR(dataManager.getDistMatrix(), 0, minDist, n, 1, path, currPath);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    cout<<"Path: "<<endl;
    for (int i = 0; i <= n; ++i) {
        cout << path[i] << " ";
    }
    cout<<endl;
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;

    return minDist;
}



