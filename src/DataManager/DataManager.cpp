//
// Created by Rodrigo on 04/05/2024.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "DataManager.h"

using namespace std;

DataManager::DataManager() {
    this->g=Graph();
    distMatrix = std::vector<std::vector<double>>(1000, std::vector<double>(100000, 0.0));

}

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
    vector<Vertex*> copy=g.getVertexSet();
    std::sort(copy.begin(), copy.end(), [](const Vertex* v1, const Vertex* v2) {
        return v1->getInfo() < v2->getInfo();
    });
    g.setVertexSet(copy);
}

//01:14 minutos


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
    distMatrix.resize(vertices.size(), vector<double>(vertices.size(), 0.0));
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

Graph DataManager::getG() {
    return g;
}

 vector<vector<double>> &DataManager::getDistMatrix()  {
    return this->distMatrix;
}

void DataManager::setDistMatrix(const vector<vector<double>> &distMatrix) {
    this->distMatrix=distMatrix;

}

Graph &DataManager::getGC() {
    return g;
}

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







