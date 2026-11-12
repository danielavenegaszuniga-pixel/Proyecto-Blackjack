#ifndef CRUPIER_H
#define CRUPIER_H

#include "mano.h"
#include "zapato.h"

class Crupier {
private:
    Mano mano;
    bool tieneSeguroActivo;

public:
    Crupier();

    void recibirCarta(Carta c);
    void revelarCartaOculta();
    bool debePedirCarta() const;
    void jugarTurno(Zapato& zapato);

    Mano& getMano();
    bool getTieneSeguroActivo() const;
    void setTieneSeguroActivo(bool seguro);
};

#endif