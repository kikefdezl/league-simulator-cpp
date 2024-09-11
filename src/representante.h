#ifndef REPRESENTANTE_H
#define REPRESENTANTE_H
#include <iostream>
#include "persona.h"

using namespace std;


class Representante : public Persona
{
public:
    Representante();
    Representante(string &nombre, int edad, string &identificador);
    string getIdentificador(){return _identificador;}
    ~Representante(){};
private:
    string _identificador;
};

#endif // REPRESENTANTE_H
