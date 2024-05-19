#include "TriangularApproximation.h"

/**
 * @brief Calculates the Haversine distance between two points on the Earth's surface.
 * @param lat1 Latitude of the first point in degrees.
 * @param lon1 Longitude of the first point in degrees.
 * @param lat2 Latitude of the second point in degrees.
 * @param lon2 Longitude of the second point in degrees.
 * @return The Haversine distance between the two points in meters.
 * @details The Haversine formula is used to calculate the distance between two points on the surface of a sphere.
 */
double haversine(double lat1, double lon1, double lat2, double lon2) {
    double rad_lat1 = lat1 * M_PI / 180;
    double rad_lon1 = lon1 * M_PI / 180;
    double rad_lat2 = lat2 * M_PI / 180;
    double rad_lon2 = lon2 * M_PI / 180;

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double aux = pow(sin(delta_lat/2),2) + cos(rad_lat1) * cos(rad_lat2) * pow(sin(delta_lon/2),2);
    double c = 2 * atan2(sqrt(aux), sqrt(1 - aux));

    return c * 6371000;
}

/**
 * @brief Calculates the distance between two vertices.
 * @param v1 Pointer to the first vertex.
 * @param v2 Pointer to the second vertex.
 * @return The distance between the two vertices.
 * @details The function first checks if there is an edge between the two vertices.
 * If there is, it returns the distance of the edge.
 * If there isn't, it calculates the haversine distance between the two vertices and returns it.
 */
double calculateDistance(Vertex* v1, Vertex* v2) {
    for(auto e : v1->getAdj()) {
        if(e->getDest()->getInfo() == v2->getInfo()) {
            return e->getdistance();
        }
    }
    return haversine(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());;
}

/**
 * @brief Executes the Prim's algorithm on the given graph.
 * @param aux The DataManager instance containing the graph and other related data.
 * @return A vector of edges representing the Minimum Spanning Tree (MST) of the graph.
 * @details The function starts by initializing a priority queue and a set of visited vertices.
 * It then iterates over all the vertices in the graph. For each vertex, it checks if it has been visited.
 * If not, it adds the vertex to the visited set and its adjacent edges to the priority queue.
 * The function continues to pop the smallest edge from the priority queue and checks if the destination vertex has been visited.
 * If not, it adds the edge to the MST and the destination vertex to the visited set.
 * This process continues until all vertices have been visited, at which point the function returns the MST.
 * @complexity O(E log V), where E is the number of edges and V is the number of vertices in the graph.
 */
vector<Edge*> prim(DataManager aux) {
    vector<Edge*> mst;
    if(aux.getG().getVertexSet().empty()) {
        return mst;
    }
    for(auto v : aux.getG().getVertexSet()) {
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    auto source = aux.getG().getVertexSet()[0];
    source->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(source);

    while(!q.empty()){
        auto v = q.extractMin();
        if(v->getPath() != nullptr) {
            mst.push_back(v->getPath());
        }
        v->setVisited(true);
        for(auto w : aux.getG().getVertexSet()) {
            if(v->getInfo() != w->getInfo() && !w->isVisited()){
                double distance = calculateDistance(v,w);
                double old_dist = w->getDist();
                if(old_dist > distance) {
                    w->setDist(distance);
                    w->setPath(new Edge(v, w, distance));
                    if(old_dist == DBL_MAX) {
                        q.insert(w);
                    }else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return mst;
}

/**
 * @brief Performs a preorder traversal on the minimum spanning tree (MST).
 * @param mst A vector of edges representing the MST.
 * @param v The starting vertex for the traversal.
 * @param path A reference to a vector of vertices where the path of the traversal will be stored.
 * @details This function performs a preorder traversal on the MST. It starts from the vertex 'v' and visits all the vertices in the MST.
 * The visited vertices are stored in the 'path' vector. The function uses a recursive approach to visit all the vertices.
 * @complexity O(V), where V is the number of vertices in the MST.
 */
void preorderTraversal(vector<Edge*> mst, Vertex* v, vector<Vertex*>& path) {
    v->setVisited(true);
    path.push_back(v);
    for(auto e : mst) {
        if(e->getOrig()->getInfo() == v->getInfo()) {
            if(e->getDest()->isVisited()) {
                preorderTraversal(mst, e->getDest(), path);
            }
        }
    }
}

/**
 * @brief Executes the Triangular Approximation algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param path A reference to a vector where the path of the traversal will be stored.
 * @details This function first creates a minimum spanning tree (MST) of the graph using Prim's algorithm.
 * Then, it performs a preorder traversal on the MST, storing the visited vertices in the 'path' vector.
 * The function finally calculates the total distance of the path and returns it.
 * @complexity O(E log 2V), where V is the number of vertices and E is the number of edges in the graph.
 */
double tspTriangular(DataManager aux, vector<Vertex*>& path) {
    double finalDistance = 0;
    vector<Edge*> mst = prim(aux);
    preorderTraversal(mst, aux.getG().getVertexSet()[0], path);
    path.push_back(aux.getG().getVertexSet()[0]);
    for(int i=0; i < path.size()-1; i++) {
        finalDistance += calculateDistance(path[i], path[i+1]);
    }

    return finalDistance;
}

/**
 * @brief Prints the path and total distance of the Triangular Approximation algorithm.
 * @param path A vector of Vertex pointers representing the path taken by the algorithm.
 * @param finalDistance The total distance covered by the path.
 * @details This function iterates over the 'path' vector and prints each vertex's information.
 * @complexity The time complexity of this function is O(n), where n is the number of vertices in the path.
 */
void printTSPTriangular(const vector<Vertex*>& path, double finalDistance) {
    cout << "Path: "<<endl;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]->getInfo()<<" ";
    }
    cout << endl;
    cout << "Total Distance: " << finalDistance << endl;
}