//
// Created by ovi on 3/28/22.
//

#include "UI.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

void UI::addUI() {
    /*
    * Citeste datele de la tastatura si adauga un film
    */
    string titlu, gen, actor;
    int an;
    cout<<"Titlul: ";
    cin>>titlu;
    cout<<"Gen: ";
    cin>>gen;
    cout<<"Anul aparitiei: ";
    cin>>an;
    cout<<"Actorul principal: ";
    cin>>actor;

    srv.addFilm(titlu, gen, an, actor);
    cout<<"Adaugat cu succes!\n";
}

void UI::tipareste(const vector<Film> &filme) {
    /*
     * Printeaza lista de filme
     */
    cout<<"Filme: \n";
    for(const auto& film : filme){
        cout<<film.getTitlu()<<", "<<film.getGen()<<", "<<film.getAn()<<", "<<film.getActor()<<'\n';
    }
    cout<<"\n";


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
}

void UI::run() {
    /*
     * Ruleaza aplicatia
     */
    while(true){
        cout<<"1. Adauga\n2.Tipareste\n";
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
    }
}
