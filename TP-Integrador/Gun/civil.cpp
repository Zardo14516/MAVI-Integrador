#include "civil.h"
#include <cstdlib>
#include <ctime>

using namespace sf;

civil::civil(Vector2f posicion) : tiempo_aparicion(0), visible(false) {
    
    if (!txt_civil.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/civil1.jpg")) {
        
    }
    spr_civil.setTexture(txt_civil);
    spr_civil.setPosition(posicion);
    srand(static_cast<unsigned int>(time(nullptr)));  
}

Sprite civil::get_sprite() {
    return spr_civil;
}

bool civil::esta_visible() const {
    return visible;
}

void civil::actualizar(float tiempo_transcurrido) {
    if (reloj_aparicion.getElapsedTime().asSeconds() >= 10 + tiempo_aparicion) {
       
        visible = true;
        spr_civil.setPosition(Vector2f(rand() % 1000, rand() % 600)); 

        
        reloj_visibilidad.restart();
        tiempo_aparicion = reloj_aparicion.getElapsedTime().asSeconds();
    }

    if (visible && reloj_visibilidad.getElapsedTime().asSeconds() >= 6) {
       
        visible = false;
    }
}

bool civil::clic_en_civil(const FloatRect& recta) {
    if (visible && spr_civil.getGlobalBounds().intersects(recta)) {
        visible = false; 
        return true; 
    }
    return false;
}