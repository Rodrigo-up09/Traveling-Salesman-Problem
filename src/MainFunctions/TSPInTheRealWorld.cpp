#include <queue>
#include "TSPInTheRealWorld.h"
#include <utility>


//greedy algorithm that search for the nearest neighbor with less distance
//works for complete graphs
//complexidade é certa de 0(v^2*E),principal problema e que o resultado acaba por ser aproximado e por vezes pode ser uma aproximação bastante distante da real

/**
 * @brief Finds the nearest unvisited neighbor of a given vertex.
 * @param vertex The vertex for which the nearest neighbor is to be found.
 * @param unvisited A map of vertices that have not been visited yet.
 * @return A pointer to the nearest unvisited neighbor. If no unvisited neighbor is found, returns nullptr.
 * @details This function iterates over the map of unvisited vertices and for each unvisited vertex,
 * it checks if there is an edge from the given vertex to the unvisited vertex. If such an edge exists,
 * it compares the distance of this edge with the minimum distance found so far. If the distance is less
 * than the minimum distance, it updates the minimum distance and sets the nearest neighbor to the current unvisited vertex.
 */
Vertex* findNearestNeighbor(Vertex* vertex, unordered_map<string, Vertex*>& unvisited) {
    double minDistance = numeric_limits<double>::max();
    Vertex* nearestNeighbor = nullptr;

    for (const auto& pair : unvisited) {
        Vertex* neighbor = pair.second;
        for (const auto& i : vertex->getAdj()) {
            Edge* edge = i.second;
            if (edge->getDest() == neighbor && edge->getdistance() < minDistance) {
                minDistance = edge->getdistance();
                nearestNeighbor = neighbor;
            }
        }
    }

    return nearestNeighbor;
}

/**
 * @brief Executes the Nearest Neighbor algorithm for the Traveling Salesman Problem (TSP).
 * @param graph The graph on which the TSP is to be solved.
 * @param origin The starting vertex for the TSP.
 * @return A pair consisting of a vector of vertices representing the path of the tour and the total distance of the tour.
 * @details This function implements the Nearest Neighbor heuristic for the TSP. It starts at the given origin vertex and,
 * at each step, it selects the unvisited vertex that is closest to the current vertex. This process is repeated until all vertices have been visited,
 * at which point the path returns to the origin vertex. The function returns the path of the tour as a vector of vertices and the total distance of the tour.
 * Note that this heuristic does not always produce the optimal solution, but it is efficient and the solution is often good enough for practical purposes.
 * @complexity O(n^2), where n is the number of vertices in the graph.
 */
pair<vector<Vertex*>, double> nearestNeighborTSP(Graph graph, const string& origin) {
    vector<Vertex*> tour;
    auto unvisited = graph.getVertexSet();

    double totalDistance = 0.0;

    Vertex* currentVertex = graph.findVertex(origin);
    if (currentVertex == nullptr) {
        cerr << "Origin vertex not found in the graph." << endl;
        return make_pair(tour, totalDistance);
    }

    tour.push_back(currentVertex);
    currentVertex->setVisited(true);
    unvisited.erase(origin);

    while (!unvisited.empty()) {

        Vertex* nearestNeighbor = findNearestNeighbor(currentVertex, unvisited);


        if (nearestNeighbor == nullptr) {
            cerr << "No path exists that returns to the origin and visits all nodes." << endl;
            return make_pair(vector<Vertex*>(), 0.0);
        }


        double distanceToNeighbor = 0.0;
        for (auto i : currentVertex->getAdj()) {
            Edge* edge = i.second;
            if (edge->getDest() == nearestNeighbor) {
                distanceToNeighbor = edge->getdistance();
                break;
            }
        }
        totalDistance += distanceToNeighbor;

        tour.push_back(nearestNeighbor);
        nearestNeighbor->setVisited(true);
        currentVertex = nearestNeighbor;
        unvisited.erase(nearestNeighbor->getInfo()); // Remove nearest neighbor from unvisited map
    }
    if((tour.size())!=(graph.getVertexSet().size())){
        cerr << "No path exists that returns to the origin and visits all nodes." << endl;
        return make_pair(vector<Vertex*>(), -1.0);
    }

    tour.push_back(graph.findVertex(origin));


    double distanceToOrigin = 0.0;
    for (auto i: currentVertex->getAdj()) {
        Edge* edge = i.second;
        if (edge->getDest() == graph.findVertex(origin)) {
            distanceToOrigin = edge->getdistance();
            break;
        }
    }


    totalDistance += distanceToOrigin;

    return make_pair(tour, totalDistance);
}

