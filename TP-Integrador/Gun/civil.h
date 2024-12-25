#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class civil {
public:
    civil(Vector2f posicion);
    Sprite get_sprite();
    bool esta_visible() const;
    void actualizar(float tiempo_transcurrido);
    bool clic_en_civil(const FloatRect& recta);

private:
    Texture txt_civil;
    Sprite spr_civil;

    Clock reloj_aparicion;
    Clock reloj_visibilidad;
    float tiempo_aparicion;
    bool visible;
};