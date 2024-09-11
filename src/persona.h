#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>

using namespace std;


class Persona
{
public:
    Persona();
    Persona(string &nombre, int edad);
    string getNombre(){return _nombre;}
    int getEdad(){return _edad;}
    ~Persona(){};
protected:
    string _nombre;
    int _edad;
};

#endif // PERSONA_H
