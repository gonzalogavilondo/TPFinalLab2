#include "stIngreso.h"
#include "menu.h"

// Declaración global del contador
static int contadorIngresos = 0;

/***************************
* FUNCIONES BASICAS DE LISTA
***************************/
nodoIngreso* inicListaIngresos()
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
    nuevo->listaPracticasXIngreso = NULL;

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
    nodoIngreso *lista = inicListaIngresos();
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
    La función (mostrarListadoGralIngresos) que permita recorrer y mostrar la lista. La misma debe ser recursiva
**/

void mostrarUnNodoIngreso(nodoIngreso *aux)
{
    if (aux != NULL)
    {
        printf("\n*** Detalles del Ingreso ***\n");
        printf("Numero de ingreso: %d\n", aux->ingreso.numeroIngreso);
        printf("Fecha de ingreso: %s\n", aux->ingreso.fechaIngreso);
        printf("Fecha de retiro: %s\n", aux->ingreso.fechaRetiro);
        printf("Matricula profesional: %d\n", aux->ingreso.matriculaProfesional);
        printf("Eliminado: %d <1:SI/0:NO>\n", aux->ingreso.eliminado);
        puts("----------------------------");
    }
    else
    {
        printf("Nodo no válido.\n");
    }
}

void mostrarListadoGralIngresos(nodoPaciente *arbolPacientes, int flag)
{
    if (arbolPacientes != NULL)
    {
        printf("\n*** Listado de Ingresos del Paciente ***\n");
        muestraUnPacienteResumido(arbolPacientes->datosPaciente);

        nodoIngreso *seg = arbolPacientes->listaIngresos;

        if (seg == NULL)
        {
            printf("\nEl paciente no tiene ingresos.\n");
            puts("--------------------------------------\n");
        }
        else
        {
            while (seg != NULL)
            {
                if ((flag == 0 && seg->ingreso.eliminado == 0) || (flag == 1))
                {
                    mostrarUnNodoIngreso(seg);
                }
                seg = seg->siguiente;
            }
        }

        printf("\n*** Fin del Listado de Ingresos del Paciente ***\n");
        puts("----------------------------------------------\n");

        // Verificar si la rama izquierda no es NULL antes de llamar recursivamente
        if (arbolPacientes->izq != NULL)
        {
            mostrarListadoGralIngresos(arbolPacientes->izq, flag);
        }

        // Verificar si la rama derecha no es NULL antes de llamar recursivamente
        if (arbolPacientes->der != NULL)
        {
            mostrarListadoGralIngresos(arbolPacientes->der, flag);
        }
    }
}


void _mostrarListadoGralIngresosFecha(nodoPaciente *arbolPacientes, int flag, const char *fechaDesde, const char *fechaHasta)
{
    if (arbolPacientes != NULL)
    {
        printf("\n*** Listado de Ingresos del Paciente ***\n");
        muestraUnPacienteResumido(arbolPacientes->datosPaciente);

        nodoIngreso *seg = arbolPacientes->listaIngresos;

        if (seg == NULL)
        {
            printf("\nEl paciente no tiene ingresos en las fechas selecionadas.\n");
            puts("--------------------------------------\n");
        }
        else
        {
            while (seg != NULL)
            {
                if ((flag == 0 && seg->ingreso.eliminado == 0) || (flag == 1))
                {
                    const char *fechaIngreso = seg->ingreso.fechaIngreso;

                    // Verificar si la fecha de ingreso está en el rango deseado
                    if (strcmp(fechaIngreso, fechaDesde) >= 0 && strcmp(fechaIngreso, fechaHasta) <= 0)
                    {
                        mostrarUnNodoIngreso(seg);
                    }
                }
                seg = seg->siguiente;
            }
        }

        printf("\n*** Fin del Listado de Ingresos del Paciente ***\n");
        puts("----------------------------------------------\n");
    }

    if (arbolPacientes->izq != NULL)
    {
        _mostrarListadoGralIngresosFecha(arbolPacientes->izq, flag, fechaDesde, fechaHasta);
    }

    if (arbolPacientes->der != NULL)
    {
        _mostrarListadoGralIngresosFecha(arbolPacientes->der, flag, fechaDesde, fechaHasta);
    }
}

