#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "mano.h"

class Jugador {
private:
    std::string nombre;
    int fichas;
    std::vector<Mano> manos;

public:
    Jugador(std::string nombre, int fichasIniciales);

    bool apostar(int monto, int indiceMano = 0);
    void recibirFichas(int monto);
    bool retirarFichas(int monto);
    bool tieneSaldoSuficiente(int monto) const;
    void agregarMano(Mano mano);

    std::string getNombre() const;
    int getFichas() const;
    std::vector<Mano>& getManos();
    void limpiarManos();
};

#endif
