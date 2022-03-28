//
// Created by ovi on 3/28/22.
//

#ifndef LAB6_7_VALIDATOR_H
#define LAB6_7_VALIDATOR_H
#include <string>
#include "Film.h"
#include <vector>
#include <ostream>

using namespace std;

class ValidateException{
    vector<string> msgs;
public:
    ValidateException(const vector<string>& errors): msgs{errors}{}
    friend ostream& operator<<(ostream& out, const ValidateException& ex);

};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator {
public:
    void validate(const Film& film);
};

/*
* Testeaza validarea
*/
void testValidator();


#endif //LAB6_7_VALIDATOR_H
