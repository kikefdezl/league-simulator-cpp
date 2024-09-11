#include "arbitro.h"

Arbitro::Arbitro()
{
    _identificador="";
}

Arbitro::Arbitro(string &nombre, int edad, string &identificador) : Persona(nombre, edad)
{
    _identificador=identificador;
}


//funcion que sanciona a un jugador
void Arbitro::sancionar(Jugador* jugador)
{
    jugador->setSancionado(1);
}
