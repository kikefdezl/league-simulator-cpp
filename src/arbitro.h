#ifndef ARBITRO_H
#define ARBITRO_H
#include <iostream>
#include "persona.h"
#include "jugador.h"


using namespace std;


class Arbitro : public Persona
{
public:
    Arbitro();
    Arbitro(string &nombre, int edad, string &identificador);
    void sancionar(Jugador* jugador); // funcion para sancionar. Entra un jugador por referencia y se cambia el estado de sancion a 1. Despues de un partido hay que hacer que vuelva a 0.
    string getIdentificador(){return _identificador;}
    ~Arbitro(){};
private:
    string _identificador;
};

#endif // ARBITRO_H
