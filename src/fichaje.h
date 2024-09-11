#ifndef FICHAJE_H
#define FICHAJE_H
#include "equipo.h"
#include "representante.h"
#include "jugador.h"



class Fichaje
{
public:
    Fichaje();
    Fichaje(Jugador* jugador, Equipo* vendedor, Equipo* comprador, Representante* representante);
    Jugador* getJugadorFichado(){return _jugadorFichado;}
    float getPrecioDelFichaje(){return _precioDelFichaje;}
    Equipo* getEquipoComprador(){return _equipoComprador;}
    Equipo* getEquipoVendedor(){return _equipoVendedor;}
    Representante* getRepresentanteDelJugador(){return _representanteDelJugador;}
    void calcularCosteDelFichaje();
    ~Fichaje(){};
private:
    Jugador* _jugadorFichado;
    float _precioDelFichaje;
    Equipo* _equipoComprador;
    Equipo* _equipoVendedor;
    Representante* _representanteDelJugador;
};

#endif // FICHAJE_H