void mostrarListadoGralIngresosFecha(nodoPaciente *arbolPacientes, int flag)
{
    char fechaDesde[20], fechaHasta[20];

    printf("Ingrese la fecha desde en formato DD/MM/YYYY: ");
    scanf("%s", fechaDesde);

    printf("Ingrese la fecha hasta en formato DD/MM/YYYY: ");
    scanf("%s", fechaHasta);

    // Validar que la fecha desde no sea posterior a la fecha hasta
    if (strcmp(fechaDesde, fechaHasta) > 0)
    {
        printf("\nError: La fecha desde no puede ser posterior a la fecha hasta.\n");
        return;
    }

    // Llamar a la función original con las fechas ingresadas
    _mostrarListadoGralIngresosFecha(arbolPacientes, flag, fechaDesde, fechaHasta);
}

void mostrarListadoIngresosXPaciente(nodoPaciente *arbolPacientes)
{
    int dni;

    printf("Ingrese el DNI del paciente a mostrar el listado: ");
    scanf("%d", &dni);

    nodoPaciente *paciente = buscaPaciente(arbolPacientes, dni);
    if (!paciente)
    {
        printf("\nEl paciente no existe en la base de datos.\n");
        system("pause");
    }
    else
    {
        if (paciente->listaIngresos != NULL)
        {
            printf("\n*** Listado de Ingresos del Paciente ***\n");
            muestraUnPacienteResumido(paciente->datosPaciente);
            nodoIngreso *seg = paciente->listaIngresos;

            while (seg != NULL)
            {
                if (seg->ingreso.eliminado == 0)
                {
                    mostrarUnNodoIngreso(seg);
                }

                seg = seg->siguiente;
            }

            printf("\n*** Fin del Listado de Ingresos del Paciente ***\n");
            puts("----------------------------------------------\n");
        }
    }
}

