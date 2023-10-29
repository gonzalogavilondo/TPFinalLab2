#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "time.h"
#include "Canciones.h"
#define arUser "User.dat"


typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char password[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int Ueliminado;
} stUser;


///====FUNCIONES USUARIOS=====
void CargarArchiUsuario();
void guardarUser(stUser a);

int buscaUltimoIdUsuario();
int validacionUsuario(char nuevoUser[]);

void MuestraUnUser(stUser a);
void  MuestraUnUserCualquiera(stUser a);
void mostrarUsers();
void mostrarUsersEliminado();
void MuestraUnUserEliminado(stUser a);
int logeoUser(char nombre[],char contrasenia[]);
int logeoAdmin(char nombre[],char contrasenia[],int contraseniaAdmin);
void ConsultaUser(int id);
void ConsultaUserXName(char nombre[]);
int encontrarIDUSERxNombre(char nombre[]);

int ValidacionUsuarioXId(int id);

void mostrarArregloUsuario(stUser a[],int validos);

//MODIFICACIONES DE USER
void elimininarUser(char nUsuario[]);
void recuperarUser(char nUsuario[]);
void modificarNombreUsuario(char nombreN[],int idIngresado);
void modificarContraseniaUsuario(char passN[],int idIngresado);
void ModifAnioNacimiento(int anioN,int idIngresado);
void Modificargenero(char sexo,int idIngresado);
void ModificarPais(char paisN[],int idIngresado);

void mostrarUsers();
void MuestraUnUser(stUser a);

int cantUsers();
/*
///PLAYLIST
void cargarPlaylist(int idcan,int idUsuario);
void mostrarPlaylist(int idUsuario);
*/

#endif // USUARIOS_H_INCLUDED
