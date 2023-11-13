#include "stIngreso.h"

/**
* Obtener la fecha actual en formato "dd/mm/aaaa"
**/
void obtenerFechaActual(char fechaActual[10])
{
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(fechaActual, 10, "%d/%m/%Y", tm_info);
}

/**
* Obtener un nuevo n�mero de ingreso
**/
int obtenerNuevoNumeroIngreso()
{
    static int contador = 1;
    return contador++;
}

/**
* // Obtener una nueva pr�ctica de laboratorio
**/

stPractica obtenerPracticaLaboratorio()
{
    stPractica practica;
    practica.nroPractica = 1;  // N�mero de pr�ctica (solo como ejemplo)
    practica.eliminado = 0;    // No eliminado
    strcpy(practica.nombrePractica, "Prueba");  // Nombre de la pr�ctica (solo como ejemplo)
    return practica;
}

/**
* Obtener un nuevo ID para una pr�ctica asociada a un ingreso (solo como ejemplo)
**/
int obtenerNuevoIdPracticaXIngreso()
{
    static int contador = 1;
    return contador++;
}

/**
* Funci�n para dar de alta un ingreso con al menos una pr�ctica de laboratorio
**/
void Alta_de_ingreso(nodoIngreso **listaIngresos, struct stPaciente paciente, stEmpleado profesional)
{
//    // Verificar existencia del paciente (puede implementarse seg�n tus necesidades)
//    // ...
//
//    // Crear un nuevo nodo de ingreso
//    nodoIngreso *nuevoIngreso = (nodoIngreso *)malloc(sizeof(nodoIngreso));
//    nuevoIngreso->ingreso.numeroIngreso = obtenerNuevoNumeroIngreso();  // Implementar funci�n seg�n tus necesidades
//
//    // Obtener la fecha actual y asignarla a nuevoIngreso->ingreso.fechaIngreso
//    obtenerFechaActual(nuevoIngreso->ingreso.fechaIngreso);
//
//    nuevoIngreso->ingreso.fechaRetiro[0] = '\0';  // Inicializar fecha de retiro
//    nuevoIngreso->ingreso.dniPaciente = paciente.dni;
//    nuevoIngreso->ingreso.matriculaProfesional = profesional.dni;
//    nuevoIngreso->ingreso.eliminado = 0;  // No eliminado
//
//    // Crear al menos una pr�ctica de laboratorio asociada al ingreso
//    stPracticaXIngreso *nuevaPracticaXIngreso = (stPracticaXIngreso *)malloc(sizeof(stPracticaXIngreso));
//    nuevaPracticaXIngreso->nroIngreso = nuevoIngreso->ingreso.numeroIngreso;
//    nuevaPracticaXIngreso->nroPractica = obtenerPracticaLaboratorio().nroPractica;  // Obtener el n�mero de pr�ctica (solo como ejemplo)
//    nuevaPracticaXIngreso->eliminado = 0;  // No eliminado
//    nuevaPracticaXIngreso->resultado[0] = '\0';  // Inicializar resultado
//    nuevaPracticaXIngreso->siguiente = NULL;
//
//    // Enlazar la nueva pr�ctica al ingreso
//    nuevoIngreso->listaPracticasXIngreso = nuevaPracticaXIngreso;
//
//    // Enlazar el nuevo ingreso a la lista de ingresos
//    nuevoIngreso->siguiente = *listaIngresos;
//    *listaIngresos = nuevoIngreso;
//
//    printf("Ingreso de laboratorio registrado con �xito.\n");
}
/**
* Funci�n para modificar fechas y matr�cula del solicitante de un ingreso
**/
void Modificacion_de_ingreso(nodoIngreso *listaIngresos, int numeroIngreso, char nuevaFechaIngreso[10], char nuevaFechaRetiro[10], int nuevaMatriculaProfesional)
{
    nodoIngreso *temp = listaIngresos;

    // Buscar el ingreso por n�mero de ingreso
    while (temp != NULL && temp->ingreso.numeroIngreso != numeroIngreso)
    {
        temp = temp->siguiente;
    }

    // Verificar si se encontr� el ingreso
    if (temp != NULL)
    {
        // Modificar fechas y matr�cula
        strcpy(temp->ingreso.fechaIngreso, nuevaFechaIngreso);
        strcpy(temp->ingreso.fechaRetiro, nuevaFechaRetiro);
        temp->ingreso.matriculaProfesional = nuevaMatriculaProfesional;

        printf("Ingreso de laboratorio modificado con �xito.\n");
    }
    else
    {
        printf("No se encontr� el ingreso de laboratorio con el n�mero especificado.\n");
    }
}

/**
* Funci�n para dar de baja un ingreso y sus pr�cticas asociadas
**/
void Baja_de_ingreso(nodoIngreso **listaIngresos, int numeroIngreso)
{
    nodoIngreso *tempIngreso = *listaIngresos;

    // Buscar el ingreso por n�mero de ingreso
    while (tempIngreso != NULL && tempIngreso->ingreso.numeroIngreso != numeroIngreso)
    {
        tempIngreso = tempIngreso->siguiente;
    }

    // Verificar si se encontr� el ingreso
    if (tempIngreso != NULL)
    {
        // Dar de baja el ingreso
        tempIngreso->ingreso.eliminado = 1;  // Marcar como eliminado

        // Recorrer y dar de baja todas las pr�cticas asociadas
        nodoPracticaXIngreso *tempPracticaXIngreso = tempIngreso->listaPracticasXIngreso;
        while (tempPracticaXIngreso != NULL)
        {
            tempPracticaXIngreso->practicaXIngreso.eliminado = 1;  // Marcar como eliminada
            tempPracticaXIngreso = tempPracticaXIngreso->siguiente;
        }

        printf("Ingreso de laboratorio y sus pr�cticas asociadas dadas de baja con �xito.\n");
    }
    else
    {
        printf("No se encontr� el ingreso de laboratorio con el n�mero especificado.\n");
    }
}

