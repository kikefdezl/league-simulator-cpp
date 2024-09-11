#include "partido.h"
#include "equipo.h"
#include "arbitro.h"
#include <random>
#include <time.h>

using namespace std;

Partido::Partido()
{

}

Partido::Partido(Equipo* equipo1,Equipo* equipo2, Arbitro* arbitro)
{
    _equipo1=equipo1;
    _equipo2=equipo2;
    _arbitro=arbitro;
    _resultado[0]=_resultado[1]=0;
}

void Partido::simularPartido(void) //por arreglar, dan resultados curioso (meh)
{
    float nivelAtaque1=0.0, nivelAtaque2=0.0, nivelDefensa1=0.0, nivelDefensa2=0.0;
    float diferencia1, diferencia2;
    _equipo1->convocarJugadores();
    _equipo2->convocarJugadores();
    //portero y defensa //estos bucles calculan los niveles de defensa y ataque de cada tipo en total. Los centrocampistas cuentan para tanto defensa como ataque (0.5 en cada uno)
    for (int i=0; i<2; i++)
    {
        nivelDefensa1+=float(_equipo1->getConvocado(i)->getNivelHabilidad()+0.5*_equipo1->getConvocado(i)->getNivelForma());
        nivelDefensa2+=float(_equipo2->getConvocado(i)->getNivelHabilidad()+0.5*_equipo2->getConvocado(i)->getNivelForma());
    }
    //centrocampistas
    for (int i=2; i<4; i++)
    {
        nivelDefensa1+=float(0.5*(_equipo1->getConvocado(i)->getNivelHabilidad()+0.5*_equipo1->getConvocado(i)->getNivelForma()));
        nivelDefensa2+=float(0.5*(_equipo2->getConvocado(i)->getNivelHabilidad()+0.5*_equipo2->getConvocado(i)->getNivelForma()));
        nivelAtaque1+=float(0.5*(_equipo1->getConvocado(i)->getNivelHabilidad()+0.5*_equipo1->getConvocado(i)->getNivelForma()));
        nivelAtaque2+=float(0.5*(_equipo2->getConvocado(i)->getNivelHabilidad()+0.5*_equipo2->getConvocado(i)->getNivelForma()));
    }
    //delantero
    nivelAtaque1+=float(_equipo1->getConvocado(4)->getNivelHabilidad()+0.5*_equipo1->getConvocado(4)->getNivelForma());
    nivelAtaque2+=float(_equipo2->getConvocado(4)->getNivelHabilidad()+0.5*_equipo2->getConvocado(4)->getNivelForma());

    //calculamos las diferencias entre ataques de un equipo y defensas del opuesto (defensa*0.66 por ser un jugador mas)
    diferencia1=(nivelAtaque1-0.66*(nivelDefensa2)+300);        //estas diferencias nos devuelven un numero entre 0 y 600. Aunque en el 99% de los casos se va a comprender entre
    diferencia2=(nivelAtaque2-0.66*(nivelDefensa1)+300);        // 200 y 400, dado que los jugadores se han creado con una distribucion gausiana centrada en 50. La idea es, que cada 20
                                                                // puntos de diferencia se da una ocasion de gol, y cada ocasion de gol tiene un 8% de probabilidades de convertirse en gol.
    do
    {
        if (rand()%100<8)       //cada iteracion (ocasion de gol) tiene un 4% de probabilidad de ser gol
        {
            _resultado[0]++;
        }
        diferencia1-=20;
    }
    while(diferencia1>0);       //la condicion del bucle nos permite iterar hasta agotar las ocasiones de gol
    do      //igual con la segunda diferencia
    {
        if (rand()%100<8)
        {
            _resultado[1]++;
        }
        diferencia2-=20;
    }
    while(diferencia2>0);
}
