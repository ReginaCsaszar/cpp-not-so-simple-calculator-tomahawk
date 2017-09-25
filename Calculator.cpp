//
// Created by jeannie on 2017.09.25..
//
#include "Calculator.h"
#include "Evaluable.hpp"

using namespace std;

Calculator::Calculator() {
    cout << "Object created" << endl;
}

double Calculator::evaluate(string data) {
    this->data = data;
    if (Calculator::parse()) {
        cout<<"Validating ok"<<endl;
    } else {
        cout<<"Validating not ok"<<endl;
    }
    return 1.0;
}

bool Calculator::parse() {
    cout<<"Given string: "<<data<<endl;
    string digit = "";
    for(char c : data) {
        if (std::isdigit(c)) {
            digit += c;
        } else {
            if (digit !="" ) {
                Evaluable number = Num(digit);
                digit = "";
                //cout<<"Number: "<<number.getNumber();
            }

        }
    }
    if (digit !="" ) {
        Evaluable number = Num(digit);
    }
    return true;
}
