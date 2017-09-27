//
// Created by jeannie on 2017.09.25..
//
#include <cmath>
#include "Calculator.h"

using namespace std;

Calculator::Calculator() {}

double Calculator::evaluate(string data) {
    this->data = data;
    double result = 0;

    if (Calculator::parse()) {

        cout<<Evaluables.size()<<"\nEvaulate: ";
        for (Evaluable eval : Evaluables) {
            cout<<eval.getSign();
        }
        cout<<endl;

        for (int i=1; i<Evaluables.size(); i+=2) {
            if (Evaluables[i].getOrder() == 3) {
                Calculator::calculate(i);
                i-=2;
            }
        }


        for (int i=1; i<Evaluables.size(); i+=2) {
            if (Evaluables[i].getOrder() == 2) {
                Calculator::calculate(i);
                i-=2;
            }
        }

        cout<<endl<<Evaluables.size()<<" elements in vector after level 1:\n";
        for (Evaluable eval : Evaluables) {
            cout<<eval.getSign()<<", ";
        }
        cout<<endl;

        for (int i=1; i<Evaluables.size(); i+=2) {
            if (Evaluables[i].getOrder() == 1) {
                Calculator::calculate(i);
                i-=2;
            }
        }
        result = Evaluables[0].getNumber();
    }

    cout<<endl<<Evaluables.size()<<" elements in vector after level 0 :\n";
    for (Evaluable eval : Evaluables) {
        cout<<eval.getSign()<<", ";
    }
    cout<<"\n\nResult: "<<result<<endl;

    return result;
}

void Calculator::calculate(int index) {
    double result;
    double firstNum = Evaluables[index-1].getNumber();
    double secondNum = Evaluables[index+1].getNumber();
    string sign = Evaluables[index].getSign();

    cout<<"\nNow calculate: "<<firstNum<<sign<<secondNum;

    if (sign == "*") { result = firstNum * secondNum; }
    else if (sign == "/") { result = firstNum / secondNum; }
    else if (sign == "+") { result = firstNum + secondNum; }
    else if (sign == "-") { result = firstNum - secondNum; }
    else if (sign == "root") { result = pow(secondNum, 1/firstNum); }
    else if (sign == "pow" || sign == "^") { result = pow(firstNum, secondNum); }


    Evaluables[index-1] = Num(result);

    cout<<" = "<<Evaluables[index-1].getSign()<<endl;

    Evaluables.erase(Evaluables.begin()+index);
    Evaluables.erase(Evaluables.begin()+index);

    }


bool Calculator::parse() {
    string digit = "";
    string op = "";
    //cout<<"String to parse: "<<data<<endl;
    for(char c : data) {

        if (c == ' ') { continue; }

        if (std::isdigit(c)) {
            digit += c;
            if (op != "") {
                if (!Calculator::createEvaluable(op)) return false;
                op = "";
            }
        } else {
            op += c;
            if (c == '.') {
                if ((digit != "")&&(digit.find('.') == std::string::npos)) {
                    digit += c;
                    op = "";
                }
            } else if (digit != "") {
                Calculator::createEvaluable(digit);
                digit = "";
            }
        }
    }

    if (digit !="" ) {
        Calculator::createEvaluable(digit);
    }

    if (op !="" ) {
        cout<<"Operator/character at the end!\n";
        return false;
    }

    /*cout<<Evaluables.size()<<" elements ";
    for (Evaluable eval : Evaluables) {
        cout<<eval.getSign();
    }
    cout<<endl;*/
    return true;
}

bool Calculator::createEvaluable(string pattern) {
    if (isdigit(pattern.front())) {
        Evaluables.push_back(Num(pattern));
    }
    else {
        if (pattern == "-" || pattern == "+") {
            Evaluables.push_back(Operator(pattern, 1));
        } else if (pattern == "*" || pattern == "/") {
            Evaluables.push_back(Operator(pattern, 2));
        } else if (pattern == "^" || pattern == "root") {
            Evaluables.push_back(Operator(pattern, 3));
        } else {
            cout << "Invalid operator/character!" << endl;
            return false;
        }
    }
    return true;
}
