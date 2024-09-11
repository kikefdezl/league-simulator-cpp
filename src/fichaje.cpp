#include "fichaje.h"
#include <random>


Fichaje::Fichaje()
{

}

Fichaje::Fichaje(Jugador* jugador, Equipo* vendedor, Equipo* comprador, Representante* representante)
{
    _jugadorFichado=jugador;
    _equipoComprador=comprador;
    _equipoVendedor=vendedor;
    _representanteDelJugador=representante;
    calcularCosteDelFichaje();
}

void Fichaje::calcularCosteDelFichaje()
{
    _precioDelFichaje=(_jugadorFichado->getNivelHabilidad()+_jugadorFichado->getNivelForma())*(_jugadorFichado->getNivelHabilidad()+_jugadorFichado->getNivelForma())*(rand()%404 + 800);
}
