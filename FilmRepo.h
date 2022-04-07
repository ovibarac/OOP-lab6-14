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
#include "MyVector.h"

using namespace std;

class FilmRepo {
    MyVector<Film> all;

public:
    FilmRepo() = default;

    /*
     * Verifica daca exista filmul in lista
     */
    bool exist(const Film& film) const;

    /*
     * Salvarea unui film
     * arunca exceptie daca mai exista film cu acelasi titlu
     */
    void store(const Film& film);

    void deleteFilm(string titlu);

    /*
     * Cauta filmul cu titlul dat
     * arunca exceptie daca nu exista
     */
    const Film& find(string titlu) const;

    /*
     * Returneaza toate filmele
     */
    const MyVector<Film>& getAll() const noexcept;
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
