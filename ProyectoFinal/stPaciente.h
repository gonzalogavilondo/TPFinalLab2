#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED

typedef struct stPaciente
{
    char apellidoNombre[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;
} stPaciente;

typedef struct nodoPaciente
{
    stPaciente datosPaciente;
    struct nodoIngreso *listaIngresos;
    struct nodoPaciente *izq;
    struct nodoPaciente *der;
} nodoPaciente;


#endif // STPACIENTE_H_INCLUDED
