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
    cout << "5- print system Variables and their Sets." << endl;
    cout << "6- print system Rules" << endl;
    cout << "7- Exit." << endl;
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

void printSystemMultiRules(FuzzyLogicSystem &system) {
    for (int i = 0; i < system.rules.size(); ++i) {
        cout << "RULE " << i + 1 << ": " << endl;
        for (int j = 0; j < system.rules[i].variables.size(); ++j) {
            cout << "var = " << system.rules[i].variables[j].first << " , set = "
                 << system.rules[i].variables[j].second << " --- ";
        }
        cout << endl;
        for (int j = 0; j < system.rules[i].operators.size(); ++j) {
            cout << "operator = " << system.rules[i].operators[j] << " ---- ";
        }
        cout << endl;
    }
};

void printSystemRules(FuzzyLogicSystem &system) {
    for (int i = 0; i < system.rules.size(); ++i) {
        system.rules[i];
        cout << "RULE " << i + 1 << ": " << system.rules[i].inVar1 << " " << system.rules[i].inSet1 << " "
             << system.rules[i]._operator;
        cout << " " << system.rules[i].inVar2 << " " << system.rules[i].inSet2 << " => " << system.rules[i].outVar
             << " " << system.rules[i].outSet
             << endl;
    }
}

void newAddRules(FuzzyLogicSystem &system) {
    cout << "Enter the rules in this format: (Press x to finish)\n";
    cout << "IN_variable set operator IN_variable set => OUT_variable set\n";
    cout << "------------------------------------------------------------\n";
    string input = "check", set = "check", _operator = "check";
    FuzzyVariable *variableChecker;
    FuzzySet *setChecker;
    while (input != "x") {
        vector<pair<string, string>> variables;
        vector<operatorType> operators;
        ///to input the first variable
        cin >> input;
        if (input == "x")
            break;
        /// if input is not x then this is a new rule
        variableChecker = system.findVariable(input);
        if (variableChecker == nullptr) {
            cout << "ERROR: you entered an unregistered variable.\n";
            continue;
        }
        cin >> set >> _operator;
        setChecker = variableChecker->findSet(set);
        if (setChecker == nullptr) {
            cout << "ERROR: you entered an unregistered set.\n";
            continue;
        }
        if (_operator != "and" && _operator != "or" && _operator != "or_not" && _operator != "and_not") {
            cout << "ERROR: you entered an unregistered operator.\n";
            cout << "Supported operators are : and, and_not, or, or_not \n";
            continue;
        }
        variables.emplace_back(input, set);
        operatorType type;
        if (_operator == "and")
            type = _and;
        else if (_operator == "and_not")
            type = _and_not;
        else if (_operator == "or")
            type = _or;
        else if (_operator == "or_not")
            type = _or_not;
        operators.push_back(type);
        bool inputProblem = false;
        while (input != "=>" && !inputProblem) {
            string var, set;
            cin >> input;    //to input possible variable
            if (input == "=>")
                break;
            ///to check the variable
            variableChecker = system.findVariable(input);
            if (variableChecker == nullptr) {
                cout << "ERROR: you entered an unregistered variable.\n";
                inputProblem = true;
                continue;
            }
            var = input;
            cin >> input;
            if (input == "=>")
                break;
            ///to check the set
            setChecker = variableChecker->findSet(input);
            if (setChecker == nullptr) {
                cout << "ERROR: you entered an unregistered set.\n";
                inputProblem = true;
                continue;
            }
            set = input;
            variables.emplace_back(var, set);
            cin >> _operator;
            if (_operator == "=>")
                break;
            if (_operator != "and" && _operator != "or" && _operator != "or_not" && _operator != "and_not") {
                cout << "ERROR: you entered an unregistered operator.\n";
                cout << "Supported operators are : and, and_not, or, or_not \n";
                inputProblem = true;
                continue;
            }

            if (_operator == "and")
                type = _and;
            else if (_operator == "and_not")
                type = _and_not;
            else if (_operator == "or")
                type = _or;
            else if (_operator == "or_not")
                type = _or_not;
            operators.push_back(type);
        }

        if (inputProblem) {
            cout << "An input problem occurred , please enter the rule again! " << endl;
            break;
        }

        //input out var
        cin >> input;
        variableChecker = system.findVariable(input);
        if (variableChecker == nullptr) {
            cout << "ERROR: you entered an unregistered variable.\n";
            inputProblem = true;
            continue;
        }
        string var = input;
        cin >> input;
        ///to check the set
        setChecker = variableChecker->findSet(input);
        if (setChecker == nullptr) {
            cout << "ERROR: you entered an unregistered set.\n";
            inputProblem = true;
            continue;
        }
        string set = input;
        variables.emplace_back(var, set);
        FuzzyRule newRule;

        for (auto iter: variables) {
            //cout << iter.first << " set-> " << iter.second << endl;
            newRule.variables.push_back(iter);
        }
        for (auto iter: operators) {
            //cout << iter << endl;
            newRule.operators.push_back(iter);
        }
        system.rules.push_back(newRule);
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
//        cout << "RULE ADDED: \n" << newRule.inVar1 << " " << newRule.inSet1 << " " << newRule._operator;
//        cout << " " << newRule.inVar2 << " " << newRule.inSet2 << " => " << newRule.outVar << " " << newRule.outSet
//             << endl;

    }
}

