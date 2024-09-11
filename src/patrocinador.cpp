#include "patrocinador.h"
#include <iostream>

using namespace std;

Patrocinador::Patrocinador()
{
    _nombre="";
    _identificador="";
}

Patrocinador::Patrocinador(string &nombre, string &identificador)
{
    _nombre=nombre;
    _identificador=identificador;
}
