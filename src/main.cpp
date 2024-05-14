#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TriangularApproximation.h"
#include "MainFunctions/OtherHeuristics.h"
#include "Graph/graph.h"
#include "MainFunctions/TSPInTheRealWorld.h"

int main() {
    DataManager dataManager;
    DataManager dataManager2;
    dataManager.readMid(200);
   dataManager2.readMid(200);
    //cout<<tspBackTrack(dataManager)<<endl;
    cout<<tspTriangular(dataManager, true)<<endl;
    pair<vector<Vertex*>, double> tspResult = nearestNeighborTSP(dataManager2.getG(), "0");

    // Check if a feasible TSP tour exists
    if (!tspResult.first.empty()) {
        cout << "TSP Tour: ";
        for (Vertex* vertex : tspResult.first) {
            cout << vertex->getInfo() << " ";
        }
        cout << endl;

        cout << "Total Distance: " << tspResult.second << endl;
    } else {
        cerr << "No feasible TSP tour found." << endl;
    }

    return 0;
}

    /*
    OtherHeuristics heuristics;

    std::vector<std::vector<double>> distances_large = {
            {0.0, 7.0, 3.0, 4.0},
            {2.0, 0.0, 5.0, 6.0},
            {3.0, 5.0, 0.0, 7.0},
            {1.0, 6.0, 1.0, 0.0}
    };

    std::vector<pair<int,Vertex*>> vertices_large = {
            {0, new Vertex("0")},
            {1, new Vertex("1")},
            {2, new Vertex("2")},
            {3, new Vertex("3")}
    };

    std::pair<int,vector<pair<int,Vertex*>>> shortest_path_large = heuristics.tsp_dynamic_programming(distances_large, vertices_large, 0, 0, vertices_large.size(), {});

    std::cout << "Shortest path (large graph): ";
    for (const auto& vertex : shortest_path_large.second) {
        std::cout << vertex.second->getInfo() << " ";
    }
    std::cout << shortest_path_large.first << std::endl;

    for (auto vertex : vertices_large) {
        delete vertex.second;
    }

    return 0;
     */
