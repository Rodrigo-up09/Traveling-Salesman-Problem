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
    int option;

    cout << "What you to test?" << endl;
    cout << "0 - Single Algoritm" << endl;
    cout << "1 - Compare Multiple" << endl;
    cin >> option;
    switch (option) {
        case 0:
            displaySingleAlgoritm(dataManager);
            break;
        case 1:
          displayMultiple( dataManager);
            break;

        default:
            cout<<"Wrong option";
    }



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





void displayMultiple(DataManager dataManager) {
    int algoritm;
    cout << "Select one option:" << endl;
    cout << "0 -Compare Light Algoritms(use small )" << endl;
    cout << "1 -Compare Mid Algoritms(use mid Graph,Backtrack is not called )" << endl;
    cout << "2 - Compare heavy algoritms (BackTrack its not called and Other Heuristic)" << endl;
    cout << "Enter your choice: ";
    cin >> algoritm;
    DataManager dataManagerB;
    DataManager dataManagerT;
    DataManager dataManagerH;
    DataManager dataManagerR;
    dataManager.copy(dataManagerB);
    dataManager.copy(dataManagerT);
    dataManager.copy(dataManagerH);
    dataManager.copy(dataManagerR);

    switch (algoritm) {
        case 0:
            displayTriangular(dataManagerT);
            displayBackTrac(dataManagerB);
            //TODO heuristic
            displayReal(dataManagerR,"0");
            break;



        case 1:
            displayTriangular(dataManagerT);
            //TODO heuristic
            displayReal(dataManagerR,"0");

            break;
        case 2:
            displayTriangular(dataManagerT);
            //TODO heuristic
            displayReal(dataManagerR,"0");

            break;
        default:
            cout<<"Wrong option";
            break;
    }
}

void displayBackTrac(DataManager dataManager){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"BackTrack"<<endl;
    double result= tspBackTrack(dataManager);
    cout<<"Total Distance: " <<result<<endl;

}
void displayTriangular(DataManager dataManager){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Triangular "<<endl;
    vector<Vertex*>path;
    auto start = std::chrono::high_resolution_clock::now();
    auto result2= tspTriangular(dataManager,path);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printTSPResultTriangular(path, result2);
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;

}
void displayReal(DataManager dataManager,const string& origin){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Real "<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto resullt= greedyTSP3(dataManager.getG(),origin,dataManager.getDistMatrix());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printTour(resullt.first,resullt.second);
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;


}
//TODO DISPLay other
