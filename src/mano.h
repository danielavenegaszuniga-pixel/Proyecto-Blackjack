#ifndef MANO_H
#define MANO_H
#include <vector>
#include <string>
#include "carta.h"

class Mano {
private:
    std::vector<Carta> cartas;
    int apuesta;
    std::string estado;
    bool esDoblada;

public:
    Mano();
    void agregarCarta(Carta c);
    int calcularPuntaje() const;
    bool esBlackjack() const;
    bool esPasado() const;
    void limpiar();
    void setApuesta(int a);
    int getApuesta() const;
    void setEstado(std::string est);
    std::string getEstado() const;
    void setEsDoblada(bool doblada);
    bool getEsDoblada() const;
    const std::vector<Carta>& getCartas() const;
};
#endif