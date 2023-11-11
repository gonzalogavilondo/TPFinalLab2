#ifndef EMPLEADODELABORATORIO_H_INCLUDED
#define EMPLEADODELABORATORIO_H_INCLUDED

typedef struct empleadoDeLaboratorio
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int eliminado;
} empleadoDeLaboratorio;


#endif // EMPLEADODELABORATORIO_H_INCLUDED
