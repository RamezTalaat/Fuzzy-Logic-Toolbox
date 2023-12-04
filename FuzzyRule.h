//
// Created by mizoe on 12/4/2023.
//

#ifndef FUZZY_LOGIC_TOOLBOX_FUZZYRULE_H
#define FUZZY_LOGIC_TOOLBOX_FUZZYRULE_H

enum operatorType{
    _and,
    _or,
    _and_not,
    _or_not
};
class FuzzyRule {
public:
    string inVar1,inVar2,outVar , inSet1,inSet2,outSet;
    operatorType _operator;
};


#endif //FUZZY_LOGIC_TOOLBOX_FUZZYRULE_H
