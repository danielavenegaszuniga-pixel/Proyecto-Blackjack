#include "mano.h"

Mano::Mano() : apuesta(0.0), estado("Activa"), esDoblada(false) {}

void Mano::agregarCarta(Carta c) {
    cartas.push_back(c);
}

int Mano::calcularPuntaje() const {
    int suma = 0;
    int ases = 0;

    for (const auto& c : cartas) {
        if (c.obtenerValor() == 1) { // Es un As
            ases++;
            suma += 11;
        }
        else {
            suma += c.obtenerValor();
        }
    }

    // Ajustar el valor de los Ases si la suma sobrepasa 21
    while (suma > 21 && ases > 0) {
        suma -= 10;
        ases--;
    }

    return suma;
}

bool Mano::esBlackjack() const {
    return (cartas.size() == 2 && calcularPuntaje() == 21);
}

bool Mano::esPasado() const {
    return calcularPuntaje() > 21;
}

void Mano::limpiar() {
    cartas.clear();
    apuesta = 0.0;
    estado = "Activa";
    esDoblada = false;
}

void Mano::setApuesta(double a) { apuesta = a; }
double Mano::getApuesta() const { return apuesta; }
void Mano::setEstado(std::string est) { estado = est; }
std::string Mano::getEstado() const { return estado; }
void Mano::setEsDoblada(bool doblada) { esDoblada = doblada; }
bool Mano::getEsDoblada() const { return esDoblada; }
const std::vector<Carta>& Mano::getCartas() const { return cartas; }
