//
// Created by ovi on 6/2/22.
//

#include "CosGUI.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::cin;

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>

void CosCRUDGUI::reloadCos(vector<Film> filme) {
    //reincarca tabelul
//    this->tableCos->clearContents();
//    this->tableCos->setRowCount(filme.size());
//
//    int lineNumber = 0;
//    for(auto& f : filme){
//        this->tableCos->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(f.getTitlu())));
//        this->tableCos->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(f.getGen())));
//        this->tableCos->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(f.getAn())));
//        this->tableCos->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(f.getActor())));
//        lineNumber++;
//    }
//
    this->qlistCos->clear();
    for(auto& f : filme){
        string linie = f.getTitlu() + " " + f.getGen() + " " + to_string(f.getAn()) + " " + f.getActor();
        qlistCos->addItem(QString::fromStdString(linie));
    }
}

void CosCRUDGUI::initialize() {
    lyMainCos = new QHBoxLayout;
    this->setLayout(lyMainCos);
    btnAddCos = new QPushButton("Adauga");
    btnEmptyCos = new QPushButton("Goleste cos");
    btnGenCos = new QPushButton("Genereaza cos");
    btnExportCos = new QPushButton("Export cos");

    //stanga
    QWidget* drCos = new QWidget;
    QVBoxLayout* lyDrCos = new QVBoxLayout;
    drCos->setLayout(lyDrCos);
    qlistCos = new QListWidget();
    lyDrCos->addWidget(qlistCos);

    //dreapta
    QWidget* stCos = new QWidget;
    QVBoxLayout* lyStCos = new QVBoxLayout;
    stCos->setLayout(lyStCos);

    editTitluCos = new QLineEdit;
    QHBoxLayout* lyAddCos = new QHBoxLayout;
    QWidget* liniaAddCos = new QWidget;
    liniaAddCos->setLayout(lyAddCos);
    lyAddCos->addWidget(editTitluCos);
    lyAddCos->addWidget(btnAddCos);

    editGenerate = new QLineEdit;
    QHBoxLayout* lyGenCos = new QHBoxLayout;
    QWidget* liniaGenCos = new QWidget;
    liniaGenCos->setLayout(lyGenCos);
    lyGenCos->addWidget(editGenerate);
    lyGenCos->addWidget(btnGenCos);

    editExport = new QLineEdit;
    QHBoxLayout* lyExCos = new QHBoxLayout;
    QWidget* liniaExCos = new QWidget;
    liniaExCos->setLayout(lyExCos);
    lyExCos->addWidget(editExport);
    lyExCos->addWidget(btnExportCos);

    lyStCos->addWidget(liniaAddCos);
    lyStCos->addWidget(btnEmptyCos);
    lyStCos->addWidget(liniaGenCos);
    lyStCos->addWidget(liniaExCos);

    //main layout (is invers)
    lyMainCos->addWidget(drCos);
    lyMainCos->addWidget(stCos);

    srv.addObserver(this);
}

void CosCRUDGUI::connectSignalsSlots() {
    QObject::connect(btnAddCos, &QPushButton::clicked, [&](){
        string text = editTitluCos->text().toStdString();
        srv.addCos(text);
        reloadCos(srv.allCos());
    });

    QObject::connect(btnEmptyCos, &QPushButton::clicked, [&](){
        srv.golesteCos();
        reloadCos(srv.allCos());
    });

    QObject::connect(btnGenCos, &QPushButton::clicked, [&](){
        int nr = editGenerate->text().toInt();
        srv.generateCos(nr);
        reloadCos(srv.allCos());
    });

    QObject::connect(btnExportCos, &QPushButton::clicked, [&](){
        string fisier = editExport->text().toStdString();
        ofstream file(fisier);
        for(auto& film : srv.allCos()){
            string out = film.getTitlu() + ", " + film.getGen() + ", " + to_string(film.getAn()) + ", " + film.getActor()+ '\n';
            file<<out;
        }
        QMessageBox::information(this, "Info", QString::fromStdString("Export successful"));

        file.close();
    });
}