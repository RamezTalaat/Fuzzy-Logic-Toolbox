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
    FuzzyVariable *variable;
    /// to check if variable exists in the system or not
    variable = system.findVariable(varName);
    if (variable == nullptr) {
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

void addRules(FuzzyLogicSystem &system) {
    cout << "Enter the rules in this format: (Press x to finish)\n";
    cout << "IN_variable set operator IN_variable set => OUT_variable set\n";
    cout << "------------------------------------------------------------\n";
    string inVar1 = "check", inVar2, outVar, inSet1, inSet2, outSet, _operator;
    while (inVar1 != "x") {
        FuzzyVariable *inVar1Check, *inVar2Check, *outVarCheck;
        FuzzySet *inSet1Check, *inSet2Check, *outSetCheck;
        char dummy;
        cin >> inVar1;
        //cout << inVar1 << " "<< inSet1 << " " << _operator <<" " << inVar2 << " "<< inSet2 << " " <<outVar << " "<< outSet << endl;
        if (inVar1 == "x")
            break;
        cin >> inSet1 >> _operator >> inVar2 >> inSet2 >> dummy >> dummy >> outVar >> outSet;
        inVar1Check = system.findVariable(inVar1);
        inVar2Check = system.findVariable(inVar2);
        outVarCheck = system.findVariable(outVar);

        ///input checks
        if (inVar1Check == nullptr || inVar2Check == nullptr || outVarCheck == nullptr) {
            cout << "ERROR: you entered an unregistered variable.\n";
            continue;
        }
        if (_operator != "and" && _operator != "or" && _operator != "or_not" && _operator != "and_not") {
            cout << "ERROR: you entered an unregistered operator.\n";
            cout << "Supported operators are : and, and_not, or, or_not \n";
            continue;
        }
        inSet1Check = inVar1Check->findSet(inSet1);
        inSet2Check = inVar2Check->findSet(inSet2);
        outSetCheck = outVarCheck->findSet(outSet);
        if (inSet1Check == nullptr || inSet2Check == nullptr || outSetCheck == nullptr) {
            cout << "ERROR: you entered an unregistered set.\n";
            continue;
        }
        FuzzyRule newRule;
        newRule.inVar1 = inVar1;
        newRule.inVar2 = inVar2;
        newRule.outVar = outVar;
        newRule.inSet1 = inSet1;
        newRule.inSet2 = inSet2;
        newRule.outSet = outSet;
        if (_operator == "and")
            newRule._operator = _and;
        else if (_operator == "and_not")
            newRule._operator = _and_not;
        else if (_operator == "or")
            newRule._operator = _or;
        else if (_operator == "or_not")
            newRule._operator = _or_not;
        system.rules.push_back(newRule);
        cout << "RULE ADDED: \n" << newRule.inVar1 << " " << newRule.inSet1 << " " << newRule._operator;
        cout << " " << newRule.inVar2 << " " << newRule.inSet2 << " => " << newRule.outVar << " " << newRule.outSet
             << endl;

    }
}

void runSimulation(FuzzyLogicSystem &system) {
    cout << "Enter the crisp values:\n-----------------------\n";
    if (system.variables.empty()) {
        cout << "CAN NOT RUN SIMULATION , NO VARIABLES IN SYSTEM\n";
        return;
    }
    vector<pair<FuzzyVariable, int>> inputValues; // to store crisp values
    for (int i = 0; i < system.variables.size(); ++i) {
        int xValue;
        if (system.variables[i].type == IN) {
            cout << system.variables[i].name << ": ";
            cin >> xValue;
            inputValues.emplace_back(system.variables[i], xValue);
        }
    }
    cout << "Running the simulation...\n";
    vector<pair<FuzzyVariable, vector<pair<string, double>>>> membershipValues;
    for (int i = 0; i < inputValues.size(); ++i) {
        vector<pair<string, double>> membershipVec = inputValues[i].first.getMembership(inputValues[i].second);
        membershipValues.emplace_back(inputValues[i].first, membershipVec);
    }
    cout << "Fuzzification => done " << endl;
    vector<pair<string, pair<string, double>>> resultMembership;
    for (int i = 0; i < system.rules.size(); ++i) {
        double value1 = 0, value2 = 0;
        for (int j = 0; j < membershipValues.size(); ++j) {
            if (membershipValues[j].first.name == system.rules[i].inVar1) {
                for (int k = 0; k < membershipValues[j].second.size(); ++k) {
                    if (membershipValues[j].second[k].first == system.rules[i].inSet1) {
                        value1 = membershipValues[j].second[k].second;
                    }
                }
            }
            if (membershipValues[j].first.name == system.rules[i].inVar2) {
                for (int k = 0; k < membershipValues[j].second.size(); ++k) {
                    if (membershipValues[j].second[k].first == system.rules[i].inSet2) {
                        value2 = membershipValues[j].second[k].second;
                    }
                }
            }
        }
        double result = 0;
        if (system.rules[i]._operator == _and) {
            result = min(value1, value2);
        } else if (system.rules[i]._operator == _and_not) {
            result = min(value1, 1 - value2);
        } else if (system.rules[i]._operator == _or) {
            result = max(value1, value2);
        } else if (system.rules[i]._operator == _or_not) {
            result = max(value1, 1 - value2);
        }
        pair<string, double> tempResultPair;
        tempResultPair.first = system.rules[i].outSet;
        tempResultPair.second = result;
        resultMembership.emplace_back(system.rules[i].outVar, tempResultPair);
    }
    ///if there were multiple values for the same set partition
    for (int i = 0; i < resultMembership.size(); ++i) {
        for (int j = 0; j < resultMembership.size(); ++j) {

            if (i != j && resultMembership[i].second.first == resultMembership[j].second.first) {
                double filteredResult = max(resultMembership[i].second.second, resultMembership[j].second.second);
                if (filteredResult == resultMembership[i].second.second) {
                    resultMembership.erase(resultMembership.begin() + j);
                } else {
                    resultMembership.erase(resultMembership.begin() + i);
                }
            }
        }
    }
    for (int i = 0; i < resultMembership.size(); ++i) {
        cout << "Variable = " << resultMembership[i].first << " " << " , set = " << resultMembership[i].second.first
             << " , membership = " << resultMembership[i].second.second << endl;
    }
    cout << "Inference => done " << endl;
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
                addRules(system);
                break;
            }
            case 4: {
                runSimulation(system);
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