/**
 * @brief Constructs the tour from the origin vertex.
 * @param origin A pointer to the origin vertex.
 * @param tour A reference to a vector of Vertex pointers where the tour will be stored.
 * @details This function starts at the origin vertex and follows the path set by the algorithm,
 * adding each vertex to the tour vector. The function stops when it encounters a vertex
 * with no path set or when it has visited all vertices in the graph.
 * @complexity O(n), where n is the number of vertices in the graph.
 */
void GetTour(Vertex* origin, vector<Vertex*>& tour) {

    Vertex* vertex = origin;
    int n = 0;
    while (vertex != nullptr && n < 1) {
        tour.push_back(vertex);
        if (vertex->getPath() == nullptr) {
            cerr << "Graph is not connected";
            return;
        }
        vertex = vertex->getPath()->getDest();
        n++;
    }
}


/**
 * @brief Prints the tour path and total distance of the Traveling Salesman Problem (TSP).
 * @param tour A vector of Vertex pointers representing the path taken by the algorithm.
 * @param totalDistance The total distance covered by the path.
 * @details This function iterates over the 'tour' vector and prints each vertex's information.
 * After all vertices are printed, it prints the total distance of the tour.
 * This function is typically used for debugging and results presentation.
 * @complexity O(n), where n is the number of vertices in the tour.
 */

void printTour(const vector<Vertex*>& tour, double totalDistance) {
    cout << "Path: "<<endl;
    for (Vertex* vertex : tour) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
    cout << "Total distance: " << totalDistance << endl;
}

/**
 * @brief Executes the Greedy algorithm for the Traveling Salesman Problem (TSP) with a priority queue.
 * @param graph The graph on which the TSP is to be solved.
 * @param origin The starting vertex for the TSP.
 * @param distMatrix The distance matrix of the graph.
 * @return A pair consisting of a vector of vertices representing the path of the tour and the total distance of the tour.
 * @details This function implements the Greedy heuristic for the TSP. It starts at the given origin vertex and,
 * at each step, it selects the unvisited vertex that is closest to the current vertex. This process is repeated until all vertices have been visited,
 * at which point the path returns to the origin vertex. The function returns the path of the tour as a vector of vertices and the total distance of the tour.
 * Note that this heuristic does not always produce the optimal solution, but it is efficient and the solution is often good enough for practical purposes.
 * The function uses a priority queue to select the next vertex to visit, which improves the efficiency of the algorithm.
 * @complexity O(n^2 log n), where n is the number of vertices in the graph.
 */

pair<vector<Vertex*>, double> greedyTSP3(Graph graph, const string& origin, double** distMatrix) {
    vector<Vertex*> tour;

    double totalDistance = 0.0;
    Vertex* currentVertex = graph.findVertex(origin);
    Vertex* first = currentVertex;

    if (currentVertex == nullptr) {
        cerr << "Origin vertex not found in the graph." << endl;
        return make_pair(vector<Vertex*>(), -1.0);
    }
    graph.setAllNonVisited();  // Assuming this sets all vertices as not visited
    first->setVisited(true);
    currentVertex->setVisited(true);
    tour.push_back( currentVertex);

      // Mark the origin as visited

    auto compareEdges = [](const Edge* a, const Edge* b) {
        return a->getdistance() > b->getdistance();  // Use > for min-heap
    };

    priority_queue<Edge*, vector<Edge*>, decltype(compareEdges)> pq(compareEdges);

    for (auto edge : currentVertex->getAdj()) {
        pq.push(edge.second);
    }

    Vertex* lastAddedVertex = nullptr;  // Store the last added vertex

    while (!pq.empty()) {
        Edge* minEdge = pq.top();
        pq.pop();
        Vertex* nextVertex = minEdge->getDest();

        if (!nextVertex->isVisited()) {
            nextVertex->setVisited(true);
            tour.push_back(nextVertex);
            lastAddedVertex = nextVertex;

            totalDistance += minEdge->getdistance();

            // Efficiently clear the priority queue
            while (!pq.empty()){
                pq.pop();
            }

            for (auto h : nextVertex->getAdj()) {
                Edge* nextEdge=h.second;
                if (!nextEdge->getDest()->isVisited()) {
                    pq.push(nextEdge);
                }
            }

        }
    }

    if (lastAddedVertex != nullptr) {
        int a = stoi(origin);
        int b = stoi(lastAddedVertex->getInfo());
        double value = distMatrix[a][b];
        if (value == INF || value == 0) {
            cerr << "No path exists that returns to the origin and visits all nodes." << endl;
            return make_pair(vector<Vertex*>(), -1.0);
        }
        totalDistance += value;
    }
    if((tour.size())!=(graph.getVertexSet().size())){
        cerr << "No path exists that returns to the origin and visits all nodes." << endl;
        return make_pair(vector<Vertex*>(), -1.0);
    }

    tour.push_back(first);  // Complete the cycle by returning to the start vertex

    return make_pair(tour, totalDistance);
}