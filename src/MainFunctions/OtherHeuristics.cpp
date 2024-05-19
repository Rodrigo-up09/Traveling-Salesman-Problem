#include "OtherHeuristics.h"

/**
 * @brief Computes the centroid of a cluster of vertices.
 * @param cluster A vector of pointers to the vertices in the cluster.
 * @return A Point object representing the centroid of the cluster.
 * @details This function calculates the centroid of a cluster of vertices by averaging the latitude and longitude of all vertices in the cluster.
 * The centroid is returned as a Point object, where the x-coordinate represents the average latitude and the y-coordinate represents the average longitude.
 * @complexity O(n), where n is the number of vertices in the cluster.
 */
Point computeCentroid(const vector<Vertex*>& cluster) {
    double sumX = 0.0, sumY = 0.0;
    int n = cluster.size();
    for (const auto& vertex : cluster) {
        sumX += vertex->getLatitude();
        sumY += vertex->getLongitude();
    }
    return {sumX / n, sumY / n};
}

/**
 * @brief Calculates the distance between two points.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Euclidean distance between the two points.
 * @details This function calculates the Euclidean distance between two points in a 2D space.
 * The Euclidean distance is calculated as the square root of the sum of the squared differences in the x and y coordinates of the two points.
 */
double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x, p2.x) + pow(p1.y, p2.y));
}

/**
 * @brief Sorts a vector of clusters based on the distance of their centroids from the origin.
 * @param clusters A reference to a vector of clusters, where each cluster is represented as a vector of Vertex pointers.
 * @return A vector of clusters sorted by the distance of their centroids from the origin.
 * @details This function calculates the centroid of each cluster and then sorts the clusters based on the distance of their centroids from the origin.
 * The function uses the `computeCentroid` function to calculate the centroid of each cluster and the `calculateDistance` function to calculate the distance of each centroid from the origin.
 * The function returns a new vector of clusters sorted by centroid distance. The original vector of clusters is not modified.
 * @complexity The time complexity is O(n log n), where n is the number of clusters.
 */
vector<vector<Vertex*>> sortClustersByCentroidDistance(vector<vector<Vertex*>>& clusters) {
    vector<Point> centroids;
    for (const auto& cluster : clusters) {
        centroids.push_back(computeCentroid(cluster));
    }

    vector<int> indices(clusters.size(), 0);

    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return calculateDistance(centroids[i], centroids[0]) < calculateDistance(centroids[j], centroids[0]);
    });

    vector<vector<Vertex*>> sortedClusters;
    for (int idx : indices) {
        sortedClusters.push_back(clusters[idx]);
    }

    return sortedClusters;
}

/**
 * @brief Divides the graph into clusters.
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @return A vector of integers, where each integer represents the index of the first vertex in each cluster.
 * @details The function iterates over the vertices of the graph. For every 'k' vertices, it adds the index of the first vertex to the vector of clusters.
 * If the total number of vertices is not a multiple of 'k', the last cluster will contain the remaining vertices.
 * @complexity The time complexity is O(n), where n is the number of vertices in the graph.
 */
vector<int> cluster_graph(DataManager aux, int k) {
    vector<Vertex *> vertexes = aux.getG().getVertexSet();
    vector<int> closures = {};
    for (size_t i = 0; i < vertexes.size(); i = i+k) {
        closures.push_back(i);
    }
    return closures;
}

/**
 * @brief Executes the dynamic programming algorithm for the Traveling Salesman Problem (TSP).
 * @param distances A 2D vector representing the distances between each pair of vertices.
 * @param vertices A vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param pos The current position in the path.
 * @param mask A bitmask representing the set of visited vertices.
 * @param k The total number of vertices in the graph.
 * @param path A pair consisting of the current total distance and a vector of pairs representing the current path.
 * @return A pair consisting of the minimum total distance and a vector of pairs representing the optimal path.
 * @details This function implements the dynamic programming approach for the TSP. It recursively explores all possible paths in the graph,
 * updating the minimum total distance and the optimal path whenever a shorter path is found. The function uses a bitmask to keep track of the visited vertices,
 * which allows it to efficiently avoid visiting the same vertex more than once. The function stops when all vertices have been visited and returns to the origin vertex.
 * @complexity The time complexity is O(n^2 * 2^n), where n is the number of vertices in the graph.
 */
