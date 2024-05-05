
#ifndef PROJETDA2_GRAPH_H
#define PROJETDA2_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Edge;

class Vertex {
public:
   
    Vertex(const string& code,  double longitude,  double latitude);
    Vertex(const string &code, double longitude, double latitude, const string& label);
    std::vector<Edge*> getAdj(); 
    std::vector<Edge*> getIncoming(); 
    bool isVisited() const; 
    bool isProcessing() const;
    double getDist() const; 
    Edge* getPath() const; 
    std::string getInfo() const;

    void setInfo(const std::string& info); 
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setDist(double dist);
    void setPath(Edge* path);

    void setLatitude(double latitude);
    double getLatitude() const;
    double getLongitude() const;

    void setLongitude(double longitude);

    Edge* addEdge(Vertex* dest, int distance);
    const string &getLabel() const;

    void setLabel(const string &label);
    void deleteEdge(Edge *edge);

protected:

    std::string info;              
    std::vector<Edge*> adj;        
    std::vector<Edge*> incoming;
    string label;
    bool visited;
    bool processing;
    double dist;
    Edge* path ;
    double latitude;
    double longitude;

};


class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, int distance);
    void setDistance(int distance);
    ~Edge();

    Vertex* getDest();
    int getdistance() const;
    bool isSelected() const; 
    Vertex* getOrig() const; 
    Edge* getReverse() const; 
    void setSelected(bool selected); 
    void setReverse(Edge* reverse); 
protected:
    Vertex* dest; 
    int distance;
    bool selected = false;
    Vertex* orig; 
    Edge* reverse = nullptr; 
    bool isReverse;
};

class Graph {
public:
    Graph();

    Vertex *findVertex(const string &code) const;

    void addVertex(Vertex *vertex);
    

    bool removeVertex(const string &code);

    bool addEdge(const string &source, const string &dest, int distance, bool direction);

    bool removeEdge(const string &source, const string &dest);

    void clear();

    vector<Vertex *> getVertexSet() const;

protected:
    vector<Vertex *> vertexset;
};

#endif 