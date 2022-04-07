//
// Created by ovi on 3/28/22.
//

#include "FilmRepo.h"
#include <assert.h>

void FilmRepo::store(const Film &film) {
    if(exist(film)){
        throw FilmRepoException("Exista deja filmul: " + film.getTitlu());
    }
    all.add(film);
}

void FilmRepo::deleteFilm(string titlu){
    all.deleteFilm(titlu);
}

bool FilmRepo::exist(const Film &film) const {
    /*
     * Verifica daca exista filmul in lista
     */
    try{
        find(film.getTitlu());
        return true;
    }
    catch(FilmRepoException& ){
        return false;
    }
}

const Film& FilmRepo::find(string titlu) const{
    /*
     * Cauta filmul cu titlul dat
     * arunca exceptie daca nu exista
     */
    IteratorVectorT<Film> it = IteratorVectorT<Film>(all, 0);
    while(it.valid()){
        if(it.element().getTitlu() == titlu){
            return it.element();
        }
        it.next();
    }

    throw FilmRepoException("Nu exista filmul: " + titlu);
}

const MyVector<Film>& FilmRepo::getAll()const noexcept{
    /*
     * Returneaza toate filmele
     */
    return all;
}

ostream& operator<<(ostream& out, const FilmRepoException& ex){out<< ex.msg;return out;}

void testAddRepo(){
    /*
     * Testeaza adaugarea unui film
     */
    FilmRepo repo;
    repo.store(Film{"Madagascar", "comedie", 2005, "Leul Alex"});
    assert(repo.getAll().size() == 1);
    assert(repo.find("Madagascar").getTitlu() == "Madagascar");
    assert(repo.find("Madagascar").getGen() == "comedie");
    assert(repo.find("Madagascar").getAn() == 2005);
    assert(repo.find("Madagascar").getActor() == "Leul Alex");

    repo.store(Film{"a", "b", 1990, "c"});
    assert(repo.getAll().size() == 2);

    try{
        repo.store(Film{"a", "b", 2000, "d"});assert(false);
    }
    catch (const FilmRepoException&){
        assert(true);
    }
}

void testCautaRepo(){
    /*
     * Testeaza cautarea unui film
     */

    FilmRepo repo;
    repo.store(Film{"a", "b", 1990, "c"});
    repo.store(Film{"b", "b", 1990, "c"});

    auto f = repo.find("a");
    assert(f.getTitlu() == "a");
    assert(f.getGen() == "b");

    try{
        repo.find("c");assert(false);
    }
    catch(FilmRepoException&){
        assert(true);
    }
}


void testExist(){
    FilmRepo repo;
    repo.store(Film{"a", "b", 1990, "c"});
    repo.store(Film{"b", "b", 1990, "c"});
    auto f = Film{"a", "b", 1990, "c"};
    assert(repo.exist(f) == true);
    f = Film{"b", "b", 1990, "c"};
    assert(repo.exist(f) == true);
    f=Film{"c", "b", 1990, "c"};
    assert(repo.exist(f) == false);
}

void testGetAllRepo(){
    FilmRepo repo;
    auto f = Film{"a", "b", 1990, "c"};
    repo.store(f);
    assert(repo.getAll().size() == 1);
}
void testeRepo(){
    testAddRepo();
    testCautaRepo();
    testExist();
    testGetAllRepo();
}