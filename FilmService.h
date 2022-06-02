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
#include "Cos.h"
#include "Undo.h"
#include "Observer.h"

class FilmService : public Observable{
    FilmRepo &repo;
    Validator &val;
    Cos &cos;

    vector<ActiuneUndo*> undoActions;

    void generalSort(vector<Film>& v, bool(*maimicF)(const Film&, const Film&)){
        for(int i = 0; i< v.size(); i++){
            for(int j = i+1; j<v.size(); j++){
                if(!maimicF(v[i], v[j])){
                    Film aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
        }
    }
public:
    FilmService(FilmRepo &repo, Validator &val, Cos &cos) : repo{repo}, val{val}, cos{cos} {}

    /*
     * Returneaza toate filmele
     */
    const vector<Film> &getAll() noexcept {
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

    void undo();

    /*
     * Filtrare
     */
    vector<Film> filtreaza(function<bool(const Film &)> fct);

    vector<Film> filtrareTitlu(string titlu);

    vector<Film> filtrareAn(int an);

    vector<Film> filtrareGen(string gen);

    vector<Film> sortByTitlu();

    vector<Film> sortByActor();

    vector<Film> sortByGen();

    vector<Film> sortByAn(vector<Film> rez);

    void addCos(string titlu);

    void golesteCos();

    vector<Film> allCos(){
        return cos.getAll();
    }

    int cosSize(){
        return cos.size();
    }

    void generateCos(int nrFilme);

    bool anyOfGen(string gen);

};
void testSrv();


#endif //LAB6_7_FILMSERVICE_H
