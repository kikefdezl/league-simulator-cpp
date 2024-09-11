#include "competiciondefutbol.h"
#include <iostream>
#include "calendario.h"
#include "fecha.h"
#include <fstream>
#include "equipo.h"
#include <vector>
#include "arbitro.h"
#include <random>
#include <time.h>
#include <math.h>
#include <iomanip>
#include "jugador.h"
#include <string>


using namespace std;

string devolverPosicion(int i);     //funcion de ayuda en crearJugadoresAleatorios()

CompeticionDeFutbol::CompeticionDeFutbol()
{
    _nombre="";
    _tipo="";
}

CompeticionDeFutbol::CompeticionDeFutbol(string nombre, string tipo)
{
    _nombre=nombre;
    _tipo=tipo;
}

//funcion que inicializa y simula todos los acontecimientos de la simulacion
void CompeticionDeFutbol::simularCompeticion()
{
    inicializarSimulacion();
    for (int i=0; i<19; i++)        //para cada jornada
    {
        for (int j=0; j<10; j++)        //para cada partido
        {
            getCalendario()->getJornada(i)->getPartido(j)->simularPartido();        //simulamos el partido
        }
    }
    //generamos nuestros fichajes a mitad de temporada
    generarFichajesDeInvierno();
    //segunda vuelta
    for (int i=19; i<38; i++)        //para cada jornada
    {
        for (int j=0; j<10; j++)        //para cada partido
        {
            getCalendario()->getJornada(i)->getPartido(j)->simularPartido();        //simulamos el partido
        }
    }
    cout << "                    SIMULADOR DEPORTIVO " << endl;
    cout << "By Enrique Fernandez-Laguilhoat Sanchez-Biezma & David Rojo Pena" << endl << endl << endl;
    cout << "              -----Simulacion Completada-----" << endl << endl;
    generarFicherosJornadas();
    generarFicheroClasificacion();
    menuPostSimulacion();
}

//inicializacion
void CompeticionDeFutbol::inicializarSimulacion()
{
    generarEquipos();     //creamos los equipos de futbol, guardandolos en la competicion y asignando los nombres del archivo txt. Cada equipo genera a los jugadores automaticamente en su constructor.
    generarArbitros();        //creamos arbitros, los guardamos en la competicion y les asignamos los nombres y edad del archivo txt
    Fecha fechaInicio(24,8,2019);        //establecemos la fecha de inicio de la temporada.
    generarCalendario(fechaInicio);     //generamos el calendario de la competicion
}

//generamos aleatoriamente 10 fichajes a mitad de temporada. Se eligen dos equipos al azar y se intercambian un jugador de la misma posicion entre ellos. El precio de la operacion
//depende de la habilidad y forma del jugador
void CompeticionDeFutbol::generarFichajesDeInvierno()
{
    bool aux[20]={0};
    int random, random2, random3;
    Jugador* auxSwap;
    for (int i=0; i<10; i++)
    {
        random=rand()%20;
        while(aux[random]==1)
        {
            random=rand()%20;
        }
        random2 = rand()%20;
        while(aux[random2]==1 || random==random2)
        {
            random2=rand()%20;
        }
        aux[random]=aux[random2]=1;   //marcamos el flag que indica que los equipos ya han realizado su fichaje
        random3=rand()%7;
        //creamos nuestros nuevos objetos de tipo Fichaje
        _fichajesDeInvierno.push_back(new Fichaje(getEquipo(random)->getJugador(random3), getEquipo(random), getEquipo(random2), getEquipo(random)->getJugador(random3)->getRepresentante()));
        _fichajesDeInvierno.push_back(new Fichaje(getEquipo(random2)->getJugador(random3), getEquipo(random2), getEquipo(random), getEquipo(random2)->getJugador(random3)->getRepresentante()));
        //procedemos a hacer el intercambio de jugadores
        auxSwap=getEquipo(random)->getJugador(random3);
        getEquipo(random)->ficharJugador(getEquipo(random2)->getJugador(random3), random3);
        getEquipo(random2)->ficharJugador(auxSwap, random3);
    }
}


