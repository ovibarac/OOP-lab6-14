//
// Created by ovi on 3/28/22.
//

#include "Validator.h"
#include "assert.h"
#include <sstream>

void Validator::validate(const Film &film) {
    vector<string> msgs;

    if(film.getTitlu().size() == 0) msgs.push_back("Titlu vid!");
    if(film.getGen().size() == 0) msgs.push_back("Gen vid!");
    if(film.getAn() < 1800) msgs.push_back("An prea mic!");
    if(film.getActor().size() == 0) msgs.push_back("Actor principal vid!");
    if(msgs.size() > 0){
        throw ValidateException(msgs);
    }
}

ostream& operator<<(ostream& out, const ValidateException& ex){
    for(const auto& msg: ex.msgs){
        out<<msg<<" ";
    }
    return out;
}

void testValidator(){
    /*
     * Testeaza validarea
     */
    Validator val;
    Film f{"", "", 0, ""};

    try{
        val.validate(f);
    }
    catch(const ValidateException& ex){
        stringstream sout;
        sout<<ex;
        auto mesaj = sout.str();
        assert(mesaj.find("mic") >=0 );
        assert(mesaj.find("vid") >= 0);
    }
}
