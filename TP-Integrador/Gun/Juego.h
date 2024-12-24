#pragma once
#include "SFML/Graphics.hpp"
#include "enemigo.h"
#include "jugador.h"
#include "civil.h" 
#include <memory>

using namespace sf;

class juego {
public:
    juego(Vector2f resolucion, String titulo);
    void gameLoop();
    void cargar_graficos();
    void procesar_eventos();
    void check_enemigos();
    void check_civiles();

private:
    RenderWindow ventana;

    Texture txt_fondo;
    Sprite spr_fondo;

    Texture txt_fondo_inicio;  
    Sprite spr_fondo_inicio;

    Texture txt_mira;
    Sprite spr_mira;

    Event evento1;

    std::unique_ptr<enemigo> enemigo1[4];
    std::unique_ptr<civil> civil1;

    Clock reloj;
    Time tiempo1;
    float tiempo2;

    jugador jugador1;

    bool game_over;
    bool slots_enemigos[4];
    int fps;

    int enemigos_eliminados;
    bool pantalla_inicio;  
};
