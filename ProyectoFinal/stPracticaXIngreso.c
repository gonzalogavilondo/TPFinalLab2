#include "stPracticaXIngreso.h"
#include "stIngreso.h"
#include "stPractica.h"
#include "menu.h"

nodoPracticaXIngreso* inicListaPracticaXIngresos()
{
    return NULL;
}

/**
    La función (crearNodoPracticaXIngreso), que reciba como parámetro un registro de tipo stPractica, y
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
    La función (agregarNodoPracticaXIngreso), que reciba la lista, un registro del tipo stPracticaXIngreso
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
    La función (crearListaPracticaXIngreso) permite recorrer el archivo y crear la lista de ingresos. La función puede
    recibir como parámetro el nombre del archivo o puede no recibiré ese parámetro si así lo prefiere. Retornar la lista
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
    La función (mostrarPracticaXIngreso) que permita recorrer y mostrar la lista. La misma debe ser recursiva
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
        printf("Nodo no válido.\n");
    }
}

void mostrarPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    if(lista != NULL)
    {
        mostrarUnNodoPracticaXIngreso(lista);
        mostrarPracticaXIngreso(lista->siguiente);
    }
}

/**
    La función (liberarListaPracticaXIngreso), que reciba la lista y hacer lo indicado. La función no debe retornar nada (no importa que
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
    La función (cargarIngreso), la cual recibirá la lista y solicitará al usuario los datos del pedido para finalmente
    agregar ese pedido a la lista y retornar la nueva lista con el nuevo ingreso.
**/

nodoPracticaXIngreso* cargarPracticaXIngreso(nodoPracticaXIngreso *lista, int nroIngreso, int nroPractica)
{
    stPracticaXIngreso registro;

    registro.nroIngreso = nroIngreso;
    registro.nroPractica = nroPractica;
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
* Función para dar de alta un ingreso con al menos una práctica de laboratorio
**/
nodoPracticaXIngreso* altaDePracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos)
{
    int nroIngreso, nroPractica;
    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Alta de Practica por Ingreso");

        gotoxy(15, 4);
        printf("Cargue el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        gotoxy(15, 6);
        printf("Cargue el numero de practica: ");
        scanf("%d", &nroPractica);

        if (!existeIngresoXnroIngreso(nroIngreso))
        {
            gotoxy(15, 8);
            printf("No existe el ingreso con ese numero en la base de datos.");
        }
        else if (!existePracticaXnroPractica(nroPractica))
        {
            gotoxy(15, 8);
            printf("No existe la practica con ese numero en la base de datos.");
        }
        else
        {
            // Crear un nuevo nodo de práctica por ingreso y agregarlo a la lista
            listaPracticaXIngresos = cargarPracticaXIngreso(listaPracticaXIngresos, nroIngreso, nroPractica);

            gotoxy(15, 8);
            printf("Practica por ingreso registrada con éxito.");
        }

        gotoxy(15, 10);
        printf("Desea cargar otra practica por ingreso? (S/N): ");
        fflush(stdin);
        opcion = getch();
        system("cls");

    } while (opcion == 's' || opcion == 'S');

    return listaPracticaXIngresos;
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
        printf("Ingrese el numero de la practica a dar de baja dentro de los ingresos: ");
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

