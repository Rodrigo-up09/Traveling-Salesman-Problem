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
    switch ( dataSet) {
        case 0:
            readSmall(type);
            break;
        case 1:
            readMid();
            break;
        case 2:
            readReal();
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

