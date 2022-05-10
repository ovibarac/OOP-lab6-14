//
// Created by ovi on 4/14/22.
//

#ifndef LAB6_7_COS_H
#define LAB6_7_COS_H
#include "Film.h"
#include <vector>

class Cos {
private:
    vector<Film> all;

public:
    Cos();

    vector<Film>& getAll(){
        return all;
    }

    int size(){
        return all.size();
    }

    void add(Film& film);

    void goleste();
};


#endif //LAB6_7_COS_H
