#include "jornada.h"
#include "competiciondefutbol.h"
#include <fstream>

using namespace std;

Jornada::Jornada()
{

}

Jornada::Jornada(Fecha &fecha, vector <Equipo*> equipos, vector <Arbitro*> arbitros)
{
    _fecha=fecha;
    _equipos=equipos;
    _arbitros=arbitros;
}

