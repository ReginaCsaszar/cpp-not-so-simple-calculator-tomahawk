#include <iostream>
#include <string>

using namespace std;

namespace {
    char openBracket = '(';
    char closeBracket = ')';
    string minusOp = "-";
    string plusOp = "+";
    string starOp = "*";
    string slashOp = "/";
    string upOp = "^";
    string rootOp = "root";
    string powOp = "pow";
}

class Evaluable {

public:

    int getOrder() { return order; }
    double getNumValue() { return numValue; }
    string getStrValue() { return strValue; }

    static Evaluable createInstance(double num) {
        return Evaluable(num);
    }

    static Evaluable createInstance(string pattern) {

        if (!isdigit(pattern.front())) {
            if (pattern == minusOp || pattern == plusOp) {
                return Evaluable(pattern, 1);
            } else if (pattern == starOp || pattern == slashOp) {
                return Evaluable(pattern, 2);
            } else if (pattern == upOp || pattern == rootOp || pattern == powOp) {
                return Evaluable(pattern, 3);
            } else if (pattern[0] == openBracket || pattern[0] == closeBracket) {
                return Evaluable(pattern, 4);
            } else {
                throw "Invalid evaluable! ";
            }
        }
        return Evaluable(pattern);
    }

private:

    unsigned int order; // 0: number, 1: +-, 2: */, 3: root/pow 4: (,) TODO: enum!
    double numValue;
    string strValue;

    Evaluable(string strNum)
    : order(0), numValue(stod(strNum)), strValue(strNum) {}

    Evaluable(double num)
    : order(0), numValue(num), strValue(to_string(num) ) {}

    Evaluable(string sign, unsigned int ord)
    : order(ord), numValue(0), strValue(sign) {}
};
