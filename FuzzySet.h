//
// Created by Ramez on 12/2/2023.
//

#ifndef FUZZY_LOGIC_TOOLBOX_FUZZYSET_H
#define FUZZY_LOGIC_TOOLBOX_FUZZYSET_H
using namespace std;

#include <bits/stdc++.h>
#include <string>

enum FuzzySetType {
    TRI,
    TRAP
};

class FuzzySet {
public:
    string name;
    FuzzySetType type;
    vector<pair<int, int>> points;  //x,y

    FuzzySet(string _name, FuzzySetType _type, int p1, int p2, int p3, int p4) {
        name = _name;
        type = _type;
        points.emplace_back(p1, 0);

        if (type == TRAP) {
            points.emplace_back(p2, 1);
            points.emplace_back(p3, 1);
            points.emplace_back(p4, 0);
        } else {
            points.emplace_back(p2, 1);
            points.emplace_back(p3, 0);
        }

    }
};


#endif //FUZZY_LOGIC_TOOLBOX_FUZZYSET_H
