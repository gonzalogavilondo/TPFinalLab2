#include "stPracticaXIngreso.h"
#include "stIngreso.h"
#include "stPractica.h"
#include "menu.h"

nodoPracticaXIngreso* inicListaPracticaXIngresos()
{
    return NULL;
}

/**
    La funci�n (crearNodoPracticaXIngreso), que reciba como par�metro un registro de tipo stPractica, y
    devuelva un nodo de tipo nodoPracticaXIngreso
**/
nodoPracticaXIngreso* crearNodoPracticaXIngreso(stPracticaXIngreso registro)
{
    nodoPracticaXIngreso *nuevo = (nodoPracticaXIngreso*) malloc(sizeof(nodoPracticaXIngreso));
    if(nuevo == NULL)
    {
        printf("No se ha podido reservar espacio en memoria.\n");
        exit(1);
    }

    nuevo->practicaXIngreso.nroIngreso = registro.nroIngreso;
    nuevo->practicaXIngreso.nroPractica = registro.nroPractica;
    strcpy(nuevo->practicaXIngreso.resultado, registro.resultado);
    nuevo->practicaXIngreso.eliminado = registro.eliminado;
    nuevo->siguiente = NULL;

    return nuevo;
}

/**
    La funci�n (agregarNodoPracticaXIngreso), que reciba la lista, un registro del tipo stPracticaXIngreso
    se agrega un nodo al final de la lista. Retornar la lista.
**/
nodoPracticaXIngreso* agregarNodoPracticaXIngreso(nodoPracticaXIngreso *lista, stPracticaXIngreso registro)
{
    nodoPracticaXIngreso *nuevo = crearNodoPracticaXIngreso(registro); ///Creo el nodo con la funcion anterior, con el registro que paso por parametro

    if(lista == NULL) ///Si la lista esta vacia, agrego en la posicion del primer elemento.
    {
        lista = nuevo;
    }
    else
    {
        nodoPracticaXIngreso *ultimo = buscaUltimoLista(lista);
        ultimo->siguiente = nuevo;
    }

    return lista;
}

nodoPracticaXIngreso* buscaUltimoLista(nodoPracticaXIngreso *lista)
{
    nodoPracticaXIngreso *seg = lista;
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
    La funci�n (crearListaPracticaXIngreso) permite recorrer el archivo y crear la lista de ingresos. La funci�n puede
    recibir como par�metro el nombre del archivo o puede no recibir� ese par�metro si as� lo prefiere. Retornar la lista
**/

nodoPracticaXIngreso* crearListaPracticaXIngreso(const char *nombreArchivo)
{
    nodoPracticaXIngreso *lista = inicListaPracticaXIngresos();
    stPracticaXIngreso practicaNueva; //Registro donde voy a guardar lo levantado
    FILE *archivo = fopen(nombreArchivo, "rb");

    /// Veo si se pudo abrir el archivo
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        exit(1); // Codigo de error
    }

    rewind(archivo);
    while(fread(&practicaNueva, sizeof(stPracticaXIngreso), 1, archivo) > 0) //fread devuelve el numero de datos leidos
    {
        lista = agregarNodoPracticaXIngreso(lista, practicaNueva);
    }
    fclose(archivo);
    return lista;
}

/**
    La funci�n (mostrarPracticaXIngreso) que permita recorrer y mostrar la lista. La misma debe ser recursiva
**/

void mostrarUnNodoPracticaXIngreso(nodoPracticaXIngreso *aux)
{
    if (aux != NULL)
    {
        puts("-----------------------------------------------------\n");
        printf("Numero de ingreso...........: %d\n", aux->practicaXIngreso.nroIngreso);
        printf("Numero de practica..........: %d\n", aux->practicaXIngreso.nroPractica);
        printf("Resultado...................: %s\n", aux->practicaXIngreso.resultado);
        printf("Eliminado...................: %d <1:SI/0:NO>\n", aux->practicaXIngreso.eliminado);
        puts("-----------------------------------------------------\n");
    }
    else
    {
        printf("Nodo no v�lido.\n");
    }
}

