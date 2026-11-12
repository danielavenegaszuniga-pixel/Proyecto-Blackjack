#include "carta.h"

Carta::Carta(std::string palo, std::string valor, int valorNumerico)
    : palo(palo), valor(valor), valorNumerico(valorNumerico) {}

int Carta::obtenerValor() const {
    return valorNumerico;
}

std::string Carta::obtenerPalo() const {
    return palo;
}

std::string Carta::obtenerDescripcion() const {
    return valor + " de " + palo;
}
