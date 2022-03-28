//
// Created by ovi on 3/28/22.
//

#include "FilmService.h"
#include <assert.h>


void FilmService::addFilm(const string& titlu, string gen, int an, string actor){
    /*
     * Adauga un nou film
     * arunca exceptie daca: exista deja titlul, nu este valid
     */
    Film f{titlu, gen, an, actor};
    val.validate(f);
    repo.store(f);
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
        s.addFilm("", "", 0, "");
        assert(false);
    }
    catch(ValidateException&){
        assert(true);
    }

    try{
        s.addFilm("a", "a", 1900, "a");
        assert(false);
    }
    catch (FilmRepoException){
        assert(true);
    }


}

void testSrv(){
    testAddSrv();
}