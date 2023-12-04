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

void addVariableSets(FuzzyLogicSystem &system) {
    cout << "Enter the variable's name:\n------------------------" << endl;
    string varName;
    cin >> varName;
    bool check = false;
    FuzzyVariable* variable;
    /// to check if variable exists in the system or not
    variable = system.findVariable(varName);
    if(variable == nullptr){
        cout << "ERROR: no variable with this name is available in the system\n";
        return;
    }
//    for (int i = 0; i < system.variables.size(); ++i) {
//        if (varName == system.variables[i].name) {
//            check = true;
//            variable = system.variables[i];
//            break;
//        }
//    }
//    if (!check) {
//        cout << "ERROR: no variable with this name is available in the system\n";
//        return;
//    }
    cout << "Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish) \n";
    cout << "-----------------------------------------------------\n";
    string setName = "check", type;
    int point1, point2, point3, point4;
    while (setName != "x") {
        cin >> setName;
        if (setName == "x")
            break;
        cin >> type >> point1 >> point2 >> point3;
        FuzzySetType tempType;
        if (type == "TRAP") {
            tempType = TRAP;
            cin >> point4;
        } else {
            tempType = TRI;
            point4 = 0;
        }

        if (!(point1 <= point2 <= point3)) {
            cout << "ERROR in the points you entered ,please enter ascending points\n";
            return;
        }
        FuzzySet newSet(setName, tempType, point1, point2, point3, point4);
        variable->sets.push_back(newSet);
        system.updateVariable(*variable);

    }
}

void addRules(FuzzyLogicSystem &system){
    cout << "Enter the rules in this format: (Press x to finish)\n";
    cout << "IN_variable set operator IN_variable set => OUT_variable set\n";
    cout << "------------------------------------------------------------\n";
    string inVar1="check" , inVar2 ,outVar, inSet1,inSet2 , outSet , _operator;
    while (inVar1 != "x"){
        cin >> inVar1;
        if (inVar1 == "x")
            break;

    }
}

void printSystemVariables(FuzzyLogicSystem &system) {
    for (int i = 0; i < system.variables.size(); ++i) {
        cout << system.variables[i].name << " : " << endl;
        for (int j = 0; j < system.variables[i].sets.size(); ++j) {
            cout << system.variables[i].sets[j].name << " " << system.variables[i].sets[j].type << " ";
            for (int k = 0; k < system.variables[i].sets[j].points.size(); ++k) {
                cout << system.variables[i].sets[j].points[k].first << " ";
            }
            cout << endl;
        }
        cout << endl;
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
                addVariableSets(system);
                printSystemVariables(system);
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
        cout << "2-Quit" << endl;

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
