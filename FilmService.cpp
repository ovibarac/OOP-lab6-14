//
// Created by ovi on 3/28/22.
//

#include "FilmService.h"
#include <assert.h>
#include <random>
#include <vector>
#include <algorithm>


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

vector<Film> FilmService::filtreaza(function<bool(const Film&)> fct){
    /*
     * Filtreaza dupa un criteriu
     * fct: functia relatie
     */
    vector<Film> rez;
    for(auto& f : repo.getAll()){
        if(fct(f)){
            rez.push_back(f);
        }
    }
    return rez;
}

vector<Film> FilmService::filtrareTitlu(string titlu) {
    /*
     * Filtrare dupa titlu
     */
//    return filtreaza([titlu](const Film& f){
//        return f.getTitlu() == titlu;
//    });
    vector<Film> rez;
    copy_if(getAll().begin(), getAll().end(), back_inserter(rez), [titlu](const Film& f){
        return f.getTitlu() == titlu;
    });
    return rez;
}

vector<Film> FilmService::filtrareAn(int an) {
    /*
     * Filtrare dupa an aparitie
     */
    return filtreaza([an](const Film& f){
        return f.getAn() == an;
    });
}

bool cmpTitlu(const Film& f1, const Film& f2){return f1.getTitlu() > f2.getTitlu();}

vector<Film> FilmService::sortByTitlu(){
    /*
     * Sorteaza dupa titlu
     */
    vector<Film> rez = getAll();
    generalSort(rez, [](const Film& f1, const Film& f2){
        return f1.getTitlu() < f2.getTitlu();
    });
    return rez;
}

vector<Film> FilmService::sortByActor(){
    /*
     * Sorteaza dupa actor
     */
    vector<Film> rez = getAll();
    generalSort(rez, [](const Film& f1, const Film& f2){
        return f1.getActor() < f2.getActor();
    });
    return rez;
}

vector<Film> FilmService::sortByGen(){
    /*
     * Sorteaza dupa actor
     */
    vector<Film> rez = getAll();
    generalSort(rez, [](const Film& f1, const Film& f2){
        return f1.getGen() > f2.getGen();
    });
    return rez;
}

vector<Film> FilmService::sortByAn(vector<Film> rez){
    /*
     * Sorteaza dupa actor
     */

    generalSort(rez, [](const Film& f1, const Film& f2){
        return f1.getAn() < f2.getAn();
    });
    return rez;
}

void FilmService::addCos(string titlu){
    auto f = repo.find(titlu);
    cos.add(f);
}

void FilmService::golesteCos() {
    cos.goleste();
}

void FilmService::generateCos(int nrFilme) {
    mt19937 mt{random_device{}()};
    uniform_int_distribution<> dist(0, getAll().size()-1);

    for(int i = 0; i< nrFilme; i++){
        int random = dist(mt);
        auto f = getAll()[random];
        cos.add(f);
    }
}

bool FilmService::anyOfGen(string gen){
    return any_of(getAll().begin(), getAll().end(), [gen](const Film& f){return f.getGen()==gen;});
}


void testAddSrv(){
    /*
     * Testeaza adaugarea service
     */
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService s {repo, val, cos};
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
    Cos cos;
    FilmService srv {repo, val, cos};
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
    Cos cos;
    FilmService srv{repo, val, cos};
    srv.addFilm("a", "b", 1990, "c");
    srv.addFilm("b", "b", 1990, "c");

    srv.modFilm("b", "x", 2000, "y");
    assert(srv.getAll()[1].getGen() == "x");
    assert(srv.getAll()[1].getAn() == 2000);
    assert(srv.getAll()[1].getActor() == "y");

}

void testDeleteSrv(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    srv.addFilm("a", "b", 1990, "c");
    srv.addFilm("b", "b", 1990, "c");
    srv.deleteFilm("a");
    assert(srv.getAll().size()==1);
    assert(srv.getAll()[0].getTitlu()=="b");
}

void testFiltrare(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
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
    Cos cos;
    FilmService srv{repo, val, cos};
    srv.addFilm("a", "a", 2000, "a");
    srv.addFilm("b", "c", 2000, "x");
    srv.addFilm("c", "g", 1990, "b");
    assert(srv.sortByTitlu()[0].getTitlu() == "a");
    assert(srv.sortByActor()[0].getActor() == "a");
    assert(srv.sortByAn(srv.sortByGen())[0].getAn() == 1990);
}

void testCos(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    srv.addFilm("a", "a", 2000, "a");
    srv.addFilm("b", "c", 2000, "x");
    srv.addFilm("c", "g", 1990, "b");

    assert(srv.cosSize() == 0);
    srv.addCos("a");
    assert(srv.cosSize() == 1);
    srv.addCos("b");
    assert(srv.cosSize() == 2);
    srv.addCos("c");
    assert(srv.cosSize() == 3);
    assert(srv.allCos()[0].getTitlu() == "a");

    try{
        srv.addCos("d");
        assert(false);
    }catch (FilmRepoException){
        assert(true);
    }

    srv.golesteCos();
    assert(srv.cosSize() == 0);

    srv.generateCos(5);
    assert(srv.cosSize() == 5);
}

void testAnyOf(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    srv.addFilm("a", "a", 2000, "a");
    srv.addFilm("b", "c", 2000, "x");
    srv.addFilm("c", "g", 1990, "b");

    assert(srv.anyOfGen("a") == true);
    assert(srv.anyOfGen("d") == false);

}

void testSrv(){
    testAddSrv();
    testFindSrv();
    testModSrv();
    testFiltrare();
    testSort();
    testDeleteSrv();
    testCos();
    testAnyOf();
}