void mostrarListadoIngresosPaciente(nodoPaciente *paciente)
{
    if (paciente != NULL)
    {
        if (paciente->listaIngresos != NULL)
        {
            printf("\n*** Listado de Ingresos del Paciente ***\n");
            muestraUnPacienteResumido(paciente->datosPaciente);
            nodoIngreso *seg = paciente->listaIngresos;

            while (seg != NULL)
            {
                if (seg->ingreso.eliminado == 0)
                {
                    mostrarUnNodoIngreso(seg);
                }

                seg = seg->siguiente;
            }

            printf("\n*** Fin del Listado de Ingresos del Paciente ***\n");
            puts("----------------------------------------------\n");
        }
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


int cantidadIngresosArchivo()
{
    int cant = 0;
    FILE* archivoIngresos = fopen(ARCHIVO_INGRESOS, "rb");

    if (archivoIngresos)
    {
        stIngreso ingreso;

        while (fread(&ingreso, sizeof(stIngreso), 1, archivoIngresos))
        {
            cant++;
        }

        fclose(archivoIngresos);
    }
    else
    {
        cant = -1;
    }

    // Actualizar el contador de ingresos al inicio del programa
    contadorIngresos = cant + 1;

    return cant;
}

nodoIngreso* cargarIngreso(nodoIngreso *lista, int dni)
{
    stIngreso registro;


    registro.numeroIngreso = contadorIngresos; // Numero de ingreso EN ARCHIVO

    // Obtener la fecha actual y asignarla a nuevoIngreso->ingreso.fechaIngreso
    obtenerFechaActual(registro.fechaIngreso);

    // Imprimir y obtener la fecha de retiro
    gotoxy(15, 5);
    printf("Ingrese la fecha de retiro: ");
    fflush(stdin);
    gets(registro.fechaRetiro);

    registro.dniPaciente = dni;

    // Imprimir y obtener la matrícula profesional
    gotoxy(15, 6);
    printf("Ingrese la matricula profesional: ");
    scanf("%d", &registro.matriculaProfesional);

    registro.eliminado = 0;
    lista = agregarNodoIngreso(lista, registro); // Finalmente agrego el ingreso a la lista

    // Incrementar el contador después de agregar el ingreso
    contadorIngresos++;

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
//int obtenerNuevoNumeroIngreso()
//{
//    return contadorIngresos++;
//}

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
void altaDeIngreso(nodoPaciente *arbolPacientes)
{
    int dni;

    system("cls");

    // Imprime el rectángulo y la cabeza después de limpiar la pantalla
    Rectangulo();
    gotoxy(15, 1);
    cabeza("Alta de Ingreso");

    gotoxy(15, 4);
    printf("Ingrese el DNI del paciente a ingresar: ");
    scanf("%d", &dni);

    arbolPacientes = buscaPaciente(arbolPacientes, dni);
    if (!arbolPacientes)
    {
        gotoxy(15, 6);
        printf("El paciente no existe en la base de datos.\n");
        system("pause");
    }
    else
    {
        // Crear un nuevo nodo de ingreso y agregarlo a la lista
        arbolPacientes->listaIngresos = cargarIngreso(arbolPacientes->listaIngresos, dni);

        // Crear al menos una práctica de laboratorio asociada al ingreso
        altaDePracticaXIngreso(arbolPacientes, 1);

        Rectangulo();
        gotoxy(15, 8);
        printf("Ingreso registrado con exito.");
    }
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


void modificarDatosIngreso(nodoPaciente *arbolPacientes)
{
    nodoIngreso *ingresoExistente = inicListaIngresos();

    int nroIngreso, matricula, dni;
    char opcion;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Modificacion de Ingreso");
        gotoxy(15, 3);
        printf("Ingrese el numero de DNI del paciente a modificar: ");
        scanf("%d", &dni);

        nodoPaciente *paciente = inicArbolPacientes();
        paciente = buscaPaciente(arbolPacientes, dni);
        system("cls");
        mostrarListadoIngresosPaciente(paciente);

        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);

        ingresoExistente = buscaIngreso(paciente->listaIngresos, nroIngreso);

        if (ingresoExistente)
        {
            do {
                system("cls");
                printf("\n");
                mostrarUnNodoIngreso(ingresoExistente);

                printf("Que dato desea modificar?\n\n");
                gotoxy(15, 10);
                printf("1. Fecha de ingreso");
                gotoxy(15, 11);
                printf("2. Fecha de retiro");
                gotoxy(15, 12);
                printf("3. Matricula");
                gotoxy(15, 14);
                printf("Ingrese una opcion: ");
                fflush(stdin);
                opcion = getch();
                system("cls");

                switch (opcion)
                {
                    case 49:
                        gotoxy(15, 4);
                        printf("Ingrese la nueva fecha de ingreso: ");
                        fflush(stdin);
                        fgets(ingresoExistente->ingreso.fechaIngreso, sizeof(ingresoExistente->ingreso.fechaIngreso), stdin);
                        break;
                    case 50:
                        gotoxy(15, 4);
                        printf("Ingrese la nueva fecha de retiro: ");
                        fflush(stdin);
                        fgets(ingresoExistente->ingreso.fechaRetiro, sizeof(ingresoExistente->ingreso.fechaRetiro), stdin);
                        break;
                    case 51:
                        gotoxy(15, 4);
                        printf("Ingrese la nueva matricula: ");
                        scanf("%d", &matricula);
                        ingresoExistente->ingreso.matriculaProfesional = matricula;
                        break;
                    default:
                        // opción incorrecta, se vuelve a mostrar el menú
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
            gotoxy(15, 4);
            printf("Se ha modificado el ingreso.");

        }
        else
        {
            system("cls");
            Rectangulo();
            gotoxy(15, 6);
            printf("El numero de ingreso cargado no esta registrado en la base de datos.\n");
            system("pause");
        }
        system("cls");
        Rectangulo();
        gotoxy(15, 6);
        printf("Desea modificar otro ingreso? (S/N): ");
        fflush(stdin);
        opcion = getch();

    } while (opcion == 's' || opcion == 'S');

}

void buscaYDaDeBajaIngreso(nodoPaciente *arbolPacientes)
{
    int nroIngreso, dni;
    char opcion;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Baja de Ingreso");

        gotoxy(5, 4);
        printf("Ingrese el numero de DNI del paciente a modificar: ");
        scanf("%d", &dni);

        nodoPaciente *paciente = inicArbolPacientes();
        paciente = buscaPaciente(arbolPacientes, dni);
        system("cls");
        mostrarListadoIngresosPaciente(paciente);

        printf("Ingrese el numero de ingreso a dar de baja: ");
        scanf("%d", &nroIngreso);
        nodoIngreso *ingresoExistente = buscaIngreso(paciente->listaIngresos, nroIngreso);

        if (ingresoExistente)
        {
            system("pause");

            ingresoExistente->ingreso.eliminado = 1;
            gotoxy(15, 6);
            printf("Se dio de baja al ingreso.");
        }
        else
        {
            system("cls");
            Rectangulo();
            gotoxy(15, 6);
            printf("El numero de ingreso cargado no esta registrado en la base de datos.\n");
            system("pause");
        }
        system("cls");
        Rectangulo();
        gotoxy(15, 8);
        printf("Desea dar de baja otro ingreso? (S/N): ");
        fflush(stdin);
        opcion = getch();

    } while (opcion == 's' || opcion == 'S');

    system("cls");
}
