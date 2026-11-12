#include "crupier.h"

Crupier::Crupier() : tieneSeguroActivo(false) {}

void Crupier::recibirCarta(Carta c) {
    mano.agregarCarta(c);
}

void Crupier::revelarCartaOculta() {
    // Método conceptual para la interfaz de consola
}

bool Crupier::debePedirCarta() const {
    // La casa debe pedir cartas obligatoriamente hasta sumar 17 o más
    return mano.calcularPuntaje() < 17;
}

void Crupier::jugarTurno(Zapato& zapato) {
    while (debePedirCarta()) {
        mano.agregarCarta(zapato.repartirCarta());
    }
}

Mano& Crupier::getMano() { return mano; }
bool Crupier::getTieneSeguroActivo() const { return tieneSeguroActivo; }
void Crupier::setTieneSeguroActivo(bool seguro) { tieneSeguroActivo = seguro; }