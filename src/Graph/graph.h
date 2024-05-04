
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
   
    Vertex(const string& code);

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

    Edge* addEdge(Vertex* dest, int capacity, bool direction);

    void deleteEdge(Edge *edge);

protected:

    std::string info;              
    std::vector<Edge*> adj;        
    std::vector<Edge*> incoming;

    bool visited = false;          
    bool processing = false;       
    double dist = 0;
    Edge* path = nullptr;
    int latitude = 0;
    int longitude = 0;
    string dest_label = "";
    string orig_label = "";



};


class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, int c, bool direction);
    void setCapacity(int capacity);
    ~Edge();

    Vertex* getDest();
    int getCapacity() const; 
    bool isSelected() const; 
    Vertex* getOrig() const; 
    Edge* getReverse() const; 
    void setSelected(bool selected); 
    void setReverse(Edge* reverse); 
protected:
    Vertex* dest; 
    int disntance; 
    bool selected = false;
    Vertex* orig; 
    Edge* reverse = nullptr; 
    bool isReverse;
};

class Graph{
public:
    Graph();
    Vertex* findVertex(const string &code) const;
    void addVertex(const string &code);
    void addVertexWithEdges(Vertex *vertex);
    bool removeVertex(const string &code);
    bool addEdge(const string &source, const string &dest, int capacity, bool direction);
    bool removeEdge(const string &source, const string &dest);
    void clear();
    unordered_map<string, Vertex*> getVertexSet() const;

protected:
    unordered_map<string, Vertex*> vertexset; 
};

#endif 