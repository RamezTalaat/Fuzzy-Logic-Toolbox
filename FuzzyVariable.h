//
// Created by Ramez on 12/2/2023.
//

#ifndef FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H
#define FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H

#include "FuzzySet.h"

using namespace std;

#include <bits/stdc++.h>
#include <string>

enum FuzzyVariableType {
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

    FuzzySet *findSet(string varName) {
        FuzzySet *temp = nullptr;
        for (int i = 0; i < sets.size(); ++i) {
            if (varName == sets[i].name) {
                temp = &sets[i];
                break;
            }
        }
        return temp;
    }

    vector<pair<string, double>> getMembership(double value) {
        vector<pair<string, double>> membership;
        for (int i = 0; i < sets.size(); ++i) {
            for (int j = 0; j < sets[i].points.size() - 1; ++j) {
                if (sets[i].points[j].first != sets[i].points[j + 1].first && value >= sets[i].points[j].first &&
                    value <= sets[i].points[j + 1].first) {
//                    cout << "CHOSEN points = " << sets[i].points[j].first << ", " << sets[i].points[j].second
//                         << " and ";
//                    cout << sets[i].points[j + 1].first << ", " << sets[i].points[j + 1].second << endl;
                    pair<int, int> point1 = sets[i].points[j], point2 = sets[i].points[j + 1];
                    double slope = (point2.second - point1.second) /
                                   (double) (point2.first - point1.first);  ///a = y2-y1/x2-x1
                    //cout << "SLOPE(a) = " << slope << endl;
                    double constant = point1.second - slope * point1.first;   ///y - ax + b  //constant = b , slope = a
                    //cout << "CONSTANT(b) = " << constant << endl;
                    double result = slope * value + constant;
                    //cout << "MEMBERSHIP AT " << value << " = " << result << endl;
                    membership.emplace_back(sets[i].name, result);
                }
            }
        }
        return membership;
    }
};

#endif //FUZZY_LOGIC_TOOLBOX_FUZZYVARIABLE_H
