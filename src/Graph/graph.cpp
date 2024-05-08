#include "graph.h"

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

Vertex:: Vertex(const string& code) {
    this->info = code;
    this->path = nullptr;
    this->dist = 0;
    this->processing = false;
    this->visited = false;
    this->latitude=0;
    this->longitude=0;
    this->label=label="";
}
Vertex::Vertex(const string &code, const string& label) {
    this->info = code;
    this->path = nullptr;
    this->dist = 0;
    this->processing = false;
    this->visited = false;
    this->latitude=0;
    this->longitude=0;
    this->label=label;
}


Edge* Vertex::addEdge(Vertex* dest, double distance) {
    Edge* edge = new Edge(this, dest, distance);
    Edge* edgeReverse = new Edge(dest, this, distance);
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

double Vertex::getLatitude() const {
    return latitude;
}

void Vertex::setLatitude(double latitude) {
    Vertex::latitude = latitude;
}

double Vertex::getLongitude() const {
    return longitude;
}

void Vertex::setLongitude(double longitude) {
    Vertex::longitude = longitude;
}

const string &Vertex::getLabel() const {
    return label;
}

void Vertex::setLabel(const string &label) {
    Vertex::label = label;
}



Edge::Edge(Vertex* orig, Vertex* dest, double distance)
        : orig(orig), dest(dest),distance(distance), selected(false),isReverse(false) {
}


Edge::~Edge() {
    delete reverse;
}



double Edge::getdistance()const {
    return distance;
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





void Edge::setDistance(double distance) {
    this-> distance=  distance;
}

Vertex* Edge::getDest() {
    return dest;
}


Vertex * Graph::findVertex(const string &code)const {
    for (Vertex *vertex: vertexset ) {
        if (vertex->getInfo()== code) {
            return vertex;
        }
    }
    return nullptr;
}


void Graph::addVertex(Vertex *vertex) {
    vertexset.push_back(vertex);
}


bool Graph::removeVertex(const string &code) {
    for (auto it = vertexset.begin(); it != vertexset.end(); ++it) {
        if ((*it)->getInfo() == code) {

            for (Edge *edge : (*it)->getAdj()) {
                removeEdge((*it)->getInfo(), edge->getDest()->getInfo());
            }


            for (auto i : vertexset) {
                for (auto a : i->getIncoming()) {
                    if (a->getOrig()->getInfo() == code) {
                        removeEdge(a->getOrig()->getInfo(), a->getDest()->getInfo());
                    }
                }
            }

            delete *it;
            vertexset.erase(it);
            return true;
        }
    }
    return false;
}


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

vector<Vertex *>  Graph::getVertexSet() const {
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


Graph::Graph() = default;


void Graph::clear() {
    for (auto v : vertexset) {
        v->getAdj().clear();
    }
    vertexset.clear();
}

