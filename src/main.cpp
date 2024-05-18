#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TriangularApproximation.h"
#include "MainFunctions/OtherHeuristics.h"
#include "MainFunctions/TSPInTheRealWorld.h"
#include "Graph/graph.h"
#include "Menu/menu.h"

int main() {
    displayMenu();


}
    /*
    DataManager dataManager1;
    DataManager dataManager2;
    DataManager dataManager3;
    DataManager dataManager4;
    DataManager dataManager5;

    dataManager1.readSmall(0);
    dataManager2.readSmall(1);
    dataManager3.readSmall(2);
    dataManager4.readMid(25);
    dataManager5.readReal(1);

    vector<Vertex *> path1;
    vector<Vertex *> path2;
    vector<Vertex *> path3;
    vector<Vertex *> path4;
    vector<Vertex *> path5;

    cout << "optimal solution: " <<tspBackTrack(dataManager1) << endl;
    cout << "approximation: " <<tspTriangular(dataManager1, path1) << endl;
    for (const auto& vertex : path1) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
    cout << endl;
    cout << "optimal solution: " <<tspBackTrack(dataManager2) << endl;
    cout << "approximation: " <<tspTriangular(dataManager2, path2) << endl;
    for (const auto& vertex : path2) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
    cout << endl;
    cout << "optimal solution: " <<tspBackTrack(dataManager3) << endl;
    cout << "approximation: " <<tspTriangular(dataManager3, path3) << endl;
    for (const auto& vertex : path3) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
    cout << endl;
    cout << "optimal solution: " <<tspBackTrack(dataManager4) << endl;
    cout << "approximation: " <<tspTriangular(dataManager4, path4) << endl;


    cout << endl;
    cout << endl;
    cout << "approximation: " <<tspTriangular(dataManager5, path5) << endl;

    DataManager dataManager1;
    DataManager dataManager2;
    dataManager1.readSmall(1);


    //auto result1= nearestNeighborTSP(dataManager2.getG(),"0");
    vector<Vertex*>path;
    auto result2= tspTriangular(dataManager1,path);
    //printTour(result.first, result.second);
    cout<<result2;
    //printTour(result1.first,result1.second);
    return 0;

}


    cout<<tspTriangular(dataManager, path)<<endl;
    for(auto v : path) {
        cout << v->getInfo() << " ";
    }
    cout << endl;
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
    } */

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
