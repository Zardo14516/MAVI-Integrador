#include "enemigo.h"
#include <stdlib.h>

using namespace sf;

enemigo::enemigo(Vector2f posicion) {
    txt_enemigo1.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/enemigo1.jpg");
    spr_enemigo1.setTexture(txt_enemigo1);
    spr_enemigo1.setPosition(posicion);

    
    spr_enemigo1.setScale(175.f / spr_enemigo1.getLocalBounds().width, 175.f / spr_enemigo1.getLocalBounds().height);
}

Sprite enemigo::get_sprite() {
    return spr_enemigo1;
}

float enemigo::get_seconds() {
    tiempo1 = reloj1.getElapsedTime();
    return tiempo1.asSeconds();
}