void runSimulation(FuzzyLogicSystem &system) {
    if (system.variables.empty() || system.rules.empty()) {
        cout << "CAN'T START THE SIMULATION! Please add the fuzzy sets and rules first.\n";
        return;
    }
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
//    for (int i = 0; i < resultMembership.size(); ++i) {
//        cout << "Variable = " << resultMembership[i].first << " " << " , set = " << resultMembership[i].second.first
//             << " , membership = " << resultMembership[i].second.second << endl;
//    }
    cout << "Inference => done " << endl;
    double crispDenominator = 0, crispNumerator = 0;
    for (int i = 0; i < resultMembership.size(); ++i) {
        FuzzyVariable *outVar = system.findVariable(resultMembership[i].first);
        for (int j = 0; j < outVar->sets.size(); ++j) {
            double weightedAVG = 0;
            if (outVar->sets[j].name == resultMembership[i].second.first) {
                for (int k = 0; k < outVar->sets[j].points.size(); ++k) {
                    weightedAVG += outVar->sets[j].points[k].first;  //to sum all x points in graph
                }
                weightedAVG /= outVar->sets[j].points.size();
                //cout << outVar->sets[j].name << " -> " << weightedAVG << endl;
                crispDenominator += resultMembership[i].second.second;
                crispNumerator += weightedAVG * resultMembership[i].second.second;
            }
        }
    }
    cout << "Defuzzification => done" << endl;
    cout << "CRISP = " << crispNumerator / crispDenominator << endl;

}