pair<double,vector<pair<int,Vertex *>>> tsp_dynamic_programming(vector<vector<double>> distances, vector<pair<int,Vertex *>> vertices, int pos, int mask, int k, pair<int,vector<pair<int,Vertex *>>> path) {
    int allVisited = (1 << k) - 1;
    if (mask == allVisited) {
        return path;
    }

    pair<double,vector<pair<int,Vertex*>>> best_path;
    double min_length = std::numeric_limits<double>::infinity();

    for (int i = 0; i < k; ++i) {
        if (!(mask & (1 << i))) {
            pair<double, vector<pair<int, Vertex*>>> new_path = path;
            new_path.second.push_back(vertices[i]);
            int new_mask = mask | (1 << i);

            pair<double,vector<pair<int,Vertex*>>> result = tsp_dynamic_programming(distances, vertices, i, new_mask, k, new_path);

            double tour_length = 0.0;
            for (int j = 0; j < result.second.size() - 1; ++j) {
                tour_length += distances[result.second[j].first][result.second[j+1].first];
            }

            if (tour_length < min_length) {
                min_length = tour_length;
                best_path = result;
                best_path.first = min_length;
            }
        }
    }
    return best_path;
}

/**
 * @brief Joins two sets of vertices into a single set.
 * @param set1 A pair consisting of the total distance of the first set's path and a vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param set2 A pair consisting of the total distance of the second set's path and a vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A pair consisting of the total distance of the joined path and a vector of pairs representing the joined path.
 * @details This function takes two sets of vertices, each represented as a pair of total distance and a vector of pairs (integer index and Vertex pointer).
 * It then calculates the minimum total distance to join the two sets into a single set. The function iterates over each pair of vertices
 * in the two sets and calculates the new total distance if the sets were joined at that pair of vertices. If the new total distance is less
 * than the current minimum total distance, it updates the minimum total distance and the best joined path. The function returns the minimum total
 * distance and the best joined path as a pair.
 * @complexity The time complexity is O(n^2), where n is the number of vertices in the larger set.
 */
pair<double,vector<pair<int, Vertex *>>> joinSets(pair<double,vector<pair<int, Vertex *>>> set1, pair<double,vector<pair<int, Vertex *>>> set2, bool toy) {
    pair<int,vector<pair<int, Vertex *>>> merged;
    if (set1.second.empty()) {
        set1 = set2;
        return set1;
    }
    else {
        Vertex * single1 = set1.second.back().second;
        Vertex * single2 = set2.second[0].second;
        double distance = 0;
        if (toy) {
            Edge * connection;
            for (auto i : single1->getAdj()) {
                if (i->getDest()->getInfo() == single2->getInfo()) {
                    connection = i;
                }
            }
            distance = set1.first + set2.first + connection->getdistance();
        }
        else {
            distance = set1.first + set2.first + haversine(single1->getLatitude(), single1->getLongitude(), single2->getLatitude(), single2->getLongitude());
        }
        vector<pair<int, Vertex*>> joinedPath;
        joinedPath.insert(joinedPath.end(), set1.second.begin(), set1.second.end());
        joinedPath.insert(joinedPath.end(), set2.second.begin(), set2.second.end());
        return {distance, joinedPath};
    } 
}

/**
 * @brief Calculates the distance between each pair of vertices.
 * @param vertices A vector of pairs, where each pair contains an integer index and a pointer to a Vertex.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A 2D vector representing the distances between each pair of vertices.
 * @details This function calculates the distance between each pair of vertices in the given vector.
 * If the 'toy' flag is set to true, the function uses toy distances; otherwise, it uses real distances.
 * The function returns a 2D vector where the element at position (i, j) represents the distance between vertices[i] and vertices[j].
 * @complexity The time complexity is O(n^2), where n is the number of vertices in the graph.
 */
vector<vector<double>> getDistances(vector<pair<int, Vertex *>> vertices, bool toy) {
    vector<vector<double>> distances(vertices.size(), vector<double>(vertices.size(), 0.0));
    for (auto col: vertices) {
        for (auto row: vertices) {
            if (col.first != row.first) {
                if (toy) {
                    for (auto y: col.second->getAdj()) {
                        if (y->getDest()->getInfo() == row.second->getInfo()) {
                            distances[col.first][row.first] = y->getdistance();
                            break;
                        }
                    }
                } else {
                    distances[col.first][row.first] = haversine(col.second->getLatitude(),
                                                                col.second->getLongitude(),
                                                                row.second->getLatitude(),
                                                                row.second->getLongitude());
                }
            }
        }
    }
    return distances;
}

