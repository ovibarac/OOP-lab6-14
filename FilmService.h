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
#include <functional>

class FilmService {
    FilmRepo &repo;
    Validator &val;

public:
    FilmService(FilmRepo &repo, Validator &val) : repo{repo}, val{val} {}

    /*
     * Returneaza toate filmele
     */
    const MyVector<Film> &getAll() noexcept {
        return repo.getAll();
    }

    /*
     * Adauga un nou film
     * arunca exceptie daca: exista deja titlul, nu este valid
     */
    void addFilm(const string &titlu, string gen, int an, string actor);

    /*
     * Cauta filmul cu titlul dat
     * arunca exceptie daca nu exista
     */
    const Film &find(const string &titlu);

    /*
     * Modifica genul, anul si actorul principal al unui film
     * arunca exceptie daca filmul nu exista
     */
    void modFilm(const string &titlu, string new_gen, int new_an, string new_actor);



    /*
     * Sterge un film
     */
    void deleteFilm(string titlu);

    /*
     * Filtrare
     */
    MyVector<Film> filtreaza(function<bool(const Film &)> fct);

    MyVector<Film> filtrareTitlu(string titlu);

    MyVector<Film> filtrareAn(int an);

    MyVector<Film> sortByTitlu();

    MyVector<Film> sortByActor();

    MyVector<Film> sortByGen();

    MyVector<Film> sortByAn(MyVector<Film> rez);

    };
    void testSrv();


#endif //LAB6_7_FILMSERVICE_H
