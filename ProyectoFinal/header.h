#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct empleadoDeLaboratorio
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int eliminado;
} empleadoDeLaboratorio;

typedef struct stPractica
{
    int nroPractica;
    char nombrePractica[30];
    int eliminado;
} stPractica;

typedef struct stPracticaXIngreso
{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
    int eliminado;
} stPracticaXIngreso;

typedef struct nodoPracticaXIngreso
{
    stPracticaXIngreso practicaXIngreso;
    struct nodoPracticaXIngreso * siguiente;
} nodoPracticaXIngreso;

typedef struct stIngreso
{

    int numeroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
} stIngreso;

typedef struct nodoIngreso
{
    stIngreso ingreso;
    struct nodoPracticaXIngreso * listaPracticasXIngreso; // listaPracticas
    struct nodoIngreso * siguiente;
} nodoIngreso;

typedef struct stPaciente {

    char apellidoNombre[40];
    int edad;
    int dni;
    char direccion[30];
    char telefono[15];
    int eliminado;
} stPaciente;

typedef struct nodoPaciente
{
    stPaciente datosPaciente;
    struct nodoIngreso * listaIngresos;
    struct nodoPaciente * izq;
    struct nodoPaciente * der;
} nodoPaciente;

#endif // HEADER_H_INCLUDED
