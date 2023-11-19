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

void mostrarUnNodoIngreso(nodoIngreso *aux)
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
        mostrarUnNodoIngreso(lista);
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
void obtenerFechaActual(char fechaActual[11])
{
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(fechaActual, 11, "%d/%m/%Y", tm_info);
    fechaActual[11] = '\0'; // Añadir el terminador nulo manualmente
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
    // Verificar existencia del paciente (Buscar en el archivo de pacientes)
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

    return listaIngresos;
}

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

        fwrite(&(ingresoNuevo->ingreso), sizeof(stIngreso), 1, archivo); // Escribir solo el contenido del ingreso

        printf("Carga otro ingreso (s/n): \n");
        fflush(stdin);
        scanf("%c",&continua);
        free(ingresoNuevo); // Liberar el nodo después de escribirlo en el archivo
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


nodoIngreso *buscaIngreso(nodoIngreso *listaIngresos, int nroIngreso)
{
    nodoIngreso *seg;
    seg = listaIngresos;
    while ( (seg != NULL) && (seg->ingreso.numeroIngreso != nroIngreso) )
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodoIngreso *modificarDatosIngreso(nodoIngreso *lista)
{
    nodoIngreso *ingresoExistente = inicListaIngresos();

    int nroIngreso, matricula;
    printf("\n Ingrese el numero de ingreso: ");
    scanf("%d", &nroIngreso);

    ingresoExistente = buscaIngreso(lista, nroIngreso);

    if (ingresoExistente)
    {
        char opcion;

        do {
            system("cls");
            printf("\n");
            mostrarUnNodoIngreso(ingresoExistente);

            printf("\n Que dato desea modificar? Ingrese una opcion:");
            printf("\n\n                1. Fecha de ingreso");
            printf("\n                2. Fecha de retiro");
            printf("\n                3. Matricula");
            opcion = getch();
            system("cls");

            switch (opcion)
            {
                case 49:

                    printf("\n Ingrese la nueva fecha de ingreso: ");
                    fflush(stdin);
                    fgets(ingresoExistente->ingreso.fechaIngreso, sizeof(ingresoExistente->ingreso.fechaIngreso), stdin);
                    break;
                case 50:

                    printf("\n Ingrese la nueva fecha de retiro: ");
                    fflush(stdin);
                    fgets(ingresoExistente->ingreso.fechaRetiro, sizeof(ingresoExistente->ingreso.fechaRetiro), stdin);
                    break;
                case 51:

                    printf("\n Ingrese la nueva matricula: ");
                    scanf("%d", &matricula);
                    ingresoExistente->ingreso.matriculaProfesional = matricula;
                    break;
                default:
                    // opcion incorrecta, se vuelve a mostrar el menu
                    break;
            }

            if (49 <= opcion && opcion <= 51)
            {
                system("cls");
                printf("\n Desea modificar algun otro dato del ingreso? En ese caso presione cualquier tecla, para finalizar presione ESC.");
                opcion = getch();
            }

        } while (opcion != ESC);

        system("cls");
        printf("\n Se ha modificado el ingreso.");

    }
    else
    {
        printf("\n El numero de ingreso cargado no esta registrado en la base de datos.\n");
    }

    return lista;
}


void buscaYDaDeBajaIngreso(nodoIngreso *lista)
{
    int nroIngreso;
    printf("\n Ingrese el numero de ingreso a dar de baja: ");
    scanf("%d", &nroIngreso);

    nodoIngreso *ingresoExistente = buscaIngreso(lista, nroIngreso);

    if (ingresoExistente)
    {
        ingresoExistente->ingreso.eliminado = 1;
        buscaYDaDeBajaPracticaXIngreso(ingresoExistente->listaPracticasXIngreso);
        printf("\n Se dio de baja al ingreso.");
    }
    else
    {
        printf("\n El numero de ingreso cargado no esta registrado en la base de datos.\n");
    }
}
