#ifndef OJEADOR_H
#define OJEADOR_H
#include <iostream>
#include "persona.h"

using namespace std;


class Ojeador : public Persona
{
public:
    Ojeador();
    Ojeador(string &nombre, int edad, string &identificador);
    string getIdentificador(){return _identificador;}
    ~Ojeador(){};
private:
    string _identificador;
};

#endif // OJEADOR_H
