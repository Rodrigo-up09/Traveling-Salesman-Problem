#include <cfloat>
#include "BacktrackingAlgorithm.h"

void tspBackTrackR(Graph graph,double actualDist, double &minDist,int n,int currI,vector<int>path,vector<int>currPath) {
    Vertex *first=graph.getVertexSet()[0];
    Edge*  dist=graph.getTheEdge(graph.getVertexSet()[currI-1],first->getInfo());

    if(currI==n){
        if(dist== nullptr){cout<<"no conection last and first";}
        actualDist+= dist->getdistance();
        if(actualDist<minDist){
            minDist=actualDist;
            for(int i=0;i<n;i++){
                path[i]=currPath[i];
            }

        }
        return;
    }
    for(int i=1;i<n;i++){
        int value=currPath[currI-1];
        Edge *next=graph.getTheEdge(graph.getVertexSet()[value], to_string(i));
        if(next!=nullptr) {
            if (actualDist + next->getdistance() < minDist) {
                bool isnewNode = true;
                for(int j=1;j<currI;j++){//verifica se o no ja esta dentro do path
                    if(currPath[j]==i){
                        isnewNode= false;
                        break;
                    }
                }
                if (isnewNode) {
                    currPath.push_back(i);
                    double nextValue=graph.getTheEdge(graph.getVertexSet()[value],to_string(currI))->getdistance();
                    tspBackTrackR(graph, actualDist += nextValue, minDist, n, currI + 1,path,currPath);
                }



            }
        }
    }



}

double tspBackTrack(DataManager dataManager){
    Graph graph=dataManager.getG();
    vector<int>currPath;
    vector<int>path;

    double  minDist= DBL_MAX;
    graph.setAllNonVisited();
    Vertex *vertex1=graph.getVertexSet()[1];
    currPath.push_back(0);
    int n=graph.getVertexSet().size();
    tspBackTrackR(graph,0.0,minDist,n,1,path,currPath);
    return minDist;


}


