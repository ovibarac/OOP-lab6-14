//
// Created by ovi on 5/4/22.
//

#ifndef QTLAB10_GUI_H
#define QTLAB10_GUI_H
#include "FilmService.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QHeaderView>
#include <QMessageBox>

class GUI : public QWidget{
private:
    FilmService& srv;

    QLabel* lblTitlu = new QLabel{"Titlu film:"};
    QLabel* lblGen = new QLabel{"Gen film:"};
    QLabel* lblAn = new QLabel{"An aparitie:"};
    QLabel* lblActor = new QLabel{"Actor principal:"};

    QLineEdit* editTitlu;
    QLineEdit* editGen;
    QLineEdit* editAn;
    QLineEdit* editActor;

    QPushButton* btnAdd;
    QPushButton* btnFind;
    QPushButton* btnMod;
    QPushButton* btnDelete;
    QPushButton* btnUndo;

    QTableWidget* tableFilme;
    /*
     * Citeste datele de la tastatura si adauga un film
     */
    void addUI();

    /*
     * Printeaza lista de filme
     */
    void tipareste(const vector<Film>& filme);

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

    void cosUI();

    void anyOf();

    void undoUI();

    void initialize();

    void connectSignalsSlots();

    void reloadFilme(vector<Film> filme);

public:
    GUI(FilmService& s): srv{s}{
        initialize();
        connectSignalsSlots();
        generate();
        reloadFilme(srv.getAll());
    }

    /*
     * Populeaza lista de filme
     */
    void generate();


};


#endif //QTLAB10_GUI_H
