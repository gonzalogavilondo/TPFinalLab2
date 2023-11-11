#ifndef STINGRESO_H_INCLUDED
#define STINGRESO_H_INCLUDED


typedef struct stIngreso
{
    int numeroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
} stIngreso;

typedef struct nodoIngreso
{
    stIngreso ingreso;
    struct nodoPracticaXIngreso *listaPracticasXIngreso;
    struct nodoIngreso *siguiente;
} nodoIngreso;



#endif // STINGRESO_H_INCLUDED
