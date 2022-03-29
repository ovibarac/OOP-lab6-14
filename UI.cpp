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
    cout<<"Titlul: \n";
    cin>>titlu;
    cout<<"Gen: \n";
    cin>>gen;
    cout<<"Anul aparitiei: \n";
    cin>>an;
    cout<<"Actorul principal: \n";
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

void UI::generate(){
    /*
     * Populeaza lista de filme
     */
    srv.addFilm("Hannibal", "horror", 1970, "Anthony Hopkins");
    srv.addFilm("Shrek", "comedie", 2005, "Mike Meyers");
    //srv.addFilm("Pretty woman", "romcom", 1990, "Julia Roberts");
    srv.addFilm("Twilight", "drama", 2010, "Robert Pattinson");
    //srv.addFilm("Dirty Dancing", "romcom", 1980, "Patrick Swayze");
    //srv.addFilm("Legends of the fall", "drama", 1990, "Brad Pitt");
    srv.addFilm("Madagascar", "comedie", 2005, "Leul Alex");

}

void UI::run() {
    /*
     * Ruleaza aplicatia
     */
    while(true){
        cout<<"1. Adauga\n2.Tipareste\n3.Cauta\n";
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
