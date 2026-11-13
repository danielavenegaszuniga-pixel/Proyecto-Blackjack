#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "zapato.h"
#include "jugador.h"
#include "crupier.h"

class Juego {
private:
    Zapato zapato;
    std::vector<Jugador> jugadores;
    Crupier crupier;

    std::vector<int> segurosPorJugador;

    void registrarJugadores();
    bool todosPuedenContinuar() const;

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
