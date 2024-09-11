#include "partido.h"
#include "competiciondefutbol.h"
#include <random>
#include <time.h>
#include <vector>

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


//funcion que simula todos los acontecimientos en un partido. Probablemente la mas importante y muy extensa.
//utiliza metodos aleatorios que favorecen a los equipos y jugadores fuertes, pero posibilitan victorias de equipos menores en casos excepcionales.
void Partido::simularPartido(void)
{
    float nivelAtaque1=0.0, nivelAtaque2=0.0, nivelDefensa1=0.0, nivelDefensa2=0.0;
    float diferencia1, diferencia2;

    //seleccionamos jugadores aptos para jugar el partido
    _equipo1->convocarJugadores();
    _equipo2->convocarJugadores();

    //introducimos los jugadores convocados en la alineacion, para mantenerlos en memoria y poder acceder a los jugadores que han jugado la jornada
    _alineacion1.clear();
    _alineacion2.clear();
    for(int i=0; i<5; i++)
    {
        _alineacion1.push_back(_equipo1->getConvocado(i));
        _alineacion2.push_back(_equipo2->getConvocado(i));
    }

    //primero calculamos los niveles de defensa y ataque de cada equipo en total. Consideramos los centrocampistas como ataque y defensa, pero contribuyen un 50% en puntos a cada uno
    //portero y defensa
    for (int i=0; i<2; i++)
    {
        nivelDefensa1+=float(_alineacion1.at(i)->getNivelHabilidad()+0.5*_alineacion1.at(i)->getNivelForma());
        nivelDefensa2+=float(_alineacion2.at(i)->getNivelHabilidad()+0.5*_alineacion2.at(i)->getNivelForma());
    }
    //centrocampistas
    for (int i=2; i<4; i++)
    {
        nivelDefensa1+=float(0.5*(_alineacion1.at(i)->getNivelHabilidad()+0.5*_alineacion1.at(i)->getNivelForma()));
        nivelDefensa2+=float(0.5*(_alineacion2.at(i)->getNivelHabilidad()+0.5*_alineacion2.at(i)->getNivelForma()));
        nivelAtaque1+=float(0.5*(_alineacion1.at(i)->getNivelHabilidad()+0.5*_alineacion1.at(i)->getNivelForma()));
        nivelAtaque2+=float(0.5*(_alineacion2.at(i)->getNivelHabilidad()+0.5*_alineacion2.at(i)->getNivelForma()));
    }
    //delantero
    nivelAtaque1+=float(_alineacion1.at(4)->getNivelHabilidad()+0.5*_alineacion1.at(4)->getNivelForma());
    nivelAtaque2+=float(_alineacion2.at(4)->getNivelHabilidad()+0.5*_alineacion2.at(4)->getNivelForma());

    //calculamos las diferencias entre ataques de un equipo y defensas del opuesto (defensa*0.66 por ser un jugador mas en total)
    //estas diferencias nos devuelven un numero entre 0 y 600. Aunque en el 99% de los casos se va a comprender entre
    //200 y 400, dado que los jugadores se han creado con una distribucion gausiana centrada en 50.
    //La mecanica que simula los partidas, consiste en que cada 10 puntos de diferencia se da una ocasion de gol, y cada ocasion de gol tiene un porcentaje de probablidad en convertirse en
    //gol que depende de la propia diferencia. Por lo tanto, un equipo fuerte tendra mas ocasiones para meter gol, y mas probabilidad de convertirlas en gol.
    //El equipo que juega en casa tiene 40 puntos mas (4 ocasiones de gol) por la ventaja de local.
    diferencia1=(nivelAtaque1-0.66*(nivelDefensa2)+340);
    diferencia2=(nivelAtaque2-0.66*(nivelDefensa1)+300);

    //a continuacion, para los dos equipos, simulamos las ocasiones de gol. Se trata de un bucle donde cada iteracion tiene una pequena probabilidad de anadir un gol al marcador.
    //El porcentaje depende de la fuerza del equipo. (Suele estar entre el 3% y el 6%).
    do
    {
        if (rand()%100<(diferencia1/60))       //ademas de tener mas ocasiones, los equipos mas fuertes tienen mas oportunidades de convertir en gol esas ocasiones. Por lo tanto, el
        {                                       //porcentaje que define la probabilidad de que una ocasion sea gol, depende de la fuerza de cada equipo.
            _resultado[0]++;
            getEquipo1()->addGolAFavor();
            getEquipo2()->addGolEnContra();
        }
        diferencia1-=10;
    }
    while(diferencia1>0);       //la condicion del bucle nos permite iterar hasta agotar las ocasiones de gol
    do                                          //repetimos el mismo prodedimiento para el segundo equipo
    {
        if (rand()%100<(diferencia2)/60)
        {
            _resultado[1]++;
            getEquipo1()->addGolEnContra();
            getEquipo2()->addGolAFavor();
        }
        diferencia2-=10;
    }
    while(diferencia2>0);

    //una vez se ha obtenido el resultado del equipo, se reparten los goles teniendo en cuenta el nivel de habilidad de cada jugador, y tambien
    //teniendo en cuenta la posicion. Delanteros 0.7, Centros 0.5, Defensa 0.3 y Portero 0.01 (probabilidad). Se multiplica el nivel de habilidad del jugador
    //por este porcentaje para obtener un indice y se genera un numero aleatorio. Si el numero es menor que el indice, se adjudica un gol al jugador. Es un bucle infinito que se saldra
    //cuando se haya asignado el gol. Asi, la mayoria de goles caeran en los jugadores buenos y en posiciones goleadoras. Se realiza una vez para cada equipo.
    for (int i=0; i<_resultado[0]; i++)
    {
        while(1)
        {
            if((_alineacion1.at(4)->getNivelHabilidad()*0.7)>rand()%100)     //delantero
            {
                _alineacion1.at(4)->addGolMarcado();
                _goleadores1.push_back(_alineacion1.at(4));
                break;
            }
            if((_alineacion1.at(3)->getNivelHabilidad()*0.5)>rand()%100)     //centrocampista
            {
                _alineacion1.at(3)->addGolMarcado();
                _goleadores1.push_back(_alineacion1.at(3));
                break;
            }
            if((_alineacion1.at(2)->getNivelHabilidad()*0.5)>rand()%100)     //centrocampista
            {
                _alineacion1.at(2)->addGolMarcado();
                _goleadores1.push_back(_alineacion1.at(2));
                break;
            }
            if((_alineacion1.at(1)->getNivelHabilidad()*0.3)>rand()%100)     //defensa
            {
                _alineacion1.at(1)->addGolMarcado();
                _goleadores1.push_back(_alineacion1.at(1));
                break;
            }
            if((_alineacion1.at(0)->getNivelHabilidad()*0.01)>rand()%100)    //portero
            {
                _alineacion1.at(0)->addGolMarcado();
                _goleadores1.push_back(_alineacion1.at(0));
                break;
            }
        }
    }
    //igual para el equipo visitante
    for (int i=0; i<_resultado[1]; i++)
    {
        int ok=0;
        while(ok==0)
        {
            if((_alineacion2.at(4)->getNivelHabilidad()*0.7)>rand()%100)
            {
                _alineacion2.at(4)->addGolMarcado();
                _goleadores2.push_back(_alineacion2.at(4));
                break;
            }
            if((_alineacion2.at(3)->getNivelHabilidad()*0.5)>rand()%100)
            {
                _alineacion2.at(3)->addGolMarcado();
                _goleadores2.push_back(_alineacion2.at(3));
                break;
            }
            if((_alineacion2.at(2)->getNivelHabilidad()*0.5)>rand()%100)
            {
                _alineacion2.at(2)->addGolMarcado();
                _goleadores2.push_back(_alineacion2.at(2));
                break;
            }
            if((_alineacion2.at(1)->getNivelHabilidad()*0.3)>rand()%100)
            {
                _alineacion2.at(1)->addGolMarcado();
                _goleadores2.push_back(_alineacion2.at(1));
                break;
            }
            if((_alineacion2.at(0)->getNivelHabilidad()*0.01)>rand()%100)
            {
                _alineacion2.at(0)->addGolMarcado();
                _goleadores2.push_back(_alineacion2.at(0));
                break;
            }
        }
    }

    //reparto de puntos
    if (_resultado[0]>_resultado[1])
    {
        getEquipo1()->addPuntos(3);
        getEquipo1()->addVictoria();
        getEquipo2()->addDerrota();
    }
    else
    {
        if (_resultado[0]<_resultado[1])
        {
            getEquipo2()->addPuntos(3);
            getEquipo2()->addVictoria();
            getEquipo1()->addDerrota();
        }
        else
        {
            getEquipo1()->addPuntos(1);
            getEquipo2()->addPuntos(1);
            getEquipo1()->addEmpate();
            getEquipo2()->addEmpate();
        }
    }

    //simulacion de sanciones
    //se hace un bucle que da un 20% de probabilidades a cada jugador de ser sancionado. Se empieza por los defensas por lo que tienen mas probabilidades de ser sancionadas las posiciones
    //defensivas. Los porteros no se pueden sancionar en esta simulacion.
    for (int i=1; i<5; i++)
    {
        if(rand()%100<20)
        {
            getArbitro()->sancionar(_alineacion1.at(i));
            _alineacion1.at(i)->addSancion();
            _jugadoresSancionados.push_back(_alineacion1.at(i));
            break;
        }
    }
    for (int i=1; i<5; i++)
    {
        if(rand()%100<20)
        {
            getArbitro()->sancionar(_alineacion2.at(i));
            _alineacion2.at(i)->addSancion();
            _jugadoresSancionados.push_back(_alineacion2.at(i));
            break;
        }
    }

    //repetimos el proceso con los lesionados. Cambiamos la probabilidad al 5%
    for (int i=1; i<5; i++)
    {
        if(rand()%100<5)
        {
            _alineacion1.at(i)->setLesionado(1);
            _jugadoresLesionados.push_back(_alineacion1.at(i));
            break;
        }
    }
    for (int i=1; i<5; i++)
    {
        if(rand()%100<5)
        {
            _alineacion2.at(i)->setLesionado(1);
            _jugadoresLesionados.push_back(_alineacion2.at(i));
            break;
        }
    }

}
