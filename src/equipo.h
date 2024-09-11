#ifndef EQUIPO_H
#define EQUIPO_H
#include <iostream>
#include <vector>
#include "patrocinador.h"
#include "jugador.h"
#include "ojeador.h"

using namespace std;


class Equipo
{
public:
    Equipo();
    Equipo(string &nombre);
    void generarJugadores();
    void generarOjeadores();
    void generarPatrocinador();
    string getNombre(){return _nombre;}
    int getPuntos(){return _puntos;}
    void addPuntos(int n){_puntos+=n;}
    void addGolAFavor(){_golesAFavor+=1;}
    void addGolEnContra(){_golesEnContra+=1;}
    void addVictoria(){_victorias+=1;}
    void addDerrota(){_derrotas+=1;}
    void addEmpate(){_empates+=1;}
    int getVictorias(){return _victorias;}
    int getDerrotas(){return _derrotas;}
    int getEmpates(){return _empates;}
    int getGolesAFavor(){return _golesAFavor;}
    int getGolesEnContra(){return _golesEnContra;}
    Patrocinador* getPatrocinador(){return _patrocinador;}
    Jugador* getJugador(int n){return _plantilla.at(n);}
    Jugador* getConvocado(int n){return _convocatoria.at(n);}
    Ojeador* getOjeador(int n){return _ojeadores.at(n);}
    void convocarJugadores(void);
    Jugador* devolverJugadorDisponibleEnPosicion(string posicion);
    void ficharJugador(Jugador* jugador, int nPosicion){_plantilla.at(nPosicion)=jugador;}
    ~Equipo(){};
private:
    string _nombre;
    vector <Jugador*> _plantilla;
    vector <Jugador*> _convocatoria;
    vector <Ojeador*> _ojeadores;
    Patrocinador *_patrocinador;
    int _puntos, _golesAFavor, _golesEnContra, _victorias, _derrotas, _empates;
    bool _equiposYaEmparejados[20];
    bool _jornadasYaJugadas[19];
};

#endif // EQUIPO_H
