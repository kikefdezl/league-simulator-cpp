#include "jugador.h"
#include <iostream>
#include <fstream>
#include "competiciondefutbol.h"

using namespace std;

Jugador::Jugador()
{
    _nivelHabilidad=0;
    _nivelForma=0;
    _posicion="";
    _anosExperiencia=0;
    _lesionado=0;
    _sancionado=0;
}

Jugador::Jugador(string nombre, int edad, int anosExperiencia, int nivelHabilidad, int nivelForma, string posicion) : Persona(nombre, edad)
{
    _nivelHabilidad=nivelHabilidad;
    _nivelForma=nivelForma;
    _anosExperiencia=anosExperiencia;
    _posicion=posicion;
    _lesionado=_sancionado=_convocado=0;
    _golesMarcados=_sanciones=_jornadasSancionadoOLesionado=0;
    if(_nombre=="" && _posicion=="")        //si introducimos un nombre y posicion vacios, nos pone -1 en goles marcados y sanciones.
    {                                       // Es de ayuda en la funcion CompeticionDeFutbol::mostrarPichichis() y en CompeticionDeFutbol::mostrarSanciones();
        _golesMarcados=-1;
        _sanciones=-1;
    }
    asignarRepresentante();
}


bool Jugador::puedeJugar()
{
    if (_sancionado==0 && _lesionado==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//funcion que recoge un representante del archivo representantes.txt y se lo asigna a un jugador
void Jugador::asignarRepresentante()
{
    ifstream archivoRepresentantes("representantes.txt");
    string nombre, identificador;
    int edad;
    //este linea nos permite saltarnos los representantes que ya han sido extraidos del archivo en otros jugadores para no repetirlos.
    static int numeroRepresentante=0;
    for (int i=0; i<numeroRepresentante;i++)        //bucle que nos permite saltarnos los representantes que ya han sido extraidos del archivo. Evitamos asi que se repitan.
    {
        getline(archivoRepresentantes, nombre);
    }
    archivoRepresentantes >> nombre >> edad >> identificador;
    _representante = new Representante(nombre, edad, identificador);
    numeroRepresentante++;
}



