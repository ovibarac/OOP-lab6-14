//
// Created by ovi on 3/28/22.
//

#ifndef LAB6_7_FILMSERVICE_H
#define LAB6_7_FILMSERVICE_H
#include "Film.h"
#include "FilmRepo.h"
#include "Validator.h"
#include <string>
#include <vector>

class FilmService {
    FilmRepo& repo;
    Validator& val;

public:
    FilmService(FilmRepo& repo, Validator& val): repo{repo}, val{val}{}

    /*
     * Returneaza toate filmele
     */
    const vector<Film>& getAll() noexcept{
        return repo.getAll();
    }

    /*
     * Adauga un nou film
     * arunca exceptie daca: exista deja titlul, nu este valid
     */
    void addFilm(const string& titlu, string gen, int an, string actor);
};

void testSrv();


#endif //LAB6_7_FILMSERVICE_H
