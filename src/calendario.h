#ifndef CALENDARIO_H
#define CALENDARIO_H
#include <vector>
#include "jornada.h"
#include "fecha.h"
#include "equipo.h"
#include "arbitro.h"
#include "fichaje.h"

using namespace std;

class Calendario
{
public:
    Calendario();
    Calendario(Fecha &fechaInicio, int numeroJornadas, vector <Equipo*> equipos, vector <Arbitro*> arbitros);
    Jornada* getJornada(int n){return _jornadas.at(n);}
    void generarJornadas(void);
    void generarEnfrentamientos(void);
    void generarFicheroCalendario();
    Equipo* getEquipo(int n){return _equipos.at(n);}
    Arbitro* getArbitro(int n){return _arbitros.at(n);}
    Fecha getFechaInicio(){return _fechaInicio;}
    Fecha getFechaFinal(){return _fechaFinal;}
    ~Calendario(){};
private:
    Fecha _fechaInicio, _fechaFinal;
    int _numeroJornadas;
    vector <Jornada*> _jornadas;
    vector <Arbitro*> _arbitros;
    vector <Equipo*> _equipos;
};

#endif // CALENDARIO_H
