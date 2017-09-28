#include <iostream>
#include <string>

using namespace std;

class Evaluable {

    unsigned int order; // 0: number, 1: +-, 2: */, 3: root/pow 4: (,) TODO: enum!
    double numValue;
    string strValue;

public:

    Evaluable(string strNum)
    : order(0), numValue(stod(strNum)), strValue(strNum) {}

    Evaluable(double num)
    : order(0), numValue(num), strValue(to_string(num) ) {}

    Evaluable(string sign, unsigned int ord)
    : order(ord), numValue(0), strValue(sign) {}

    int getOrder() {
        return order;
    }

    double getNumValue() {
        return numValue;
    }

    string getStrValue() {
        return strValue;
    }
};
