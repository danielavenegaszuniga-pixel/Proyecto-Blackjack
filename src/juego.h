#ifndef JUEGO_H
#define JUEGO_H
#include "zapato.h"
#include "jugador.h"
#include "crupier.h"

const int FICHAS_INICIALES = 1000;
const int APUESTA_MINIMA = 10;
const int APUESTA_MAXIMA = 500;

class Juego {
private:
    Zapato zapato;
    Jugador jugador;
    Crupier crupier;

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