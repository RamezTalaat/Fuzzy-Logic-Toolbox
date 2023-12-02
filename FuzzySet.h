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
    vector<int> points;
    FuzzySet(string _name , FuzzySetType _type , int p1, int p2, int p3, int p4){
        name = _name;
        type = _type;
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        if(type == TRAP){
            points.push_back(p4);
        }

    }
};


#endif //FUZZY_LOGIC_TOOLBOX_FUZZYSET_H
