//
// Created by jeannie on 2017.09.25..
//
#include "Calculator.h"
using namespace std;

Calculator::Calculator() {
    cout << "Object created" << endl;
}

double Calculator::evaluate(string data) {
    this->data = data;
    if (Calculator::validate()) {
        cout<<"Validating ok"<<endl;
    } else {
        cout<<"Validating not ok"<<endl;
    }
    return 1.0;
}

bool Calculator::validate() {
    cout<<"Given string: "<<data;
    return true;
}
