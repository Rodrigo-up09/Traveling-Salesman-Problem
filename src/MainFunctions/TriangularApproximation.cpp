#include "TriangularApproximation.h"

#include "TriangularApproximation.h"
#include <corecrt_math_defines.h>

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

double tspTriangular(DataManager aux, vector<Vertex*>& path) {
    for(auto v : aux.getG().getVertexSet()) {
        v->setVisited(false);
    }
    double finalDistance = 0;
    auto current = aux.getG().getVertexSet()[0];
    current->setVisited(true);
    path.push_back(current);


    for(int i=0; i < aux.getG().getVertexSet().size(); i++) {
        double minDist = DBL_MAX;
        Vertex* next = nullptr;

        for(auto v : aux.getG().getVertexSet()) {
            if(!v->isVisited()) {
                double dist;
                for(auto e : current->getAdj()) {
                    if(e->getDest()->getInfo() == v->getInfo()) {
                        dist = e->getdistance();
                        break;
                    }
                }
                if(dist < minDist) {
                    minDist = dist;
                    next = v;
                }
            }
        }
        if(next != nullptr) {
            next->setVisited(true);
            finalDistance += minDist;
            current = next;
            path.push_back(current);

        }
    }
    for(auto e : current->getAdj()) {
        if(e->getDest()->getInfo() == aux.getG().getVertexSet()[0]->getInfo()) {
            finalDistance += e->getdistance();
            break;
        }
    }
    path.push_back(aux.getG().getVertexSet()[0]);

    return finalDistance;
}