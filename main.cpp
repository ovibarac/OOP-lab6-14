#include <iostream>
#include "FilmRepo.h"
#include "Validator.h"
#include "FilmService.h"
#include "UI.h"
#include "Cos.h"

void testAll(){
    testeRepo();
    testValidator();
    testSrv();
}
void start(){
    FilmRepo repo;
    Validator val;
    Cos cos;
    FilmService srv{repo, val, cos};
    UI ui{srv};
    ui.generate();
    ui.run();
}

int main() {
    testAll();
    start();
}
