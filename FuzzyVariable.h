//
// Created by Ramez on 12/2/2023.
//

#ifndef FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H
#define FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H

#include "FuzzySet.h"
using namespace std;
#include <bits/stdc++.h>
#include <string>

enum FuzzyVariableType{
    IN,
    OUT
};


class FuzzyVariable {
public:
    string name;
    FuzzyVariableType type; //IN our out
    int rangeMin;
    int rangeMax;
    vector<FuzzySet> sets;
};

#endif //FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H
