#include <iostream>
#include "FilmRepo.h"
#include "Validator.h"
#include "FilmService.h"
#include "UI.h"

void testAll(){
    testeRepo();
    testValidator();
    testSrv();
}
void start(){
    FilmRepo repo;
    Validator val;
    FilmService srv{repo, val};
    UI ui{srv};
    ui.generate();
    ui.run();
}

int main() {
    testAll();
//    start();
}
