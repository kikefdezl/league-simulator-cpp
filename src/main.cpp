// Grupo 14
// David Rojo Peña
// Enrique Fernandez-Laguilhoat Sanchez-Biezma

//Es necesario incluir los archivos .txt en la carpeta 'build' que se genera al compilar el proyecto. Si no, no se abren y da error.

#include <iostream>
#include "competiciondefutbol.h"
#include <vector>
#include "time.h"

using namespace std;


int main()
{
    srand(time(NULL));
    CompeticionDeFutbol LFP("LFP", "Liga de Puntos");   //creacion de la competicion
    LFP.simularCompeticion();       //simulacion de la competicion (incluye inicializacion)
    return 0;
}



