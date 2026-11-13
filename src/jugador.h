#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "mano.h"

class Jugador {
private: //Atributos privados del jugador
    std::string nombre;
    int fichas;
    std::vector<Mano> manos;

public:
    Jugador(std::string nombre, int fichasIniciales);

    bool apostar(double monto, int indiceMano = 0);
    void recibirFichas(double monto);
    bool tieneSaldoSuficiente(double monto) const;
    void agregarMano(Mano mano);

    std::string getNombre() const;
    int getFichas() const;
    std::vector<Mano>& getManos();
    void limpiarManos();
};

#endif
