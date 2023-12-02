#include <iostream>
#include "FuzzyLogicSystem.h"

using namespace std;

void systemDataInput(FuzzyLogicSystem &system) {
    cout << "Enter the system's name and a brief description:\n";
    cout << "-------------------------------------------------" << endl;
    string projectName, projectDescription;
    cin.ignore();
    cout << "NAME:";
    getline(cin, projectName);
    cout << "DESCRIPTION:";
    getline(cin, projectDescription);

    system.name = projectName;
    system.description = projectDescription;
}

void printMenu() {
    cout << "Main Menu:\n==========" << endl;
    cout << "1- Add variables." << endl;
    cout << "2- Add fuzzy sets to an existing variable." << endl;
    cout << "3- Add rules." << endl;
    cout << "4- Run the simulation on crisp values." << endl;
    cout << "5- Exit." << endl;
}

void addVariables(FuzzyLogicSystem &system) {
    cout << "Enter the variable's name, type (IN/OUT) and range ([lower, upper]):\n(Press x to finish)\n";
    cout << "--------------------------------------------------------------------\n";
    string variable = "name", type;
    int minRange, maxRange;
    while (variable != "x") {
        char dummy;
        cin >> variable;
        if (variable == "x") //to exit loop
            break;

        cin >> type >> dummy >> minRange >> dummy >> maxRange >> dummy;  //to enter type and range properly
        if (type != "IN" && type != "OUT") {
            cout << "Error : please enter a valid type (IN or OUT) " << endl;
            break;
        }
        if (minRange >= maxRange) {
            cout << "Error : please enter a valid range " << endl;
            break;
        }
        FuzzyVariable var;
        var.name = variable;
        var.rangeMin = minRange;
        var.rangeMax = maxRange;
        if (type == "IN")
            var.type = IN;
        else
            var.type = OUT;

        system.variables.push_back(var);
    }


}

void mainMenu(FuzzyLogicSystem &system) {

    int choice = 1;
    while (choice != 5) {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                addVariables(system);
                break;
            }
            case 2: {

                break;
            }
            case 3: {

                break;
            }
            case 4: {

                break;
            }
            case 5: {
                cout << "Thank you for using our system :)" << endl;
                break;
            }
            default: {
                cout << "please choose a number from 1 to 5" << endl;
            }
        }
    }
}

int main() {
    //ios::sync_with_stdio('0');
    //cin.tie(nullptr), cout.tie(nullptr);
    //freopen("input.txt","r",stdin);
    int choice = 1;
    FuzzyLogicSystem *system = nullptr;
    while (choice != 2) {
        cout << "Fuzzy Logic Toolbox\n===================" << endl;
        cout << "1-Create a new fuzzy system" << endl;
        cout << "2- Quit" << endl;

        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Error: wrong input , please try again" << endl;
        } else if (choice == 1) {
            delete system;
            system = new FuzzyLogicSystem();
            systemDataInput(*system);
            mainMenu(*system);
        }


    }

    return 0;
}
