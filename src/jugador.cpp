#include "jugador.h"
#include "constantes.h"

Jugador::Jugador(std::string nombre, int fichasIniciales)
    : nombre(nombre), fichas(fichasIniciales) {}

bool Jugador::tieneSaldoSuficiente(int monto) const {
    return monto > 0 && fichas >= monto;
}

bool Jugador::apostar(int monto, int indiceMano) {
    if (monto < Constantes::APUESTA_MINIMA ||
        monto > Constantes::APUESTA_MAXIMA) {
        return false;
    }

    if (indiceMano < 0 ||
        indiceMano >= static_cast<int>(manos.size())) {
        return false;
    }

    if (!tieneSaldoSuficiente(monto)) {
        return false;
    }

    fichas -= monto;
    manos[indiceMano].setApuesta(monto);

    return true;
}

void Jugador::recibirFichas(int monto) {
    if (monto > 0) {
        fichas += monto;
    }
}

bool Jugador::retirarFichas(int monto) {
    if (!tieneSaldoSuficiente(monto)) {
        return false;
    }

    fichas -= monto;
    return true;
}

void Jugador::agregarMano(Mano mano) {
    manos.push_back(mano);
}

std::string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getFichas() const {
    return fichas;
}

std::vector<Mano>& Jugador::getManos() {
    return manos;
}

void Jugador::limpiarManos() {
    manos.clear();
}
