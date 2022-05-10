#include <iostream>
#include "FilmRepo.h"
#include "Validator.h"
#include "FilmService.h"
#include "UI.h"
#include "Cos.h"
#include "GUI.h"

void testAll(){
    testeRepo();
    testValidator();
    testSrv();
}
void startConsole(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    UI ui{srv};
    ui.generate();
    ui.run();
}

int startGUI(int argc, char **argv){
    QApplication a(argc, argv);

    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    GUI gui{srv};

    gui.show();
    return a.exec();
}

int main(int argc, char **argv) {
    testAll();
//    startConsole();
    return startGUI(argc, argv);
}
