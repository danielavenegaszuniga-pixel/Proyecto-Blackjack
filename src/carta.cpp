#include "carta.h"

Carta::Carta(std::string p, std::string v, int vn) : palo(p), valor(v), valorNumerico(vn) {}

int Carta::obtenerValor() const { return valorNumerico; }
std::string Carta::obtenerPalo() const { return palo; }
std::string Carta::obtenerDescripcion() const { return valor + " de " + palo; }
