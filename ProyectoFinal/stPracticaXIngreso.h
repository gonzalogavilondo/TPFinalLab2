#ifndef STPRACTICAXINGRESO_H_INCLUDED
#define STPRACTICAXINGRESO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

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
void mostrarPracticaXIngreso(nodoPracticaXIngreso *lista);
nodoPracticaXIngreso* liberarListaPracticaXIngreso(nodoPracticaXIngreso *lista);
nodoPracticaXIngreso* cargarPracticaXIngreso(nodoPracticaXIngreso *lista, int nroIngreso, int nroPractica);

/**
    FUNCIONES DEL PROBLEMA EN SI
**/
nodoPracticaXIngreso* altaDePracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos);

///Modificacion de PracticaXIngreso
nodoPracticaXIngreso *buscaPracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos, int nroPractica);
nodoPracticaXIngreso *modificarDatosPracticaXIngreso(nodoPracticaXIngreso *lista);

///Dar de baja una practica por ingreso
void buscaYDaDeBajaPracticaXIngreso(nodoPracticaXIngreso *lista);

#endif // STPRACTICAXINGRESO_H_INCLUDED
