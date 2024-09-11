#include "persona.h"
#include <iostream>

using namespace std;

Persona::Persona()
{
    _nombre="";
    _edad=0;
}

Persona::Persona(string &nombre, int edad)
{
    _nombre=nombre;
    _edad=edad;
}
