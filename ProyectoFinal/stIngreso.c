#include "stIngreso.h"

/***************************
* FUNCIONES BASICAS DE LISTA
***************************/
nodoIngreso* inicLista()
{
    return NULL;
}

/**
    La funci�n (crearNodoIngreso), que reciba como par�metro un registro de tipo stIngreso, y
    devuelva un nodo de tipo nodoIngreso
**/
nodoIngreso* crearNodoIngreso(stIngreso registro)
{
    nodoIngreso *nuevo = (nodoIngreso*) malloc(sizeof(nodoIngreso));
    if(nuevo == NULL)
    {
        printf("No se ha podido reservar espacio en memoria.\n");
        exit(1);
    }

    nuevo->ingreso.numeroIngreso = registro.numeroIngreso;
    strcpy(nuevo->ingreso.fechaIngreso, registro.fechaIngreso);
    strcpy(nuevo->ingreso.fechaRetiro, registro.fechaRetiro);
    nuevo->ingreso.dniPaciente = registro.dniPaciente;
    nuevo->ingreso.matriculaProfesional = registro.matriculaProfesional;
    nuevo->ingreso.eliminado = registro.eliminado;
    nuevo->siguiente = NULL;

    return nuevo;
}

/**
    La funci�n (agregarNodoIngreso), que reciba la lista, un registro del tipo stIngreso y un empleado para que agregue ese
    nodo al final de la lista. Retornar la lista.
**/
nodoIngreso* agregarNodoIngreso(nodoIngreso *lista, stIngreso registro)
{

    nodoIngreso *nuevo = crearNodoIngreso(registro); ///Creo el nodo con la funcion anterior, con el registro que paso por parametro

    if(lista == NULL) ///Si la lista esta vacia, agrego en la posicion del primer elemento.
    {
        lista = nuevo;
    }
    else
    {
        nodoIngreso *ultimo = buscaUltimoLista(lista);
        ultimo->siguiente = nuevo;
    }

    return lista;
}

nodoIngreso* buscaUltimoLista(nodoIngreso *lista)
{
    nodoIngreso *seg = lista;
    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

/**
    La funci�n (crearListaIngresos) permite recorrer el archivo y crear la lista de ingresos. La funci�n puede
    recibir como par�metro el nombre del archivo o puede no recibir� ese par�metro si as� lo prefiere. Retornar la lista
**/

nodoIngreso* crearListaIngresos(const char *nombreArchivo)
{
    nodoIngreso *lista = inicLista();
    stIngreso ingresoNuevo; //Registro donde voy a guardar lo levantado
    FILE *archivo = fopen(nombreArchivo, "rb");

    /// Veo si se pudo abrir el archivo
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        exit(1); // Codigo de error
    }

    rewind(archivo);
    while(fread(&ingresoNuevo, sizeof(stIngreso), 1, archivo) > 0) //fread devuelve el numero de datos leidos
    {
        lista = agregarNodoIngreso(lista, ingresoNuevo);
    }
    fclose(archivo);
    return lista;
}

/**
    La funci�n (mostrarIngreso) que permita recorrer y mostrar la lista. La misma debe ser recursiva
**/

void mostrarUnNodo(nodoIngreso *aux)
{
    if (aux != NULL)
    {
        puts("-----------------------------------------------------\n");
        printf("Numero de ingreso...........: %d\n", aux->ingreso.numeroIngreso);
        printf("Fecha de ingreso............: %s\n", aux->ingreso.fechaIngreso);
        printf("Fecha de retiro.............: %s\n", aux->ingreso.fechaRetiro);
        printf("DNI del paciente............: %d\n", aux->ingreso.dniPaciente);
        printf("Matricula profesional.......: %d\n", aux->ingreso.matriculaProfesional);
        printf("Eliminado...................: %d <1:SI/0:NO>\n", aux->ingreso.eliminado);
        puts("-----------------------------------------------------\n");
    }
    else
    {
        printf("Nodo no v�lido.\n");
    }
}

