#include "menu.h"


/*
 *   DataManager dataManagerB;
    DataManager dataManagerT;
    DataManager dataManagerH;
    DataManager dataManagerR;
    dataManager.copy(dataManagerB);
    dataManager.copy(dataManagerT);
    dataManager.copy(dataManagerH);
    dataManager.copy(dataManagerR);
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */

void displayMenu() {
    int dataSet, type;

    cout << "Select Dataset:" << endl;
    cout << "0 - Small" << endl;
    cout << "1 - Medium" << endl;
    cout << "2 - Real" << endl;
    cout << "Enter your choice: ";
    cin >> dataSet;

    switch (dataSet) {
        case 0:
            cout << "Select Small Dataset Type:" << endl;
            cout << "0 - Shipping" << endl;
            cout << "1 - Stadiums" << endl;
            cout << "2 - Tourism" << endl;
            cout << "Enter your choice: ";
            cin >> type;
            break;
        case 1:
            cout << "Enter the number of nodes (e.g., 25, 50, 75, etc.): ";
            cin >> type;
            break;
        case 2:
            cout << "Select Real Dataset Type:" << endl;
            cout << "1 - Graph 1" << endl;
            cout << "2 - Graph 2" << endl;
            cout << "Enter your choice: ";
            cin >> type;
            break;
        default:
            cout << "Invalid choice" << endl;
            return;
    }

    DataManager dataManager;
    dataManager.start(dataSet, type);

}

void displaySingleAlgoritm(DataManager dataManager){
    int algoritm;

    cout << "Select Algoritm:" << endl;
    cout << "0 - Bactrack" << endl;
    cout << "1 - Triangular" << endl;
    cout << "2 -Other Heuristic" << endl;
    cout << "3 -Real Word" << endl;
    cout << "Enter your choice: ";
    cin >> algoritm;

    switch (algoritm) {
        case 0:
            displayBackTrac(dataManager);

            break;
        case 1:
            displayTriangular(dataManager);

            break;
        case 2:
            //TODO



            break;
        case 3:{
            string origin;
            cout << "Chose the Sorce Vertex:" << endl;
            cin >> origin;
            displayReal( dataManager, origin);
            break;
        }
        default:
            cout<<"Wrong option";
            return;
    }


}

void displayBackTrac(DataManager dataManager){
        cout<<"BackTrack"<<endl;
        double result= tspBackTrack(dataManager);
        cout<<"Total Distance: " <<result<<endl;
}
void displayTriangular(DataManager dataManager){
    cout<<"Triangular "<<endl;
    vector<Vertex*>path;
    auto result2= tspTriangular(dataManager,path);
    printTSPResultTriangular(path, result2);

}
void displayReal(DataManager dataManager,const string& origin){
    cout<<"Real "<<endl;
    auto resullt= greedyTSP3(dataManager.getG(),origin,dataManager.getDistMatrix());
    printTour(resullt.first,resullt.second);
}
//TODO DISPLay other



