#ifndef STINGRESO_H_INCLUDED
#define STINGRESO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conio.h"
#include "stEmpleado.h"
#include "stPractica.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"

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

void obtenerFechaActual(char fechaActual[10]);
int obtenerNuevoNumeroIngreso();
stPractica obtenerPracticaLaboratorio();
int obtenerNuevoIdPracticaXIngreso();
void Alta_de_ingreso(nodoIngreso **listaIngresos, struct stPaciente paciente, stEmpleado profesional);
void Modificacion_de_ingreso(nodoIngreso *listaIngresos, int numeroIngreso, char nuevaFechaIngreso[10], char nuevaFechaRetiro[10], int nuevaMatriculaProfesional);
void Baja_de_ingreso(nodoIngreso **listaIngresos, int numeroIngreso);


#endif // STINGRESO_H_INCLUDED
