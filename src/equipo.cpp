#include "equipo.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

Equipo::Equipo()
{

}

Equipo::Equipo(string &nombre)
{
    _nombre=nombre;
    generarJugadores();     //al crear un equipo, generamos sus jugadores automaticamente
    generarOjeadores();     //igual con ojeadores
    generarPatrocinador();  //igual con el patrocinador
    _puntos=_golesAFavor=_golesEnContra=_victorias=_derrotas=_empates=0;
}

//para realizar la convocatoria, escogemos 1 portero, 1 defensa, 2 centros y 1 delantero. Utilizamos la funcion de ayuda _devolverJugadorDisponibleEnPosicion(), que comprueba automaticamente
//si un jugador esta lesionado o sancionado, y devuelve a un jugador apto para jugar. Tiene preferencia hacia los titulares, frente a los suplentes "Versatiles".
void Equipo::convocarJugadores()
{
    _convocatoria.clear();      //primero borramos la convocatoria
    //para que las lesiones y sanciones caduquen tras una semana, hay que analizar que jugadores estan lesionados o sancionados y anadir un dia a _jornadasSancionadoOLesionado
    //si han pasado 2 jornadas, se eliminan la sancion/lesion y el jugador podra jugar
    for (int i=0; i<7; i++)
    {
        if (getJugador(i)->puedeJugar()==0)
        {
            getJugador(i)->addJornadaSancionadoOLesionado();
        }
        if (getJugador(i)->getJornadasSancionadoOLesionado()>1)
        {
            getJugador(i)->setLesionado(0);
            getJugador(i)->setSancionado(0);
            getJugador(i)->resetJornadasSancionadoOLesionado();
        }
    }
    _convocatoria.push_back(devolverJugadorDisponibleEnPosicion("Portero"));
    _convocatoria.push_back(devolverJugadorDisponibleEnPosicion("Defensa"));
    _convocatoria.push_back(devolverJugadorDisponibleEnPosicion("Centrocampista"));
    _convocatoria.push_back(devolverJugadorDisponibleEnPosicion("Centrocampista"));
    _convocatoria.push_back(devolverJugadorDisponibleEnPosicion("Delantero"));
    //reseteamos el tag yaConvocado
    for (int i=0; i<7; i++)
    {
        getJugador(i)->resetYaConvocado();
    }
}

//funcion de ayuda en convocarJugadores(). Devuelve un jugador apto para jugar el proximo partido
Jugador* Equipo::devolverJugadorDisponibleEnPosicion(string posicion)
{
    for (int i=0; i<7; i++)
    {
        if ((getJugador(i)->getPosicion()==posicion || getJugador(i)->getPosicion()=="Versatil") && getJugador(i)->getYaConvocado()==0 && getJugador(i)->puedeJugar())
        {
            getJugador(i)->setYaConvocado();
            return getJugador(i);
        }
    }
    return NULL;
}

//funcion que genera a nuestros 7 jugadores para cada equipo
//se ejecuta en el constructor del equipo
void Equipo::generarJugadores(void)
{
    ifstream archivoJugadores("jugadores.txt");
    if (!archivoJugadores)
    {
        cout << "Error al abrir el archivo de jugadores" << endl;
    }
    string nombre, apellido, posicion;
    int edad, anosExperiencia, nivelHabilidad, nivelForma;
    //este linea nos permite saltarnos los jugadores que ya han sido extraidos del archivo en otros equipos para no repetirlos.
    static int numeroJugador=0;
    for (int i=0; i<numeroJugador ; i++)
    {
        getline(archivoJugadores, nombre);
    }
    for (int i=0; i<7 ; i++)
    {
        archivoJugadores >> nombre >> apellido >> edad >> posicion >> anosExperiencia >> nivelHabilidad >> nivelForma;
        nombre.append(" ").append(apellido);
        _plantilla.push_back(new Jugador(nombre, edad, anosExperiencia, nivelHabilidad, nivelForma, posicion));
        numeroJugador++;
    }
    archivoJugadores.close();
}

//funcion que genera a nuestros 2 ojeadores para cada equipo
//se ejecuta en el constructor del equipo
void Equipo::generarOjeadores(void)
{
    ifstream archivoOjeadores("ojeadores.txt");
    if (!archivoOjeadores)
    {
        cout << "Error al abrir el archivo de ojeadores" << endl;
    }
    string nombre, identificador;
    int edad;
    //este linea nos permite saltarnos los ojeadores que ya han sido extraidos del archivo en otros equipos para no repetirlos.
    static int numeroOjeador=0;
    for (int i=0; i<numeroOjeador; i++)
    {
        getline(archivoOjeadores, nombre);
    }
    for (int i=0; i<2 ; i++)
    {
        archivoOjeadores >> nombre >> edad >> identificador;
        _ojeadores.push_back(new Ojeador(nombre, edad, identificador));
        numeroOjeador++;
    }
    archivoOjeadores.close();
}

//funcion que genera a nuestro patrocinador para cada equipo
//se ejecuta en el constructor del equipo
void Equipo::generarPatrocinador(void)
{
    ifstream archivoPatrocinadores("patrocinadores.txt");
    if (!archivoPatrocinadores)
    {
        cout << "Error al abrir el archivo de Patrocinadores" << endl;
    }
    string nombre, identificador;
    //este linea nos permite saltarnos los patrocinadores que ya han sido extraidos del archivo en otros equipos para no repetirlos.
    static int numeroPatrocinador=0;                                 //este bucle nos permite saltarnos los ojeadores que ya han sido extraidos del archivo para no repetirlos
    for (int i=0; i<numeroPatrocinador; i++)
    {
        getline(archivoPatrocinadores, nombre);
    }
    archivoPatrocinadores >> nombre >> identificador;
    _patrocinador = new Patrocinador(nombre, identificador);
    numeroPatrocinador++;
    archivoPatrocinadores.close();
}


