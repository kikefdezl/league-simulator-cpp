#ifndef PARTIDO_H
#define PARTIDO_H
#include <vector>
#include "equipo.h"
#include "jugador.h"
#include "arbitro.h"

using namespace std;


class Partido
{
public:
    Partido();
    Partido(Equipo* equipo1,Equipo* equipo2, Arbitro* arbitro);
    void simularPartido(void);
    Equipo* getEquipo1(void){return _equipo1;}
    Equipo* getEquipo2(void){return _equipo2;}
    Arbitro* getArbitro(void){return _arbitro;}
    Jugador* getGoleador1(int n){return _goleadores1.at(n);}
    Jugador* getGoleador2(int n){return _goleadores2.at(n);}
    Jugador* getAlineado1(int n){return _alineacion1.at(n);}
    Jugador* getAlineado2(int n){return _alineacion2.at(n);}
    int getResultado(int n){return _resultado[n];}
    vector <Jugador*> getJugadoresSancionados(){return _jugadoresSancionados;}
    vector <Jugador*> getJugadoresLesionados(){return _jugadoresLesionados;}
    ~Partido(){};
private:
    Equipo *_equipo1, *_equipo2;
    vector <Jugador*> _alineacion1;
    vector <Jugador*> _alineacion2;
    vector <Jugador*> _goleadores1;
    vector <Jugador*> _goleadores2;
    vector <Jugador*> _jugadoresSancionados;
    vector <Jugador*> _jugadoresLesionados;
    Arbitro *_arbitro;
    int _resultado[2];
};

#endif // PARTIDO_H
