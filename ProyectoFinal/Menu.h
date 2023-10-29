#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "time.h"
#include "Usuarios.h"
#include "Canciones.h"
#include "ADL(Usuarios).h"

///LOGUEO admin
int logeoAdmin(char nombre[],char contrasenia[],int contraseniaAdmin);

///LOGUEO USER
int logeoUser(char nombre[],char contrasenia[]);

///Funciones Swich///
void switchMenuPrincipal(int op,stCeldaUsuarios a[],int validos);
void switchMenuAdmin(int op,stCeldaUsuarios a[],int validos);
void switchAdminSubUsuario(int op,stCeldaUsuarios a[],int validos);
void switchAdminSubCancion(int op);
void switchIngresoDivision(int op,stCeldaUsuarios a[],int validos);
void switchMenuUsuario(int op,char nombreU[],stCeldaUsuarios a[],int validos);
void eleccionGenONombCancion(int op);
void modificacionCancion(int op);
void modificacionUsuario(int op,stCeldaUsuarios adl[],int validos,int userModi);
///PRINTFS FUNCIONES//
void Rectangulo();
void RectanguloChico();
void cabeza(char a[]);
void imprimirCabecera(char cabecera[]);
void menuPrincipalPrint();
void submenuAdminUsuarioPrintf(stCeldaUsuarios a[],int validos);
void submenuAdminCancionPrintf();
void menuIngresoUserPrintf(stCeldaUsuarios a[],int validos);
void menuPrincipalUsuarioPrint(stCeldaUsuarios a[],int validos);
void OrdenarPorNoGPrintf();
void menuModificacionCancionPrintf();
void menuModificacionUsuarioPrintf(stCeldaUsuarios a[],int validos);

int obtenerID();
void fGetNow(char date[]);
int fGetDayOfWeek(char date[]);
void fStrStr(char o[], char d[], int desde, int cant);
void fGetDayShort(char date[],char day[]);
int fGetHour(char date[]);
int fGetMinute(char date[]);

#endif // MENU_H_INCLUDED
