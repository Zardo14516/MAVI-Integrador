#include "Juego.h"
#include <stdlib.h>
#include <iostream>

using namespace sf;

juego::juego(Vector2f resolucion, String titulo) : ventana(VideoMode(resolucion.x, resolucion.y), titulo), fps(60), game_over(false), tiempo2(0), enemigos_eliminados(0) {
    ventana.setFramerateLimit(fps);
    ventana.setMouseCursorVisible(false);

    for (int i = 0; i < 4; i++) {
        slots_enemigos[i] = false;
    }

    cargar_graficos();

    
    civil1 = std::make_unique<civil>(Vector2f(500.0f, 300.0f)); 

    gameLoop();
}

void juego::gameLoop() {
    while (!game_over) {
        tiempo1 = reloj.getElapsedTime();

        if (tiempo1.asSeconds() > 5 + tiempo2) {
            tiempo2 = tiempo1.asSeconds();
            int resultado = rand() % 100 + 1;

            if (resultado >= 30) {
                bool espacio_disponible = false;
                for (int i = 0; i < 4; i++) {
                    if (!slots_enemigos[i]) {
                        espacio_disponible = true;
                        break;
                    }
                }

                if (espacio_disponible) {
                    while (true) {
                        int resultado = rand() % 4;
                        if (!slots_enemigos[resultado]) {
                            enemigo1[resultado] = std::make_unique<enemigo>(Vector2f(200.0f * resultado, 300.0f));
                            slots_enemigos[resultado] = true;
                            break;
                        }
                    }
                }
            }
        }

        check_enemigos();
        check_civiles(); 
        procesar_eventos();

        ventana.clear();
        ventana.draw(spr_fondo);

        for (int i = 0; i < 4; i++) {
            if (enemigo1[i]) {
                ventana.draw(enemigo1[i]->get_sprite());
            }
        }

        if (civil1 && civil1->esta_visible()) {
            ventana.draw(civil1->get_sprite()); 
        }

        ventana.draw(spr_mira);
        if (game_over) {
            Font font;
            if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
                
            }

            if (game_over) {
                std::cout << "GAME OVER! TU PUNTUACIÓN ES DE: " << enemigos_eliminados << std::endl;
            }
        }

        ventana.display();
    }
}

void juego::check_enemigos() {
    for (int i = 0; i < 4; i++) {
        if (enemigo1[i] && enemigo1[i]->get_seconds() > 5) {
            enemigo1[i] = nullptr;
            slots_enemigos[i] = false;
            jugador1.perder_vida();

            if (!jugador1.esta_vivo()) {
                game_over = true;
            }
        }
    }
}


void juego::check_civiles() {
    if (civil1) {
        civil1->actualizar(tiempo1.asSeconds());

        FloatRect recta(spr_mira.getPosition(), (Vector2f)spr_mira.getTexture()->getSize());

        if (civil1->clic_en_civil(recta)) {
            jugador1.perder_vida();  
            if (!jugador1.esta_vivo()) {
                game_over = true;
            }
        }
    }
}

void juego::cargar_graficos() {
    txt_fondo.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/fondo.png");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float)ventana.getSize().x / txt_fondo.getSize().x, (float)ventana.getSize().y / txt_fondo.getSize().y);
    
    txt_mira.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/crosshair.png");
    spr_mira.setTexture(txt_mira);
    spr_mira.setScale(30.f / spr_mira.getLocalBounds().width, 30.f / spr_mira.getLocalBounds().height);
}

void juego::procesar_eventos() {
    while (ventana.pollEvent(evento1)) {
        switch (evento1.type) {
        case Event::MouseMoved:
            spr_mira.setPosition((Vector2f)Mouse::getPosition(ventana)); 
            break;

        case Event::Closed:
            game_over = true;
            break;

        case Event::MouseButtonPressed: {
            FloatRect recta(spr_mira.getPosition(), (Vector2f)spr_mira.getTexture()->getSize());

           
            for (int i = 0; i < 4; i++) {
                if (enemigo1[i] && enemigo1[i]->get_sprite().getGlobalBounds().intersects(recta)) {
                    enemigo1[i] = nullptr;
                    slots_enemigos[i] = false;
                    enemigos_eliminados++;
                }
            }

            
            if (civil1 && civil1->clic_en_civil(recta)) {
                jugador1.perder_vida();  
                if (!jugador1.esta_vivo()) {
                    game_over = true;
                }
            }
            break;
        }
        }
    }
}