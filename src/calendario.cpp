#include "calendario.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include "jugador.h"

using namespace std;

Calendario::Calendario()
{

}

Calendario::Calendario(Fecha &fechaInicio, int numeroJornadas, vector <Equipo*> equipos, vector <Arbitro*> arbitros)
{
    _fechaInicio=fechaInicio;
    _numeroJornadas=numeroJornadas;
    _equipos=equipos;
    _arbitros=arbitros;
    generarJornadas();
    generarEnfrentamientos();
    generarFicheroCalendario();
}

void Calendario::generarJornadas(void) //para simplificar, todos los meses son de 30 dias. Calculamos una jornada cada 7 dias y las metemos en el vector de jornadas
{
    Fecha fechaProvisional(_fechaInicio);
    int i=1;
    while(i<39)     //38 jornadas
    {
        _jornadas.push_back(new Jornada(fechaProvisional, _equipos, _arbitros));      //anadimos la fecha de cada iteracion del bucle al vector de jornadas
        if(fechaProvisional.getDia()<24)
        {
            fechaProvisional.setDia(fechaProvisional.getDia()+7); //Si estamos a mas de 7 dias del final de mes, tan solo anadimos 7 dias
        }
        else
        {
            fechaProvisional.setDia(fechaProvisional.getDia()-23);      //Si quedan menos de 7 dias para el final del mes, el nuevo dia del mes es el actual -23
            if(fechaProvisional.getMes()<12)
            {
                fechaProvisional.setMes(fechaProvisional.getMes()+1);   //Si no es diciembre, anadimos un mes al mes actual
            }
            else
            {
                fechaProvisional.setMes(1);
                fechaProvisional.setAno(fechaProvisional.getAno()+1);       //Si es diciembre, pasamos a Enero y anadimos un ano al ano actual
            }
        }
        i++;        //incrementamos variable del bucle   
    }
    _fechaFinal=fechaProvisional;       //guardamos la fecha del final de temporada
}

void Calendario::generarFicheroCalendario()
{
    ofstream ficheroCalendario;
    ficheroCalendario.open("calendario.txt");
    for (int i=0; i<38; i++)
    {
        ficheroCalendario << "Jornada " << i+1 << ": " << getJornada(i)->getFecha().getDia() << "/" << getJornada(i)->getFecha().getMes() << "/" << getJornada(i)->getFecha().getAno() << endl;
    }
    ficheroCalendario.close();
}

void Calendario::generarEnfrentamientos()       //se han generado mediante el algoritmo 'Round-Robin'
{
    int robin[10][2];
    int aux;
    int x=1;
    for (int jor=0; jor<19; jor++)
    {
            for (int i=0; i<10; i++)
            {
                if(i==0)
                {
                    robin[0][0]=0;
                }
                else
                {
                    robin[i][0]=x;
                    x++;
                }
                if(x==20)
                {
                    x=1;
                }
            }
            for (int i=9; i>=0; i--)
            {
                robin[i][1]=x;
                x++;
                if(x==20)
                {
                    x=1;
                }
            }
        x--;
        if(x==0)
        {
            x=19;
        }
        // hasta aqui se ejecuta el algoritmo round robin y se deposita en el array robin

        if(jor%2!=0)        //cada 2 jornadas se hace un swap local-visitante para garantizar que no se juegue mas de 3 veces seguidas fuera de casa o en casa
        {
            for (int i=0; i<10; i++)
            {
                aux=robin[i][0];
                robin[i][0]=robin[i][1];
                robin[i][1]=aux;
            }
        }

        //por ultimo creamos nuestros partidos con los enfrentamientos obtenidos mediante el algoritmo round-robin
        for (int part=0; part<10; part++)
        {
            getJornada(jor)->pushPartido(new Partido(getEquipo(robin[part][0]), getEquipo(robin[part][1]), getArbitro(rand()%15)));
            //segunda vuelta de la competicion
            getJornada(jor+19)->pushPartido(new Partido(getEquipo(robin[part][1]), getEquipo(robin[part][0]), getArbitro(rand()%15)));
        }
    }
}


