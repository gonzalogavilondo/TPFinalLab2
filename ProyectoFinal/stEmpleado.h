#ifndef STEMPLEADO_H_INCLUDED
#define STEMPLEADO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "stEmpleado.h"

#define arEmpleados "archivoEmpleados.txt"

typedef struct stEmpleado
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int eliminado;
} stEmpleado;

int existeDNIEnEmpleados(int dniEmpleado);
int existeUsuarioEnEmpleados(char usuario[]);
int guardarEmpleadoEnArchivo(stEmpleado e);
stEmpleado traerEmpleadoXDNI(int dni);
void mostrarEmpleado(stEmpleado e);
void modificarUsuarioEmpleadoXDNI(char usuarioNuevo[],int dni);
void modificarDNIEmpleadoXUsuario(int dniNuevo,int dni);
void modificarNombreEmpleadoXDNI(char nombreNuevo[],int dni);
stEmpleado altaDeEmpleados ();
int existeDNIEnEmpleados(int dniEmpleado);
void modificarEstadoEmpleadoXDNI(int estado,int dni);
int compararPorApellidoYNombre(const void *a, const void *b);
void ordenarPorApellidoYNombre(stEmpleado arreglo[], int numEmpleados);
int pasarArchivoAArregloEmpleados(stEmpleado e[],int dimension,int validos);
int inicioDeSesion(char usuario[],char contrasenia[], char tipoMenu[]);

#endif // STEMPLEADO_H_INCLUDED
