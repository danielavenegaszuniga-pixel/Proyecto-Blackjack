#ifndef JUEGO_H
#define JUEGO_H

#include "zapato.h"
#include "jugador.h"
#include "crupier.h"

class Juego {
private:
    Zapato zapato;
    Jugador jugador;
    Crupier crupier;

    static const int APUESTA_MINIMA = 10;
    static const int APUESTA_MAXIMA = 500;
    static const int FICHAS_INICIALES = 1000;

public:
    Juego();

    void iniciarPartida();
    void gestionarRonda();
    void repartirCartasIniciales();
    void ofrecerSeguro();
    void procesarAccionesJugador();
    void procesarTurnoCrupier();
    void calcularPagosYResultados();
};

#endif