/**
 * @brief Executes a heuristic algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return The minimum total distance of the path.
 * @details This function implements a heuristic algorithm for the TSP. It starts by dividing the graph into clusters of 'k' vertices each.
 * For each cluster, it calculates the optimal path using the dynamic programming approach for the TSP. It then joins the clusters into a single set,
 * calculating the minimum total distance to join the clusters. The function returns the minimum total distance of the joined path.
 * If the 'toy' flag is set to true, the function uses toy distances; otherwise, it uses real distances.
 * @complexity The time complexity is O(n^2 * 2^n), where n is the number of vertices in the graph.
 */
double OtherHeuristic(DataManager aux, int k, bool toy) {
   vector<Vertex *> vertices = aux.getG().getVertexSet();
   vector<pair<int,Vertex *>> workingVertices = {};
   pair<int,vector<pair<int, Vertex *>>> finalPath;
   finalPath.first = 0;
   finalPath.second = {};
   vector<int> clusters = cluster_graph(aux, k);
   int i = 0;
   for (int y : clusters) {
        for (int w = 0; w < k; w++) {
            if (y + w > vertices.size() - 1) {
                break;
            }
            workingVertices.push_back({i, vertices[y + w]});
            i++;
        }
        vector<vector<double>> distances = getDistances(workingVertices, toy);
        finalPath = joinSets(finalPath, tsp_dynamic_programming(distances, workingVertices, 0, 0, k, {0, {}}), toy);
    }
    if (toy) {
        int x;
        for (auto y: finalPath.second.back().second->getAdj()) {
            if (y->getDest()->getInfo() == finalPath.second[0].second->getInfo()) {
                x = y->getdistance();
            }
        }
        finalPath.first += x;
    }
    else {
        int x;
        Vertex* v1 = finalPath.second[0].second;
        Vertex* v2 = finalPath.second.back().second;
        x = haversine(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
        finalPath.first += x;
    }
    return finalPath.first;
}

/**
 * @brief Executes a heuristic algorithm for the Traveling Salesman Problem (TSP).
 * @param aux The DataManager instance containing the graph and other related data.
 * @param k The number of vertices in each cluster.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return The minimum total distance of the path.
 * @details This function implements a heuristic algorithm for the TSP. It starts by dividing the graph into clusters of 'k' vertices each.
 * For each cluster, it calculates the optimal path using the dynamic programming approach for the TSP. It then joins the clusters into a single set,
 * calculating the minimum total distance to join the clusters. The function returns the minimum total distance of the joined path.
 * If the 'toy' flag is set to true, the function uses toy distances; otherwise, it uses real distances.
 * @complexity The time complexity is O(n^2 * 2^n), where n is the number of vertices in the graph.
 */
double OtherHeuristic2(DataManager aux, int k, bool toy) {
    vector<Vertex *> vertices = aux.getG().getVertexSet();
    vector<vector<Vertex*>> divisions;
    pair<int,vector<Vertex *>> finalPath;
    finalPath.first = 0;
    finalPath.second = {};
    vector<int> clusters = cluster_graph(aux, k);
    for (int y : clusters) {
        vector<Vertex *> workingVertices = {};
        for (int w = 0; w < k; w++) {
            if (y + w > vertices.size() - 1) {
                break;
            }
            workingVertices.push_back( vertices[y + w]);
        }
        vector<Vertex*> path1;
        if (toy) {
            double distance = adaptedTspTriangular(workingVertices, path1);
            finalPath = joinSets2(finalPath, {distance, workingVertices}, toy);
        }
        else {
            divisions.push_back(workingVertices);
        }
    }
    if (toy) {
        int x;
        for (auto y: finalPath.second.back()->getAdj()) {
            if (y->getDest()->getInfo() == finalPath.second[0]->getInfo()) {
                x = y->getdistance();
            }
        }
        finalPath.first += x;
    }
    else {
        vector<Vertex*> path1;
        sortClustersByCentroidDistance(divisions);
        finalPath.first = adaptedTspTriangular(divisions[0], path1);
        finalPath.second = path1;
        for (auto i = 1; i < divisions.size(); i++) {
            path1 = {};
            double dis = adaptedTspTriangular(divisions[i], path1);
            finalPath = joinClustersWithPaths(finalPath, {dis, path1});
        }
    }
    return finalPath.first;
}

/**
 * @brief Executes a modified version of the TSP algorithm using a triangular inequality.
 * @param vertices A vector of pointers to the vertices of the graph.
 * @param path A reference to a vector of vertices where the path will be stored.
 * @return The minimum total distance of the path.
 * @details This function implements a heuristic algorithm for the TSP. It starts by finding the Minimum Spanning Tree (MST) of the graph using the Prim's algorithm.
 * Then, it performs a preorder traversal of the MST to obtain a path. This path is not necessarily optimal, but it is a good approximation.
 * The function stores the path in the 'path' vector and returns the total distance of the path.
 * If the 'toy' flag is set to true, the function uses toy distances; otherwise, it uses real distances.
 * @complexity The time complexity is O(n^2 log n), where n is the number of vertices in the graph.
 */
double adaptedTspTriangular(vector<Vertex*> vertices, vector<Vertex*>& path) {
    double finalDistance = 0;
    vector<Edge*> mst = adaptedPrim(vertices);
    preorderTraversal(mst, vertices[0], path);
    path.push_back(vertices[0]);
    for(int i=0; i < path.size()-1; i++) {
        finalDistance += calculateDistance(path[i], path[i+1], false);
    }

    return finalDistance;
}

/**
 * @brief Executes the Prim's algorithm to find the Minimum Spanning Tree (MST) of a graph.
 * @param vertices A vector of pointers to the vertices of the graph.
 * @return A vector of pointers to the edges that form the MST.
 * @details This function implements the Prim's algorithm to find the MST of a graph. It starts with an arbitrary vertex
 * and greedily grows the MST by adding the minimum weight edge that connects the tree to a vertex not yet in the tree.
 * The function uses a priority queue to efficiently select the next edge to add to the MST. The function returns a vector o
 * f pointers to the edges that form the MST.
 * @complexity The time complexity is O(E log V), where E is the number of edges and V is the number of vertices in the graph.
 */
vector<Edge*> adaptedPrim(vector<Vertex*> vertices) {
    vector<Edge*> mst;
    if(vertices.empty()) {
        return mst;
    }
    for(auto v : vertices) {
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    auto source = vertices[0];
    source->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(source);

    while(!q.empty()){
        auto v = q.extractMin();
        if(v->getPath() != nullptr) {
            mst.push_back(v->getPath());
        }
        v->setVisited(true);
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            if(!w->isVisited()){
                double old_dist = w->getDist();
                if(old_dist > e->getdistance()) {
                    w->setDist(e->getdistance());
                    w->setPath(e);
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
 * @brief Joins two sets of vertices into a single set.
 * @param set1 A pair consisting of the total distance of the first set's path and a vector of vertices representing the first set's path.
 * @param set2 A pair consisting of the total distance of the second set's path and a vector of vertices representing the second set's path.
 * @param toy A boolean flag indicating whether the function should use toy distances or real distances.
 * @return A pair consisting of the total distance of the joined path and a vector of vertices representing the joined path.
 * @details This function takes two sets of vertices, each represented as a pair of total distance and a vector of vertices.
 * It then calculates the minimum total distance to join the two sets into a single set. The function iterates over each pair of vertices
 * in the two sets and calculates the new total distance if the sets were joined at that pair of vertices. If the new total distance is less
 * than the current minimum total distance, it updates the minimum total distance and the best joined path. The function returns the minimum total
 * distance and the best joined path as a pair. If the 'toy' flag is set to true, the function uses toy distances; otherwise, it uses real distances.
 * @complexity The time complexity is O(n^2), where n is the number of vertices in the larger set.
 */
pair<double,vector< Vertex*>> joinSets2(pair<double,vector< Vertex*>> set1, pair<double,vector< Vertex*>> set2, bool toy) {
    pair<int,vector<pair<int, Vertex *>>> merged;
    if (set1.second.empty()) {
        set1 = set2;
        return set1;
    }
    else {
        Vertex * single1 = set1.second.back();
        Vertex * single2 = set2.second[0];
        double distance = 0;
        if (toy) {
            Edge * connection;
            for (auto i : single1->getAdj()) {
                if (i->getDest()->getInfo() == single2->getInfo()) {
                    connection = i;
                }
            }
            distance = set1.first + set2.first + connection->getdistance();
        }
        else {
            distance = set1.first + set2.first + haversine(single1->getLatitude(), single1->getLongitude(), single2->getLatitude(), single2->getLongitude());
        }
        vector< Vertex*> joinedPath;
        joinedPath.insert(joinedPath.end(), set1.second.begin(), set1.second.end());
        joinedPath.insert(joinedPath.end(), set2.second.begin(), set2.second.end());
        return {distance, joinedPath};
    }
}

/**
 * @brief Joins two clusters of vertices into a single cluster.
 * @param cluster1 A pair consisting of the total distance of the first cluster's path and a vector of vertices representing the first cluster's path.
 * @param cluster2 A pair consisting of the total distance of the second cluster's path and a vector of vertices representing the second cluster's path.
 * @return A pair consisting of the total distance of the joined path and a vector of vertices representing the joined path.
 * @details This function takes two clusters of vertices, each represented as a pair of total distance and a vector of vertices.
 * It then calculates the minimum total distance to join the two clusters into a single cluster. The function iterates over each pair of vertices
 * in the two clusters and calculates the new total distance if the clusters were joined at that pair of vertices. If the new total distance is less
 * than the current minimum total distance, it updates the minimum total distance and the best joined path. The function returns the minimum total
 * distance and the best joined path as a pair.
 * @complexity The time complexity is O(n^2), where n is the number of vertices in the larger cluster.
 */
pair<double, std::vector<Vertex*>> joinClustersWithPaths(
        const std::pair<double, std::vector<Vertex*>>& cluster1,
        const std::pair<double, std::vector<Vertex*>>& cluster2) {

    double minTotalDistance = std::numeric_limits<double>::infinity();
    vector<Vertex*> bestJoinedPath;

    double originalDistance1 = cluster1.first;
    double originalDistance2 = cluster2.first;
    const std::vector<Vertex*>& path1 = cluster1.second;
    const std::vector<Vertex*>& path2 = cluster2.second;

    for (size_t i = 0; i < path1.size() - 1; ++i) {
        for (size_t j = 0; j < path2.size() - 1; ++j) {
            double distRemoved1 = calculateDistanceVer(path1[i], path1[i + 1]);
            double distRemoved2 = calculateDistanceVer(path2[j], path2[j + 1]);
            double distAdded1 = calculateDistanceVer(path1[i], path2[j]);
            double distAdded2 = calculateDistanceVer(path1[i + 1], path2[j + 1]);
            double newTotalDistance = originalDistance1 + originalDistance2
                                      - distRemoved1 - distRemoved2
                                      + distAdded1 + distAdded2;

            if (newTotalDistance < minTotalDistance) {
                minTotalDistance = newTotalDistance;

                std::vector<Vertex*> newPath;
                newPath.insert(newPath.end(), path1.begin(), path1.begin() + i + 1);
                newPath.insert(newPath.end(), path2.begin() + j + 1, path2.end());
                newPath.insert(newPath.end(), path2.begin(), path2.begin() + j + 1);
                newPath.insert(newPath.end(), path1.begin() + i + 1, path1.end());

                bestJoinedPath = newPath;
            }
        }
    }

    return {minTotalDistance, bestJoinedPath};
}

/**
 * @brief Calculates the distance between two vertices using the Haversine formula.
 * @param a A pointer to the first vertex.
 * @param b A pointer to the second vertex.
 * @return The distance between the two vertices.
 * @details This function calculates the distance between two vertices based on their latitude and longitude.
 * It uses the Haversine formula, which calculates the distance between two points on the surface of a sphere.
 * The function assumes that the Earth is a perfect sphere, which is a good approximation for short distances.
 */
double calculateDistanceVer(Vertex* a, Vertex* b) {
    return haversine(a->getLatitude(), a->getLongitude(), b->getLatitude(), b->getLongitude());
}



