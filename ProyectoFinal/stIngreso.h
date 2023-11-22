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
#include "gotoxy.h"

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
nodoIngreso* inicListaIngresos();
nodoIngreso* crearNodoIngreso(stIngreso registro);
nodoIngreso* agregarNodoIngreso(nodoIngreso *lista, stIngreso registro);
nodoIngreso* buscaUltimoListaIngresos(nodoIngreso *lista);
nodoIngreso* crearListaIngresos(const char *nombreArchivo);
void mostrarUnNodoIngreso(nodoIngreso *aux);
void mostrarListadoGralIngresos(nodoPaciente *arbolPacientes, int flag); //Si flag == 1 entonces lo llama el administrador
void mostrarListadoIngresosPaciente(nodoPaciente *paciente);
nodoIngreso* liberarListaIngresos(nodoIngreso *lista);
int cantidadNodosListaIngresos(nodoIngreso * lista);
nodoIngreso* cargarIngreso(nodoIngreso *lista, int dni);

/**
    FUNCIONES ESPECIFICAS DEL PROBLEMA
**/
void obtenerFechaActual(char fechaActual[11]);
stPractica obtenerPracticaLaboratorio();
void altaDeIngreso(nodoPaciente *arbolPacientes);

///Modificar datos de ingreso
void modificarDatosIngreso(nodoPaciente * arbolPacientes);
nodoIngreso *buscaIngreso(nodoIngreso *listaIngresos, int nroIngreso);

///Buscar y dar de baja un ingreso
void buscaYDaDeBajaIngreso(nodoPaciente *arbolPacientes);

///Adicionales para la funcionalidad
void generarArchivoBinIngresos(const char *nombreArchivo);
//int existeIngresoXnroIngreso(int nroIngresoBuscar);


#endif // STINGRESO_H_INCLUDED
