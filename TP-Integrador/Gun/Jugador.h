#pragma once

class jugador {
public:
    jugador();
    void perder_vida();
    int get_vidas();
    bool esta_vivo();

private:
    int vidas;
};