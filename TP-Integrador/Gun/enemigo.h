#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class enemigo {
public:
    enemigo(Vector2f posicion);
    Sprite get_sprite();
    float get_seconds();

private:
    Texture txt_enemigo1;
    Sprite spr_enemigo1;

    Clock reloj1; 
    Time tiempo1;
};