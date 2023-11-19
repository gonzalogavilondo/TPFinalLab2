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
#define ARCHIVO_INGRESOS "ingresos.dat"

typedef struct stIngreso
{
    int numeroIngreso;
    char fechaIngreso[11]; //Por defecto, la actual
    char fechaRetiro[11];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
} stIngreso;

typedef struct nodoIngreso
{
    stIngreso ingreso;
    nodoPracticaXIngreso *listaPracticasXIngreso;
    struct nodoIngreso *siguiente;
} nodoIngreso;

/**
    FUNCIONES BASICAS DE LISTAS
**/
nodoIngreso* inicLista();
nodoIngreso* crearNodoIngreso(stIngreso registro);
nodoIngreso* agregarNodoIngreso(nodoIngreso *lista, stIngreso registro);
nodoIngreso* buscaUltimoListaIngresos(nodoIngreso *lista);
nodoIngreso* crearListaIngresos(const char *nombreArchivo);
void mostrarUnNodo(nodoIngreso *aux);
void mostrarIngreso(nodoIngreso *lista);
nodoIngreso* liberarListaIngresos(nodoIngreso *lista);
nodoIngreso* cargarIngreso(nodoIngreso *lista);

/**
    FUNCIONES ESPECIFICAS DEL PROBLEMA
**/
void obtenerFechaActual(char fechaActual[11]);
int obtenerNuevoNumeroIngreso();
stPractica obtenerPracticaLaboratorio();
nodoIngreso* altaDeIngreso(nodoIngreso *listaIngresos, nodoPracticaXIngreso *nuevaPracticaXIngreso);
void Modificacion_de_ingreso(nodoIngreso *listaIngresos, int numeroIngreso, char nuevaFechaIngreso[10], char nuevaFechaRetiro[10], int nuevaMatriculaProfesional);
void Baja_de_ingreso(nodoIngreso **listaIngresos, int numeroIngreso);
void generarArchivoBinIngresos(const char *nombreArchivo);
int existeIngresoXnroIngreso(int nroIngresoBuscar);


#endif // STINGRESO_H_INCLUDED
