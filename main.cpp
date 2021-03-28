#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>

#include "draw.h"
#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{

    initSDL();
    background();
    khoiTaoBanDau();
    startGame();
    quitSDL();
return 0;
}
