#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gotoxy.h"
#include "stEmpleado.h"
#include "stIngreso.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"

void submenuManejoEmpleados();
void menuAltaDeEmpleado(char tipoEmpleadoEjecuta[]);
void menuBajaDeEmpleado(char tipoEmpleadoEjecuta[]);
void cabeza(char a[]);
void imprimirCabecera(char cabecera[]);
void Rectangulo();
void modificarPerfilEmpleadoXDNI(char perfil[],int dni);
void modificarContraseniaEmpleadoXDNI(char contrasenia[],int dni);
void submenuManejoIngresos(nodoPaciente *arbolPaciente);
void submenuManejoPracticasXIngreso(nodoPaciente *arbolPacientes);
void submenuAdministrativo(nodoPaciente * arbolPacientes);
void submenuElijeOrdenamientoPacientes(nodoPaciente * arbolPacientes);
void submenuGestionPacientes(nodoPaciente * arbolPacientes);
void submenuAdministrador(nodoPaciente * arbolPacientes);
void menuPrincipal(nodoPaciente* arbol);
void menuIngresoUserPrintf(char tipoMenu[], nodoPaciente* arbol);

#endif // MENU_H_INCLUDED
