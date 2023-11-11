#ifndef STPRACTICAXINGRESO_H_INCLUDED
#define STPRACTICAXINGRESO_H_INCLUDED


typedef struct stPracticaXIngreso
{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
    int eliminado;
} stPracticaXIngreso;

typedef struct nodoPracticaXIngreso
{
    stPracticaXIngreso practicaXIngreso;
    struct nodoPracticaXIngreso *siguiente;
} nodoPracticaXIngreso;

#endif // STPRACTICAXINGRESO_H_INCLUDED
