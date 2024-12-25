#include "jugador.h"

jugador::jugador() : vidas(3) {}

void jugador::perder_vida() {
    if (vidas > 0) {
        vidas--;
    }
}

int jugador::get_vidas() {
    return vidas;
}

bool jugador::esta_vivo() {
    return vidas > 0;
}