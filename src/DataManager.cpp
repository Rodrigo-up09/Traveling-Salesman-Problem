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
        Vertex *vertex;
        vector<string> values;
        istringstream info(line);
        for (int i = 0; i < size; i++) {
            getline(info, value, ',');
            values.push_back(value);
        }
        string code = values[0];
        double longitude = stod(values[1]);
        double latitude = stod(values[2]);
        if (tourism) {
            string labelOrigem = values[3];
            vertex = new Vertex(code, longitude, latitude, labelOrigem);
        } else {
            vertex = new Vertex(code, longitude, latitude);
        }
        g.addVertex(vertex);
    }
}

