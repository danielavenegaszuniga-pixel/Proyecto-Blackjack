#include "jugador.h"

Jugador::Jugador(std::string n, int fi) : nombre(n), fichas(fi) {}

bool Jugador::apostar(int cantidad, int indiceMano) {
    if (fichas >= cantidad) {
        fichas -= cantidad;
        manos[indiceMano].setApuesta(cantidad);
        return true;
    }
    return false;
}

void Jugador::recibirFichas(int monto) { fichas += monto; }
bool Jugador::tieneSaldoSuficiente(int monto) const { return fichas >= monto; }
void Jugador::agregarMano(Mano mano) { manos.push_back(mano); }
void Jugador::limpiarManos() { manos.clear(); }
std::string Jugador::getNombre() const { return nombre; }
int Jugador::getFichas() const { return fichas; }
std::vector<Mano>& Jugador::getManos() { return manos; }