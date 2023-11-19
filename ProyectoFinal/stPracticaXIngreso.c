#include "stPracticaXIngreso.h"
#include "stIngreso.h"
#include "stPractica.h"

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

void mostrarPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    if(lista != NULL)
    {
        mostrarUnNodoPracticaXIngreso(lista);
        mostrarPracticaXIngreso(lista->siguiente);
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
nodoPracticaXIngreso* altaDePracticaXIngreso(nodoPracticaXIngreso *listaPracticaXIngresos)
{
    int nroIngreso, nroPractica;
    char opcion = 0;
    // Verificar existencia del nro de ingreso y de practica
    do
    {
        printf("Cargue el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        printf("Cargue el numero de practica: ");
        scanf("%d", &nroPractica);
        if(!existeIngresoXnroIngreso(nroIngreso))
        {
            printf("\nNo existe el ingreso con ese numero de ingreso en la base de datos\n.");
        }
        else if(!existePracticaXnroPractica(nroPractica))
        {
            printf("\nNo existe la practica con ese numero de practica en la base de datos\n.");
        }
        else
        {
            // Crear un nuevo nodo de ingreso y se agrega a la lista
            listaPracticaXIngresos = cargarPracticaXIngreso(listaPracticaXIngresos, nroIngreso, nroPractica);

            printf("Practica por ingreso registrada con �xito.\n");
        }
        printf("\n\n Para cargar otra practica por ingreso presione cualquier tecla, ESC para finalizar...");
        opcion = getch();
        system("cls");
    }while (opcion != ESC);

    return listaPracticaXIngresos;
}
