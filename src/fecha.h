#ifndef FECHA_H
#define FECHA_H


class Fecha // con esta clase es mas facil utilizar el formato fecha. Alomejor hay que crear las funciones get day, get month, etc... segun avanzamos el programa.
{           // se lo he copiado al de la foto que me has mandado, y es la mejor manera creo.
public:
    Fecha();
    Fecha(int dia, int mes, int ano);
    Fecha(const Fecha &F);
    void setDia(int dia);
    void setMes(int mes);
    void setAno(int ano);
    int getDia(void);
    int getMes(void);
    int getAno(void);
    ~Fecha(){};
private:
    int _dia;
    int _mes;
    int _ano;
};

#endif // FECHA_H
