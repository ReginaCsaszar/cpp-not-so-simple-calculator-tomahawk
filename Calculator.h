//
// Created by jeannie on 2017.09.25..
//


#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H

#include <iostream>
#include <string>

using namespace std;

class Calculator {

private:
    string data;
    bool parse();


public:
    Calculator();
    double evaluate(string data);

};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_TOMAHAWK_CALCULATOR_H
