#include "jugador.h"

Jugador::Jugador(std::string nombre, int fichasIniciales)
    : nombre(nombre), fichas(fichasIniciales) {}

bool Jugador::tieneSaldoSuficiente(int monto) const {
    return fichas >= monto;
}

bool Jugador::apostar(int monto, int indiceMano) {
    if (monto < 10 || monto > 500) {
        return false;
    }

    if (indiceMano < 0 || indiceMano >= static_cast<int>(manos.size())) {
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
