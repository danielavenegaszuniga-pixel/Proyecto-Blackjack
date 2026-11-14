#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta {
private:
    std::string palo;
    std::string valor;
    int valorNumerico;

public:
    Carta(std::string palo, std::string valor, int valorNumerico);
    int obtenerValor() const;
    std::string obtenerPalo() const;
    std::string obtenerDescripcion() const;
};
#endif