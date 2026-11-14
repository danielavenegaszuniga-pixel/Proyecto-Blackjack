#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta {
private: // Atributos privados de carta
    std::string palo;
    std::string valor;
    int valorNumerico;

public: // Atributos publicos de carta
    Carta(std::string palo, std::string valor, int valorNumerico);
    int obtenerValor() const;
    std::string obtenerPalo() const;
    std::string obtenerDescripcion() const;
};
#endif
