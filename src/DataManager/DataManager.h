/**
 * @file DataManager.h
 * @brief Declaration of the DataManager class.
 */

#ifndef DAPROJ2_DATAMANAGER_H
#define DAPROJ2_DATAMANAGER_H

#include "Graph/graph.h"

#include <string>
#include <fstream>
#include <sstream>
#include <limits>

#define INF std::numeric_limits<double>::infinity()

using namespace std;
/**
 * @class DataManager
 * @brief Manages data related to the Graph.
 */
class DataManager {
public:
    /**
     * @brief Constructor for DataManager class.
     */
    DataManager();

    /**
     * @brief Starts the data manager and performs initialization.
     * @param dataSet Indicating what type of graph to read.
     * @param type Indicating what graph to read.
     */
    void start(int dataSet,int type);

    void readSmall(int type);
    void readMid(int n);
    void readReal(int type);
    void readEdges(string filePath, bool flag);

    /**
     * @brief Gets the graph.
     * @return the graph.
     */
    Graph getG();

    /**
     * @brief Sets the graph.
     * @param graph The graph to set.
     */
    void setG(Graph graph);

    /**
     * @brief Gets the distance matrix.
     * @return A reference to the distance matrix.
     */
    double** &getDistMatrix() ;

    /**
     * @brief Sets the distance matrix.
     * @param distMatrix A reference to the distance matrix to set.
     */
    void setDistMatrix(double **&distMatrix);

    /**
     * @brief Prints the graph.
     * @param g The graph to be printed.
     */
    void printGraph(const Graph &g);

    /**
     * @brief Copies the state of the current DataManager instance to another.
     * @param copy The DataManager instance to copy to.
     */
    void copy(DataManager& copy);

private:
    Graph g;
    double **distMatrix;

};

#endif //DAPROJ2_DATAMANAGER_H
