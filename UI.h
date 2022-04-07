//
// Created by ovi on 3/28/22.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H
#include "FilmService.h"
#include "Film.h"

class UI {
    FilmService& srv;

    /*
     * Citeste datele de la tastatura si adauga un film
     */
    void addUI();

    /*
     * Printeaza lista de filme
     */
    void tipareste(const MyVector<Film>& filme);

    /*
     * Cauta un film
     */
    void findUI();

    /*
     * Modifica un film
     */
    void modUI();

    /*
     * Sterge un film
     */
    void deleteUI();

    void filterUI();

    void sortUI();

public:
    UI(FilmService& s): srv{s}{}

    /*
     * Populeaza lista de filme
     */
    void generate();

    /*
     * Ruleaza aplicatia
     */
    void run();
};


#endif //LAB6_7_UI_H