void mostrarPracticaXIngreso(nodoPaciente *arbolPacientes)
{
    if (arbolPacientes != NULL)
    {
        printf("\n*** Listado de Practicas por Ingreso del Paciente ***\n");
        muestraUnPacienteResumido(arbolPacientes->datosPaciente);

        if (arbolPacientes->listaIngresos != NULL)
        {
            nodoPracticaXIngreso *practicasXIngreso = arbolPacientes->listaIngresos->listaPracticasXIngreso;

            if (practicasXIngreso == NULL)
            {
                printf("\nEl paciente no tiene practicas por ingreso.\n");
                puts("--------------------------------------\n");
                system("pause");
            }
            else
            {
                while (practicasXIngreso != NULL)
                {
                    mostrarUnNodoPracticaXIngreso(practicasXIngreso);
                    practicasXIngreso = practicasXIngreso->siguiente;
                }

                printf("\n*** Fin del Listado de Practicas por Ingreso del Paciente ***\n");
                puts("----------------------------------------------\n");
            }
        }
        else
        {
            printf("\n*** No hay ningun ingreso para el paciente. ***\n");
            puts("----------------------------------------------\n");
            system("pause");
            system("cls");
        }

        mostrarPracticaXIngreso(arbolPacientes->izq);
        mostrarPracticaXIngreso(arbolPacientes->der);
    }
}




/**
    La funci�n (liberarListaPracticaXIngreso), que reciba la lista y hacer lo indicado. La funci�n no debe retornar nada (no importa que
    la cabecera no quede en NULL)
**/

nodoPracticaXIngreso* liberarListaPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    nodoPracticaXIngreso *proximo;
    nodoPracticaXIngreso *seg = lista;

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
    agregar ese pedido a la lista y retornar la nueva lista con el nuevo ingreso.
**/

nodoPracticaXIngreso* cargarPracticaXIngreso(nodoPracticaXIngreso *lista, int nroIngreso, int nroPractica)
{
    stPracticaXIngreso registro;

    registro.nroIngreso = nroIngreso;
    registro.nroPractica = nroPractica;
    gotoxy(15,7);
    printf("Ingrese el resultado obtenido: ");
    fflush(stdin);
    gets(registro.resultado);
    registro.eliminado = 0;
    lista = agregarNodoPracticaXIngreso(lista, registro); ///Finalmente agrego el pedido a la lista

    return lista;
}

int existePracticaXIngreso(nodoPracticaXIngreso * listaPracticasXIngreso, int nroIngreso, int nroPractica)
{
    int existe = 0;

    while (listaPracticasXIngreso && !existe) {

        if ((listaPracticasXIngreso->practicaXIngreso.nroIngreso = nroIngreso) && (listaPracticasXIngreso->practicaXIngreso.nroPractica = nroPractica))
        {
            existe = 1;
        }

        listaPracticasXIngreso = listaPracticasXIngreso->siguiente;
    }

    return existe;
}

/**
* Funci�n para dar de alta un ingreso con al menos una pr�ctica de laboratorio
**/
void altaDePracticaXIngreso(nodoPaciente *arbolPacientes, int altaIngreso)
{
    int nroIngreso, nroPractica, dni,
        error = 0;

    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Alta de Practica por Ingreso");

        gotoxy(15, 4);
        printf("Cargue el numero de practica: ");
        scanf("%d", &nroPractica);

        if (!existePracticaXnroPractica(nroPractica))
        {
            gotoxy(15, 8);
            printf("No existe la practica con ese numero en la base de datos.");
        }
        else
        {
            if(altaIngreso == 1) ///Si se llama a este alta mediante el alta de ingresos
            {
                nodoPaciente *paciente = inicArbolPacientes();
                paciente = buscaPaciente(arbolPacientes, arbolPacientes->datosPaciente.dni);
                system("cls");
                mostrarListadoIngresosPaciente(paciente);
                printf("Cargue el numero de ingreso: ");
                scanf("%d", &nroIngreso);
                system("cls");
                Rectangulo();
                gotoxy(15, 1);
                cabeza("Alta de Practica por Ingreso");
                if (!existeIngresoXnroIngreso(nroIngreso))
                {
                    gotoxy(15, 8);
                    printf("No existe el ingreso con ese numero en la base de datos.");
                    error = 1;
                }
            }
            else ///Se llama al alta de practicas por ingreso sin dar un alta de ingreso
            {
                system("cls");
                Rectangulo();
                gotoxy(5, 4);
                printf("Ingrese el numero de DNI del paciente a modificar: ");
                scanf("%d", &dni);
                arbolPacientes = buscaPaciente(arbolPacientes, dni);

            }
            if(error == 0)
            {
                nodoPracticaXIngreso *practicasXIngreso = inicListaPracticaXIngresos();
                if(arbolPacientes->listaIngresos) ///Si existe un ingreso para el paciente
                {
                    arbolPacientes->listaIngresos->listaPracticasXIngreso = practicasXIngreso;
                    // Crear un nuevo nodo de pr�ctica por ingreso y agregarlo a la lista
                    arbolPacientes->listaIngresos->listaPracticasXIngreso = cargarPracticaXIngreso(arbolPacientes->listaIngresos->listaPracticasXIngreso, nroIngreso, nroPractica);
                    gotoxy(15, 9);
                    printf("Practica por ingreso registrada con exito.\n");
                }
                else
                {
                    system("cls");
                    Rectangulo();
                    gotoxy(15, 1);
                    printf("No existe un ingreso para ese paciente.\n");
                }
            }
        }
        gotoxy(15, 10);
        system("pause");
        system("cls");
        Rectangulo();
        gotoxy(15, 8);
        printf("Desea cargar otra practica por ingreso? (S/N): ");
        fflush(stdin);
        opcion = getch();
        system("cls");

    } while (opcion == 's' || opcion == 'S');
}

