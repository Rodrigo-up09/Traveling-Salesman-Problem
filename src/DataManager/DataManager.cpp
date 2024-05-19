#include <iostream>
#include <vector>
#include <algorithm>
#include "DataManager.h"

using namespace std;

DataManager::DataManager() {
    this->g=Graph();
    distMatrix = (double **)malloc(10000 * sizeof(double *));
    for (int i = 0; i < 10000; i++) {
        distMatrix[i] = (double *)malloc(10000 * sizeof(double));

        // Set each element to zero
        for (int j = 0; j < 10000; j++) {
            distMatrix[i][j] = INF;
        }
    }
}

/**
    * @brief Initializes the DataManager based on the provided dataset and type.
    * @param dataSet The dataset to be used. This can be 0 for small, 1 for mid, and 2 for real.
    * @param type The type of graph to read. For small and mid datasets, this can be 0, 1, or 2. For real datasets, this can be 1 or 2.
    * @details This method decides what type of graph to read based on the provided dataset and type.
    * @complexity O(n^2) for small datasets, O(n) for mid datasets and for real datasets, where n is the number of vertices in the graph.
    */
void DataManager::start(int dataSet, int type) {
    switch (dataSet) {
        case 0:
            readSmall(type);
            break;
        case 1:
            readMid(type);
            break;
        case 2:
            if(type==1 || type==2)
                readReal(type);
            break;
    }
}

/**
    * @brief Reads a small graph from a file based on the provided type.
    * @param type The type of graph to read. This can be 0 for shipping, 1 for stadiums, and 2 for tourism.
    * @details This method opens the appropriate file based on the type parameter. It then reads each line of the file.
    * The distance between each pair of vertices is also stored in the distance matrix.
    * @complexity O(n^2), where n is the number of vertices in the graph.
    */
void DataManager::readSmall(int type) {
    ifstream file;
    bool tourism = false;
    switch (type) {
        case 0:
            file.open("../data/Toy-Graphs/shipping.csv");
            break;
        case 1:
            file.open("../data/Toy-Graphs/stadiums.csv");
            break;
        case 2:
            file.open("../data/Toy-Graphs/tourism.csv");
            tourism = true;
            break;
    }
    if (!file.is_open()) {
        cout << "Erro ao abrir o ficheiro" << endl;
        return;
    }
    string value, line;
    getline(file, line);
    int size;
    if (tourism) { size = 5; }
    else { size = 3; }

    while (getline(file, line)) {
        bool destInGraph = true;
        Vertex *vertexOrigem;
        Vertex *vertexDest;
        vector<string> values;
        istringstream info(line);
        for (int i = 0; i < size; i++) {
            getline(info, value, ',');
            values.push_back(value);
        }
        string code = values[0];
        string destCode = values[1];
        double destancia = stod(values[2]);

        if (tourism) {
            string labelOrigem = values[3];
            string labelDest = values[4];
            vertexOrigem = new Vertex(code, labelOrigem);
            vertexDest = new Vertex(destCode, labelDest);
        } else {
            vertexOrigem = new Vertex(code);
            vertexDest= new Vertex(destCode);
        }
        distMatrix[stoi(code)][stoi(destCode)]=destancia;
        distMatrix[stoi(destCode)][stoi(code)]=destancia;

        Vertex *vertexFoundDest = g.findVertex(vertexDest->getInfo());
        Vertex *vertexFoundOrig = g.findVertex(vertexOrigem->getInfo());
        if (vertexFoundDest == nullptr) {
            g.addVertex(vertexDest);
            destInGraph = false;
        }

        if (vertexFoundOrig == nullptr) {
            vertexOrigem->addEdge(vertexDest, destancia);
            vertexDest->addEdge(vertexOrigem,destancia);
            g.addVertex(vertexOrigem);
        } else {
            if (destInGraph) {
                vertexFoundOrig->addEdge(vertexFoundDest, destancia);
                vertexFoundDest->addEdge(vertexOrigem,destancia);
            } else {
                vertexFoundOrig->addEdge(vertexDest, destancia);
                vertexDest->addEdge(vertexOrigem,destancia);
            }
        }
    }

}

/**
    * @brief Reads a mid-sized graph from a file.
    * @param n The number of nodes to read from the file.
    * @details This method opens the nodes.csv file and reads the first n lines,
    * creating a vertex for each line and adding it to the graph of the DataManager instance.
    * @complexity O(n), where n is the number of vertices in the graph.
    */
