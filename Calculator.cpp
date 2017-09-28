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

    cout<<"string to parse: "<<data<<endl;
    if (Calculator::parse()) {

        if (openBracketCount > 0) {
            vector<int> openBracketIndices;
            for (int i = 0; i < evaluables.size(); i++) {
                if (evaluables[i].getStrValue() == "(") {
                    openBracketIndices.push_back(i);
                } else if (evaluables[i].getStrValue() == ")") {
                    int firstIndex = openBracketIndices.back()+1;
                    Calculator::process(firstIndex, i);
                    i = firstIndex-1;
                    evaluables.erase(evaluables.begin()+i);
                    evaluables.erase(evaluables.begin()+i+1);
                    openBracketIndices.pop_back();
                }
            }
        }

        Calculator::process(0, evaluables.size()-1);

        result = evaluables[0].getNumValue();

        cout<<endl<<evaluables.size()<<" elements in vector after +- :\n";
        for (Evaluable eval : evaluables) {
            cout<<eval.getStrValue()<<", ";
        }
        cout<<"\n\nResult: "<<result<<endl;
    } else {
        cout<<"Error in parsing, invalid input string!!!"<<endl;
    }
    
    if (std::isinf(result)) {
        cout<<"Division by zero!"<<endl;
        result = 0;
    }
    return result;
}

void Calculator::process(int startIndex, int endIndex) {

    cout<<"\nEvaulate: ";
        for (int i = startIndex; i < endIndex; i++) {
            cout<<evaluables[i].getStrValue();
        }
        cout<<endl;

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == 3) {
            Calculator::calculate(i);
            i-=2;
        }
    }

    cout<<endl<<evaluables.size()<<" elements in vector after pow, ^, root:\n";
    for (Evaluable eval : evaluables) {
        cout<<eval.getStrValue()<<", ";
    }
    cout<<endl;

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == 2) {
            Calculator::calculate(i);
            i-=2;
        }
    }

    cout<<endl<<evaluables.size()<<" elements in vector after *, /:\n";
    for (Evaluable eval : evaluables) {
        cout<<eval.getStrValue()<<", ";
    }
    cout<<endl;

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == 1) {
            Calculator::calculate(i);
            i-=2;
        }
    }
}

void Calculator::calculate(int index) {
    double result;
    double firstNum = evaluables[index-1].getNumValue();
    double secondNum = evaluables[index+1].getNumValue();
    string sign = evaluables[index].getStrValue();

    cout<<"\nNow calculate: "<<firstNum<<sign<<secondNum;

    if (sign == "*") { result = firstNum * secondNum; }
    else if (sign == "/") { result = firstNum / secondNum; }
    else if (sign == "+") { result = firstNum + secondNum; }
    else if (sign == "-") { result = firstNum - secondNum; }
    else if (sign == "root") { result = pow(secondNum, 1/firstNum); }
    else if (sign == "pow" || sign == "^") { result = pow(firstNum, secondNum); }


    evaluables[index-1] = Evaluable(result);

    cout<<" = "<<evaluables[index-1].getStrValue()<<endl;

    evaluables.erase(evaluables.begin()+index);
    evaluables.erase(evaluables.begin()+index);

    }


bool Calculator::parse() {
    string digit = "";
    string op = "";

    openBracketCount = 0;
    closeBracketCount = 0;
    cout<<"String to parse: "<<data<<endl;
    if (!std::isdigit(data[0]) && data[0] != '(' && data[0] != ' ') return false;
    for(char c : data) {

        if (c == ' ') { continue; }

        if (std::isdigit(c)) {
            digit += c;
            if (op != "") {
                if (!Calculator::createEvaluable(op)) return false;
                op = "";
            }
        // if not digit
        } else {
            if (c == '(') {
                if (digit != "") {
                    return false;
                } else if (op!="") {
                    if (op == ")") {
                        return false;
                    } else {
                        Calculator::createEvaluable(op);
                        op = "";
                    }
                }
            } else if (c == ')') {
                if (++closeBracketCount <= openBracketCount) {
                    if (digit != "") {
                        Calculator::createEvaluable(digit);
                        digit = "";
                    } else if (op == ")") {
                        Calculator::createEvaluable(op);
                        op="";
                    }
                } else return false;
            }
            if (op == ")") {
                Calculator::createEvaluable(op);
                op="";
            }

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

    if (openBracketCount != closeBracketCount) return false;

    if (digit !="" ) {
        Calculator::createEvaluable(digit);
    }

    if (op==")") {
        Calculator::createEvaluable(op);
        op="";
    }

    if (op !="" ) {
        cout<<"Operator/character at the end!\n";
        return false;
    }

    cout<<evaluables.size()<<" elements ";
    for (Evaluable eval : evaluables) {
        cout<<eval.getStrValue();
    }
    cout<<endl;
    return true;
}

bool Calculator::createEvaluable(string pattern) {
    if (isdigit(pattern.front())) {
        evaluables.push_back(Evaluable(pattern));
    }
    else {
        if (pattern == "-" || pattern == "+") {
            evaluables.push_back(Evaluable(pattern, 1));
        } else if (pattern == "*" || pattern == "/") {
            evaluables.push_back(Evaluable(pattern, 2));
        } else if (pattern == "^" || pattern == "root") {
            evaluables.push_back(Evaluable(pattern, 3));
        } else if (pattern == "(") {
            ++openBracketCount;
            evaluables.push_back(Evaluable(pattern, 4));}
        else if (pattern == ")") {
            evaluables.push_back(Evaluable(pattern, 4));
        } else {
            cout << "Invalid operator/character!" << endl;
            return false;
        }
    }
    return true;
}
