#include "juego.h"
#include "constantes.h"

#include <iostream>
#include <limits>
#include <stdexcept>

using namespace Constantes;

Juego::Juego() : zapato(), crupier() {
    // El zapato se baraja una sola vez al comenzar la partida.
    zapato.barajar();
}

void Juego::registrarJugadores() {
    int cantidad;

    // Validar que participen entre 2 y 7 jugadores.
    do {
        std::cout << "Ingrese la cantidad de jugadores ("
                  << MIN_JUGADORES << "-" << MAX_JUGADORES << "): ";

        std::cin >> cantidad;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cantidad = 0;
        }

    } while (cantidad < MIN_JUGADORES || cantidad > MAX_JUGADORES);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Registrar los nombres y asignar las fichas iniciales.
    for (int i = 0; i < cantidad; i++) {
        std::string nombre;

        std::cout << "Nombre del jugador " << i + 1 << ": ";
        std::getline(std::cin, nombre);

        while (nombre.empty()) {
            std::cout << "El nombre no puede estar vacio. Intente nuevamente: ";
            std::getline(std::cin, nombre);
        }

        jugadores.emplace_back(nombre, FICHAS_INICIALES);
    }

    std::cout << "\n¡Bienvenidos al Blackjack!\n";

    for (const auto& jugador : jugadores) {
        std::cout << jugador.getNombre()
                  << ": " << jugador.getFichas() << " fichas\n";
    }
}

bool Juego::todosPuedenContinuar() const {
    for (const auto& jugador : jugadores) {
        if (jugador.getFichas() < APUESTA_MINIMA) {
            return false;
        }
    }

    return true;
}

void Juego::iniciarPartida() {
    std::cout << "=======================================\n";
    std::cout << "       SIMULADOR DE BLACKJACK\n";
    std::cout << "=======================================\n\n";

    registrarJugadores();

    char opcion = 's';

    while ((opcion == 's' || opcion == 'S') &&
           todosPuedenContinuar() &&
           !zapato.estaVacio()) {

        try {
            gestionarRonda();
        }
        catch (const std::runtime_error& e) {
            // Se controla el agotamiento de las cartas.
            std::cout << "\nNo fue posible completar la ronda: "
                      << e.what() << "\n";
            std::cout << "La partida ha finalizado.\n";
            break;
        }

        if (zapato.estaVacio()) {
            std::cout << "\nEl zapato se ha quedado sin cartas.\n";
            break;
        }

        if (!todosPuedenContinuar()) {
            std::cout << "\nUno o mas jugadores no tienen fichas suficientes "
                         "para continuar.\n";
            break;
        }

        std::cout << "\n¿Desean jugar otra ronda? (s/n): ";
        std::cin >> opcion;
    }

    std::cout << "\n========== FICHAS FINALES ==========\n";

    for (const auto& jugador : jugadores) {
        std::cout << jugador.getNombre() << ": "
                  << jugador.getFichas() << " fichas\n";
    }

    std::cout << "\nGracias por jugar.\n";
}

void Juego::gestionarRonda() {
    // Preparar las manos y los seguros para una nueva ronda.
    segurosPorJugador.assign(jugadores.size(), 0);

    crupier.getMano().limpiar();
    crupier.setTieneSeguroActivo(false);

    std::cout << "\n========== NUEVA RONDA ==========\n";

    // Cada jugador recibe una mano inicial y realiza su apuesta.
    for (auto& jugador : jugadores) {
        jugador.limpiarManos();
        jugador.agregarMano(Mano());

        int montoApuesta;

        do {
            std::cout << "\nJugador: " << jugador.getNombre()
                      << "\nFichas disponibles: " << jugador.getFichas()
                      << "\nIngrese su apuesta (" << APUESTA_MINIMA
                      << "-" << APUESTA_MAXIMA << "): ";

            std::cin >> montoApuesta;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                montoApuesta = 0;
            }

        } while (!jugador.apostar(montoApuesta, 0));
    }

    repartirCartasIniciales();
    ofrecerSeguro();

    // Comprobar si el crupier tiene Blackjack natural.
    bool blackjackCrupier = crupier.getMano().esBlackjack();

    if (blackjackCrupier) {
        std::cout << "\n¡El crupier tiene Blackjack natural!\n";
    }
    else {
        procesarAccionesJugador();
    }

    // El crupier juega si no tiene Blackjack y al menos
    // un jugador continúa con una mano que no está pasada.
    if (!blackjackCrupier) {
        bool hayManosActivas = false;

        for (const auto& jugador : jugadores) {
            if (!jugador.getManos()[0].esPasado()) {
                hayManosActivas = true;
                break;
            }
        }

        if (hayManosActivas) {
            procesarTurnoCrupier();
        }
    }
    else {
        std::cout << "\nCarta oculta del crupier: "
                  << crupier.getMano().getCartas()[0].obtenerDescripcion()
                  << "\n";
    }

    calcularPagosYResultados();
}

