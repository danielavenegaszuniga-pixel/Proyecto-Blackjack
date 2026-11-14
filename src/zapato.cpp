#include "zapato.h"
#include <algorithm>
#include <random>
#include <chrono>

Zapato::Zapato() : indiceActual(0) {
    std::string palos[] = { "Corazones", "Diamantes", "Picas", "Treboles" };
    std::string valores[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

    for (int m = 0; m < 6; ++m) {
        for (const auto& palo : palos) {
            int valNum = 2;
            for (const auto& val : valores) {
                int v = valNum;
                if (val == "J" || val == "Q" || val == "K") v = 10;
                else if (val == "A") v = 1;

                cartas.push_back(Carta(palo, val, v));
                valNum++;
                if (valNum > 10) valNum = 10;
            }
        }
    }
}

void Zapato::barajar() {
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(cartas.begin(), cartas.end(), std::default_random_engine(seed));
    indiceActual = 0;
}

Carta Zapato::repartirCarta() {
    return cartas[indiceActual++];
}

int Zapato::cartasRestantes() const {
    return static_cast<int>(cartas.size()) - indiceActual;
}

bool Zapato::estaVacio() const {
    return indiceActual >= cartas.size();
}