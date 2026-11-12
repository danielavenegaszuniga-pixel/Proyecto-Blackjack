#include "jugador.h"
#include <cmath>

Jugador::Jugador(std::string nombre, int fichasIniciales)
    : nombre(nombre), fichas(fichasIniciales) {}

bool Jugador::tieneSaldoSuficiente(double monto) const {
    return fichas >= monto;
}

bool Jugador::apostar(double monto, int indiceMano) {
    if (monto > 0 && tieneSaldoSuficiente(monto)) {
        fichas -= static_cast<int>(monto);
        if (indiceMano < static_cast<int>(manos.size())) {
            manos[indiceMano].setApuesta(monto);
        }
        return true;
    }
    return false;
}

void Jugador::recibirFichas(double monto) {
    fichas += static_cast<int>(std::floor(monto)); // Aplica redondeo hacia abajo si aplica
}

void Jugador::agregarMano(Mano mano) {
    manos.push_back(mano);
}

std::string Jugador::getNombre() const { return nombre; }
int Jugador::getFichas() const { return fichas; }
std::vector<Mano>& Jugador::getManos() { return manos; }

void Jugador::limpiarManos() {
    manos.clear();
}