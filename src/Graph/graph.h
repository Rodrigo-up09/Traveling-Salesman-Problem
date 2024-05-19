/**
 * @file graph.h
 * @brief Declaration of the graph class and its associated classes.
 */

#ifndef PROJETDA2_GRAPH_H
#define PROJETDA2_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * @class Edge
 * @brief Represents an Edge in a graph.
 */
class Edge;

/**
 * @class Vertex
 * @brief Represents a Vertex in a graph.
 */
class Vertex {
public:

    /**
     * @brief Constructor for Vertex class.
     * @param code The code representing the Vertex.
     */
    Vertex(const string& code);

    /**
     * @brief Constructor for Vertex class.
     * @param code The code representing the Vertex.
     * @param label The label or tag associated with the Vertex.
     */
    Vertex(const string &code, const string& label);

    //Getters
    std::vector<Edge*> getAdj(); 
    std::vector<Edge*> getIncoming(); 
    bool isVisited() const; 
    bool isProcessing() const;
    double getDist() const; 
    Edge* getPath() const; 
    std::string getInfo() const;
    double getLatitude() const;
    double getLongitude() const;
    const string &getLabel() const;
    unsigned int getQueueIndex() const;

    //Setters
    void setInfo(const std::string& info); 
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setDist(double dist);
    void setPath(Edge* path);
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setLabel(const string &label);
    void setQueueIndex(unsigned int index);

    /**
     * @brief Compares this vertex with another for ordering purposes.
     * @param other The other vertex to compare with.
     * @return True if this vertex's distance is less than the other vertex's distance, false otherwise.
     */
    bool operator<(const Vertex& other) const;

    /**
     * @brief Adds an edge form this vertex to the specified destination vertex.
     * @param dest The destination vertex.
     * @param distance The distance between the two vertex.
     * @return Pointer to the created edge.
     */
    Edge* addEdge(Vertex* dest, double distance);

    /**
     * @brief Deletes the specified edge from the outgoing edges of this vertex.
     * @param edge Pointer to the edge to be deleted.
     */
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
    unsigned int queueIndex;

};

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 */
class Edge {
public:

    /**
     * @brief Constructor for Edge class.
     * @param orig The origin vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @param distance The distance between orig and dest.
     */
    Edge(Vertex* orig, Vertex* dest, double distance);
    ~Edge();

    //Getters
    Vertex* getDest();
    double getdistance() const;
    bool isSelected() const; 
    Vertex* getOrig() const; 
    Edge* getReverse() const;

    //Setters
    void setDistance(double distance);
    void setSelected(bool selected); 
    void setReverse(Edge* reverse);

protected:

    Vertex* dest;
    double distance;
    bool selected = false;
    Vertex* orig; 
    Edge* reverse = nullptr; 
    bool isReverse;
    bool operator>(const Edge& other) const;
};

/**
 * @class Graph
 * @brief Represents a graph.
 */
class Graph {
public:
    /**
     * @brief Constructor for Graph class.
     */
    Graph();

    /**
    * @brief Finds a vertex in the graph based on its code.
    * @param code The code of the vertex to find.
    * @return Pointer to the found vertex, or nullptr if not found.
    */
    Vertex *findVertex(const string &code) const;

    /**
     * @brief Adds a new vertex to the graph.
     * @param code The code of the new vertex.
     */
    void addVertex(Vertex *vertex);

    /**
     * @brief Removes a vertex from the graph.
     * @param code The code of the vertex to remove.
     * @return True if the vertex was successfully removed, false otherwise.
     */
    bool removeVertex(const string &code);

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param source The code of the source vertex.
     * @param dest The code of the destination vertex.
     * @param distance The distance of the edge.
     * @param direction The direction of the edge.
     * @return True if the edge was successfully added, false otherwise.
     */
    bool addEdge(const string &source, const string &dest, double distance, bool direction);

    /**
     * @brief Removes an edge between two vertices in the graph.
     * @param source The code of the source vertex.
     * @param dest The code of the destination vertex.
     * @return True if the edge was successfully removed, false otherwise.
     */
    bool removeEdge(const string &source, const string &dest);

    /**
     * @brief Clears the graph.
     * @details This method removes all vertices and edges from the graph, effectively resetting it to an empty state.
     */
    void clear();

    //Getters
    Edge* getEdgeP(Vertex* origin,Vertex* dest);
    bool checkTheVertexInPath(Vertex* vertex,string infoToFound);
    vector<Vertex *> getVertexSet() const;

    //Setters
    void setAllNonVisited();
    void setVertexSet(const std::vector<Vertex*>& newVertexSet);

protected:
    vector<Vertex *> vertexset;
};

#endif 