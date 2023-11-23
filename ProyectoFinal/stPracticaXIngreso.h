#ifndef STPRACTICAXINGRESO_H_INCLUDED
#define STPRACTICAXINGRESO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gotoxy.h"
#include "stPaciente.h"

#define ARCHIVO_PRACTICAXINGRESOS "practicaXIngresos.dat"

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

/**
    FUNCIONES BASICAS DE LISTAS
**/
nodoPracticaXIngreso* inicListaPracticaXIngresos();
nodoPracticaXIngreso* crearNodoPracticaXIngreso(stPracticaXIngreso registro);
nodoPracticaXIngreso* agregarNodoPracticaXIngreso(nodoPracticaXIngreso *lista, stPracticaXIngreso registro);
nodoPracticaXIngreso* buscaUltimoLista(nodoPracticaXIngreso *lista);
nodoPracticaXIngreso* crearListaPracticaXIngreso(const char *nombreArchivo);
void mostrarUnNodoPracticaXIngreso(nodoPracticaXIngreso *aux);
void mostrarPracticaXIngreso(nodoPaciente *arbolPacientes, int flag);
void mostrarPracticaXIngreso(nodoPaciente *arbolPacientes, int flag);
nodoPracticaXIngreso* liberarListaPracticaXIngreso(nodoPracticaXIngreso *lista);
nodoPracticaXIngreso* cargarPracticaXIngreso(nodoPracticaXIngreso *lista, int nroIngreso, int nroPractica);

/**
    FUNCIONES DEL PROBLEMA EN SI
**/
void altaDePracticaXIngreso(nodoPaciente *arbolPacientes, int altaIngreso);

///Modificacion de PracticaXIngreso
nodoPracticaXIngreso *buscaPracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos, int nroPractica);
void modificarDatosPracticaXIngreso(nodoPaciente *arbolPacientes);

///Dar de baja una practica por ingreso
void buscaYDaDeBajaPracticaXIngreso(nodoPracticaXIngreso *lista);

void registrarResultadoPracticaXIngreso(nodoPaciente *arbol);
void mostrarUnaPractica(nodoPaciente * arbol);

/// SE USA EN stPaciente.c AL DAR DE BAJA A UN PACIENTE EN CASCADA:
void darDeBajaTodasLasPracticasXIngreso(nodoPracticaXIngreso * listaPracticasXIngreso);

void mostrarUnaPracticaXIngreso(nodoPaciente *arbol);
int cantidadPracticasXIngreso(nodoPaciente * arbol);


#endif // STPRACTICAXINGRESO_H_INCLUDED
