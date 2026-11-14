#ifndef ZAPATO_H
#define ZAPATO_H
#include <vector>
#include "carta.h"

class Zapato {
private:
    std::vector<Carta> cartas;
    int indiceActual;

public:
    Zapato();
    void barajar();
    Carta repartirCarta();
    int cartasRestantes() const;
    bool estaVacio() const;
};
#endif