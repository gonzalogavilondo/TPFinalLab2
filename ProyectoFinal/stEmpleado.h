#ifndef STEMPLEADO_H_INCLUDED
#define STEMPLEADO_H_INCLUDED

typedef struct stEmpleado
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int eliminado;
} stEmpleado;

#endif // STEMPLEADO_H_INCLUDED
