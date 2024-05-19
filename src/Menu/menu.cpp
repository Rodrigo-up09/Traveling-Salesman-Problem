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

    cout << "What do you want to test?" << endl;
    cout << "0 - Single Algorithm" << endl;
    cout << "1 - Compare Multiple" << endl;
    cin >> option;
    switch (option) {
        case 0:
            displaySingleAlgorithm(dataManager);
            break;
        case 1:
          displayMultiple( dataManager);
            break;

        default:
            cout<<"Wrong option";
    }



}

void displaySingleAlgorithm(DataManager dataManager){
    int algorithm;

    cout << "Select Algorithm:" << endl;
    cout << "0 - Backtrack" << endl;
    cout << "1 - Triangular" << endl;
    cout << "2 - Other Heuristic" << endl;
    cout << "3 - Real Word" << endl;
    cout << "Enter your choice: ";
    cin >> algorithm;


    switch (algorithm) {
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
            cout << "Choose the Source Vertex:" << endl;
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
    int algorithm;
    cout << "Select one option:" << endl;
    cout << "0 - Compare Light Algorithms (use small)" << endl;
    cout << "1 - Compare Mid Algorithms (use mid Graph, Backtrack is not called)" << endl;
    cout << "2 - Compare heavy algorithms (BackTrack is not called and Other Heuristic)" << endl;
    cout << "Enter your choice: ";
    cin >> algorithm;
    DataManager dataManagerB;
    DataManager dataManagerT;
    DataManager dataManagerH;
    DataManager dataManagerR;
    dataManager.copy(dataManagerB);
    dataManager.copy(dataManagerT);
    dataManager.copy(dataManagerH);
    dataManager.copy(dataManagerR);

    switch (algorithm) {
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
    printTSPTriangular(path, result2);
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;

}
void displayReal(DataManager dataManager,const string& origin){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Real "<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto result= greedyTSP3(dataManager.getG(),origin,dataManager.getDistMatrix());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printTour(result.first,result.second);
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;


}
//TODO DISPLay other
