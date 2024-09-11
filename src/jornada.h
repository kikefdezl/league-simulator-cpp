#ifndef JORNADA_H
#define JORNADA_H
#include <vector>
#include "partido.h"
#include "fecha.h"
#include "arbitro.h"
#include "equipo.h"

using namespace std;


class Jornada
{
public:
    Jornada();
    Jornada(Fecha &fecha, vector <Equipo*> equipos, vector <Arbitro*> arbitros);
    Equipo* getEquipo(int n){return _equipos.at(n);}
    Arbitro* getArbitro(int n){return _arbitros.at(n);}
    void pushPartido(Partido* partido){_partidos.push_back(partido);}
    Partido* getPartido(int n){return _partidos.at(n);}
    Fecha getFecha(){return _fecha;}
    ~Jornada(){};
private:
    vector <Partido*> _partidos;
    vector <Equipo*> _equipos;
    vector <Arbitro*> _arbitros;
    Fecha _fecha;
};

#endif // JORNADA_H
