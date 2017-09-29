//
// Created by jeannie on 2017.09.25..
//
#include <cmath>
#include <utility>
#include "Calculator.h"

using namespace std;

Calculator::Calculator() = default;

double Calculator::evaluate(string data) {
    this->data = std::move(data);
    double result = 0;

    if (Calculator::parse()) {

        Calculator::handleBrackets();

        Calculator::process(0, evaluables.size()-1);

        result = evaluables[0].getNumValue();

    } else { cout<<"Error in parsing."<<endl; }

    if (std::isinf(result)) {
        cout<<"Division by zero!"<<endl;
        result = 0;
    }

    cout<<"Result: "<<result<<endl;
    return result;
}

bool Calculator::parse() {
    string digit;
    string op;

    int openBracketCount = 0;
    int closeBracketCount = 0;
    cout<<"Input string: "<<data<<endl;
    if (!std::isdigit(data[0]) && data[0] != openBracket && data[0] != ' ') return false;
    for(char c : data) {

        if (c == ' ') { continue; }

        if (std::isdigit(c)) {
            digit += c;
            if (!op.empty()) {
                if (!Calculator::factory(op)) return false;
                op = "";
            }
        // if not digit
        } else {
            if (c == openBracket) {
                if (!digit.empty()) {
                    return false;
                } else if (!op.empty()) {
                    if (op[0] == closeBracket) {
                        return false;
                    } else {
                        Calculator::factory(op);
                        op = "";
                    }
                }
                openBracketCount++;
            } else if (c == closeBracket) {
                if (++closeBracketCount <= openBracketCount) {
                    if (!digit.empty()) {
                        Calculator::factory(digit);
                        digit = "";
                    } else if (op[0] == closeBracket) {
                        Calculator::factory(op);
                        op="";
                    }
                } else {
                    return false;
                }
            }
            if (op[0] == closeBracket) {
                Calculator::factory(op);
                op="";
            }

            op += c;
            if (c == dot) {
                if ((!digit.empty())&&(digit.find(dot) == std::string::npos)) {
                    digit += c;
                    op = "";
                }
            } else if (!digit.empty()) {
                Calculator::factory(digit);
                digit = "";
            }
        }
    }

    if (openBracketCount > 0) {
        if (openBracketCount != closeBracketCount) { return false; }
        isBracketInFormula = true;
    }

    if (!digit.empty()) { Calculator::factory(digit); }


    if (!op.empty()) {
        if (op[0]==closeBracket) {
            Calculator::factory(op);
        } else {
            cout << "Invalid character at the end! ";
            return false;
        }
    }
    return true;
}

bool Calculator::factory(string pattern) {

    if (isdigit(pattern.front())) {
        evaluables.push_back(Evaluable::createInstance(pattern));
    }
    else {
        try {
            evaluables.push_back(Evaluable::createInstance(pattern));
        } catch (const char* msg) {
            cout <<msg;
            return false;
        }
    }
    return true;
}

void Calculator::handleBrackets() {

    if (isBracketInFormula) {
        vector<int> openBracketIndices;

        for (int i = 0; i < evaluables.size(); i++) {

            if (evaluables[i].getStrValue()[0] == openBracket) {
                openBracketIndices.push_back(i);

            } else if (evaluables[i].getStrValue()[0] == closeBracket) {
                int firstIndex = openBracketIndices.back() + 1;

                Calculator::process(firstIndex, i);

                i = firstIndex - 1;
                evaluables.erase(evaluables.begin() + i);
                evaluables.erase(evaluables.begin() + i + 1);
                openBracketIndices.pop_back();
            }
        }
    }
}

void Calculator::process(int startIndex, int endIndex) {

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == THIRD) {
            Calculator::calculate(i);
            i-=2;
        }
    }

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == SECOND) {
            Calculator::calculate(i);
            i-=2;
        }
    }

    for (int i=startIndex+1; i<endIndex; i+=2) {
        if (evaluables[i].getOrder() == BASE) {
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

    if (sign == starOp) { result = firstNum * secondNum; }
    else if (sign == slashOp) { result = firstNum / secondNum; }
    else if (sign == plusOp) { result = firstNum + secondNum; }
    else if (sign == minusOp) { result = firstNum - secondNum; }
    else if (sign == rootOp) { result = pow(secondNum, 1/firstNum); }
    else if (sign == powOp || sign == upOp) { result = pow(firstNum, secondNum); }

    evaluables[index-1] = Evaluable::createInstance(result);

    evaluables.erase(evaluables.begin()+index);
    evaluables.erase(evaluables.begin()+index);

}
