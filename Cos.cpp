//
// Created by ovi on 4/14/22.
//

#include "Cos.h"

Cos::Cos() {
    all = vector<Film>();
//    all.push_back(Film("a", "b", 2000, "c"));
}

void Cos::add(Film &film) {
    all.push_back(film);
}

void Cos::goleste() {
    all.clear();
}