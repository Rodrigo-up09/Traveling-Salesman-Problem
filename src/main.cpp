#include "DataManager/DataManager.h"
#include "MainFunctions/BacktrackingAlgorithm.h"
#include "MainFunctions/TriangularApproximation.h"
#include "MainFunctions/OtherHeuristics.h"
#include "Graph/graph.h"

int main() {
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
}