void DataManager::readMid(int n) {
    int x=0;
    ifstream file;
    file.open("../data/Extra_Fully_Connected_Graphs/nodes.csv");

    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    string value, line;
    getline(file, line);
    while (getline(file, line)) {
        if(x==n)break;
        bool destInGraph = true;
        Vertex *newVertex;
        vector<string> values;
        int size = 3;
        istringstream info(line);
        for (int i = 0; i < size; i++) {
            getline(info, value, ',');
            values.push_back(value);
        }
        string code = values[0];
        string longitude = values[1];
        string latitude = values[2];
        newVertex = new Vertex(code);
        newVertex->setLatitude(stod(latitude));
        newVertex->setLongitude(stod(longitude));
        g.addVertex(newVertex);
        x++;

    }
    switch (n) {
        case 25:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_25.csv",false);
            break;
        case 50:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_50.csv",false);
            break;
        case 75:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_75.csv",false);
            break;
        case 100:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_100.csv",false);
            break;
        case 200:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_200.csv",false);
            break;
        case 300:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_300.csv",false);
            break;
        case 400:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_400.csv",false);
            break;
        case 500:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_500.csv",false);
            break;
        case 600:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_600.csv",false);
            break;
        case 700:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_700.csv",false);
            break;
        case 800:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_800.csv",false);
            break;
        case 900:
            readEdges("../data/Extra_Fully_Connected_Graphs/edges_900.csv",false);
            break;
        default:
            cout<<"especific n";
            break;
    }
}

/**
    * @brief Reads a real-world graph from a file based on the provided type.
    * @param type The type of graph to read. This can be 1 for graph1, and 2 for graph2.
    * @details This method opens the appropriate file based on the type parameter,
    * then reads each line of the file, creating vertices as it goes.
    * @complexity O(n), where n is the number of vertices in the graph.
    */
void DataManager::readReal(int type) {
    ifstream file;
    switch (type) {
        case 1:
            file.open("../data/Real-world Graphs/graph1/nodes.csv");
            break;
        case 2:
            file.open("../data/Real-world Graphs/graph2/nodes.csv");
            break;
    }
    if(!file.is_open()) {
        cout << "Erro ao abrir o ficheiro" << endl;
        return;
    }
    string value, line;
    getline(file,line);
    vector<Vertex*> vertices;
    while(getline(file,line)) {
        Vertex *v;
        vector<string> values;
        istringstream info(line);
        for(int i=0; i < 3; i++) {
            getline(info, value, ',');
            values.push_back(value);
        }
        string code = values[0];
        string lon = values[1];
        string lat = values[2];
        v = new Vertex(code);
        vertices.push_back(v);
    }
    for(auto v : vertices) {
        g.addVertex(v);
    }
    switch (type) {
        case 1:
            readEdges("../data/Real-world Graphs/graph1/edges.csv",true);
            break;
        case 2:
            readEdges("../data/Real-world Graphs/graph2/edges.csv",true);
            break;
    }
}

/**
    * @brief Reads edges from a file and adds them to the graph.
    * @param filePath The path to the file containing the edges.
    * @param flag A boolean flag indicating whether the first line of the file should be skipped.
    * @details This method opens the file specified by filePath, then reads each line of the file, creating edges.
    * @complexity O(e), where e is the number of edges in the graph.
 */
void DataManager::readEdges(string filePath, bool flag) {
    ifstream file;
    file.open(filePath);
    if (!file.is_open()) {
        cout << "Error opening file: " << filePath << endl;
        return;
    }
    string value, line;
    if(flag) {
        getline(file, line);
    }
    while (getline(file, line)) {
        vector<string> values;
        int size = 3;
        istringstream info(line);
        for (int i = 0; i < size; i++) {
            getline(info, value, ',');
            values.push_back(value);
        }
        string origCode = values[0];
        string destCode = values[1];
        double dist = stod(values[2]);
        distMatrix[stoi(origCode)][stoi(destCode)]= dist;
        distMatrix[stoi(destCode)][stoi(origCode)]= dist;
        g.addEdge(origCode, destCode, dist, false);
    }
}

/**
    * @brief Gets the graph.
    * @return the graph.
    */
Graph DataManager::getG() {
    return g;
}

/**
    * @brief Sets the graph.
    * @param graph The graph to set.
    */
void DataManager::setG(Graph graph) {
    this->g=graph;

}

/**
    * @brief Gets the distance matrix.
    * @return A reference to the distance matrix.
    */
double** &DataManager::getDistMatrix()  {
    return this->distMatrix;
}

/**
    * @brief Sets the distance matrix.
    * @param distMatrix A reference to the distance matrix to set.
    */
void DataManager::setDistMatrix(double **&distMatrix) {
    this->distMatrix=distMatrix;

}

/**
    * @brief Prints the vertices and their adjacent vertices of the graph.
    * @param g The graph to be printed.
    * @details This method iterates over each vertex in the graph and prints the vertex's information
    * and the information of its adjacent vertices along with the distance to them.
    * @complexity O(v + e), where v is the number of vertices and e is the number of edges in the graph.
    */
void DataManager::printGraph(const Graph &g) {
    for (const auto& vertex : g.getVertexSet()) {
        std::cout << "Vertex: " << vertex->getInfo() << std::endl;
        std::cout << "Adjacent vertices: ";
        for (const auto& edge : vertex->getAdj()) {
            std::cout << edge->getDest()->getInfo() << " (distance: " << edge->getdistance() << ") ";
        }
        std::cout << std::endl;
    }
}

/**
    * @brief Copies the state of the current DataManager instance to another.
    * @param copy The DataManager instance to copy to.
    */
void DataManager::copy(DataManager &copy) {
    copy.setDistMatrix(distMatrix);
    copy.setG(g);
}







