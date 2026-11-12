#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
private:
    std::string palo;         // Corazones, Diamantes, Picas, Tréboles
    std::string valor;        // 2-10, J, Q, K, A
    int valorNumerico;        // 2-10, 10 para J,Q,K, y 1 u 11 para A

public:
    Carta(std::string palo, std::string valor, int valorNumerico);

    int obtenerValor() const;
    std::string obtenerPalo() const;
    std::string obtenerDescripcion() const;
};

#endif
