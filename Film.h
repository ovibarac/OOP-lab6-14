//
// Created by ovi on 3/28/22.
//

#ifndef LAB6_7_FILM_H
#define LAB6_7_FILM_H
#include <iostream>
#include <string>

using namespace std;

class Film {
    string titlu;
    string gen;
    int an;
    string actor;
public:
    Film(const string t, string g, int an, string a):titlu{t}, gen{g}, an{an}, actor{a}{}

    string getTitlu() const{
        return titlu;
    }

    string getGen() const{
        return gen;
    }

    int getAn() const{
        return an;
    }

    string getActor() const{
        return actor;
    }
};


#endif //LAB6_7_FILM_H