//funcion que gestiona la impresion y navegacion del menu post-simulacion
void CompeticionDeFutbol::menuPostSimulacion()
{
    char input;
    int input2;
    while(1)
    {
        cout << endl << "Elige una opcion intruduciendo el numero asociado" << endl;
        cout << "1 Ver clasificacion final" << endl;
        cout << "2 Ver resultados de las jornadas" << endl;
        cout << "3 Ver jornada detallada " << endl;
        cout << "4 Ver tabla de pichichis" << endl;
        cout << "5 Ver tabla de zamoras" << endl;
        cout << "6 Ver tabla de sanciones" << endl;
        cout << "7 Acceder a datos de equipos" << endl;
        cout << "8 Acceder a datos de la competicion" << endl;
        cout << "9 Ver los fichajes de Invierno" << endl;
        cout << "0 Salir" << endl;
        cin >> input;
        switch (input)
        {
        case '1':
            mostrarClasificacion();
            break;

        case '2':
            mostrarResultadosJornadas();
            break;

        case '3':
            cout << "Indica a que jornada quieres acceder (1-38)" << endl;
            cin >> input2;
            while(input2<1 || input2>38)
            {
                cout<< "Error: Introduce un entero entre 1 y 38" << endl;
                cin >> input2;
            }
            mostrarJornadaDetallada(input2);
            break;

        case '4':
            mostrarPichichis();
            break;

        case '5':
            mostrarZamoras();
            break;

        case '6':
            mostrarSanciones();
            break;

        case '7':
            int n;
            cout << "Selecciona a que equipo quieres acceder (1-20)" << endl;
            for (int i=0; i<20; i++)
            {
                cout << setw(2) << right << i+1 << " " << getEquipo(i)->getNombre() << endl;
            }
            cin >> n;
            while(n<1 || n>20)
            {
                cout<< "Error: Introduce un entero entre 1 y 20" << endl;
                cin >> n;
            }
            mostrarDatosDeEquipo(n-1);
            break;

        case '8':
            mostrarDatosDeCompeticion();
            break;

        case '9':
            mostrarFichajesDeInvierno();
            break;

        case '0':
            exit(0);


        default:
            cout << "ERROR: Intruduce un valor entre 0 y 9" << endl;
        }
        cout << "Pulse ENTER para continuar" << endl;
        getchar();
        getchar();
    }
}

//funcion que genera nuestros 20 equipos, cogiendo como informacion los datos guardados en equipos.txt
void CompeticionDeFutbol::generarEquipos(void)
{
    ifstream archivoEquipos("equipos.txt");
    if (!archivoEquipos)
    {
        cout << "Error al abrir archivo de equipos" << endl;
        exit(1);
    }
    string part1, part2;
    for (int i=0; i<20 ; i++)    //este bucle crea los 20 equipos de la liga, y les asigna un nombre, guardados en el archivo equipos.txt
    {
        archivoEquipos >> part1 >> part2;       //leemos nombre del equipo
        part1.append(" ").append(part2);
        _equipos.push_back(new Equipo(part1));      //creamos equipo con el nombre leido, y lo añadimos al vector de Equipos.
    }

    archivoEquipos.close();
}

//funcion que genera nuestros 15 arbitros, cogiendo la informacion del archivo arbitros.txt
void CompeticionDeFutbol::generarArbitros(void)        //funcion que genera nuestros 15 arbitros y les asigna su nombre
{
    ifstream archivoArbitros("arbitros.txt");
    if(!archivoArbitros)
    {
        cout << "Error al abrir archivo de arbitros" << endl;
        exit(1);
    }
    string nombre, identificador;
    int edad;
    for (int i=0; i<15 ; i++)
    {
        archivoArbitros >> nombre >> edad >> identificador;
        _arbitros.push_back(new Arbitro(nombre, edad, identificador));
    }
    archivoArbitros.close();
}

//generamos el calendario de la temporada
void CompeticionDeFutbol::generarCalendario(Fecha &fechaInicio)
{
    _calendario = new Calendario(fechaInicio, 38, _equipos, _arbitros);
}

