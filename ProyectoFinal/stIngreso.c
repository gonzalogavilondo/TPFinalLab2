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
* Obtener un nuevo número de ingreso
**/
int obtenerNuevoNumeroIngreso()
{
    static int contador = 1;
    return contador++;
}

/**
* // Obtener una nueva práctica de laboratorio
**/

stPractica obtenerPracticaLaboratorio()
{
    stPractica practica;
    practica.nroPractica = 1;  // Número de práctica (solo como ejemplo)
    practica.eliminado = 0;    // No eliminado
    strcpy(practica.nombrePractica, "Prueba");  // Nombre de la práctica (solo como ejemplo)
    return practica;
}

/**
* Obtener un nuevo ID para una práctica asociada a un ingreso (solo como ejemplo)
**/
int obtenerNuevoIdPracticaXIngreso()
{
    static int contador = 1;
    return contador++;
}

/**
* Función para dar de alta un ingreso con al menos una práctica de laboratorio
**/
void Alta_de_ingreso(nodoIngreso **listaIngresos, struct stPaciente paciente, stEmpleado profesional)
{
//    // Verificar existencia del paciente (puede implementarse según tus necesidades)
//    // ...
//
//    // Crear un nuevo nodo de ingreso
//    nodoIngreso *nuevoIngreso = (nodoIngreso *)malloc(sizeof(nodoIngreso));
//    nuevoIngreso->ingreso.numeroIngreso = obtenerNuevoNumeroIngreso();  // Implementar función según tus necesidades
//
//    // Obtener la fecha actual y asignarla a nuevoIngreso->ingreso.fechaIngreso
//    obtenerFechaActual(nuevoIngreso->ingreso.fechaIngreso);
//
//    nuevoIngreso->ingreso.fechaRetiro[0] = '\0';  // Inicializar fecha de retiro
//    nuevoIngreso->ingreso.dniPaciente = paciente.dni;
//    nuevoIngreso->ingreso.matriculaProfesional = profesional.dni;
//    nuevoIngreso->ingreso.eliminado = 0;  // No eliminado
//
//    // Crear al menos una práctica de laboratorio asociada al ingreso
//    stPracticaXIngreso *nuevaPracticaXIngreso = (stPracticaXIngreso *)malloc(sizeof(stPracticaXIngreso));
//    nuevaPracticaXIngreso->nroIngreso = nuevoIngreso->ingreso.numeroIngreso;
//    nuevaPracticaXIngreso->nroPractica = obtenerPracticaLaboratorio().nroPractica;  // Obtener el número de práctica (solo como ejemplo)
//    nuevaPracticaXIngreso->eliminado = 0;  // No eliminado
//    nuevaPracticaXIngreso->resultado[0] = '\0';  // Inicializar resultado
//    nuevaPracticaXIngreso->siguiente = NULL;
//
//    // Enlazar la nueva práctica al ingreso
//    nuevoIngreso->listaPracticasXIngreso = nuevaPracticaXIngreso;
//
//    // Enlazar el nuevo ingreso a la lista de ingresos
//    nuevoIngreso->siguiente = *listaIngresos;
//    *listaIngresos = nuevoIngreso;
//
//    printf("Ingreso de laboratorio registrado con éxito.\n");
}
/**
* Función para modificar fechas y matrícula del solicitante de un ingreso
**/
void Modificacion_de_ingreso(nodoIngreso *listaIngresos, int numeroIngreso, char nuevaFechaIngreso[10], char nuevaFechaRetiro[10], int nuevaMatriculaProfesional)
{
    nodoIngreso *temp = listaIngresos;

    // Buscar el ingreso por número de ingreso
    while (temp != NULL && temp->ingreso.numeroIngreso != numeroIngreso)
    {
        temp = temp->siguiente;
    }

    // Verificar si se encontró el ingreso
    if (temp != NULL)
    {
        // Modificar fechas y matrícula
        strcpy(temp->ingreso.fechaIngreso, nuevaFechaIngreso);
        strcpy(temp->ingreso.fechaRetiro, nuevaFechaRetiro);
        temp->ingreso.matriculaProfesional = nuevaMatriculaProfesional;

        printf("Ingreso de laboratorio modificado con éxito.\n");
    }
    else
    {
        printf("No se encontró el ingreso de laboratorio con el número especificado.\n");
    }
}

/**
* Función para dar de baja un ingreso y sus prácticas asociadas
**/
void Baja_de_ingreso(nodoIngreso **listaIngresos, int numeroIngreso)
{
    nodoIngreso *tempIngreso = *listaIngresos;

    // Buscar el ingreso por número de ingreso
    while (tempIngreso != NULL && tempIngreso->ingreso.numeroIngreso != numeroIngreso)
    {
        tempIngreso = tempIngreso->siguiente;
    }

    // Verificar si se encontró el ingreso
    if (tempIngreso != NULL)
    {
        // Dar de baja el ingreso
        tempIngreso->ingreso.eliminado = 1;  // Marcar como eliminado

        // Recorrer y dar de baja todas las prácticas asociadas
        nodoPracticaXIngreso *tempPracticaXIngreso = tempIngreso->listaPracticasXIngreso;
        while (tempPracticaXIngreso != NULL)
        {
            tempPracticaXIngreso->practicaXIngreso.eliminado = 1;  // Marcar como eliminada
            tempPracticaXIngreso = tempPracticaXIngreso->siguiente;
        }

        printf("Ingreso de laboratorio y sus prácticas asociadas dadas de baja con éxito.\n");
    }
    else
    {
        printf("No se encontró el ingreso de laboratorio con el número especificado.\n");
    }
}

