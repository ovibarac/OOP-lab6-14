//
// Created by ovi on 5/4/22.
//

#include "GUI.h"
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

void GUI::reloadFilme(vector<Film> filme){
    //reincarca tabelul
    this->tableFilme->clearContents();
    this->tableFilme->setRowCount(filme.size());

    int lineNumber = 0;
    for(auto& f : filme){
        this->tableFilme->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(f.getTitlu())));
        this->tableFilme->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(f.getGen())));
        this->tableFilme->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(f.getAn())));
        this->tableFilme->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(f.getActor())));
        lineNumber++;
    }
}

void GUI::genuriList(){
    genuri.clear();
    for(auto& f: srv.getAll()){
        bool exista = false;
        for(auto g : genuri){
            if(g == f.getGen()){
                exista = true;
            }
        }
        if(!exista){
            genuri.push_back(f.getGen());
        }
    }
}

void GUI::refreshBtns(){
    if(lyBtnDinamice != NULL){
        QLayoutItem* item;
        while((item = lyBtnDinamice->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
        }
        delete lyBtnDinamice;
    }
//    delete lyBtnDinamice;
    delete subTabelBox;
    lyBtnDinamice = new QVBoxLayout;
    subTabelBox = new QGroupBox;
    subTabelBox->setLayout(lyBtnDinamice);
    lyMain->addWidget(subTabelBox);

    for(auto g : genuri){
        QPushButton* btnGenCrt = new QPushButton(QString::fromStdString(g));
        btnDinamice.push_back(btnGenCrt);
        QObject::connect(btnGenCrt, &QPushButton::clicked, [&, g](){
            int nr = this->srv.filtrareGen(g).size();
            string nr_str = to_string(nr);
            QMessageBox::information(this, "Info", QString::fromStdString(nr_str));

        });
        lyBtnDinamice->addWidget(btnGenCrt);
    }


}

void GUI::addUI() {
    /*
    * Citeste datele de la tastatura si adauga un film
    */

    try{
        //preluare date
        string titlu = editTitlu->text().toStdString();
        string gen = editGen->text().toStdString();
        int an = editAn->text().toInt();
        string actor = editActor->text().toStdString();

        editTitlu->clear();
        editGen->clear();
        editAn->clear();
        editActor->clear();

        this->srv.addFilm(titlu, gen, an, actor);
        this->reloadFilme(srv.getAll());
        bool exista = false;
        for(auto g:genuri){
            if(g == gen){
                exista  = true;
            }
        }
        if(!exista){
            genuri.push_back(gen);
            refreshBtns();
        }
        QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat cu succes"));

    }
    catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
    catch(const ValidateException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
    catch(...){
        QMessageBox::warning(this, "Warning", QString::fromStdString("An invalid"));    }

}

void GUI::tipareste(const vector<Film> &filme) {
    /*
     * Printeaza lista de filme
     */
    cout<<"Filme: \n";
    for(auto& film : filme){
        cout<<film.getTitlu()<<", "<<film.getGen()<<", "<<film.getAn()<<", "<<film.getActor()<<'\n';
    }
    cout<<"\n";
}

void GUI::findUI(){
    /*
     * Cauta un film
     */

    //preluare date
    try{
        string titlu = editTitlu->text().toStdString();

        editTitlu->clear();
        editGen->clear();
        editAn->clear();
        editActor->clear();

        const Film& film = srv.find(titlu);

        string ftext = film.getTitlu() + ", " + film.getGen() + ", " + std::to_string(film.getAn()) + ", " + film.getActor();
        QMessageBox::information(this, "Info", QString::fromStdString(ftext));
    }catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::modUI() {
    /*
     * Modifica un film
     */

    try{
        //preluare date
        string titlu = editTitlu->text().toStdString();
        string gen = editGen->text().toStdString();
        int an = editAn->text().toInt();
        string actor = editActor->text().toStdString();

        editTitlu->clear();
        editGen->clear();
        editAn->clear();
        editActor->clear();

        this->srv.modFilm(titlu, gen, an, actor);
        this->reloadFilme(srv.getAll());
        genuriList();
        refreshBtns();
        QMessageBox::information(this, "Info", QString::fromStdString("Film modificat cu succes"));

    }
    catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
    catch(const ValidateException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
    catch(...){
        QMessageBox::warning(this, "Warning", QString::fromStdString("An invalid"));    }

}

void GUI::deleteUI() {
    //preluare date
    try{
        string titlu = editTitlu->text().toStdString();

        editTitlu->clear();
        editGen->clear();
        editAn->clear();
        editActor->clear();

        auto f = srv.find(titlu);
        string genSters = f.getGen();
        srv.deleteFilm(titlu);
        genuriList();
        refreshBtns();

        reloadFilme(srv.getAll());


        QMessageBox::information(this, "Info", QString::fromStdString("Film sters cu succes"));
    }catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::filterUI() {
    if(radioFilterTitlu->isChecked()){
        string titlu = editFilter->text().toStdString();
        reloadFilme(srv.filtrareTitlu(titlu));
    }else if(radioFilterAn->isChecked()){
        try{
            int an = editFilter->text().toInt();
            reloadFilme(srv.filtrareAn(an));
        }catch(...){
            QMessageBox::warning(this, "Warning", QString::fromStdString("An invalid"));
        }
    }
}

void GUI::sortUI() {
    if(radioSrtTitlu->isChecked()){
        reloadFilme(srv.sortByTitlu());
    }else if(radioSrtActor->isChecked()){
        reloadFilme(srv.sortByActor());
    }else if(radioSrtAnGen->isChecked()){
        reloadFilme(srv.sortByAn(srv.sortByGen()));
    }
}



void GUI::cosUI() {
    CosCRUDGUI* cos = new CosCRUDGUI(srv);
    cos->show();
    allCosCRUD.push_back(cos);
}

void GUI::anyOf(){
    string gen;
    cout<<"Gen: ";
    cin>>gen;
    if(srv.anyOfGen(gen)){
        cout<<"Exista filme cu genul " << gen<<'\n';
    }else{
        cout<<"Nu exista filme cu genul " << gen<<'\n';
    }
}

void GUI::undoUI(){
    try{
        srv.undo();
        reloadFilme(srv.getAll());
        QMessageBox::information(this, "Info", QString::fromStdString("Undo efectuat cu succes"));
    }catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::generate(){
    /*
     * Populeaza lista de filme
     */
    srv.addFilm("Hannibal", "horror", 1970, "Anthony Hopkins");
    srv.addFilm("Shrek", "comedie", 2005, "Mike Meyers");
    srv.addFilm("Pretty woman", "romcom", 1990, "Julia Roberts");
    srv.addFilm("Twilight", "drama", 2010, "Robert Pattinson");
    srv.addFilm("Dirty Dancing", "romcom", 1980, "Patrick Swayze");
    srv.addFilm("Legends of the fall", "drama", 1990, "Brad Pitt");
    srv.addFilm("Madagascar", "comedie", 2005, "Leul Alex");
    genuri.push_back("horror");
    genuri.push_back("comedie");
    genuri.push_back("romcom");
    genuri.push_back("drama");
    refreshBtns();
}


void GUI::initialize() {
    //main layout
    lyMain = new QHBoxLayout();
    this->setLayout(lyMain);

    //partea stanga
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    //componente adaugare filme
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);
    editTitlu = new QLineEdit;
    editGen = new QLineEdit;
    editAn = new QLineEdit;
    editActor = new QLineEdit;

    lyForm->addRow(lblTitlu, editTitlu);
    lyForm->addRow(lblGen, editGen);
    lyForm->addRow(lblAn, editAn);
    lyForm->addRow(lblActor, editActor);

    btnAdd = new QPushButton("Adauga");
    btnFind = new QPushButton("Cauta");
    btnMod = new QPushButton("Modifica");
    btnDelete = new QPushButton("Sterge");
    btnUndo = new QPushButton("Undo");

    QWidget* butoane = new QWidget;
    QHBoxLayout* lyButoane = new QHBoxLayout;
    butoane->setLayout(lyButoane);

    QWidget* butoaneSt = new QWidget;
    QVBoxLayout* lyBSt = new QVBoxLayout;
    butoaneSt->setLayout(lyBSt);

    QWidget* butoaneDr = new QWidget;
    QVBoxLayout* lyBDr = new QVBoxLayout;
    butoaneDr->setLayout(lyBDr);

    lyBSt->addWidget(btnAdd);
    lyBSt->addWidget(btnMod);
    lyBDr->addWidget(btnFind);
    lyBDr->addWidget(btnDelete);

    lyButoane->addWidget(butoaneSt);
    lyButoane->addWidget(butoaneDr);
    lyForm->addWidget(butoane);
    lyLeft->addWidget(form);

    QHBoxLayout* lySort = new QHBoxLayout;
    sortGroupBox->setLayout(lySort);
    lySort->addWidget(radioSrtTitlu);
    lySort->addWidget(radioSrtActor);
    lySort->addWidget(radioSrtAnGen);
    btnSort = new QPushButton("Sorteaza");
    lySort->addWidget(btnSort);
    lyLeft->addWidget(sortGroupBox);

    QHBoxLayout* lyFilter = new QHBoxLayout;
    filterGroupBox->setLayout(lyFilter);
    editFilter = new QLineEdit;
    lyFilter->addWidget(editFilter);
    lyFilter->addWidget(radioFilterTitlu);
    lyFilter->addWidget(radioFilterAn);
    btnFilter = new QPushButton("Filtreaza");
    lyFilter->addWidget(btnFilter);
    lyLeft->addWidget(filterGroupBox);

    //partea dreapta
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    //deasupra tabel
    QGroupBox* deasupraTabelBox = new QGroupBox;
    QHBoxLayout* lyDeasupraTabel = new QHBoxLayout;
    btnReload = new QPushButton("Reload");
    btnCos = new QPushButton("Cos CRUD");
    btnCosR = new QPushButton("Cos Read Only");
    deasupraTabelBox->setLayout(lyDeasupraTabel);
    lyDeasupraTabel->addWidget(btnReload);
    lyDeasupraTabel->addWidget(btnUndo);
    lyDeasupraTabel->addWidget(btnCos);
    lyDeasupraTabel->addWidget(btnCosR);

    //tabel
    int nLines = 10;
    int nColumns = 4;
    tableFilme = new QTableWidget{nLines, nColumns};

    //header tabel
    QStringList tbHeaderList;
    tbHeaderList << "Titlu"<<"Gen"<<"An"<<"Actor principal";
    this->tableFilme->setHorizontalHeaderLabels(tbHeaderList);
    this->tableFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //sub tabel

    lyBtnDinamice = new QVBoxLayout;
    subTabelBox = new QGroupBox;
    subTabelBox->setLayout(lyBtnDinamice);



    lyRight->addWidget(deasupraTabelBox);
    lyRight->addWidget(tableFilme);
    lyRight->addWidget(subTabelBox);

    //main
    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void GUI::connectSignalsSlots(){
    QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::addUI);
    QObject::connect(btnFind, &QPushButton::clicked, this, &GUI::findUI);
    QObject::connect(btnMod, &QPushButton::clicked, this, &GUI::modUI);
    QObject::connect(btnDelete, &QPushButton::clicked, this, &GUI::deleteUI);
    QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::undoUI);
    QObject::connect(btnSort, &QPushButton::clicked, this, &GUI::sortUI);
    QObject::connect(btnFilter, &QPushButton::clicked, this, &GUI::filterUI);
    QObject::connect(btnReload, &QPushButton::clicked, this,  [&](){ reloadFilme(srv.getAll());});
    QObject::connect(btnCos, &QPushButton::clicked, this,  &GUI::cosUI);
}
