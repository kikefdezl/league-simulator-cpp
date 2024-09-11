#ifndef COMPETICIONDEFUTBOL_H
#define COMPETICIONDEFUTBOL_H
#include <iostream>
#include <vector>
#include "equipo.h"
#include "calendario.h"
#include "arbitro.h"
#include "representante.h"
#include "jugador.h"
#include "ojeador.h"
#include "fecha.h"
#include "partido.h"
#include "persona.h"
#include "fichaje.h"
#include "arbitro.h"
#include "patrocinador.h"
#include "jornada.h"

using namespace std;


class CompeticionDeFutbol
{
public:
    CompeticionDeFutbol();
    CompeticionDeFutbol(string nombre, string tipo); //de momento inicializamos solo con nombre y tipo, igual en el futuro hay que meter algo mas.
    string getNombre(){return _nombre;}
    string getTipo(){return _tipo;}
    Equipo* getEquipo(int n){return _equipos.at(n);}
    Arbitro* getArbitro(int n){return _arbitros.at(n);}
    Calendario* getCalendario(){return _calendario;}
    Fichaje* getFichaje(int n){return _fichajesDeInvierno.at(n);}
    void generarFichajesDeInvierno();
    void generarEquipos(void);
    void generarArbitros(void);
    void generarCalendario(Fecha &fechaInicial);
    void generarFicherosJornadas();
    void generarFicheroClasificacion();
    void crearJugadoresAleatorios(void);        //estas tres funciones se podrian separar del proyecto. Su funcion es generar un archivo con los datos al azar (para no hacerlo de forma manual)
    void crearRepresentantesAleatorios(void);       //se ejecutan una vez para generar el archivo y ya
    void crearOjeadoresAleatorios(void);
    void simularCompeticion();
    void inicializarSimulacion();
    void menuPostSimulacion();
    void mostrarClasificacion();
    void mostrarPichichis();
    void mostrarZamoras();
    void mostrarSanciones();
    void mostrarResultadosJornadas();
    void mostrarJornadaDetallada(int n);
    void mostrarDatosDeEquipo(int n);
    void mostrarDatosDeCompeticion();
    void mostrarFichajesDeInvierno();
    ~CompeticionDeFutbol(){};
private:
    string _nombre;
    string _tipo;
    vector <Equipo*> _equipos ; //vector temporal de la lista de equipos. no se como va aun, lo he declarado solo y compila. Fijate que hace falta #include <vector>, si no no va.
    vector <Arbitro*> _arbitros;        //vector de punteros que apuntan a los arbitros de la liga
    Calendario *_calendario; // este puntero va a apuntar a el calendario que vamos a generar al pricipio de la simulacion y al que vamos a acceder cada vez que lo necesitemos.
    vector <Fichaje*> _fichajesDeInvierno;

};

#endif // COMPETICIONDEFUTBOL_H
