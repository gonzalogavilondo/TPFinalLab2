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
nodoPractica * buscaPracticaPorNombre(nodoPractica * listaPracticas, char nombreBusqueda[]);
nodoPractica * darDeAltaPracticas(nodoPractica * listaPracticas);
/// FUNCIONES PARA LA OPCION 2 Y 3:
nodoPractica * buscaPracticaPorNroPractica(nodoPractica * listaPracticas, int numeroPractica);
void manejaModificarOBajaDePractica(nodoPractica * listaPracticas, int variante);
/// FUNCIONES PARA LA OPCION 4:
void mostrarUnNodoPractica(nodoPractica * practica);
void muestraListaPacientes(nodoPractica * listaPracticas);
/// FUNCIONES PARA LA OPCION 5:
void guardaListaPracticasEnArchivo(nodoPractica * listaPracticas);
/// FUNCIONES PARA LA OPCION 6:
void liberarListaPracticas(nodoPractica * listaPracticas);
nodoPractica * archivoToListaPracticas(nodoPractica * listaPracticas);
/// SE USA EN stPracticaXIngreso.c:
int existePracticaXnroPractica(int nroPracticaBuscar);


#endif // STPRACTICA_H_INCLUDED
