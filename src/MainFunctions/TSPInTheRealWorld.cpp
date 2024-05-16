
#include <queue>
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



//Greedy heuristic
//Algoritm that is better than the nn, but still with not the best preformance.
//This algoritm iterate throw all the vertex, and check the shortest edge.Always cheking it the smallest edge have an Indegree of 1,if it have a Indegree>1,can go to that edge.
//At the end it goes to the init vertice,its a better aproximation than the nn algoritm

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
pair<vector<Vertex*>, double> greedyTSP(Graph graph, const string& origin) {

    vector<Vertex *> tour;
    Vertex* lastVertex = nullptr;
    double totalDistance = 0.0;
    Vertex *currentVertex = graph.findVertex(origin);
    if (currentVertex == nullptr) {
        cerr << "Origin vertex not found in the graph." << endl;
        return make_pair(tour, totalDistance);
    }
    for(auto vertex:graph.getVertexSet()){

        if(vertex!=currentVertex){
           lastVertex=vertex;
        }
        double smallestDist=numeric_limits<double>::max();
        Edge* smallEdgge=nullptr;
        for(Edge*  edge:vertex->getAdj()){
            bool degree=edge->getDest()->getPath()== nullptr;
            if(edge->getdistance()<smallestDist && (degree)){
                smallestDist=edge->getdistance();
                smallEdgge=edge;
            }
        }
        totalDistance+=smallEdgge->getdistance();
        if(smallEdgge!= nullptr) {
            vertex->setPath(smallEdgge);
        }
    }
    if (lastVertex != nullptr) {
        Edge* edgeToOrigin = graph.getEdgeP(lastVertex,currentVertex);
        if (edgeToOrigin != nullptr) {
            totalDistance += edgeToOrigin->getdistance();
            lastVertex->setPath(edgeToOrigin);

        }
        if(edgeToOrigin!= nullptr){
            cerr<<"Graph is not conected";
        }
    }
    GetTour(currentVertex,tour);
    return make_pair(tour,totalDistance);



}//not tested




void printTour(const vector<Vertex*>& tour, double totalDistance) {
    cout << "Tour: ";
    for (Vertex* vertex : tour) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
    cout << "Total distance: " << totalDistance << endl;
}
pair<vector<Vertex*>, double> greedyTSP2(Graph graph, const string& origin, vector<vector<double>> distMatrix) {//very good,but dont know why with big dataSets repeat numbers
    
    vector<Vertex *> tour;
    double totalDistance = 0.0;
    Vertex *currentVertex = graph.findVertex(origin);
    Vertex *first = currentVertex;
    Vertex *lastAddedVertex = nullptr; // Store the last added vertex
    if (currentVertex == nullptr) {
        cerr << "Origin vertex not found in the graph." << endl;
        return make_pair(tour, totalDistance);
    }


    graph.setAllNonVisited();


    priority_queue<pair<double, Edge*>, vector<pair<double, Edge*>>, greater<>> pq;


    for (auto edge : currentVertex->getAdj()) {
        pq.push({edge->getdistance(), edge});
    }

    currentVertex->setVisited(true); // Mark the current vertex as visited


    while (!pq.empty()) {
        auto [distance, edge] = pq.top();
        pq.pop();
        Vertex *nextVertex = edge->getDest();

        // Check if the next vertex has not been visited and it's not the same as the first vertex (to ensure bidirectionality)
        if (!nextVertex->isVisited() && nextVertex != first) {
            tour.push_back(nextVertex);
            lastAddedVertex = nextVertex; // Update the last added vertex
            nextVertex->setVisited(true);
            totalDistance += distance;


            for (auto nextEdge : nextVertex->getAdj()) {
                pq.push({nextEdge->getdistance(), nextEdge});
            }
        }
    }



    // Add the distance between the last added vertex and the origin to the total distance
    if (lastAddedVertex != nullptr) {
        int a = stoi(origin);
        int b = stoi(lastAddedVertex->getInfo());
        double value = distMatrix[a][b];
        totalDistance += value;
    }
    tour.push_back(first);

    return make_pair(tour, totalDistance);
}

// Christofides algorithm
//this algoritm first get the mst-i will use prime algoritm
//But there is a problem this algoritm just handle complete graph,so maybe it can be a risky solotion

std::vector<Vertex*> prim(Graph* g) {
    // Initialize
    if (g->getVertexSet().empty()) return g->getVertexSet();
    double INF = std::numeric_limits<double>::infinity();
    for (Vertex* vertex : g->getVertexSet()) {
        vertex->setDist(INF);
        vertex->setPath(nullptr);
        vertex->setVisited(false);
    }
    // Obtain a random vertex
    Vertex* start = g->getVertexSet().front();
    start->setDist(0);
    priority_queue<Vertex*> q;
    q.push(start);
    while (!q.empty()) {
        Vertex* v = q.top();
        q.pop();
        v->setVisited(true);
        for (Edge* edge : v->getAdj()) {
            Vertex* w = edge->getDest();
            if (!w->isVisited()) {
                double old_dist = w->getDist();
                if (old_dist > edge->getdistance()) {
                    w->setDist(edge->getdistance());
                    w->setPath(edge);
                    if (old_dist == INF) {
                        q.push(w);
                    }
                }
            }
        }
    }
    return g->getVertexSet();
}