//imprimimos la clasificacion en orden de puntuacion, y teniendo en cuenta el golaveras en caso de empate a puntos. Se hace una copia de nuestro vector de equipos para despues organizarlo
//mediante un simple sorting-algorithm y despues imprimirlo.
void CompeticionDeFutbol::mostrarClasificacion()
{
    vector <Equipo*> aux;
    Equipo* aux2;
    for (int i=0; i<20; i++)        //hacemos una copia de nuestro vector de equipos
    {
        aux.push_back(getEquipo(i));
    }
    for (int i=1; i<20; i++)            //ordenamos por orden de puntuacion el vector copia
    {
        for (int j=i; j>0; j--)
        {
            if(aux.at(j)->getPuntos()>aux.at(j-1)->getPuntos())
            {
                aux2=aux.at(j);
                aux.at(j)=aux.at(j-1);
                aux.at(j-1)=aux2;
            }
            //con esta segunda condicion tenemos en cuenta el golaveras en caso de empate a puntos
            if(aux.at(j)->getPuntos()==aux.at(j-1)->getPuntos() && (aux.at(j)->getGolesAFavor()-aux.at(j)->getGolesEnContra()>aux.at(j-1)->getGolesAFavor()-aux.at(j-1)->getGolesEnContra()))
            {
                aux2=aux.at(j);
                aux.at(j)=aux.at(j-1);
                aux.at(j-1)=aux2;
            }
        }
    }
    cout << endl;
    cout << "                 CLASIFICACION" << endl;
    cout << "_____________________________________________" << endl << endl;
    cout << "   Equipo                   PTS   V   E   D     GF  GC  " << endl;
    for (int i=0; i<20; i++)
    {

        cout << setw(2) << right << i+1 << left << " " << setw(25) << aux.at(i)->getNombre();
        cout << setw(6) << aux.at(i)->getPuntos();
        cout << setw(4) << aux.at(i)->getVictorias();
        cout << setw(4) << aux.at(i)->getEmpates();
        cout << setw(6) << aux.at(i)->getDerrotas();
        cout << setw(3) << aux.at(i)->getGolesAFavor() << " ";
        cout << setw(3) << aux.at(i)->getGolesEnContra() << endl;
    }
}

//imprimimos los resultados de todas las jornadas
void CompeticionDeFutbol::mostrarResultadosJornadas()
{
    for (int i=0; i<38; i++)        //para todas las jornadas
    {
        cout << endl<< "Jornada " << i + 1 << ":" << endl;
        cout << getCalendario()->getJornada(i)->getFecha().getDia() << "/" << getCalendario()->getJornada(i)->getFecha().getMes() << "/" << getCalendario()->getJornada(i)->getFecha().getAno() << endl;
        for (int j=0; j<10; j++)        //para todos los partidos
        {
            cout << getCalendario()->getJornada(i)->getPartido(j)->getEquipo1()->getNombre() << " " << getCalendario()->getJornada(i)->getPartido(j)->getResultado(0);
            cout << " - ";
            cout << getCalendario()->getJornada(i)->getPartido(j)->getResultado(1) << " " <<  getCalendario()->getJornada(i)->getPartido(j)->getEquipo2()->getNombre() << endl;
        }
    }
}

