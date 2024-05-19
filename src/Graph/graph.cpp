#include "graph.h"

/**
 * @brief Retrieves the information associated with the Vertex.
 * @return The information (code) of the Vertex as a string.
 */
std::string Vertex::getInfo() const {
    return info;
}

/**
 * @brief Check if the vertex has been visited.
 * @return True if the vertex has been visited, otherwise false.
 */
bool Vertex::isVisited() const {
    return visited;
}

/**
 * @brief Check if the vertex is being processed.
 * @return True if the vertex is being processed, otherwise false.
 */
bool Vertex::isProcessing() const {
    return processing;
}

/**
 * @brief Get the distance of the vertex from a source vertex.
 * @return The distance of the vertex from a source vertex.
 */
double Vertex::getDist() const {
    return dist;
}

/**
 * @brief Get the path from the source vertex to this vertex.
 * @return The path from the source vertex to this vertex.
 */
Edge* Vertex::getPath() const {
    return path;
}

/**
 * @brief Set the information associated with the vertex.
 * @param info The information to be associated with the vertex.
 */
void Vertex::setInfo(const std::string& info) {
    this->info = info;
}

/**
 * @brief Set the visited status of the vertex.
 * @param visited The visited status to be set.
 */
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Set the processing status of the vertex.
 * @param processing The processing status to be set.
 */
void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

/**
 * @brief Set the distance of the vertex from a source vertex.
 * @param dist The distance to be set.
 */
void Vertex::setDist(double dist) {
    this->dist = dist;
}

/**
 * @brief Set the path from the source vertex to this vertex.
 * @param path The path to be set.
 */
void Vertex::setPath(Edge* path) {
    this->path = path;
}

/**
 * @brief Constructor for creating a vertex with the given code.
 * @param code The code associated with the vertex.
 */
Vertex:: Vertex(const string& code) {
    this->info = code;
    this->path = nullptr;
    this->dist = 0;
    this->processing = false;
    this->visited = false;
    this->latitude = 0;
    this->longitude = 0;
    this->label = "";
    this->queueIndex = 0;
}

/**
 * @brief Constructor for creating a vertex with the given code and label.
 * @param code The code associated with the vertex.
 * @param label The label associated with the vertex.
 */
Vertex::Vertex(const string &code, const string& label) {
    this->info = code;
    this->path = nullptr;
    this->dist = 0;
    this->processing = false;
    this->visited = false;
    this->latitude = 0;
    this->longitude = 0;
    this->label = label;
    this->queueIndex = 0;
}

/**
 * @brief Add an edge between this vertex and a destination vertex.
 * @param dest The destination vertex.
 * @param distance The distance of the edge.
 * @return The created edge.
 */
Edge* Vertex::addEdge(Vertex* dest, double distance) {
    Edge* edge = new Edge(this, dest, distance);
    Edge* edgeReverse = new Edge(dest, this, distance);
    edge->setReverse(edgeReverse);
    adj[dest->getInfo()] = edge;
    dest->incoming[this->getInfo()] = edge;
    return edge;
}

/**
 * @brief Delete the given edge from the adjacency list.
 * @param edge The edge to be deleted.
 */
void Vertex::deleteEdge(Edge* edge) {
    adj.erase(edge->getDest()->getInfo());
    edge->getDest()->incoming.erase(this->getInfo());
}

/**
 * @brief Get the adjacency list of the vertex.
 * @return The adjacency list of the vertex.
 */
unordered_map<string, Edge*> Vertex::getAdj() const {
    return adj;
}

/**
 * @brief Get the incoming edges to the vertex.
 * @return The incoming edges to the vertex.
 */
unordered_map<string, Edge*> Vertex::getIncoming() const {
    return incoming;
}

/**
 * @brief Get the latitude of the vertex.
 * @return The latitude of the vertex.
 */
double Vertex::getLatitude() const {
    return latitude;
}

/**
 * @brief Set the latitude of the vertex.
 * @param latitude The latitude to be associated with the vertex.
 */
