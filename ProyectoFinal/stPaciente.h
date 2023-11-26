#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>


/// Constantes:

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

/// Se usa en varias partes:
void textoPresioneCualquierTecla();
void textoPresioneCualquierTecla2();
/// MENU PRINCIPAL GESTION DE PACIENTES:
void submenuGestionPacientes(nodoPaciente * arbolPacientes, int flag);
/// FUNCIONES OPCION 1 DEL MENU 'submenuGestionPacientes':
void submenuBuscaPacienteYMuestraDatos(nodoPaciente * arbolPacientes, int flag);
nodoPaciente * inicArbolPacientes();
nodoPaciente * buscaPaciente(nodoPaciente * arbolPacientes, int dni);
void muestraUnPaciente(stPaciente datosPaciente);
void textoDniNoEnBaseDeDatos();
/// FUNCIONES OPCION 2 DEL MENU 'submenuGestionPacientes':
void submenuModificarDatosPaciente(nodoPaciente * arbolPacientes, int flag);
void muestraUnPacienteEnRectangulo(stPaciente datosPaciente);
int existeElPaciente(nodoPaciente * arbolPacientes, int dni);
nodoPaciente * eliminarNodoArbolPacientes(nodoPaciente * arbolPacientes, int dniPaciente);
nodoPaciente * encontrarMinimoDni(nodoPaciente* arbolPacientes);
nodoPaciente * insertarPaciente(nodoPaciente * arbolPacientes, stPaciente nuevoPaciente);
nodoPaciente * crearNodoArbolPaciente(stPaciente datosStPaciente);
/// FUNCIONES OPCION 3 DEL MENU 'submenuGestionPacientes':
nodoPaciente * altaDePaciente(nodoPaciente * arbolPacientes);
int consultaDniYVerifica();
/// FUNCIONES OPCION 4 DEL MENU 'submenuGestionPacientes':
void submenuDarDeBajaUnPaciente(nodoPaciente * arbolPacientes, int flag);
/// FUNCIONES OPCION 5 DEL MENU 'submenuGestionPacientes':
void submenuElijeOrdenamientoPacientes(nodoPaciente * arbolPacientes, int flag);
void inorderPacientes(nodoPaciente * arbolPacientes, int flag);
int cantidadNodosArbolPacientes(nodoPaciente * arbolPacientes);
void pacienteToArregloOrdenadoXApellidoNombre(stPaciente * arreglo, int validosArre, stPaciente datosPaciente);
void recorreArbolEIngresaEnArregloXApellidoNombre(nodoPaciente * arbolPacientes, stPaciente * arreglo, int * validosArre);
stPaciente * arbolPacientesToArreglo(nodoPaciente * arbolPacientes);
void muestraArregloPacientes(stPaciente arregloPacientes[], int validosArre, int flag);
void imprimePacientesOrdenadosPorApellido(nodoPaciente * arbolPacientes, int flag);
/// FUNCIONES PARA MANEJO DE ARCHIVO PACIENTES:
void imprimePacientesInorderEnArchivo(nodoPaciente * arbolPacientes, FILE * archi);
void guardaArbolPacientesEnArchivo(nodoPaciente * arbolPacientes);
void liberarArbolPacientes(nodoPaciente * arbolPacientes);
nodoPaciente * archivoToArbolPacientes(nodoPaciente * arbolPacientes);
///FUNCION QUE LA USA INGRESOS:
int existePacienteXDNI(int dniBuscar);
void muestraUnPacienteResumido(stPaciente datosPaciente);
///FUNCIONES QUE LAS USA PRACTICAXINGRESO:
int existeIngresoXnroIngreso(nodoPaciente *arbolPacientes, int nroIngresoBuscar);
int existeIngreso(nodoPaciente *arbolPacientes);

#endif // STPACIENTE_H_INCLUDED
