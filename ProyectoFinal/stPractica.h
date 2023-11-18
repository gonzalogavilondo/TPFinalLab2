#ifndef STPRACTICA_H_INCLUDED
#define STPRACTICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


/// Constantes:

#define ESC 27
#define ARCHIVO_PRACTICAS "practicas.dat"


/// Estructuras:

typedef struct stPractica {

    int nroPractica;
    char nombrePractica[30];
    int eliminado;

} stPractica;

typedef struct nodoPractica {

    stPractica datosPractica;

    struct nodoPractica * siguiente;

} nodoPractica;


/// Prototipados:

void menuProvisorioGestionarPracticas();
/// FUNCIONES PARA LA OPCION 1:
nodoPractica * inicListaPracticas();
nodoPractica * crearNodoPractica(stPractica nuevaPractica);
int tamanioListaPracticas(nodoPractica * listaPracticas);
nodoPractica * agregarPracticaPpio(nodoPractica * listaPracticas, nodoPractica * nuevoNodo);
nodoPractica * agregaNodoPracticaOrdenadoXNombre(nodoPractica * listaPracticas, nodoPractica * nuevoNodo);
int existePractica(nodoPractica * listaPracticas, char nombrePractica[]);
nodoPractica * darDeALtaPracticas(nodoPractica * listaPracticas);







#endif // STPRACTICA_H_INCLUDED
