#ifndef PATROCINADOR_H
#define PATROCINADOR_H
#include <iostream>
#include "persona.h"

using namespace std;


class Patrocinador
{
public:
    Patrocinador();
    Patrocinador(string &nombre, string &identificador);
    string getNombre(){return _nombre;}
    string getIdentificador(){return _identificador;}
    ~Patrocinador(){};
private:
    string _nombre, _identificador;
};

#endif // PATROCINADOR_H
