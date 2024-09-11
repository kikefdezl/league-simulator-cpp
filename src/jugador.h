#ifndef JUGADOR_H
#define JUGADOR_H
#include <iostream>
#include "persona.h"
#include "representante.h"

using namespace std;

class Jugador : public Persona
{
public:
    Jugador();
    Jugador(string nombre, int edad, int anosExperiencia, int nivelHabilidad, int nivelForma, string posicion);
    void setSancionado(bool x){_sancionado=x;}
    int getSanciones(){return _sanciones;}
    bool getSancionado(){return _sancionado;}
    void addSancion(){_sanciones+=1;}
    void setLesionado(bool x){_lesionado=x;}
    bool getLesionado(){return _lesionado;}
    void asignarRepresentante(void);
    Representante* getRepresentante(){return _representante;}
    float getNivelHabilidad(){return _nivelHabilidad;}
    float getNivelForma(){return _nivelForma;}
    string getPosicion(){return _posicion;}
    int getAnosExperiencia(){return _anosExperiencia;}
    void addGolMarcado(){_golesMarcados+=1;}
    int getGolesMarcados(){return _golesMarcados;}
    bool getYaConvocado(){return _convocado;}
    void setYaConvocado(){_convocado=1;}
    void resetYaConvocado(){_convocado=0;}
    bool puedeJugar();
    int getJornadasSancionadoOLesionado(){return _jornadasSancionadoOLesionado;}
    void addJornadaSancionadoOLesionado(){_jornadasSancionadoOLesionado+=1;}
    void resetJornadasSancionadoOLesionado(){_jornadasSancionadoOLesionado=0;}
    ~Jugador(){};
protected:
    string _posicion;
    float _nivelHabilidad, _nivelForma;
    int _anosExperiencia;
    bool _lesionado, _sancionado, _convocado;
    Representante* _representante;
    int _golesMarcados, _sanciones;
    int _jornadasSancionadoOLesionado;

};

#endif // JUGADOR_H
