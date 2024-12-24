#include "Juego.h"

using namespace sf;

int main(int argc, char* args[]) {
    srand(time(NULL));
    juego partida({ 1200, 700 }, "Juego Disparos");
    return 0;
}