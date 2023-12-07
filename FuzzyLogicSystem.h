#ifndef FUZZY_LOGIC_TOOLBOX_FUZZYLOGICSYSTEM_H
#define FUZZY_LOGIC_TOOLBOX_FUZZYLOGICSYSTEM_H

using namespace std;

#include <bits/stdc++.h>
#include <string>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"

class FuzzyLogicSystem {
public:
    string name;
    string description;
    vector<FuzzyVariable> variables;
    vector<FuzzyRule> rules;

    FuzzyVariable *findVariable(string varName) {
        //cout << "IN find variable"<<endl;
        FuzzyVariable *temp = nullptr;
        for (int i = 0; i < variables.size(); ++i) {
            if (varName == variables[i].name) {
                temp = &variables[i];
                break;

            }

        }

        return temp;
    }

    void updateVariable(FuzzyVariable &_var) {
        for (int i = 0; i < variables.size(); ++i) {
            if (variables[i].name == _var.name) {
                variables[i] = _var;
            }
        }
    }
};


#endif //FUZZY_LOGIC_TOOLBOX_FUZZYLOGICSYSTEM_H
