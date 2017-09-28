//
// Created by jeannie on 2017.09.25..
//


#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Evaluable.hpp"

using namespace std;

class Calculator {

private:
    string data;
    int openBracketCount;
    int closeBracketCount;
    vector<Evaluable> evaluables;

    bool parse();
    void calculate(int);
    bool createEvaluable(string);
    void process(int, int);


public:
    Calculator();
    double evaluate(string data);
};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H
