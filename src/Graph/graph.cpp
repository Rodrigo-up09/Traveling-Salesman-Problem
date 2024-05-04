#include "Graph.h"

std::string Vertex::getInfo() const {
    return info;
}

bool Vertex::isVisited() const {
    return visited;
}

bool Vertex::isProcessing() const {
    return processing;
}

double Vertex::getDist() const {
    return dist;
}

Edge* Vertex::getPath() const {
    return path;
}

void Vertex::setInfo(const std::string& info) {
    this->info = info;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}


void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge* path) {
    this->path = path;
}

Vertex::Vertex(const std::string& code) {
    this->info = code;
    this->path = nullptr;
    this->dist = 0;
    this->processing = false;
    this->visited = false;
}

Edge* Vertex::addEdge(Vertex* dest, int capacity, bool direction) {
    Edge* edge = new Edge(this, dest, capacity, direction);
    Edge* edgeReverse = new Edge(dest, this, capacity, direction);
    edge->setReverse(edgeReverse);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

void Vertex::deleteEdge(Edge* edge) {
    for(auto it = adj.begin(); it != adj.end(); ++it) {
        if(*it == edge) {
            adj.erase(it);
            break;
        }
    }
}

std::vector<Edge*> Vertex::getAdj() {
    return adj;
}

std::vector<Edge*> Vertex::getIncoming() {
    return incoming;
}



Edge::Edge(Vertex* orig, Vertex* dest, int c, bool direction)
        : orig(orig), dest(dest), selected(false),isReverse(false) {
}


Edge::~Edge() {
    delete reverse;
}



int Edge::getCapacity() const {
    return disntance;
}

bool Edge::isSelected() const {
    return selected;
}


Vertex* Edge::getOrig() const {
    return orig;
}


Edge* Edge::getReverse() const {
    return reverse;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}


void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}





void Edge::setCapacity(int capacity) {
    this->disntance= capacity;
}

Vertex* Edge::getDest() {
    return dest;
}


Vertex* Graph::findVertex(const std::string& code) const {
    auto it = vertexset.find(code);
    if (it != vertexset.end()) {
        return it->second;
    }
    return nullptr;
}


void Graph::addVertex(const std::string& code) {
    Vertex* vertex = new Vertex(code);
    vertexset.insert(std::make_pair(code, vertex));
}


bool Graph::removeVertex(const string &code) {
    auto it = vertexset.find(code);
    if (it != vertexset.end()) {
        Vertex *vertexToRemove = it->second;
        for (Edge *edge : vertexToRemove->getAdj()) {
            removeEdge(vertexToRemove->getInfo(), edge->getDest()->getInfo());
        }
        for(auto i:vertexset){
            for(auto a:i.second->getIncoming()){
                if(a->getOrig()->getInfo()==code){
                    removeEdge(a->getOrig()->getInfo(),a->getDest()->getInfo());
                }
            }
        }

        vertexset.erase(it);

        return true;
    }
    return false;
}


bool Graph::addEdge(const std::string& source, const std::string& dest, int capacity, bool direction) {
    Vertex* sourceV = findVertex(source);
    Vertex* destV = findVertex(dest);
    if (sourceV == nullptr || destV == nullptr)
        return false;
    sourceV->addEdge(destV, capacity, direction);
    if (!direction) {
        destV->addEdge(sourceV, capacity, direction);
    }
    return true;
}


std::unordered_map<std::string, Vertex*> Graph::getVertexSet() const {
    return vertexset;
}


bool Graph::removeEdge(const std::string& source, const std::string& dest) {
    Vertex* sourceV = findVertex(source);
    Vertex* destV = findVertex(dest);
    if (sourceV == nullptr || destV == nullptr)
        return false;
    for (auto e : sourceV->getAdj()) {
        if (e->getDest() == destV) {
            sourceV->deleteEdge(e);
            return true;
        }
    }
    return false;
}


Graph::Graph() {
}


void Graph::clear() {
    for (auto v : vertexset) {
        v.second->getAdj().clear();
    }
    vertexset.clear();
}

void Graph::addVertexWithEdges(Vertex* vertex) {
    vertexset.insert(std::make_pair(vertex->getInfo(), vertex));
}