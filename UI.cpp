//
// Created by ovi on 3/28/22.
//

#include "UI.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::cin;

void UI::addUI() {
    /*
    * Citeste datele de la tastatura si adauga un film
    */
    string titlu, gen, actor;
    string str_an;
    int an;
    cout<<"Titlul: \n";
    cin>>titlu;
    cout<<"Gen: \n";
    cin>>gen;
    cout<<"Anul aparitiei: \n";
    cin>>str_an;
    try{
        an=stoi(str_an);

        cout<<"Actorul principal: \n";
        cin>>actor;

        srv.addFilm(titlu, gen, an, actor);
        cout<<"Adaugat cu succes!\n";
    }
    catch (const FilmRepoException& ex){
        cout<<ex<<'\n';
    }
    catch(const ValidateException& ex){
        cout<<ex<<'\n';
    }
    catch(...){
        cout<<"An invalid\n";
    }

}

void UI::tipareste(const vector<Film> &filme) {
    /*
     * Printeaza lista de filme
     */
    cout<<"Filme: \n";
    for(auto& film : filme){
        cout<<film.getTitlu()<<", "<<film.getGen()<<", "<<film.getAn()<<", "<<film.getActor()<<'\n';
    }
    cout<<"\n";
}

void UI::findUI(){
    /*
     * Cauta un film
     */
    string titlu;
    cout<<"Titlul: ";
    cin>>titlu;

    const Film& film = srv.find(titlu);
    cout<<film.getTitlu()<<", "<<film.getGen()<<", "<<film.getAn()<<", "<<film.getActor()<<'\n';

}

void UI::modUI() {
    /*
     * Modifica un film
     */
    string titlu, new_gen, new_actor;
    string str_an;
    int new_an;
    cout<<"Titlul: ";
    cin>>titlu;

    cout<<"Noul gen: \n";
    cin>>new_gen;
    cout<<"Noul an: \n";
    cin>>str_an;
    try{
        new_an = stoi(str_an);

        cout<<"Noul actor: \n";
        cin>>new_actor;

        srv.modFilm(titlu, new_gen, new_an, new_actor);
        cout<<"Modificare efectuata cu succes\n";
    }
    catch (const FilmRepoException& ex){
        cout<<ex<<'\n';
    }
    catch(const ValidateException& ex){
        cout<<ex<<'\n';
    }
    catch(...){
        cout<<"An invalid\n";
    }

}

void UI::deleteUI() {
    string titlu;
    cout<<"Titlu: \n";
    cin>>titlu;
    srv.deleteFilm(titlu);
    tipareste(srv.getAll());
}

void UI::filterUI() {
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

void UI::sortUI() {
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

void UI::cosUI() {
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

void UI::anyOf(){
    string gen;
    cout<<"Gen: ";
    cin>>gen;
    if(srv.anyOfGen(gen)){
        cout<<"Exista filme cu genul " << gen<<'\n';
    }else{
        cout<<"Nu exista filme cu genul " << gen<<'\n';
    }
}

void UI::undoUI(){
    srv.undo();
    cout<<"Undo efectuat cu succes\n";
    tipareste(srv.getAll());
}

void UI::generate(){
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

void UI::run() {
    /*
     * Ruleaza aplicatia
     */
    while(true){
        cout<<"1.Adauga\n2.Tipareste\n3.Cauta\n4.Modifica\n5.Sterge\n6.Filtreaza\n7.Sort\n8.Cos\n9.Any of gen\n10.Undo\n0. Exit\n";
        int cmd;
        cin>>cmd;
        try{
            switch(cmd){
                case 1:
                    addUI();
                    break;
                case 2:
                    tipareste(srv.getAll());
                    break;
                case 3:
                    findUI();
                    break;
                case 4:
                    modUI();
                    break;
                case 5:
                    deleteUI();
                    break;
                case 6:
                    filterUI();
                    break;
                case 7:
                    sortUI();
                    break;
                case 8:
                    cosUI();
                    break;
                case 9:
                    anyOf();
                    break;
                case 10:
                    undoUI();
                    break;
                case 0:
                    return;
                default:
                    cout<<"Comanda invalida\n";
                    break;
            }
        }
        catch (const FilmRepoException& ex){
            cout<<ex<<'\n';
        }
        catch(const ValidateException& ex){
            cout<<ex<<'\n';
        }

        cout<<"Numarul filmelor din cos: "<<srv.cosSize()<<"\n";
    }
}