//imprime toda la informacion de una jornada determinada
void CompeticionDeFutbol::mostrarJornadaDetallada(int n)
{
    cout << endl << "Jornada " << n  << ":" << endl;
    cout << getCalendario()->getJornada(n-1)->getFecha().getDia() << "/" << getCalendario()->getJornada(n-1)->getFecha().getMes() << "/" << getCalendario()->getJornada(n-1)->getFecha().getAno() << endl << endl;
    for (int i=0; i<10; i++)
    {
        cout << endl << "Partido " << i+1 << ":" << endl;
        cout << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << " " << getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0);
        cout << " - " << getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1) << " " << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << endl;
        cout << "Arbitrado por " << getCalendario()->getJornada(n-1)->getPartido(i)->getArbitro()->getNombre() << "." << endl << endl;
        cout << "ALINEACIONES:" << endl << endl;
        cout << "Posicion:          " << left << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << endl;
        for (int j=0; j<5; j++)
        {
            cout << setw(20) << devolverPosicion(j);
            cout << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getAlineado1(j)->getNombre();
            cout << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getAlineado2(j)->getNombre() << endl;
        }
        cout << endl;

        //goles de ambos equipos
        if(getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0)>0)
        {
            cout << "Goles de '" << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << "':" << endl;
            for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0); j++)
            {
                cout << getCalendario()->getJornada(n-1)->getPartido(i)->getGoleador1(j)->getNombre() << endl;
            }
            cout << endl;
        }
        if(getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1)>0)
        {
            cout << "Goles de '" << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << "':" << endl;
            for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1); j++)
            {
                cout << getCalendario()->getJornada(n-1)->getPartido(i)->getGoleador2(j)->getNombre() << endl;
            }
            cout << endl;
        }

        //sanciones
        if(getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().size()>0)
        {
            cout << "Sancionados: " << endl;
            for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().size();j++)
            {
                cout << getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().at(j)->getNombre() << endl;
            }
            cout << endl;
        }

        //lesiones
        if(getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().size()>0)
        {
            cout << "Lesionados: " << endl;
            for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().size();j++)
            {
                cout << getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().at(j)->getNombre() << endl;
            }
            cout << endl;
        }
        cout << "_____________________________________" << endl << endl;
    }
}

//hacemos una tabla que ordena los 20 jugadores con mas goles marcados, en orden. Se hace mediante un simple sorting-algorithm. Es un algoritmo ligeramente diferente al de la clasificacion
//de equipos, dado que en el otro hay siempre 20 equipos, y aqui al solo mostrar los 20 jugadores (de 140) con mas goles, entran y salen jugadores de nuestro vector de 20 posiciones.
void CompeticionDeFutbol::mostrarPichichis()
{
    vector <Jugador*> aux;
    for (int i=0; i<20; i++)        //primero rellenamos el vector 20 jugadores y 0 goles
    {
        aux.push_back(new Jugador("",0,0,0,0,""));
    }
    for (int i=0; i<20; i++)        //para cada equipo
    {
        for (int j=0; j<7; j++)     //para cada jugador
        {
            int k=19;
            while((getEquipo(i)->getJugador(j)->getGolesMarcados())>(aux.at(k)->getGolesMarcados()))       //comparamos con los 20 jugadores que ya estan introducidos en el vector
            {
                k--;
                if(k==-1)
                {
                    break;
                }
            }
            k++;
            for (int l=19; l>k; l--)
            {
                aux.at(l)=aux.at(l-1);
            }
            if(k<19)
            {
                aux.at(k)=getEquipo(i)->getJugador(j);
            }
        }
    }

    cout << endl << "            PICHICHIS  " << endl;
    cout << "___________________________________" << endl << endl;
    cout << "   Nombre                        Posicion        Goles " << endl;
    for (int i=0; i<20; i++)
    {
        cout << right <<setw(2) << i+1 << " " << left << setw(30) << aux.at(i)->getNombre() << setw(16) << aux.at(i)->getPosicion() << setw(3) << aux.at(i)->getGolesMarcados() << endl;
    }

}

//se ordenan los 20 porteros en funcion de la cantidad de goles recibidos
void CompeticionDeFutbol::mostrarZamoras()
{
    vector <Equipo*> aux;
    Equipo* aux2;
    for (int i=0; i<20; i++)        //hacemos una copia de nuestro vector de equipos
    {
        aux.push_back(getEquipo(i));
    }
    for (int i=1; i<20; i++)            //ordenamos por orden de puntuacion el vector copia
    {
        for (int j=i; j>0; j--)
        {
            if(aux.at(j)->getGolesEnContra()<aux.at(j-1)->getGolesEnContra())
            {
                aux2=aux.at(j);
                aux.at(j)=aux.at(j-1);
                aux.at(j-1)=aux2;
            }
        }
    }
    cout << "            ZAMORAS" << endl;
    cout << "___________________________________" << endl << endl;
    cout << "   Nombre                        Goles Recibidos" << endl;
    for (int i=0; i<20; i++)
    {

        cout << setw(2) << right << i+1 << left << " " << setw(30) << aux.at(i)->getJugador(0)->getNombre();
        cout << setw(3) << aux.at(i)->getGolesEnContra() << endl;
    }
}

