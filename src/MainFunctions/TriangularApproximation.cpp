#include "TriangularApproximation.h"

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double rad_lat1 = lat1 * M_PI / 180;
    double rad_lon1 = lon1 * M_PI / 180;
    double rad_lat2 = lat2 * M_PI / 180;
    double rad_lon2 = lon2 * M_PI / 180;

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double aux = pow(sin(delta_lat/2),2) + cos(rad_lat1) * cos(rad_lat2) * pow(sin(delta_lon/2),2);
    double c = 2 * atan2(sqrt(aux), sqrt(1 - aux));

    return c * 6371000;
}

double calculateDistance(Vertex* v1, Vertex* v2) {
    for(auto e : v1->getAdj()) {
        if(e->getDest()->getInfo() == v2->getInfo()) {
            return e->getdistance();
        }
    }
    double haversineDistance = haversine(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
    return haversineDistance;
}

vector<Edge*> prim(DataManager aux) {
    vector<Edge*> mst;
    if(aux.getG().getVertexSet().empty()) {
        return mst;
    }
    for(auto v : aux.getG().getVertexSet()) {
        v->setDist(DBL_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    auto source = aux.getG().getVertexSet()[0];
    source->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(source);

    while(!q.empty()){
        auto v = q.extractMin();
        if(v->getPath() != nullptr) {
            mst.push_back(v->getPath());
        }
        v->setVisited(true);
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            if(!w->isVisited()){
                double old_dist = w->getDist();
                if(old_dist > e->getdistance()) {
                    w->setDist(e->getdistance());
                    w->setPath(e);
                    if(old_dist == DBL_MAX) {
                        q.insert(w);
                    }else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return mst;
}


void preorderTraversal(vector<Edge*> mst, Vertex* v, vector<Vertex*>& path) {
    v->setVisited(true);
    path.push_back(v);
    for(auto e : mst) {
        if(e->getOrig()->getInfo() == v->getInfo()) {
            if(e->getDest()->isVisited()) {
                preorderTraversal(mst, e->getDest(), path);
            }
        }
    }
}

double tspTriangular(DataManager aux, vector<Vertex*>& path) {
    double finalDistance = 0;
    vector<Edge*> mst = prim(aux);
    preorderTraversal(mst, aux.getG().getVertexSet()[0], path);
    path.push_back(aux.getG().getVertexSet()[0]);
    for(int i=0; i < path.size()-1; i++) {
        finalDistance += calculateDistance(path[i], path[i+1]);
    }

    return finalDistance;
}
void printTSPResultTriangular(const vector<Vertex*>& path, double finalDistance) {
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]->getInfo();
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total Distance: " << finalDistance << endl;
}