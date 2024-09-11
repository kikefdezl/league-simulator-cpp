#include "ojeador.h"

Ojeador::Ojeador()
{
    _identificador="";
}

Ojeador::Ojeador(string &nombre, int edad, string &identificador) : Persona(nombre, edad)
{
    _identificador = identificador;
}
