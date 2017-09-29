#include <iostream>
#include <string>
#include <utility>

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

enum Level { NUMBER, BASE, SECOND, THIRD, PARENTHESIS };

class Evaluable {

public:

    Level getOrder() { return order; }
    double getNumValue() { return numValue; }
    string getStrValue() { return strValue; }

    static Evaluable createInstance(double num) {
        return Evaluable(num);
    }

    static Evaluable createInstance(string pattern) {

        if (!isdigit(pattern.front())) {
            if (pattern == minusOp || pattern == plusOp) {
                return Evaluable(pattern, BASE);
            } else if (pattern == starOp || pattern == slashOp) {
                return Evaluable(pattern, SECOND);
            } else if (pattern == upOp || pattern == rootOp || pattern == powOp) {
                return Evaluable(pattern, THIRD);
            } else if (pattern[0] == openBracket || pattern[0] == closeBracket) {
                return Evaluable(pattern, PARENTHESIS);
            } else {
                throw "Invalid evaluable! ";
            }
        }
        return Evaluable(pattern);
    }

private:

    Level order;
    double numValue;
    string strValue;

    explicit Evaluable(const string &strNum)
    : order(NUMBER), numValue(stod(strNum)), strValue(strNum) {}

    explicit Evaluable(double num)
    : order(NUMBER), numValue(num), strValue(to_string(num) ) {}

    Evaluable(string sign, Level ord)
    : order(ord), numValue(0), strValue(std::move(sign)) {}
};
