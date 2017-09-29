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

namespace {
    char dot = '.';
}

class Calculator {

public:
    Calculator();
    double evaluate(string data);

private:
    string data;
    int openBracketCount;
    int closeBracketCount;
    vector<Evaluable> evaluables;

    bool parse();
    bool factory(string);
    void handleBrackets();
    void process(int, int);
    void calculate(int);
};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H
