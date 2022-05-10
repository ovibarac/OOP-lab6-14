//
// Created by ovi on 4/25/22.
//

#ifndef LAB6_7_UNDO_H
#define LAB6_7_UNDO_H
#include "Film.h"
#include "FilmRepo.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;

    virtual ~ActiuneUndo(){};
};

class UndoAdd : public ActiuneUndo{
private:
    Film filmAdaugat;
    FilmRepo& repo;
public:
    UndoAdd(FilmRepo& r, const Film& film): repo{r}, filmAdaugat{film}{}

    //suprascrie Undo
    void doUndo() override{
        repo.deleteFilm(filmAdaugat.getTitlu());        ////////////////////////////////////
    }
};

class UndoDelete : public ActiuneUndo{
private:
    Film filmSters;
    FilmRepo& repo;
public:
    UndoDelete(FilmRepo& r, const Film& film) : repo{r}, filmSters{film}{}

    void doUndo() override{
        repo.store(filmSters);
    }
};

class UndoMod : public ActiuneUndo{
private:
    Film filmInitial;
    Film filmModificat;
    FilmRepo& repo;
public:
    UndoMod(FilmRepo& r, const Film& fInit, const Film& fMod) : repo{r}, filmInitial{fInit}, filmModificat{fMod}{}

    void doUndo() override{
        repo.deleteFilm(filmModificat.getTitlu());
        repo.store(filmInitial);
    }
};


#endif //LAB6_7_UNDO_H
