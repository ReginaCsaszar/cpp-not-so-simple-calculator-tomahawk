//
// Created by jeannie on 2017.09.25..
//
#include "Calculator.h"

using namespace std;

Calculator::Calculator() {}

double Calculator::evaluate(string data) {
    this->data = data;
    double result = 0;

    Calculator::parse();
    return result;
}

bool Calculator::parse() {
    string digit = "";
    string op = "";
    cout<<"String to parse: "<<data<<endl;
    for(char c : data) {

        if (c == ' ') { continue;}

        if (std::isdigit(c)) {
            digit += c;
            if (op == "-" || op == "+") {
                Evaluables.push_back(Operator(op, 1));
                            }
            else if (op == "*" || op == "/") {
                Evaluables.push_back(Operator(op, 2));
            }
            else if (op == "^" || op == "root") {
                Evaluables.push_back(Operator(op, 3));
            }
            op = "";
        }

        else {
            if (digit !="" ) {
                Evaluables.push_back(Num(digit));
                digit = "";
            }
            op += c;
            }
        }

    if (digit !="" ) {
        Evaluables.push_back(Num(digit));
    }
    cout<<Evaluables.size()<<" elements\n";
    for (Evaluable eval : Evaluables) {
        cout<<eval.getSign();
    }
    cout<<endl;
    return true;
}