nodoPracticaXIngreso *buscaPracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos, int nroPractica)
{
    nodoPracticaXIngreso *seg;
    seg = listaPracticaXIngresos;
    while ( (seg != NULL) && (seg->practicaXIngreso.nroPractica != nroPractica) )
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodoPracticaXIngreso *modificarDatosPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    nodoPracticaXIngreso *practicaXingresoExistente = inicListaPracticaXIngresos();

    int nroPractica;
    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Modificar Practica por Ingreso");

        gotoxy(15, 4);
        printf("Ingrese el numero de practica: ");
        scanf("%d", &nroPractica);

        practicaXingresoExistente = buscaPracticaXIngreso(lista, nroPractica);

        if (practicaXingresoExistente)
        {
            do
            {
                system("cls");
                Rectangulo();
                gotoxy(15, 1);
                cabeza("Modificar Practica por Ingreso");

                mostrarUnNodoPracticaXIngreso(practicaXingresoExistente);

                gotoxy(15, 10);
                printf("Que dato desea modificar? Ingrese una opcion:");
                gotoxy(15, 12);
                printf("1. Numero de practica");
                gotoxy(15, 13);
                printf("2. Resultado");

                opcion = getch();
                system("cls");

                switch (opcion)
                {
                    case '1':
                        gotoxy(15, 4);
                        printf("Ingrese el nuevo numero de practica: ");
                        scanf("%d", &nroPractica);
                        practicaXingresoExistente->practicaXIngreso.nroPractica = nroPractica;
                        break;
                    case '2':
                        gotoxy(15, 4);
                        printf("Ingrese un nuevo resultado: ");
                        fflush(stdin);
                        fgets(practicaXingresoExistente->practicaXIngreso.resultado, sizeof(practicaXingresoExistente->practicaXIngreso.resultado), stdin);
                        break;
                    default:
                        // Opcion incorrecta, se vuelve a mostrar el menu
                        break;
                }

                if (opcion == '1' || opcion == '2')
                {
                    system("cls");
                    Rectangulo();
                    gotoxy(15, 1);
                    cabeza("Modificar Practica por Ingreso");

                    mostrarUnNodoPracticaXIngreso(practicaXingresoExistente);

                    gotoxy(15, 10);
                    printf("Desea modificar otro dato de la practica por ingreso? (S/N): ");
                    opcion = getch();
                    system("cls");
                }

            } while (opcion == 's' || opcion == 'S');
        }
        else
        {
            gotoxy(15, 10);
            printf("El numero de practica cargado no esta registrado en la base de datos de practica por ingreso.");
        }

        gotoxy(15, 12);
        printf("\nPresione S para intentar modificar otra practica por ingreso, cualquier otra tecla para finalizar...");
        opcion = getch();
        system("cls");

    } while (opcion == 's' || opcion == 'S');

    return lista;
}

void buscaYDaDeBajaPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    int nroPractica;
    char opcion = 0;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Baja de Practica por Ingreso");

        gotoxy(15, 4);
        printf("Ingrese el numero de la practica a dar de baja: ");
        scanf("%d", &nroPractica);

        nodoPracticaXIngreso *practicaXingresoExistente = buscaPracticaXIngreso(lista, nroPractica);

        if (practicaXingresoExistente)
        {
            practicaXingresoExistente->practicaXIngreso.eliminado = 1;
            gotoxy(15, 6);
            printf("Se dio de baja a la practica por ingreso.");
        }
        else
        {
            gotoxy(15, 6);
            printf("El numero de practica cargado no esta registrado en la base de datos de practica por ingreso.");
        }

        gotoxy(15, 8);
        printf("Desea dar de baja otra practica por ingreso? (S/N): ");
        fflush(stdin);
        opcion = getch();
        system("cls");

    } while (opcion == 's' || opcion == 'S');
}

