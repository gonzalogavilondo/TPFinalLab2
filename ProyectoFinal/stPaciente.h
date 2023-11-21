#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


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

void menuProvisorioGestionarPacientes();
/// Se usa en varias partes:
void textoPresioneCualquierTecla();
void textoPresioneCualquierTecla2();
/// MENU PRINCIPAL GESTION DE PACIENTES:
void submenuGestionPacientes(nodoPaciente * arbolPacientes);
/// FUNCIONES OPCION 1 DEL MENU 'submenuGestionPacientes':
void submenuBuscaPacienteYMuestraDatos(nodoPaciente * arbolPacientes);
nodoPaciente * inicArbolPacientes();
nodoPaciente * buscaPaciente(nodoPaciente * arbolPacientes, int dni);
nodoPaciente * textoIngreseDNILuegoBuscaPaciente2(nodoPaciente * arbolPacientes, int * dni);
void muestraUnPaciente(stPaciente datosPaciente);
void textoDniNoEnBaseDeDatos2();
/// FUNCIONES OPCION 2 DEL MENU 'submenuGestionPacientes':
void submenuModificarDatosPaciente(nodoPaciente * arbolPacientes);
void muestraUnPacienteEnRectangulo(stPaciente datosPaciente);
int existeElPaciente(nodoPaciente * arbolPacientes, int dni);
nodoPaciente * eliminarNodoArbolPacientes(nodoPaciente * arbolPacientes, int dniPaciente);
nodoPaciente * encontrarMinimoDni(nodoPaciente* arbolPacientes);
nodoPaciente * insertarPaciente(nodoPaciente * arbolPacientes, stPaciente nuevoPaciente);
nodoPaciente * crearNodoArbolPaciente(stPaciente datosStPaciente);
/// FUNCIONES OPCION 3 DEL MENU 'submenuGestionPacientes':
nodoPaciente * altaDePaciente(nodoPaciente * arbolPacientes);
/// FUNCIONES OPCION 4 DEL MENU 'submenuGestionPacientes':
void submenuDarDeBajaUnPaciente(nodoPaciente * arbolPacientes);
/// FUNCIONES OPCION 5 DEL MENU 'submenuGestionPacientes':
void submenuElijeOrdenamientoPacientes(nodoPaciente * arbolPacientes);
int cantidadNodosArbolPacientes(nodoPaciente * arbolPacientes);
void pacienteToArregloOrdenadoXApellidoNombre(stPaciente * arreglo, int validosArre, stPaciente datosPaciente);
void recorreArbolEIngresaEnArregloXApellidoNombre(nodoPaciente * arbolPacientes, stPaciente * arreglo, int * validosArre);
stPaciente * arbolPacientesToArreglo(nodoPaciente * arbolPacientes);
void muestraArregloPacientes(stPaciente arregloPacientes[], int validosArre);
void imprimePacientesOrdenadosPorApellido(nodoPaciente * arbolPacientes);








/// FUNCIONES PARA LA OPCION 2: menu viejo, PARA CAMBIAR ----------------------------------------------------
void textoDniNoEnBaseDeDatos();
nodoPaciente * textoIngreseDNILuegoBuscaPaciente(nodoPaciente * arbolPacientes, int * dni);
/// FUNCIONES PARA LA OPCION 5: menu viejo, PARA CAMBIAR ----------------------------------------------------
void inorderPacientes(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 6: menu viejo, PARA CAMBIAR ----------------------------------------------------
void imprimePacientesInorderEnArchivo(nodoPaciente * arbolPacientes, FILE * archi);
void guardaArbolPacientesEnArchivo(nodoPaciente * arbolPacientes);
/// FUNCIONES PARA LA OPCION 7: menu viejo, PARA CAMBIAR ----------------------------------------------------
void liberarArbolPacientes(nodoPaciente * arbolPacientes);
nodoPaciente * archivoToArbolPacientes(nodoPaciente * arbolPacientes);






///FUNCION QUE LA USA INGRESOS:
int existePacienteXDNI(int dniBuscar);
void muestraUnPacienteResumido(stPaciente datosPaciente);
///FUNCIONES QUE LAS USA PRACTICAXINGRESO:
int existeIngresoXnroIngreso(nodoPaciente *arbolPacientes, int nroIngresoBuscar);

#endif // STPACIENTE_H_INCLUDED
