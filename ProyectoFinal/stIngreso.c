#include "stIngreso.h"

/***************************
* FUNCIONES BASICAS DE LISTA
***************************/
nodoIngreso* inicLista()
{
    return NULL;
}

/**
    La función (crearNodoIngreso), que reciba como parámetro un registro de tipo stIngreso, y
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
    La función (agregarNodoIngreso), que reciba la lista, un registro del tipo stIngreso
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
        nodoIngreso *ultimo = buscaUltimoListaIngresos(lista);
        ultimo->siguiente = nuevo;
    }

    return lista;
}

nodoIngreso* buscaUltimoListaIngresos(nodoIngreso *lista)
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
    La función (crearListaIngresos) permite recorrer el archivo y crear la lista de ingresos. La función puede
    recibir como parámetro el nombre del archivo o puede no recibiré ese parámetro si así lo prefiere. Retornar la lista
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
    La función (mostrarIngreso) que permita recorrer y mostrar la lista. La misma debe ser recursiva
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
        printf("Nodo no válido.\n");
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
    La función (liberarLista), que reciba la lista y hacer lo indicado. La función no debe retornar nada (no importa que
    la cabecera no quede en NULL)
**/

nodoIngreso* liberarListaIngresos(nodoIngreso *lista)
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
    La función (cargarIngreso), la cual recibirá la lista y solicitará al usuario los datos del pedido para finalmente
    agregar ese pedido a la lista y retornar la nueva lista con el nuevo ingreso.
**/

nodoIngreso* cargarIngreso(nodoIngreso *lista)
{
    stIngreso registro;

    registro.numeroIngreso = obtenerNuevoNumeroIngreso(); //Numero de ingreso
    obtenerFechaActual(registro.fechaIngreso);  // Obtener la fecha actual y asignarla a nuevoIngreso->ingreso.fechaIngreso
    printf("Ingrese la fecha de retiro: ");
    fflush(stdin);
    gets(registro.fechaRetiro);
    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &registro.dniPaciente);
    printf("Ingrese la matricula profesional: ");
    scanf("%d", &registro.matriculaProfesional);
    registro.eliminado = 0;
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
* Función para dar de alta un ingreso con al menos una práctica de laboratorio
**/
nodoIngreso* altaDeIngreso(nodoIngreso *listaIngresos, nodoPracticaXIngreso *nuevaPracticaXIngreso)
{
    int dni;
    char opcion = 0;
    // Verificar existencia del paciente (Buscar en el archivo de pacientes)
    do
    {
        printf("\n Ingrese el DNI del paciente a ingresar: ");
        scanf("%d", &dni);
        if(!existePacienteXDNI(dni))
        {
            printf("\n El paciente no existe en la base de datos.\n");
        }
        else
        {
            // Crear un nuevo nodo de ingreso y se agrega a la lista
            listaIngresos = cargarIngreso(listaIngresos);

            // Crear al menos una práctica de laboratorio asociada al ingreso
            nuevaPracticaXIngreso = altaDePracticaXIngreso(nuevaPracticaXIngreso);

           // Enlazar la nueva práctica al ingreso
            listaIngresos->listaPracticasXIngreso = nuevaPracticaXIngreso;

            printf("Ingreso registrado con éxito.\n");
        }
        printf("\n\n Para cargar otro ingreso presione cualquier tecla, ESC para finalizar...");
        opcion = getch();
        system("cls");
    }while (opcion != ESC);

    return listaIngresos;
}

nodoIngreso *buscarIngreso(nodoIngreso *lista, int nroIngreso)
{
    nodoIngreso *seg = lista;
    nodoIngreso *ingresoEncontrado = NULL;
    int flag = 0;
        while(seg!= NULL && flag == 0)
        {
            if(seg->ingreso.numeroIngreso == nroIngreso)
            {
                ingresoEncontrado = seg;
                flag = 1;
            }
            seg = seg->siguiente;
        }
    return ingresoEncontrado;
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

int existeIngresoXnroIngreso(int nroIngresoBuscar)
{
    FILE *archivo = fopen(ARCHIVO_INGRESOS, "rb");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 0; // Indicar que no se encontró debido a un error
    }

    stIngreso ingresoActual;

    while (fread(&ingresoActual, sizeof(stIngreso), 1, archivo) == 1)
    {
        if (ingresoActual.numeroIngreso == nroIngresoBuscar)
        {
            fclose(archivo);
            return 1; // Se encontró el ingreso con el nro de ingreso
        }
    }

    fclose(archivo);
    return 0; // No se encontró el registro
}