//mismo algoritmo que para la tabla de pichichis
void CompeticionDeFutbol::mostrarSanciones()
{
    vector <Jugador*> aux;
    for (int i=0; i<20; i++)        //primero rellenamos el vector 20 jugadores y 0 goles
    {
        aux.push_back(new Jugador("",0,0,0,0,""));
    }
    for (int i=0; i<20; i++)        //para cada equipo
    {
        for (int j=0; j<7; j++)     //para cada jugador
        {
            int k=19;
            while((getEquipo(i)->getJugador(j)->getSanciones())>(aux.at(k)->getSanciones()))       //comparamos con los 20 jugadores que ya estan introducidos en el vector
            {
                k--;
                if(k==-1)
                {
                    break;
                }
            }
            k++;
            for (int l=19; l>k; l--)
            {
                aux.at(l)=aux.at(l-1);
            }
            if(k<19)
            {
                aux.at(k)=getEquipo(i)->getJugador(j);
            }
        }
    }

    cout << endl << "            SANCIONES  " << endl;
    cout << "___________________________________" << endl << endl;
    cout << "   Nombre                        Posicion        Sanciones " << endl;
    for (int i=0; i<20; i++)
    {
        cout << right <<setw(2) << i+1 << " " << left << setw(30) << aux.at(i)->getNombre() << setw(16) << aux.at(i)->getPosicion() << setw(3) << aux.at(i)->getSanciones() << endl;
    }

}

//imprimimos la informacion detallada de un equipo
void CompeticionDeFutbol::mostrarDatosDeEquipo(int n)
{
    cout << endl << getEquipo(n)->getNombre() << ":" << endl << endl;
    cout << "Jugadores                     Posicion        Edad  Habilidad  Forma  Sanciones  Goles  Representante(Edad, Identificador)     " << endl;
    for (int i=0; i<7; i++)
    {
        cout << setw(30) << left << getEquipo(n)->getJugador(i)->getNombre();
        cout << setw(16) << getEquipo(n)->getJugador(i)->getPosicion();
        cout << setw(6) << getEquipo(n)->getJugador(i)->getEdad();
        cout << setw(11) << getEquipo(n)->getJugador(i)->getNivelHabilidad();
        cout << setw(7) << getEquipo(n)->getJugador(i)->getNivelForma();
        cout << setw(11) << getEquipo(n)->getJugador(i)->getSanciones();
        cout << setw(7) << getEquipo(n)->getJugador(i)->getGolesMarcados();
        cout << getEquipo(n)->getJugador(i)->getRepresentante()->getNombre() << "(" << getEquipo(n)->getJugador(i)->getRepresentante()->getEdad() << ", " << getEquipo(n)->getJugador(i)->getRepresentante()->getIdentificador() << ")"<< endl;
    }
    cout << endl << "Ojeadores(Edad, Identificador):" << endl;
    for (int i=0; i<2; i++)
    {
        cout << getEquipo(n)->getOjeador(i)->getNombre() << "(" << getEquipo(n)->getOjeador(i)->getEdad()  << ", " << getEquipo(n)->getOjeador(i)->getIdentificador() << ")" << endl;
    }
    cout << endl << "Patrocinador(Identificador): " << getEquipo(n)->getPatrocinador()->getNombre() << "(" << getEquipo(n)->getPatrocinador()->getIdentificador() << ")" << endl;
}

