#include <iostream>
#include <string>

using namespace std;

class Evaluable {

protected:
    double value;
    string sign; // sign or "not op"
    unsigned int order; // 0: number, 1: +-, 2: */, 3: root/powr

public:
    double getNumber() {
        return this->value;
    }

    string getSign() {
        return this->sign;
    }

    int getOrder() {
        return this->order;
    }
};

class Num: public Evaluable {

public:
    Num(string value) {
        this->value = stod(value);
        this->sign = value;
        this->order = 0;
    }
};

class Operator: public Evaluable {

public:
    Operator(string sign, int order) {
        this->value = 1;
        this->sign = sign;
        this->order = order;
    }
};

