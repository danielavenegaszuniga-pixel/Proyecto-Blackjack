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
    bool apostar(int cantidad, int indiceMano);
    void recibirFichas(int monto);
    bool tieneSaldoSuficiente(int monto) const;
    void agregarMano(Mano mano);
    void limpiarManos();
    std::string getNombre() const;
    int getFichas() const;
    std::vector<Mano>& getManos();
};
#endif