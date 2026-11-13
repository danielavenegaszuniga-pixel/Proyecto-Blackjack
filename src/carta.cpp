#include "carta.h"

Carta::Carta(std::string palo, std::string valor, int valorNumerico)
    : palo(palo), valor(valor), valorNumerico(valorNumerico) {}

// Devuelve el valor numérico de la carta
int Carta::obtenerValor() const {
    return valorNumerico;
}

//Devuelve el palo de la carta
std::string Carta::obtenerPalo() const {
    return palo;
}

std::string Carta::obtenerDescripcion() const {
    return valor + " de " + palo;
}
