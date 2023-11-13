#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "stIngreso.h"

#define ESC 27
#define ARCHIVO_PACIENTES "pacientes.dat"

/// Estructuras:

typedef struct stPaciente {
    char apellidoNombre[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;

} stPaciente;

typedef struct nodoPaciente {
    stPaciente datosPaciente;

    struct nodoIngreso *listaIngresos;

    struct nodoPaciente *izq;
    struct nodoPaciente *der;
} nodoPaciente;

/// Prototipados:

void menuProvisorioGestionarPacientes();
/// Se usa en varias partes:
void textoPresioneCualquierTecla();
/// FUNCIONES PARA LA OPCION 1:
nodoPaciente * inicArbolPacientes();
struct nodoIngreso * inicListaIngresos();
int existeElPaciente(nodoPaciente * arbolPacientes, int dni);
nodoPaciente * crearNodoArbolPaciente(stPaciente datosStPaciente);
nodoPaciente * insertarPaciente(nodoPaciente * arbolPacientes, stPaciente nuevoPaciente);
nodoPaciente * altaDePacientes(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 2:
void muestraUnPaciente(stPaciente datosPaciente);
nodoPaciente * encontrarMinimoDni(nodoPaciente* arbolPacientes);
nodoPaciente * eliminarNodoArbolPacientes(nodoPaciente * arbolPacientes, int dniPaciente);
nodoPaciente * buscaPaciente(nodoPaciente * arbolPacientes, int dni);
void textoDniNoEnBaseDeDatos();
nodoPaciente * modificarDatosPaciente(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 3:
void buscaYDaDeBajaPaciente(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 4:
void inorderPacientes(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 5:
void imprimePacientesInorderEnArchivo(nodoPaciente * arbolPacientes, FILE * archi);
void guardaArbolPacientesEnArchivo(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 6:
void liberarArbolPacientes(nodoPaciente * arbolPacientes);
nodoPaciente * archivoToArbolPacientes(nodoPaciente * arbolPacientes);






#endif // STPACIENTE_H_INCLUDED
