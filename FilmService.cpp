//
// Created by ovi on 3/28/22.
//

#include "FilmService.h"
#include <assert.h>
#include "MyVector.h"


void FilmService::addFilm(const string& titlu, string gen, int an, string actor){
    /*
     * Adauga un nou film
     * arunca exceptie daca: exista deja titlul, nu este valid
     */
    Film f{titlu, gen, an, actor};
    val.validate(f);
    repo.store(f);
}

const Film& FilmService::find(const string& titlu){
    /*
     * Cauta filmul cu titlul dat
     * arunca exceptie daca nu exista
     */
    return repo.find(titlu);
}

void FilmService::modFilm(const string& titlu, string new_gen, int new_an, string new_actor){
    /*
    * Modifica genul, anul si actorul principal al unui film
     * titlu: titlul cautat
     * new_gen, new_an, new_actor: datele noi
    * arunca exceptie daca filmul nu exista sau modificarea nu e valida
    */
    Film& film = const_cast<Film &>(find(titlu));
    val.validate(Film {titlu, new_gen, new_an, new_actor});
    film.setGen(new_gen);
    film.setAn(new_an);
    film.setActor(new_actor);
}

void FilmService::deleteFilm(string titlu) {
    repo.deleteFilm(titlu);
}

MyVector<Film> FilmService::filtreaza(function<bool(const Film&)> fct){
    /*
     * Filtreaza dupa un criteriu
     * fct: functia relatie
     */
    MyVector<Film> rez;
    IteratorVectorT<Film> it = IteratorVectorT<Film>(getAll(), 0);
    while(it.valid()){
        if(fct(it.element())){
            rez.add(it.element());
        }
        it.next();
    }
    return rez;
}

MyVector<Film> FilmService::filtrareTitlu(string titlu) {
    /*
     * Filtrare dupa titlu
     */
    return filtreaza([titlu](const Film& f){
        return f.getTitlu() == titlu;
    });
}

MyVector<Film> FilmService::filtrareAn(int an) {
    /*
     * Filtrare dupa an aparitie
     */
    return filtreaza([an](const Film& f){
        return f.getAn() == an;
    });
}

bool cmpTitlu(const Film& f1, const Film& f2){
    return f1.getTitlu() > f2.getTitlu();
}

MyVector<Film> FilmService::sortByTitlu(){
    /*
     * Sorteaza dupa titlu
     */
    MyVector<Film> rez = getAll();
    rez.generalSort([](const Film& f1, const Film& f2){
        return f1.getTitlu() < f2.getTitlu();
    });
    return rez;
}

MyVector<Film> FilmService::sortByActor(){
    /*
     * Sorteaza dupa actor
     */
    MyVector<Film> rez = getAll();
    rez.generalSort([](const Film& f1, const Film& f2){
        return f1.getActor() < f2.getActor();
    });
    return rez;
}

MyVector<Film> FilmService::sortByGen(){
    /*
     * Sorteaza dupa actor
     */
    MyVector<Film> rez = getAll();
    rez.generalSort([](const Film& f1, const Film& f2){
        return f1.getGen() > f2.getGen();
    });
    return rez;
}

MyVector<Film> FilmService::sortByAn(MyVector<Film> rez){
    /*
     * Sorteaza dupa actor
     */

    rez.generalSort([](const Film& f1, const Film& f2){
        return f1.getAn() < f2.getAn();
    });
    return rez;
}

void testAddSrv(){
    /*
     * Testeaza adaugarea service
     */
    FilmRepo repo;
    Validator val;
    FilmService s {repo, val};
    s.addFilm("a", "b", 1900, "a");
    s.addFilm("b", "b", 1900, "a");
    s.addFilm("c", "b", 1900, "a");
    assert(s.getAll().size() == 3);
    try{
        s.addFilm("", "", 0, "");assert(false);
    }
    catch(ValidateException&){
        assert(true);
    }
    try{
        s.addFilm("a", "a", 1900, "a");assert(false);
    }
    catch (FilmRepoException){
        assert(true);
    }
    s.addFilm("d", "b", 1900, "a");
    s.addFilm("e", "b", 1900, "a");
    s.addFilm("f", "b", 1900, "a");
    s.addFilm("g", "b", 1900, "a");
    s.addFilm("h", "b", 1900, "a");
    s.addFilm("i", "b", 1900, "a");
    s.addFilm("j", "b", 1900, "a");
    s.addFilm("k", "b", 1900, "a");
    s.addFilm("l", "b", 1900, "a");
}


void testFindSrv(){
    FilmRepo repo;
    Validator val;
    FilmService srv {repo, val};
    srv.addFilm("a", "b", 1990, "c");
    srv.addFilm("b", "b", 1990, "c");

    auto f = srv.find("a");
    assert(f.getTitlu() == "a");
    assert(f.getGen() == "b");

    try{
        srv.find("c");assert(false);
    }
    catch(FilmRepoException&){
        assert(true);
    }
}

void testModSrv() {
    FilmRepo repo;
    Validator val;
    FilmService srv{repo, val};
    srv.addFilm("a", "b", 1990, "c");
    srv.addFilm("b", "b", 1990, "c");

    srv.modFilm("b", "x", 2000, "y");
    assert(srv.getAll().get(1).getGen() == "x");
    assert(srv.getAll().get(1).getAn() == 2000);
    assert(srv.getAll().get(1).getActor() == "y");

}

void testDeleteSrv(){
    FilmRepo repo;
    Validator val;
    FilmService srv{repo, val};
    srv.addFilm("a", "b", 1990, "c");
    srv.addFilm("b", "b", 1990, "c");
    srv.deleteFilm("a");
    assert(srv.getAll().size()==1);
    assert(srv.getAll().get(0).getTitlu()=="b");
}

void testFiltrare(){
    FilmRepo repo;
    Validator val;
    FilmService srv{repo, val};
    srv.addFilm("a", "a", 2000, "a");
    srv.addFilm("b", "a", 2000, "a");
    srv.addFilm("c", "a", 1990, "a");
    assert(srv.filtrareTitlu("a").size()==1);
    assert(srv.filtrareTitlu("b").size()==1);
    assert(srv.filtrareAn(2000).size()==2);
    assert(srv.filtrareAn(1990).size()==1);
}

void testSort(){
    FilmRepo repo;
    Validator val;
    FilmService srv{repo, val};
    srv.addFilm("a", "a", 2000, "a");
    srv.addFilm("b", "c", 2000, "x");
    srv.addFilm("c", "g", 1990, "b");
    assert(srv.sortByTitlu().get(0).getTitlu() == "a");
    assert(srv.sortByActor().get(0).getActor() == "a");
    assert(srv.sortByAn(srv.sortByGen()).get(0).getAn() == 1990);
}

void testSrv(){
    testAddSrv();
    testFindSrv();
    testModSrv();
    testFiltrare();
    testSort();
    testDeleteSrv();
}