//
// Created by ovi on 5/4/22.
//

#ifndef QTLAB10_GUI_H
#define QTLAB10_GUI_H
#include "FilmService.h"
#include "Observer.h"
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
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include "CosGUI.h"

class GUI : public QWidget{
private:
    FilmService& srv;

    vector<CosCRUDGUI*> allCosCRUD;
    vector<CosReadOnlyGUI*> allCosROnly;

    QHBoxLayout *lyMain;

    vector<QPushButton*> btnDinamice;
    vector<string> genuri;

    QVBoxLayout* lyBtnDinamice;
    QGroupBox* subTabelBox;

    QLabel* lblTitlu = new QLabel{"Titlu film:"};
    QLabel* lblGen = new QLabel{"Gen film:"};
    QLabel* lblAn = new QLabel{"An aparitie:"};
    QLabel* lblActor = new QLabel{"Actor principal:"};

    QLineEdit* editTitlu;
    QLineEdit* editGen;
    QLineEdit* editAn;
    QLineEdit* editActor;

    QPushButton* btnAdd;
    QPushButton* btnReload;
    QPushButton* btnFind;
    QPushButton* btnMod;
    QPushButton* btnDelete;
    QPushButton* btnUndo;
    QPushButton* btnSort;
    QPushButton* btnFilter;
    QPushButton* btnCos;
    QPushButton* btnCosR;

    QGroupBox* sortGroupBox = new QGroupBox("Sortare");
    QGroupBox* filterGroupBox = new QGroupBox("Filtrare");

    QRadioButton* radioSrtTitlu = new QRadioButton(QString::fromStdString("Titlu"));
    QRadioButton* radioSrtActor = new QRadioButton(QString::fromStdString("Actor"));
    QRadioButton* radioSrtAnGen = new QRadioButton(QString::fromStdString("An+Gen"));

    QLineEdit* editFilter;
    QRadioButton* radioFilterTitlu = new QRadioButton(QString::fromStdString("Titlu"));
    QRadioButton* radioFilterAn = new QRadioButton(QString::fromStdString("An"));

    QTableWidget* tableFilme;

    void refreshBtns();
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

    void cosRUI();

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

    void genuriList();

};

#endif //QTLAB10_GUI_H
