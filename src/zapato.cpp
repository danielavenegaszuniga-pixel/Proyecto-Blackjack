#include "zapato.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

Zapato::Zapato() : indiceActual(0) {
    std::string palos[] = { "Corazones", "Diamantes", "Picas", "Tréboles" };
    std::string valores[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

    // Crear 6 mazos completos (312 cartas)
    for (int mazo = 0; mazo < 6; ++mazo) {
        for (const auto& palo : palos) {
            for (const auto& valor : valores) {
                int valNum = 0;
                if (valor == "J" || valor == "Q" || valor == "K") {
                    valNum = 10;
                }
                else if (valor == "A") {
                    valNum = 1; // El valor base del As es 1, se gestiona dinámicamente en Mano
                }
                else {
                    valNum = std::stoi(valor);
                }
                cartas.push_back(Carta(palo, valor, valNum));
            }
        }
    }
}

void Zapato::barajar() {
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(cartas.begin(), cartas.end(), std::default_random_engine(seed)); //Utiliza std::shuffle para mezclar las cartas y reinicia el índice.
    indiceActual = 0;
}

Carta Zapato::repartirCarta() {
    if (estaVacio()) {
        throw std::runtime_error("El zapato no tiene mas cartas.");
    }
    return cartas[indiceActual++];
}

int Zapato::cartasRestantes() const {
    return static_cast<int>(cartas.size()) - indiceActual;
}

bool Zapato::estaVacio() const {
    return indiceActual >= static_cast<int>(cartas.size());
}