void Vertex::setLatitude(double latitude) {
    Vertex::latitude = latitude;
}

/**
 * @brief Get the longitude of the vertex.
 * @return The longitude of the vertex.
 */
double Vertex::getLongitude() const {
    return longitude;
}

/**
 * @brief Set the longitude of the vertex.
 * @param longitude The longitude to be associated with the vertex.
 */
void Vertex::setLongitude(double longitude) {
    Vertex::longitude = longitude;
}

/**
 * @brief Get the label of the vertex.
 * @return The label of the vertex.
 */
const string &Vertex::getLabel() const {
    return label;
}

/**
 * @brief Set the label of the vertex.
 * @param label The label to be associated with the vertex.
 */
void Vertex::setLabel(const string &label) {
    Vertex::label = label;
}

/**
 * @brief Get the queueIndex of the vertex.
 * @return The queueIndex of the vertex.
 */
unsigned int Vertex::getQueueIndex() const {
    return queueIndex;
}

/**
 * @brief Set the queueIndex of the vertex.
 * @param queueIndex The queueIndex to be associated with the vertex.
 */
void Vertex::setQueueIndex(unsigned int index) {
    Vertex::queueIndex = index;
}

/**
 * @brief Compares this vertex with another for ordering purposes.
 * @param other The other vertex to compare with.
 * @return true if this vertex's distance is less than the other vertex's distance, false otherwise.
 */
bool Vertex::operator<(const Vertex &other) const {
    return dist < other.dist;
}

/**
 * @brief Constructor for creating an edge between two vertices.
 * @param orig The origin vertex of the edge.
 * @param dest The destination vertex of the edge.
 * @param distance The distance of the edge.
 */
Edge::Edge(Vertex* orig, Vertex* dest, double distance)
        : orig(orig), dest(dest), distance(distance), selected(false), isReverse(false) {
}

/**
 * @brief Destructor for properly deleting the reverse edge.
 */
Edge::~Edge() {
    delete reverse;
}

/**
 * @brief Get the distance of the edge.
 * @return The distance of the edge.
 */
double Edge::getdistance() const {
    return distance;
}

/**
 * @brief Check if the edge is selected.
 * @return True if the edge is selected, otherwise false.
 */
bool Edge::isSelected() const {
    return selected;
}

/**
 * @brief Get the origin vertex of the edge.
 * @return The origin vertex of the edge.
 */
Vertex* Edge::getOrig() const {
    return orig;
}

/**
 * @brief Get the reverse edge of the current edge.
 * @return The reverse edge of the current edge.
 */
Edge* Edge::getReverse() const {
    return reverse;
}

/**
 * @brief Set the selection status of the edge.
 * @param selected The selection status to be set.
 */
void Edge::setSelected(bool selected) {
    this->selected = selected;
}

/**
 * @brief Set the reverse edge of the current edge.
 * @param reverse The reverse edge to be set.
 */
void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

/**
 * @brief Set the distance of the edge.
 * @param distance The distance to be set.
 */
void Edge::setDistance(double distance) {
    this->distance = distance;
}

/**
 * @brief Get the destination vertex of the edge.
 * @return The destination vertex of the edge.
 */
Vertex* Edge::getDest() {
    return dest;
}

/**
 * @brief Find a vertex with the given code.
 * @param code The code of the vertex to find.
 * @return The found vertex or nullptr if not found.
 */
Vertex *Graph::findVertex(const string &code) const {
    auto it = vertexset.find(code);
    if (it != vertexset.end()) {
        return it->second;
    }
    return nullptr;
}

/**
 * @brief Add a vertex with the given code to the graph.
 * @param vertex The vertex to be added.
 */
void Graph::addVertex(Vertex *vertex) {
    vertexset[vertex->getInfo()] = vertex;
}

/**
 * @brief Remove a vertex with the given code from the graph.
 * @param code The code of the vertex to be removed.
 * @return True if the vertex is successfully removed, otherwise false.
 */