//imprimimos la informacion detallada de la competicion
void CompeticionDeFutbol::mostrarDatosDeCompeticion()
{
    cout << endl << "Liga de Futbol " << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Tipo: " << getTipo() << endl;
    cout << "Fecha de Inicio: " << getCalendario()->getFechaInicio().getDia() << "/" << getCalendario()->getFechaInicio().getMes() << "/" << getCalendario()->getFechaInicio().getAno() << endl;
    cout << "Fecha Final: " << getCalendario()->getFechaFinal().getDia() << "/" << getCalendario()->getFechaFinal().getMes() << "/" << getCalendario()->getFechaFinal().getAno() << endl;
    cout << "Numero de Jornadas: 38" << endl;
    cout << endl << "Arbitros(Edad, Identificador): " << endl;
    for (int i=0; i<15; i++)
    {
        cout << getArbitro(i)->getNombre() << "(" << getArbitro(i)->getEdad() << ", " << getArbitro(i)->getIdentificador() << ")" << endl;
    }
}

void CompeticionDeFutbol::mostrarFichajesDeInvierno()
{
    cout << endl << "Fichajes de la temporada: " << endl << endl;
    cout << "   Jugador                  Equipo Comprador         Equipo Vendedor         Precio(euros)    Representante(Identificador)" << endl;
    for (int i=0; i<20; i++)
    {
        cout << setw(2) << right << i+1 << left << " " << setw(25) << getFichaje(i)->getJugadorFichado()->getNombre();
        cout << setw(25) << getFichaje(i)->getEquipoComprador()->getNombre();
        cout << setw(25) << getFichaje(i)->getEquipoVendedor()->getNombre();
        cout << setw(10) << setprecision(0) << fixed << right << getFichaje(i)->getPrecioDelFichaje() << left << "      ";
        cout << getFichaje(i)->getRepresentanteDelJugador()->getNombre() << "(" << getFichaje(i)->getRepresentanteDelJugador()->getIdentificador() << ")" << endl;
    }
}



//funcion para imprimir la informacion detallada de todas las jornadas en archivos .txt
void CompeticionDeFutbol::generarFicherosJornadas()
{
    ofstream archivoJornadas;
    for (int n=1; n<39; n++)
    {
        archivoJornadas.open("Jornadas/Jornada " + to_string(n) + ".txt");
        archivoJornadas << endl << "Jornada " << n  << ":" << endl;
        archivoJornadas << getCalendario()->getJornada(n-1)->getFecha().getDia() << "/" << getCalendario()->getJornada(n-1)->getFecha().getMes() << "/" << getCalendario()->getJornada(n-1)->getFecha().getAno() << endl << endl;
        for (int i=0; i<10; i++)
        {
            archivoJornadas << endl << "Partido " << i+1 << ":" << endl;
            archivoJornadas << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << " " << getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0);
            archivoJornadas << " - " << getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1) << " " << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << endl;
            archivoJornadas << "Arbitrado por " << getCalendario()->getJornada(n-1)->getPartido(i)->getArbitro()->getNombre() << "." << endl << endl;
            archivoJornadas << "ALINEACIONES:" << endl << endl;
            archivoJornadas << "Posicion:          " << left << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << endl;
            for (int j=0; j<5; j++)
            {
                archivoJornadas << setw(20) << devolverPosicion(j);
                archivoJornadas << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getAlineado1(j)->getNombre();
                archivoJornadas << setw(30) << getCalendario()->getJornada(n-1)->getPartido(i)->getAlineado2(j)->getNombre() << endl;
            }
            archivoJornadas << endl;

            //goles de ambos equipos
            if(getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0)>0)
            {
                archivoJornadas << "Goles de '" << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo1()->getNombre() << "':" << endl;
                for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(0); j++)
                {
                    archivoJornadas << getCalendario()->getJornada(n-1)->getPartido(i)->getGoleador1(j)->getNombre() << endl;
                }
                archivoJornadas << endl;
            }
            if(getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1)>0)
            {
                archivoJornadas << "Goles de '" << getCalendario()->getJornada(n-1)->getPartido(i)->getEquipo2()->getNombre() << "':" << endl;
                for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getResultado(1); j++)
                {
                    archivoJornadas << getCalendario()->getJornada(n-1)->getPartido(i)->getGoleador2(j)->getNombre() << endl;
                }
                archivoJornadas << endl;
            }

            //sanciones
            if(getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().size()>0)
            {
                archivoJornadas << "Sancionados: " << endl;
                for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().size();j++)
                {
                    archivoJornadas << getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresSancionados().at(j)->getNombre() << endl;
                }
                archivoJornadas << endl;
            }

            //lesiones
            if(getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().size()>0)
            {
                archivoJornadas << "Lesionados: " << endl;
                for (int j=0; j<getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().size();j++)
                {
                    archivoJornadas << getCalendario()->getJornada(n-1)->getPartido(i)->getJugadoresLesionados().at(j)->getNombre() << endl;
                }
                archivoJornadas << endl;
            }
            archivoJornadas << "_____________________________________" << endl << endl;
        }
        archivoJornadas.close();
    }
}


