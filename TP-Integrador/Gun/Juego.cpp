#include "Juego.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace sf;

juego::juego(Vector2f resolucion, String titulo)
    : ventana(VideoMode(resolucion.x, resolucion.y), titulo),
    fps(60), game_over(false), tiempo2(0),
    enemigos_eliminados(0), en_menu(true) {
    ventana.setFramerateLimit(fps);
    ventana.setMouseCursorVisible(false);

    for (int i = 0; i < 4; i++) {
        slots_enemigos[i] = false;
    }

    cargar_graficos();
    procesar_eventos_menu();
}

void juego::procesar_eventos_menu() {
    while (en_menu) {
        while (ventana.pollEvent(evento1)) {
            if (evento1.type == Event::MouseButtonPressed) {
                en_menu = false;

                txt_fondo_menu = Texture();
                spr_fondo_menu.setTexture(txt_fondo_menu);

                gameLoop();
            }

            if (evento1.type == Event::Closed) {
                ventana.close();
                return;
            }
        }

        ventana.clear();
        ventana.draw(spr_fondo_menu);
        ventana.display();
    }
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

        
        texto_vidas.setString("Vidas: " + std::to_string(jugador1.get_vidas()));
        texto_puntuacion.setString("Puntuacion: " + std::to_string(enemigos_eliminados));

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

        ventana.draw(texto_vidas);
        ventana.draw(texto_puntuacion);
        ventana.draw(spr_mira);

        ventana.display();
    }

    
    std::ostringstream ss;
    ss << "GAME OVER! TU PUNTUACIÓN ES DE: " << enemigos_eliminados;
    texto_game_over.setString(ss.str());

    while (ventana.isOpen()) {
        while (ventana.pollEvent(evento1)) {
            if (evento1.type == Event::Closed) {
                ventana.close();
                return;
            }
        }

        ventana.clear();
        ventana.draw(spr_fondo);
        ventana.draw(texto_game_over);
        ventana.display();
    }
}

void juego::cargar_graficos() {
    txt_fondo_menu.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/fondo2.png");
    spr_fondo_menu.setTexture(txt_fondo_menu);
    spr_fondo_menu.setScale((float)ventana.getSize().x / txt_fondo_menu.getSize().x, (float)ventana.getSize().y / txt_fondo_menu.getSize().y);

    txt_fondo.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/fondo.png");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float)ventana.getSize().x / txt_fondo.getSize().x, (float)ventana.getSize().y / txt_fondo.getSize().y);

    txt_mira.loadFromFile("C:/Users/Usuario/Desktop/Lu Facultad/MAVI/TP-Integrador/Assets/crosshair.png");
    spr_mira.setTexture(txt_mira);
    spr_mira.setScale(30.f / spr_mira.getLocalBounds().width, 30.f / spr_mira.getLocalBounds().height);

    if (!fuente.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }

    texto_game_over.setFont(fuente);
    texto_game_over.setFillColor(Color::Red);
    texto_game_over.setCharacterSize(40);
    texto_game_over.setPosition(ventana.getSize().x / 2 - 200, ventana.getSize().y / 2 - 20);

    texto_vidas.setFont(fuente);
    texto_vidas.setFillColor(Color::White);
    texto_vidas.setCharacterSize(30);
    texto_vidas.setPosition(10, 10);

    texto_puntuacion.setFont(fuente);
    texto_puntuacion.setFillColor(Color::White);
    texto_puntuacion.setCharacterSize(30);
    texto_puntuacion.setPosition(10, 50);
}

void juego::procesar_eventos() {
    while (ventana.pollEvent(evento1)) {
        switch (evento1.type) {
        case Event::MouseMoved:
            spr_mira.setPosition((Vector2f)Mouse::getPosition(ventana));
            break;

        case Event::Closed:
            game_over = true;
            ventana.close();
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
    if (!civil1) {
        civil1 = std::make_unique<civil>(Vector2f(rand() % 600, 300));
    }
    else {
        civil1->actualizar(tiempo1.asSeconds());
    }
}