bool Graph::removeVertex(const string &code) {
    auto it = vertexset.find(code);
    if (it != vertexset.end()) {
        Vertex* vertex = it->second;

        for (auto& pair : vertex->getAdj()) {
            removeEdge(vertex->getInfo(), pair.second->getDest()->getInfo());
        }

        for (auto& pair : vertexset) {
            auto incoming = pair.second->getIncoming();
            auto it_in = incoming.find(code);
            if (it_in != incoming.end()) {
                removeEdge(it_in->second->getOrig()->getInfo(), it_in->second->getDest()->getInfo());
            }
        }

        delete vertex;
        vertexset.erase(it);
        return true;
    }
    return false;
}

/**
 * @brief Add an edge between two vertices in the graph.
 * @param source The source vertex code.
 * @param dest The destination vertex code.
 * @param distance The distance of the edge.
 * @param direction The direction of the edge.
 * @return True if the edge is added successfully, otherwise false.
 */
bool Graph::addEdge(const std::string& source, const std::string& dest, double distance, bool direction) {
    Vertex* sourceV = findVertex(source);
    Vertex* destV = findVertex(dest);
    if (sourceV == nullptr || destV == nullptr)
        return false;
    sourceV->addEdge(destV, distance);
    if (!direction) {
        destV->addEdge(sourceV, distance);
    }
    return true;
}

/**
 * @brief Get the vertex set of the graph.
 * @return The vertex set of the graph.
 */
unordered_map<string, Vertex*> Graph::getVertexSet() const {
    return vertexset;
}

/**
 * @brief Remove an edge between two vertices in the graph.
 * @param source The source vertex code.
 * @param dest The destination vertex code.
 * @return True if the edge is removed successfully, otherwise false.
 */
bool Graph::removeEdge(const std::string& source, const std::string& dest) {
    Vertex* sourceV = findVertex(source);
    Vertex* destV = findVertex(dest);
    if (sourceV == nullptr || destV == nullptr)
        return false;
    auto it = sourceV->getAdj().find(dest);
    if (it != sourceV->getAdj().end()) {
        sourceV->deleteEdge(it->second);
        return true;
    }
    return false;
}

/**
 * @brief Default constructor for Graph class.
 */
Graph::Graph() = default;

/**
 * @brief Clear the graph by removing all vertices and edges.
 */
void Graph::clear() {
    for (auto& pair : vertexset) {
        pair.second->getAdj().clear();
    }
    vertexset.clear();
}

/**
 * @brief Sets all vertices in the graph as not visited.
 *
 */
void Graph::setAllNonVisited() {
    for (auto& pair : vertexset) {
        pair.second->setVisited(false);
        pair.second->setProcessing(false);
        pair.second->setPath(nullptr);
    }
}

/**
 * @brief Checks if a specific vertex is in the path of another vertex.
 * @param vertex The vertex whose path is to be checked.
 * @param infoToFound The information string of the vertex to be found in the path.
 * @return True if the vertex with the information string is found in the path, false otherwise.
 */
bool Graph::checkTheVertexInPath(Vertex* vertex, string infoToFound) {
    Edge* edgePath = vertex->getPath();
    if (edgePath->getDest() == nullptr) return false;
    if (edgePath->getDest()->getInfo() == infoToFound) {
        return true;
    }
    return checkTheVertexInPath(edgePath->getDest(), infoToFound);
}

/**
 * @brief Sets the vertex set of the graph.
 * @param newVertexSet A vector of pointers to Vertex objects, representing the new set of vertices for the graph.
 */
void Graph::setVertexSet(const std::unordered_map<string, Vertex*>& newVertexSet) {
    vertexset = newVertexSet;
}

/**
 * @brief Retrieves the edge between two vertices in the graph.
 * @param origin A pointer to the origin vertex.
 * @param dest A pointer to the destination vertex.
 * @return A pointer to the edge between the origin and destination vertices.
 */
Edge* Graph::getEdgeP(Vertex* origin, Vertex* dest) {
    auto it = origin->getAdj().find(dest->getInfo());
    if (it != origin->getAdj().end()) {
        return it->second;
    }
    return nullptr;
}