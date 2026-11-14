#include "juego.h"
#include <iostream>
#include <string>

// Inicializamos temporalmente con un nombre genérico; se pedirá en iniciarPartida
Juego::Juego() : zapato(), jugador("Jugador", FICHAS_INICIALES), crupier() {
    zapato.barajar();
}

void Juego::iniciarPartida() {
    std::cout << "=======================================\n";
    std::cout << "  SIMULADOR DE BLACKJACK EN CONSOLA \n";
    std::cout << "=======================================\n\n";

    std::string nombreIngresado;
    std::cout << "Ingrese el nombre del jugador: ";
    std::cin >> nombreIngresado;

    // Recreamos el jugador con el nombre ingresado por consola
    jugador = Jugador(nombreIngresado, FICHAS_INICIALES);
    std::cout << "n/¡Bienvenido a la mesa, " << jugador.getNombre() << "!\n";

    char opcion = 's';
    while ((opcion == 's' || opcion == 'S') && jugador.getFichas() >= APUESTA_MINIMA) {
        gestionarRonda();

        if (jugador.getFichas() < APUESTA_MINIMA) {
            std::cout << "\nNo tienes suficientes fichas para continuar jugando.\n";
            break;
        }

        std::cout << "\n¿Deseas jugar otra ronda? (s/n): ";
        std::cin >> opcion;
    }

    std::cout << "\nGracias por jugar, " << jugador.getNombre() << ". Fichas finales: " << jugador.getFichas() << "\n";
}

void Juego::gestionarRonda() {
    jugador.limpiarManos();
    crupier.getMano().limpiar();

    Mano manoInicial;
    jugador.agregarMano(manoInicial);

    std::cout << "\n---------------------------------------\n";
    std::cout << "Turno de: " << jugador.getNombre() << " | Fichas disponibles: " << jugador.getFichas() << "\n";

    int montoApuesta = 0;
    do {
        std::cout << "Ingrese su apuesta (" << APUESTA_MINIMA << " - " << APUESTA_MAXIMA << "): ";
        std::cin >> montoApuesta;
    } while (montoApuesta < APUESTA_MINIMA || montoApuesta > APUESTA_MAXIMA || !jugador.apostar(montoApuesta, 0));

    repartirCartasIniciales();
    ofrecerSeguro();

    if (!jugador.getManos()[0].esBlackjack()) {
        procesarAccionesJugador();
    }

    if (!jugador.getManos()[0].esPasado()) {
        procesarTurnoCrupier();
    }

    calcularPagosYResultados();
}

void Juego::repartirCartasIniciales() {
    jugador.getManos()[0].agregarCarta(zapato.repartirCarta());
    crupier.recibirCarta(zapato.repartirCarta());
    jugador.getManos()[0].agregarCarta(zapato.repartirCarta());
    crupier.recibirCarta(zapato.repartirCarta());

    std::cout << "\nCarta visible del Crupier: " << crupier.getMano().getCartas()[1].obtenerDescripcion() << "\n";
    std::cout << "Cartas de " << jugador.getNombre() << ":\n";
    for (const auto& c : jugador.getManos()[0].getCartas()) {
        std::cout << " - " << c.obtenerDescripcion() << "\n";
    }
    std::cout << "Puntaje actual: " << jugador.getManos()[0].calcularPuntaje() << "\n";
}

void Juego::ofrecerSeguro() {
    if (crupier.getMano().getCartas()[1].obtenerValor() == 1) {
        char resp;
        std::cout << "\nLa carta del crupier es un As. ¿Deseas comprar seguro? (s/n): ";
        std::cin >> resp;
        if (resp == 's' || resp == 'S') {
            crupier.setTieneSeguroActivo(true);
            std::cout << "Seguro activado.\n";
        }
    }
}

void Juego::procesarAccionesJugador() {
    Mano& mano = jugador.getManos()[0];
    char opcion;

    while (!mano.esPasado()) {
        std::cout << "\n¿Qué deseas hacer? (P: Pedir, S: Plantarse, D: Doblar): ";
        std::cin >> opcion;

        if (opcion == 'p' || opcion == 'P') {
            Carta nueva = zapato.repartirCarta();
            mano.agregarCarta(nueva);
            std::cout << "Recibiste: " << nueva.obtenerDescripcion() << "\n";
            std::cout << "Puntaje actual: " << mano.calcularPuntaje() << "\n";

            if (mano.esPasado()) {
                std::cout << "¡Te has pasado de 21! (Bust)\n";
                break;
            }
        }
        else if (opcion == 'd' || opcion == 'D') {
            if (jugador.tieneSaldoSuficiente(mano.getApuesta())) {
                jugador.apostar(mano.getApuesta(), 0);
                mano.setApuesta(mano.getApuesta() * 2);
                mano.setEsDoblada(true);

                Carta nueva = zapato.repartirCarta();
                mano.agregarCarta(nueva);
                std::cout << "Doblaste. Recibes solo una carta: " << nueva.obtenerDescripcion() << "\n";
                std::cout << "Puntaje final: " << mano.calcularPuntaje() << "\n";
                break;
            }
            else {
                std::cout << "No tienes fichas suficientes para doblar.\n";
            }
        }
        else if (opcion == 's' || opcion == 'S') {
            break;
        }
    }
}

void Juego::procesarTurnoCrupier() {
    std::cout << "\n--- Turno del Crupier ---\n";
    std::cout << "Mano completa del Crupier:\n";
    for (const auto& c : crupier.getMano().getCartas()) {
        std::cout << " - " << c.obtenerDescripcion() << "\n";
    }

    crupier.jugarTurno(zapato);
    std::cout << "Puntaje final del Crupier: " << crupier.getMano().calcularPuntaje() << "\n";
}

void Juego::calcularPagosYResultados() {
    Mano& mano = jugador.getManos()[0];
    int ptosJugador = mano.calcularPuntaje();
    int ptosCrupier = crupier.getMano().calcularPuntaje();
    int apuesta = mano.getApuesta();

    std::cout << "\n--- RESULTADO DE LA RONDA ---\n";

    if (mano.esBlackjack()) {
        if (crupier.getMano().esBlackjack()) {
            std::cout << "Empate de Blackjack (Push). Recuperas tu apuesta.\n";
            jugador.recibirFichas(apuesta);
        }
        else {
            int ganancia = apuesta + (apuesta * 3 / 2);
            std::cout << "¡BLACKJACK NATURAL! Ganaste (Pago 3:2).\n";
            jugador.recibirFichas(ganancia);
        }
    }
    else if (mano.esPasado()) {
        std::cout << "Has perdido la mano (Bust).\n";
    }
    else if (crupier.getMano().esPasado()) {
        std::cout << "El crupier se pasó de 21. ¡Ganaste, " << jugador.getNombre() << "! (Pago 1:1)\n";
        jugador.recibirFichas(apuesta * 2);
    }
    else if (ptosJugador > ptosCrupier) {
        std::cout << "¡Puntaje superior! Ganaste, " << jugador.getNombre() << " (Pago 1:1).\n";
        jugador.recibirFichas(apuesta * 2);
    }
    else if (ptosJugador < ptosCrupier) {
        std::cout << "El crupier gana la mano. Lo siento, " << jugador.getNombre() << ".\n";
    }
    else {
        std::cout << "Empate (Push). Recuperas tu apuesta.\n";
        jugador.recibirFichas(apuesta);
    }
}