void Juego::repartirCartasIniciales() {
    // Primera carta para cada jugador.
    for (auto& jugador : jugadores) {
        jugador.getManos()[0].agregarCarta(zapato.repartirCarta());
    }

    // Primera carta del crupier: permanece oculta.
    crupier.recibirCarta(zapato.repartirCarta());

    // Segunda carta para cada jugador.
    for (auto& jugador : jugadores) {
        jugador.getManos()[0].agregarCarta(zapato.repartirCarta());
    }

    // Segunda carta del crupier: queda visible.
    crupier.recibirCarta(zapato.repartirCarta());

    std::cout << "\nCarta visible del crupier: "
              << crupier.getMano().getCartas()[1].obtenerDescripcion()
              << "\n";

    for (auto& jugador : jugadores) {
        std::cout << "\nCartas de " << jugador.getNombre() << ":\n";

        for (const auto& carta : jugador.getManos()[0].getCartas()) {
            std::cout << " - " << carta.obtenerDescripcion() << "\n";
        }

        std::cout << "Puntaje: "
                  << jugador.getManos()[0].calcularPuntaje() << "\n";
    }
}

void Juego::ofrecerSeguro() {
    // El seguro solamente se ofrece si la carta visible es un As.
    if (crupier.getMano().getCartas()[1].obtenerValor() != 1) {
        return;
    }

    std::cout << "\nEl crupier muestra un As.\n";

    for (int i = 0; i < static_cast<int>(jugadores.size()); i++) {
        Jugador& jugador = jugadores[i];
        int apuestaOriginal = jugador.getManos()[0].getApuesta();

        int montoSeguro = apuestaOriginal / 2;

        char respuesta;

        std::cout << "\n" << jugador.getNombre()
                  << ", ¿deseas comprar seguro por "
                  << montoSeguro << " fichas? (s/n): ";

        std::cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
            if (montoSeguro > 0 && jugador.retirarFichas(montoSeguro)) {
                segurosPorJugador[i] = montoSeguro;
                std::cout << "Seguro registrado.\n";
            }
            else {
                std::cout << "No tienes fichas suficientes para el seguro.\n";
            }
        }
    }
}

void Juego::procesarAccionesJugador() {
    // Cada jugador toma sus decisiones individualmente.
    for (auto& jugador : jugadores) {
        Mano& mano = jugador.getManos()[0];

        std::cout << "\n========== TURNO DE "
                  << jugador.getNombre() << " ==========\n";

        if (mano.esBlackjack()) {
            std::cout << "¡Tienes Blackjack natural!\n";
            continue;
        }

        char opcion;

        while (!mano.esPasado() && mano.getEstado() != "Plantada") {
            std::cout << "\n¿Que deseas hacer?\n";
            std::cout << "P: Pedir carta\n";
            std::cout << "S: Plantarse\n";
            std::cout << "D: Doblar\n";
            std::cout << "Opcion: ";

            std::cin >> opcion;

            if (opcion == 'p' || opcion == 'P') {
                Carta nueva = zapato.repartirCarta();
                mano.agregarCarta(nueva);

                std::cout << "Recibiste: "
                          << nueva.obtenerDescripcion() << "\n";

                std::cout << "Puntaje: "
                          << mano.calcularPuntaje() << "\n";

                if (mano.esPasado()) {
                    mano.setEstado("Pasada");
                    std::cout << "¡Te has pasado de 21!\n";
                }
            }
            else if (opcion == 's' || opcion == 'S') {
                mano.setEstado("Plantada");
            }
            else if (opcion == 'd' || opcion == 'D') {
                // Para doblar se necesita disponer de otra apuesta igual.
                int apuestaActual = mano.getApuesta();

                if (jugador.apostar(apuestaActual, 0)) {
                    mano.setApuesta(apuestaActual * 2);
                    mano.setEsDoblada(true);

                    Carta nueva = zapato.repartirCarta();
                    mano.agregarCarta(nueva);

                    std::cout << "Doblaste. Recibiste: "
                              << nueva.obtenerDescripcion() << "\n";

                    if (mano.esPasado()) {
                        mano.setEstado("Pasada");
                    }
                    else {
                        mano.setEstado("Plantada");
                    }
                }
                else {
                    std::cout << "No tienes suficientes fichas para doblar.\n";
                }
            }
            else {
                std::cout << "Opcion no valida.\n";
            }
        }
    }
}

