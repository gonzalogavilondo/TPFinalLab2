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
    int tieneAlMenosUnUso;
    int eliminado;

} stPractica;

typedef struct nodoPractica {

    stPractica datosPractica;

    struct nodoPractica * siguiente;

} nodoPractica;


/// Prototipados:

/// MENU PRINCIPAL GESTION DE PRACTICAS:
void submenuGestionPracticas();
nodoPractica * inicListaPracticas();
void liberarListaPracticas(nodoPractica * listaPracticas);
/// FUNCIONES OPCION 1 DEL MENU 'submenuGestionPracticas':
void mostrarUnNodoPractica(nodoPractica * practica);
void muestraListaPracticas(nodoPractica * listaPracticas);
/// FUNCIONES OPCION 2 DEL MENU 'submenuGestionPracticas':
void manejaVerModificarOBajaDePractica(nodoPractica * listaPracticas, int variante);
nodoPractica * buscaPracticaPorNombre(nodoPractica * listaPracticas, char nombreBusqueda[]);
nodoPractica * buscaPracticaPorNroPractica(nodoPractica * listaPracticas, int numeroPractica);
/// FUNCIONES OPCION 3 DEL MENU 'submenuGestionPracticas':
nodoPractica * darDeAltaPracticas(nodoPractica * listaPracticas);
int tamanioListaPracticas(nodoPractica * listaPracticas);
nodoPractica * agregaNodoPracticaOrdenadoXNombre(nodoPractica * listaPracticas, nodoPractica * nuevoNodo);
nodoPractica * agregarPracticaPpio(nodoPractica * listaPracticas, nodoPractica * nuevoNodo);
nodoPractica * crearNodoPractica(stPractica nuevaPractica);
/// FUNCIONES PARA MANEJO DE ARCHIVO PRACTICAS:
void guardaListaPracticasEnArchivo(nodoPractica * listaPracticas);
nodoPractica * archivoToListaPracticas(nodoPractica * listaPracticas);
/// SE USA EN stPracticaXIngreso.c:
int existePracticaXnroPractica(int nroPracticaBuscar);

#endif // STPRACTICA_H_INCLUDED
