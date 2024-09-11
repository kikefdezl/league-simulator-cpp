#include "fecha.h"

Fecha::Fecha() // no se va a usar, pero para que quede bonito, en caso de constructor vacio inicializamos a 1/1/2000
{
    _dia=1;
    _mes=1;
    _ano=2000;
}

Fecha::Fecha(int dia, int mes, int ano)
{
    _dia=dia;
    _mes=mes;
    _ano=ano;
}

Fecha::Fecha(const Fecha &F)
{
    _dia=F._dia;
    _mes=F._mes;
    _ano=F._ano;
}

void Fecha::setDia(int dia)
{
    _dia=dia;
}

void Fecha::setMes(int mes)
{
    _mes=mes;
}

void Fecha::setAno(int ano)
{
    _ano=ano;
}

int Fecha::getDia(void)
{
    return _dia;
}

int Fecha::getMes(void)
{
    return _mes;
}

int Fecha::getAno(void)
{
    return _ano;
}
