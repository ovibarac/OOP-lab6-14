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
    Film() = delete;

    Film(string t, string g, int an, string a):titlu{t}, gen{g}, an{an}, actor{a}{}

    Film& operator=(const Film& ot){
        this->titlu = ot.titlu;
        this->gen = ot.gen;
        this->an = ot.an;
        this->actor = ot.actor;
        return (*this);
    }

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

    void setGen(string& new_gen){
        gen = new_gen;
    }

    void setAn(int& new_an){
        an = new_an;
    }

    void setActor(string& new_actor){
        actor = new_actor;
    }
};


#endif //LAB6_7_FILM_H