void Juego::procesarTurnoCrupier() {
    std::cout << "\n========== TURNO DEL CRUPIER ==========\n";

    std::cout << "La carta oculta del crupier es: "
              << crupier.getMano().getCartas()[0].obtenerDescripcion()
              << "\n";

    std::cout << "Mano completa del crupier:\n";

    for (const auto& carta : crupier.getMano().getCartas()) {
        std::cout << " - " << carta.obtenerDescripcion() << "\n";
    }

    // El crupier pide obligatoriamente hasta llegar a 17 o más.
    crupier.jugarTurno(zapato);

    std::cout << "Puntaje final del crupier: "
              << crupier.getMano().calcularPuntaje() << "\n";
}

void Juego::calcularPagosYResultados() {
    int puntosCrupier = crupier.getMano().calcularPuntaje();
    bool blackjackCrupier = crupier.getMano().esBlackjack();

    std::cout << "\n========== RESULTADOS ==========\n";

    for (int i = 0; i < static_cast<int>(jugadores.size()); i++) {
        Jugador& jugador = jugadores[i];
        Mano& mano = jugador.getManos()[0];

        int apuesta = mano.getApuesta();
        int puntosJugador = mano.calcularPuntaje();

        std::cout << "\nJugador: " << jugador.getNombre() << "\n";

        // El seguro paga 2 a 1, además de devolver la apuesta del seguro.
        if (segurosPorJugador[i] > 0) {
            if (blackjackCrupier) {
                int pagoSeguro = segurosPorJugador[i] * 3;
                jugador.recibirFichas(pagoSeguro);

                std::cout << "El seguro gano. Recibes "
                          << pagoSeguro << " fichas.\n";
            }
            else {
                std::cout << "El seguro se pierde.\n";
            }
        }

        if (mano.esBlackjack() && blackjackCrupier) {
            std::cout << "Empate de Blackjack. Recuperas tu apuesta.\n";
            jugador.recibirFichas(apuesta);
        }
        else if (blackjackCrupier) {
            std::cout << "El crupier gana con Blackjack.\n";
        }
        else if (mano.esBlackjack()) {
            // Pago 3:2 por Blackjack natural.
            int ganancia = apuesta + (apuesta * 3 / 2);

            std::cout << "¡Blackjack natural! Ganaste "
                      << (apuesta * 3 / 2) << " fichas.\n";

            jugador.recibirFichas(ganancia);
        }
        else if (mano.esPasado()) {
            std::cout << "Perdiste: superaste los 21 puntos.\n";
        }
        else if (crupier.getMano().esPasado()) {
            std::cout << "El crupier se paso. ¡Ganaste!\n";
            jugador.recibirFichas(apuesta * 2);
        }
        else if (puntosJugador > puntosCrupier) {
            std::cout << "¡Ganaste la mano!\n";
            jugador.recibirFichas(apuesta * 2);
        }
        else if (puntosJugador < puntosCrupier) {
            std::cout << "El crupier gana la mano.\n";
        }
        else {
            std::cout << "Empate. Recuperas tu apuesta.\n";
            jugador.recibirFichas(apuesta);
        }

        std::cout << "Fichas actuales: "
                  << jugador.getFichas() << "\n";
    }
}
