#ifndef PROJETDA2_TRIANGULARAPPROXIMATION_H
#define PROJETDA2_TRIANGULARAPPROXIMATION_H

#include "../DataManager/DataManager.h"
#include <cmath>
#include <cfloat>
using namespace std;

double haversine(double lat1, double lon1, double lat2, double lon2);
double tspTriangular(DataManager dataManager, bool flag);

#endif