void runMultiVarSimulation(FuzzyLogicSystem &system) {
    if (system.variables.empty() || system.rules.empty()) {
        cout << "CAN'T START THE SIMULATION! Please add the fuzzy sets and rules first.\n";
        return;
    }
    cout << "Enter the crisp values:\n-----------------------\n";
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
        vector<pair<pair<string, string>, double>> values;
        for (int j = 0; j < membershipValues.size(); ++j) {  // to loop on every variable
            for (int k = 0; k < membershipValues[j].second.size(); ++k) {  // to loop on sets of every variable

                for (int l = 0; l < system.rules[i].variables.size() - 1; ++l) { //-1 because last var is output var
                    double value = 0;
//                    cout << "rule" << i + 1 << " " << "membership of " << membershipValues[j].first.name << " ";
//                    cout << "value of " << system.rules[i].variables[l].first << " "
//                         << system.rules[i].variables[l].second << endl;
                    if (membershipValues[j].first.name == system.rules[i].variables[l].first &&
                        membershipValues[j].second[k].first == system.rules[i].variables[l].second) {

                        value = membershipValues[j].second[k].second;
//                        cout << membershipValues[j].first.name << " variable of set "
//                             << membershipValues[j].second[k].first << " = " << value << endl;
                        values.emplace_back(
                                make_pair(membershipValues[j].first.name, membershipValues[j].second[k].first), value);
                    }

                }


            }
        }
//        cout << "VALUES" << endl;
//        for (int j = 0; j < values.size(); ++j) {
//            cout << values[j].second << " ";
//        }
//        cout << endl;
        double result = 0;
        vector<double> ruleValues;
        for (int j = 0; j < system.rules[i].variables.size() - 1; ++j) {
            double setVal = 0;
            for (int k = 0; k < values.size(); ++k) {
                if (values[k].first.first == system.rules[i].variables[j].first &&
                    values[k].first.second == system.rules[i].variables[j].second) {
                    setVal = values[k].second;
                    break;
                }
            }
            ruleValues.push_back(setVal);

        }
//        cout << "RULE values" << endl;
//        for (int j = 0; j < ruleValues.size(); ++j) {
//            cout << ruleValues[j] << " ";
//        }
//        cout << endl;
        for (int k = 0; k < system.rules[i].operators.size(); ++k) {
            operatorType _op = system.rules[i].operators[k];
            if (_op == _and) {
                result += min(ruleValues[k], ruleValues[k + 1]);
            } else if (_op == _and_not) {
                result = min(ruleValues[k], 1 - ruleValues[k + 1]);
            } else if (_op == _or) {
                result = max(ruleValues[k], ruleValues[k + 1]);
            } else if (_op == _or_not) {
                result = max(ruleValues[k], 1 - ruleValues[k + 1]);
            }
        }


        pair<string, double> tempResultPair;
        //tempResultPair.first = system.rules[i].outSet;
        tempResultPair.first = system.rules[i].variables[system.rules[i].variables.size() - 1].second;
        tempResultPair.second = result;
        resultMembership.emplace_back(system.rules[i].variables[system.rules[i].variables.size() - 1].first,
                                      tempResultPair);
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
//    ///testing purposes
//    for (int i = 0; i < resultMembership.size(); ++i) {
//        cout << "Variable = " << resultMembership[i].first << " " << " , set = " << resultMembership[i].second.first
//             << " , membership = " << resultMembership[i].second.second << endl;
//    }
    cout << "Inference => done " << endl;
    double crispDenominator = 0, crispNumerator = 0;
    for (int i = 0; i < resultMembership.size(); ++i) {
        FuzzyVariable *outVar = system.findVariable(resultMembership[i].first);
        for (int j = 0; j < outVar->sets.size(); ++j) {
            double weightedAVG = 0;
            if (outVar->sets[j].name == resultMembership[i].second.first) {
                for (int k = 0; k < outVar->sets[j].points.size(); ++k) {
                    weightedAVG += outVar->sets[j].points[k].first;  //to sum all x points in graph
                }
                weightedAVG /= outVar->sets[j].points.size();
                //cout << outVar->sets[j].name << " -> " << weightedAVG << endl;
                crispDenominator += resultMembership[i].second.second;
                crispNumerator += weightedAVG * resultMembership[i].second.second;
            }
        }
    }
    cout << "Defuzzification => done" << endl;
    double finalCrisp = crispNumerator / crispDenominator;

    FuzzyVariable output;
    vector<pair<string, double>> outputMembershipVec;
    for (int i = 0; i < system.variables.size(); ++i) {
        if (system.variables[i].type == OUT) {
            output = system.variables[i];
            outputMembershipVec = output.getMembership(finalCrisp);
            break;
        }
    }
    double tempMax = -1;
    for (int i = 0; i < outputMembershipVec.size(); ++i) {
        //cout << outputMembershipVec[i].first << " -> " << outputMembershipVec[i].second << endl;
        tempMax = max(tempMax, outputMembershipVec[i].second);
    }
    //cout << "tempMax = " << tempMax << endl;
    cout << "The predicted " << output.name << " is ";
    for (int i = 0; i < outputMembershipVec.size(); ++i) {
        //cout << "condition = " << (tempMax == outputMembershipVec[i].second) << endl;
        if (tempMax == outputMembershipVec[i].second) {
            cout << outputMembershipVec[i].first << " (" << finalCrisp << ")  ";
        }
    }
    cout << endl;

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
    while (choice != 7) {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                addVariables(system);
                break;
            }
            case 2: {
                addVariableSets(system);
                break;
            }
            case 3: {
                //addRules(system);
                newAddRules(system);
                break;
            }
            case 4: {
                //runSimulation(system);
                runMultiVarSimulation(system);
                break;
            }
            case 5: {
                if (system.variables.empty()) {
                    cout << "NO VARIABLES YET" << endl;
                } else {
                    printSystemVariables(system);
                }
                break;
            }
            case 6: {
                if (system.rules.empty()) {
                    cout << "NO RULES YET" << endl;
                } else {
                    //printSystemRules(system);
                    printSystemMultiRules(system);
                }
                break;
            }
            case 7: {
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
