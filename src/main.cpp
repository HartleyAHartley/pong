#include "main.h"
#include <iostream>
#include <fstream>

int main( int argc, char * argv[] ) {

    Game * pong = new Game(1);
    if(pong->InitError()) {
        return 1;
    }
    while(!pong->quit()) {
        pong->Step();
        pong->Draw();
        pong->DTime();
    }
    return 0;
}
