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

    while (true) {
        cout << "Select Dataset:" << endl;
        cout << "0 - Small" << endl;
        cout << "1 - Medium" << endl;
        cout << "2 - Real" << endl;
        cout << "Enter your choice: ";
        cin >> dataSet;

        if (cin.fail() || dataSet < 0 || dataSet > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (dataSet == 0) {
            cout << "Select Small Dataset Type:" << endl;
            cout << "0 - Shipping" << endl;
            cout << "1 - Stadiums" << endl;
            cout << "2 - Tourism" << endl;
            cout << "Enter your choice: ";
            cin >> type;

            if (cin.fail() || type < 0 || type > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
        } else if (dataSet == 1) {
            cout << "Enter the number of nodes (e.g., 25, 50, 75, etc.): ";
            cin >> type;

            if (cin.fail() || type <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number of nodes. Please try again." << endl;
                continue;
            }
        } else if (dataSet == 2) {
            cout << "Select Real Dataset Type:" << endl;
            cout << "1 - Graph 1" << endl;
            cout << "2 - Graph 2" << endl;
            cout << "Enter your choice: ";
            cin >> type;

            if (cin.fail() || type < 1 || type > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
        }

        break;
    }

    DataManager dataManager;
    bool shipping;
    shipping = dataManager.start(dataSet, type);
    int option;

    while (true) {
        cout << "What do you want to test?" << endl;
        cout << "0 - Single Algorithm" << endl;
        cout << "1 - Compare Multiple" << endl;
        cin >> option;

        if (cin.fail() || option < 0 || option > 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (option == 0) {
            displaySingleAlgorithm(dataManager, shipping);
        } else if (option == 1) {
            displayMultiple(dataManager, shipping);
        }

        break;
    }
}

/**
 * @brief Displays the results of a single algorithm.
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @details This function prompts the user to select an algorithm, runs the selected algorithm, and displays the results.
 */
void displaySingleAlgorithm(DataManager dataManager, bool shipping) {
    int algorithm;

    while (true) {
        cout << "Select Algorithm:" << endl;
        cout << "0 - Backtrack" << endl;
        cout << "1 - Triangular" << endl;
        cout << "2 - Other Heuristic" << endl;
        cout << "3 - Real World" << endl;
        cout << "Enter your choice: ";
        cin >> algorithm;

        if (cin.fail() || algorithm < 0 || algorithm > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        switch (algorithm) {
            case 0:
                displayBackTrac(dataManager);
                break;
            case 1:
                displayTriangular(dataManager, shipping);
                break;
            case 2:
                int k;
                cout << "Choose size of Cluster: ";
                cin >> k;
                displayOtherHeuristic(dataManager, shipping, k);
                break;
            case 3: {
                string origin;
                cout << "Choose the Source Vertex: ";
                cin >> origin;
                displayReal(dataManager, origin);
                break;
            }
        }
        break;
    }
}

/**
 * @brief Displays the results of multiple algorithms for comparison.
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @details This function prompts the user to select an option for comparing different algorithms, runs the selected algorithms, and displays the results.
 */
void displayMultiple(DataManager dataManager, bool shipping) {
    int algorithm, k;
    while (true) {
        cout << "Select one option:" << endl;
        cout << "0 - Compare Light Algorithms (use small)" << endl;
        cout << "1 - Compare Mid Algorithms (use mid Graph, Backtrack is not called)" << endl;
        cout << "2 - Compare Heavy Algorithms (Backtrack and Other Heuristic are not called)" << endl;
        cout << "Enter your choice: ";
        cin >> algorithm;

        if (cin.fail() || algorithm < 0 || algorithm > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
        cout << "Choose size of Cluster: ";
        cin >> k;

        DataManager dataManagerB, dataManagerT, dataManagerH, dataManagerR;
        dataManager.copy(dataManagerB);
        dataManager.copy(dataManagerT);
        dataManager.copy(dataManagerH);
        dataManager.copy(dataManagerR);

        switch (algorithm) {
            case 0:
                displayTriangular(dataManagerT, shipping);
                displayBackTrac(dataManagerB);
                displayOtherHeuristic(dataManager, shipping, k);
                displayReal(dataManagerR, "0");
                break;
            case 1:
                displayTriangular(dataManagerT, shipping);
                displayOtherHeuristic(dataManager, shipping, k);
                displayReal(dataManagerR, "0");
                break;
            case 2:
                displayTriangular(dataManagerT, shipping);
                displayOtherHeuristic(dataManager, shipping, k);
                displayReal(dataManagerR, "0");
                break;
        }
        break;
    }
}

/**
 * @brief Displays the results of the Backtrack algorithm.
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @details This function runs the Backtrack algorithm on the provided data and displays the results.
 */
void displayBackTrac(DataManager dataManager){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"BackTrack"<<endl;
    double result= tspBackTrack(dataManager);
    cout<<"Total Distance: " <<result<<endl;

}

/**
 * @brief Displays the results of the Triangular Approximation algorithm.
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @details This function runs the Triangular Approximation algorithm on the provided data, measures the execution time, and displays the results.
 */
void displayTriangular(DataManager dataManager, bool shipping){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Triangular "<<endl;
    vector<Vertex*>path;
    auto start = std::chrono::high_resolution_clock::now();
    auto result2= tspTriangular(dataManager,path, shipping);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printTSPTriangular(path, result2);
    std::cout << "The function took " << duration.count() << " seconds to execute." << std::endl;

}

/**
 * @brief Displays the results of the Real World algorithm.
 * @param dataManager The DataManager instance containing the graph and other related data.
 * @param origin The origin vertex from where the algorithm starts.
 * @details This function runs the Real World algorithm on the provided data, measures the execution time, and displays the results.
 */

void displayOtherHeuristic(DataManager dataManager, bool shipping, int k){
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"Other Heuristic "<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto result2= OtherHeuristic2(dataManager, k, shipping);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printOtherHeuristic(result2);
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
