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

        srv.deleteFilm(titlu);
        reloadFilme(srv.getAll());
        QMessageBox::information(this, "Info", QString::fromStdString("Film sters cu succes"));
    }catch (const FilmRepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::filterUI() {
    string titlu;
    string an_str;
    int cmd;
    cout<<"1.Filtrare titlu\n2.Filtrare anul aparitiei\n";
    cin>>cmd;
    if(cmd==1){
        cout<<"Tiltu: \n";
        cin>>titlu;
        tipareste(srv.filtrareTitlu(titlu));
    }else if(cmd==2){
        cout<<"Anul aparitiei: \n";
        cin>>an_str;
        try{
            int an = stoi(an_str);
            tipareste(srv.filtrareAn(an));
        }catch(...){
            cout<<"An invalid\n";
        }
    }
}

void GUI::sortUI() {
    int cmd;
    cout<<"Sortare dupa:\n1.Titlu\n2.Actor principal\n3.Anul aparitiei + gen\n";
    cin>>cmd;
    if(cmd == 1){
        tipareste(srv.sortByTitlu());
    }else if(cmd == 2){
        tipareste(srv.sortByActor());
    }else if(cmd == 3){
        tipareste(srv.sortByAn(srv.sortByGen()));
    }
}

void GUI::cosUI() {
    int cmd;
    cout<<"1.Adaugare in cos\n2.Goleste cos\n3.Genereaza cos\n4.Export cos\n5.Afiseaza cos\n";
    cin>>cmd;
    if(cmd == 1){
        string titlu;
        cout<<"Tiltu: \n";
        cin>>titlu;

        srv.addCos(titlu);
    }else if(cmd == 2){
        srv.golesteCos();
        cout<<"Cos golit \n";
    }else if(cmd == 3){
        int nrFilme;
        cout<<"Numarul de filme: ";
        cin>>nrFilme;
        srv.generateCos(nrFilme);

        tipareste(srv.allCos());
    }else if(cmd == 4){
        string fisier;
        cout<<"Nume fisier CVS sau HTML: ";
        cin>>fisier;
        ofstream file(fisier);
        for(auto& film : srv.allCos()){
            string out = film.getTitlu() + ", " + film.getGen() + ", " + to_string(film.getAn()) + ", " + film.getActor()+ '\n';
            file<<out;
        }

        file.close();
    }else if(cmd == 5){
        tipareste(srv.allCos());
    }
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
}


void GUI::initialize() {
    //main layout
    QHBoxLayout *lyMain = new QHBoxLayout();
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
    QFormLayout* lyBSt = new QFormLayout;
    butoaneSt->setLayout(lyBSt);

    QWidget* butoaneDr = new QWidget;
    QFormLayout* lyBDr = new QFormLayout;
    butoaneDr->setLayout(lyBDr);

    lyBSt->addWidget(btnAdd);
    lyBSt->addWidget(btnFind);
    lyBSt->addWidget(btnMod);
    lyBDr->addWidget(btnDelete);
    lyBDr->addWidget(btnUndo);

    lyButoane->addWidget(butoaneSt);
    lyButoane->addWidget(butoaneDr);
    lyForm->addWidget(butoane);
    lyLeft->addWidget(form);

    //partea dreapta
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    int nLines = 10;
    int nColumns = 4;
    tableFilme = new QTableWidget{nLines, nColumns};

    //header tabel
    QStringList tbHeaderList;
    tbHeaderList << "Titlu"<<"Gen"<<"An"<<"Actor principal";
    this->tableFilme->setHorizontalHeaderLabels(tbHeaderList);
    this->tableFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    lyRight->addWidget(tableFilme);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void GUI::connectSignalsSlots(){
    QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::addUI);
    QObject::connect(btnFind, &QPushButton::clicked, this, &GUI::findUI);
    QObject::connect(btnMod, &QPushButton::clicked, this, &GUI::modUI);
    QObject::connect(btnDelete, &QPushButton::clicked, this, &GUI::deleteUI);
    QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::undoUI);
}