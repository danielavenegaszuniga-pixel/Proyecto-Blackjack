#ifndef ZAPATO_H
#define ZAPATO_H

#include <vector>
#include "carta.h"

class Zapato {
private:
    std::vector<Carta> cartas; // Almacena las 312 cartas (6 mazos)
    int indiceActual;

public:
    Zapato();
    void barajar();
    Carta repartirCarta();
    int cartasRestantes() const;
    bool estaVacio() const;
};

#endif
