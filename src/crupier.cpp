#include "crupier.h"

Crupier::Crupier() : tieneSeguroActivo(false) {}

void Crupier::recibirCarta(Carta c) { mano.agregarCarta(c); }
void Crupier::revelarCartaOculta() {}

bool Crupier::debePedirCarta() const {
    return mano.calcularPuntaje() < 17;
}

void Crupier::jugarTurno(Zapato& zapato) { // metodo para jugar su turno
    while (debePedirCarta()) {
        mano.agregarCarta(zapato.repartirCarta());
    }
}

Mano& Crupier::getMano() { return mano; }
bool Crupier::getTieneSeguroActivo() const { return tieneSeguroActivo; }
void Crupier::setTieneSeguroActivo(bool seguro) { tieneSeguroActivo = seguro; }
