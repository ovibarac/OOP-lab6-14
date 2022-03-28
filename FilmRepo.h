//
// Created by ovi on 3/28/22.
//

#ifndef LAB6_7_FILMREPO_H
#define LAB6_7_FILMREPO_H
#include "Film.h"
#include <vector>
#include <string>
#include <iostream>
#include <ostream>

using namespace std;

class FilmRepo {
    vector<Film> all;

    /*
     * Verifica daca exista filmul in lista
     */
    bool exist(const Film& film) const;

public:
    FilmRepo() = default;

    /*
     * Salvarea unui film
     * arunca exceptie daca mai exista film cu acelasi titlu
     */
    void store(const Film& film);

    /*
     * Cauta filmul cu titlul dat
     * arunca exceptie daca nu exista
     */
    const Film& find(string titlu) const;

    /*
     * Returneaza toate filmele
     */
    const vector<Film>& getAll() const noexcept;
};

class FilmRepoException{
    string msg;
public:
    FilmRepoException(string m): msg{m}{}
    friend ostream& operator<<(ostream& out, const FilmRepoException& ex);
};

ostream& operator<<(ostream& out, const FilmRepoException& ex);

void testeRepo();

#endif //LAB6_7_FILMREPO_H
