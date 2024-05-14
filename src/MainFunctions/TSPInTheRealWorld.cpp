
#include "TSPInTheRealWorld.h"


//greedy algortim that seach for the nearest neibor with less distance
//works for complete graphs
//complexidade e certa de 0(v^2*E),principal problema e que o resultado acaba por ser aproximado e por vezes pode ser uma aproximação bastante distante da real
Vertex* findNearestNeighbor(Vertex* vertex, const vector<Vertex*>& unvisited) {
    double minDistance = numeric_limits<double>::max();
    Vertex* nearestNeighbor = nullptr;

    for (Vertex* neighbor : unvisited) {
        for (Edge* edge : vertex->getAdj()) {
            if (edge->getDest() == neighbor && edge->getdistance() < minDistance) {
                minDistance = edge->getdistance();
                nearestNeighbor = neighbor;
            }
        }
    }

    return nearestNeighbor;
}

pair<vector<Vertex*>, double> nearestNeighborTSP(Graph graph, const string& origin) {
    vector<Vertex*> tour;
    vector<Vertex*> unvisited = graph.getVertexSet();
    double totalDistance = 0.0;


    Vertex* currentVertex = graph.findVertex(origin);
    if (currentVertex == nullptr) {
        cerr << "Origin vertex not found in the graph." << endl;
        return make_pair(tour, totalDistance);
    }

    tour.push_back(currentVertex);
    currentVertex->setVisited(true);
    unvisited.erase(remove(unvisited.begin(), unvisited.end(), currentVertex), unvisited.end());


    while (!unvisited.empty()) {

        Vertex* nearestNeighbor = findNearestNeighbor(currentVertex, unvisited);


        if (nearestNeighbor == nullptr) {
            cerr << "No path exists that returns to the origin and visits all nodes." << endl;
            return make_pair(vector<Vertex*>(), 0.0);
        }


        double distanceToNeighbor = 0.0;
        for (Edge* edge : currentVertex->getAdj()) {
            if (edge->getDest() == nearestNeighbor) {
                distanceToNeighbor = edge->getdistance();
                break;
            }
        }
        totalDistance += distanceToNeighbor;

        tour.push_back(nearestNeighbor);
        nearestNeighbor->setVisited(true);
        currentVertex = nearestNeighbor;
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), nearestNeighbor), unvisited.end()); // Remove nearest neighbor from unvisited list
    }


    tour.push_back(graph.findVertex(origin));


    double distanceToOrigin = 0.0;
    for (Edge* edge : currentVertex->getAdj()) {
        if (edge->getDest() == graph.findVertex(origin)) {
            distanceToOrigin = edge->getdistance();
            break;
        }
    }


    totalDistance += distanceToOrigin;

    return make_pair(tour, totalDistance);
}
