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

stEmpleado altaDeEmpleados ();

stEmpleado traerEmpleadoXDNI(int dni);

#endif // STEMPLEADO_H_INCLUDED
