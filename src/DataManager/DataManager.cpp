//
// Created by Rodrigo on 04/05/2024.
//

#include <iostream>
#include <vector>
#include "DataManager.h"

using namespace std;

DataManager::DataManager() {
    this->g=Graph();

}

void DataManager::start(int dataSet, int type) {
    switch (dataSet) {
        case 0:
            readSmall(type);
            break;
        case 1:
            readMid();
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
        int destancia = stoi(values[2]);

        if (tourism) {
            string labelOrigem = values[3];
            string labelDest = values[4];
            vertexOrigem = new Vertex(code, labelOrigem);
            vertexDest = new Vertex(destCode, labelDest);
        } else {
            vertexOrigem = new Vertex(code);
        }
        Vertex *vertexFoundDest = g.findVertex(vertexDest->getInfo());
        Vertex *vertexFoundOrig = g.findVertex(vertexOrigem->getInfo());
        if (vertexFoundDest == nullptr) {
            g.addVertex(vertexDest);
            destInGraph = false;
        }
        if (vertexFoundOrig == nullptr) {
            vertexOrigem->addEdge(vertexDest, destancia);
            g.addVertex(vertexOrigem);
        } else {
            if (destInGraph) {
                vertexFoundOrig->addEdge(vertexFoundDest, destancia);
            } else {
                vertexFoundOrig->addEdge(vertexDest, destancia);
            }
        }
    }
}

void DataManager::readMid() {
    ifstream file;
    file.open("../data/Extra_Fully_Connected_Graphs/nodes.csv");

    if (!file.is_open()) {
        cout << "Erro ao abrir o ficheiro" << endl;
        return;
    }
    string value, line;
    getline(file, line);
    while (getline(file, line)) {
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
    }
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_25.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_50.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_75.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_100.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_200.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_300.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_400.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_500.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_600.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_700.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_800.csv");
    readEdges("../data/Extra_Fully_Connected_Graphs/edges_900.csv");
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
        g.addVertex(v);
    }
    switch (type) {
        case 1:
            readEdges("../data/Real-world Graphs/graph1/edges.csv");
            break;
        case 2:
            readEdges("../data/Real-world Graphs/graph2/edges.csv");
            break;
    }
}

void DataManager::readEdges(string filePath) {
    ifstream file;
    file.open(filePath);

    if (!file.is_open()) {
        cout << "Erro ao abrir o ficheiro" << endl;
        return;
    }
    string value, line;
    getline(file, line);
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
        int dist = stoi(values[2]);
        g.addEdge(origCode, destCode, dist, true);
    }
}






