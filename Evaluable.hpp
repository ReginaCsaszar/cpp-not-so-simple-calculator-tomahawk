class Evaluable {
public:
    double getNumber();
    char getSign();

};

class Num: public Evaluable {


public:
    double value;
    Num(string value) {
        this->value=stod(value);
        std::cout<<"Num parsed: "<<value<<endl;
    }

    double getNumber(){
        return value;
    }
};

class Operator: public Evaluable {
    char sign;

public:
    Operator(char sign) {
        this->sign=sign;
        std::cout<<"Sign parsed"<<endl;
    }
};