void CompeticionDeFutbol::generarFicheroClasificacion()
{
    ofstream ficheroClasificacion;
    ficheroClasificacion.open("clasificacion.txt");
    vector <Equipo*> aux;
    Equipo* aux2;
    for (int i=0; i<20; i++)        //hacemos una copia de nuestro vector de equipos
    {
        aux.push_back(getEquipo(i));
    }
    for (int i=1; i<20; i++)            //ordenamos por orden de puntuacion el vector copia
    {
        for (int j=i; j>0; j--)
        {
            if(aux.at(j)->getPuntos()>aux.at(j-1)->getPuntos())
            {
                aux2=aux.at(j);
                aux.at(j)=aux.at(j-1);
                aux.at(j-1)=aux2;
            }
            //con esta segunda condicion tenemos en cuenta el golaveras en caso de empate a puntos
            if(aux.at(j)->getPuntos()==aux.at(j-1)->getPuntos() && (aux.at(j)->getGolesAFavor()-aux.at(j)->getGolesEnContra()>aux.at(j-1)->getGolesAFavor()-aux.at(j-1)->getGolesEnContra()))
            {
                aux2=aux.at(j);
                aux.at(j)=aux.at(j-1);
                aux.at(j-1)=aux2;
            }
        }
    }
    ficheroClasificacion << "                 CLASIFICACION" << endl;
    ficheroClasificacion << "_____________________________________________" << endl << endl;
    ficheroClasificacion << "   Equipo                   PTS   V   E   D     GF  GC  " << endl;
    for (int i=0; i<20; i++)
    {

        ficheroClasificacion << setw(2) << right << i+1 << left << " " << setw(25) << aux.at(i)->getNombre();
        ficheroClasificacion << setw(6) << aux.at(i)->getPuntos();
        ficheroClasificacion << setw(4) << aux.at(i)->getVictorias();
        ficheroClasificacion << setw(4) << aux.at(i)->getEmpates();
        ficheroClasificacion << setw(6) << aux.at(i)->getDerrotas();
        ficheroClasificacion << setw(3) << aux.at(i)->getGolesAFavor() << " ";
        ficheroClasificacion << setw(3) << aux.at(i)->getGolesEnContra() << endl;
    }
    ficheroClasificacion.close();

}













//estas tres funciones se han implementado para realizar los ficheros con datos de persona aleatorios. Se han ejecutado una vez para generar los archivos .txt con datos y se
//eliminan del main. Se pueden instanciar en el main si se desea modificar aleatoriamente los datos de los jugadores, representantes, etc. Es necesario previamente un archivo
//que incluya los nombres de las personas. En este caso, se llaman nombresJugadores.txt, nombresRepresentantes.txt y nombresOjeadores.txt