void mostrarIngreso(nodoIngreso *lista)
{
    if(lista != NULL)
    {
        mostrarUnNodo(lista);
        mostrarIngreso(lista->siguiente);
    }
}

/**
    La funci�n (liberarLista), que reciba la lista y hacer lo indicado. La funci�n no debe retornar nada (no importa que
    la cabecera no quede en NULL)
**/

nodoIngreso* liberarLista(nodoIngreso *lista)
{
    nodoIngreso *proximo;
    nodoIngreso *seg = lista;

    while(seg != NULL)
    {
        proximo = seg->siguiente;
        free(seg);
        seg = proximo;
    }
    return seg;
}

/**
    La funci�n (cargarIngreso), la cual recibir� la lista y solicitar� al usuario los datos del pedido para finalmente
    agregar ese pedido a la lista y retornar la lista. Modularizar de ser conveniente.
**/

nodoIngreso* cargarIngreso(nodoIngreso *lista)
{
    stIngreso registro;

    printf("Ingrese el numero de ingreso: ");
    scanf("%d", &registro.numeroIngreso);
    printf("Ingrese la fecha de ingreso: ");
    fflush(stdin);
    gets(registro.fechaIngreso);
    printf("Ingrese la fecha de retiro: ");
    fflush(stdin);
    gets(registro.fechaRetiro);
    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &registro.dniPaciente);
    printf("Ingrese la matricula profesional: ");
    scanf("%d", &registro.matriculaProfesional);
    printf("Ingrese si esta eliminado: "); //Esto va?
    scanf("%d", &registro.eliminado);
    lista = agregarNodoIngreso(lista, registro); ///Finalmente agrego el pedido a la lista

    return lista;
}



/**************************
* FUNCIONES DEL PROBLEMA
**************************/

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
void Alta_de_ingreso(nodoIngreso **listaIngresos, stIngreso paciente, stEmpleado profesional)
{
    // Verificar existencia del paciente (Buscar en el archivo de pacientes)
    // ...

    // Crear un nuevo nodo de ingreso
    nodoIngreso *nuevoIngreso = crearNodoIngreso(paciente);
    nuevoIngreso->ingreso.numeroIngreso = obtenerNuevoNumeroIngreso();

    // Obtener la fecha actual y asignarla a nuevoIngreso->ingreso.fechaIngreso
    obtenerFechaActual(nuevoIngreso->ingreso.fechaIngreso);

    nuevoIngreso->ingreso.fechaRetiro[0] = '\0';  // Inicializar fecha de retiro
    nuevoIngreso->ingreso.dniPaciente = paciente.dniPaciente;
    nuevoIngreso->ingreso.matriculaProfesional = profesional.dni;
    nuevoIngreso->ingreso.eliminado = 0;  // No eliminado

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

    printf("Ingreso de laboratorio registrado con �xito.\n");
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

//int existePaciente(int dni)
//{
//    FILE * arch = fopen("ingresos.dat", "rb");
//    stIngresos ingresoPaciente;
//    nodoIngresos * listaPaciente = inicLista();
//
//    if(arch != NULL)
//    {
//        while(fread(&ingresoPaciente,sizeof(stIngresos),1,arch)>0) //borrar los datos?
//        {
//            if(ingresoPaciente.dni == dni)
//            {
//                listaPaciente = agregoFinalListaIngresos(listaPaciente,ingresoPaciente);
//            }
//        }
//    }
//
//    fclose(arch);
//    return listaPaciente;
//
//}

void generarArchivoBinIngresos(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "wb");

    /// Veo si se pudo abrir el archivo
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }
    nodoIngreso *ingresoNuevo = inicLista();
    char continua = 's';
    while(continua == 's')
    {
        ingresoNuevo = cargarIngreso(ingresoNuevo);

        fwrite(ingresoNuevo,sizeof(nodoIngreso), 1, archivo);

        printf("Carga otro ingreso (s/n): \n");
        fflush(stdin);
        scanf("%c",&continua);
    }

    /// Cerrar el archivo
    fclose(archivo);

    printf("Datos guardados en el archivo '%s'.\n", nombreArchivo);
}
