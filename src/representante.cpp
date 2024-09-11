#include "representante.h"
#include "competiciondefutbol.h"

using namespace std;

Representante::Representante()
{
    _identificador="";
}

Representante::Representante(string &nombre, int edad, string &identificador) : Persona(nombre, edad)
{
    _identificador=identificador;
}