void CompeticionDeFutbol::crearJugadoresAleatorios(void)        // Funcion para generar un fichero con datos de jugadores aleatorios
{                                       // (hace falta un archivo previo con los nombres, sacados aleatoriamente en listofrandomnames.com y guardados en nombresJugadores.txt)
    ofstream archivoJugadores("jugadores.txt");
    ifstream archivoNombresJugadores("nombresJugadores.txt");
    if (!archivoJugadores || !archivoNombresJugadores)
    {
        cout << "Error al abrir los archivos de jugadores" << endl;
    }
    string nombre, posicion;
    int edad;
    int nivelForma, nivelHabilidad;
    for (int i=0; i<140; i++)   //para los 140 jugadores
    {
        nivelForma=rand()%100;
        nivelHabilidad=rand()%100;
        posicion = devolverPosicion(i);
        edad = rand() % 20 + 17;
        getline(archivoNombresJugadores, nombre);       //sacamos un nombre de la lista de nombres que hay guardada

        //estas cuatro condiciones sirven para crear una distribucion gausiana de las habilidades y formas de los jugadores y para que la diferencia entre ellos no sea demasiado grande.
        //cuando el numero sale <50, se multiplica por una funcion logaritmica, y cuando sale >50 se multiplica por una funcion exponencial. Esto nos permite acumular jugadores con
        //habilidades medias en torno a 50, y hacer que los jugadores estrella con ~90 de habilidad o jugadores malos con ~10 de habilidad sean excepciones muy escasas. Los numeros exactos
        //se han calculado tanteando.
        if (nivelForma<50)
        {
            nivelForma=log(1+nivelForma)*12.72;
        }
        else
        {
            nivelForma=(((nivelForma-50)*(nivelForma-50))/50)+50;
        }
        if (nivelHabilidad<50)
        {
            nivelHabilidad=log(1+nivelHabilidad)*12.72;
        }
        else
        {
            nivelHabilidad=(((nivelHabilidad-50)*(nivelHabilidad-50))/50)+50;
        }

        //formato: Nombre Edad Posicion AnosExperiencia NivelHabilidad NivelForma
        archivoJugadores << nombre << edad << " " << posicion << " " << edad - (rand()%10+5) << " " << nivelHabilidad << " " << nivelForma <<endl;
    }
    archivoJugadores.close();
    archivoNombresJugadores.close();
}

//esta funcion devuelve la posicion del jugador en crearJugadoresAleatorios(). Asi garantizamos 20 porteros, 20 defensas, 40 Centros, 20 Delanteros y 40 versatiles.
string devolverPosicion(int i)
{
    if (i%7==0)
    {
        return "Portero";
    }
    if (i%7==1)
    {
        return "Defensa";
    }
    if (i%7==2 || i%7==3)
    {
        return "Centrocampista";
    }
    if (i%7==4)
    {
        return "Delantero";
    }
    else
    {
        return "Versatil";
    }
}

//creamos un archivo de representantes con edades aleatorias a partir de un archivo existente con nombres (sacados de listofrandomnames.com)
void CompeticionDeFutbol::crearRepresentantesAleatorios()
{
    ifstream archivoNombresRepresentantes("nombresRepresentantes.txt");
    ofstream archivoRepresentantes("representantes.txt");
    string nombre;

    if (!archivoRepresentantes || !archivoNombresRepresentantes)
    {
        cout << "Error al abrir los archivos de representantes" << endl;
    }

    for (int i=0; i<140; i++)           //en este bucle sacamos un nombre de nuestra lista de nombres y se le anadimos una edad e identificador. Se guarda en el archivo representantes.txt
    {
        getline(archivoNombresRepresentantes, nombre);
        archivoRepresentantes << nombre << " " << rand() % 40 + 21 << " R" << i << endl;
    }

    archivoNombresRepresentantes.close();
    archivoRepresentantes.close();
}

//creamos un archivo de ojeadores con edades aleatorias a partir de un archivo existente con nombres (sacados de listofrandomnames.com)
void CompeticionDeFutbol::crearOjeadoresAleatorios()
{
    ifstream archivoNombresOjeadores("nombresOjeadores.txt");
    ofstream archivoOjeadores("ojeadores.txt");
    string nombre;

    if (!archivoOjeadores || !archivoNombresOjeadores)
    {
        cout << "Error al abrir los archivos de ojeadores" << endl;
    }

    for (int i=0; i<40; i++)           //en este bucle sacamos un nombre de nuestra lista de nombres y se le anadimos una edad e identificador. Se guarda en el archivo representantes.txt
    {
        getline(archivoNombresOjeadores, nombre);
        archivoOjeadores << nombre << " " << rand() % 40 + 21 << " O" << i << endl;
    }

    archivoNombresOjeadores.close();
    archivoOjeadores.close();
}
