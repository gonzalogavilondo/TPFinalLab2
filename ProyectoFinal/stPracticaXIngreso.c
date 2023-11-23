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
        puts("  -----------------------------------------------------\n");
        printf("  Numero de ingreso...........: %d\n", aux->practicaXIngreso.nroIngreso);
        printf("  Numero de practica..........: %d\n", aux->practicaXIngreso.nroPractica);
        printf("  Resultado...................: %s\n", aux->practicaXIngreso.resultado);
        printf("  Eliminado...................: %d <1:SI/0:NO>\n", aux->practicaXIngreso.eliminado);
        puts("  -----------------------------------------------------\n");
    }
    else
    {
        printf("Nodo no válido.\n");
    }
}

void mostrarPracticaXIngreso(nodoPaciente *arbolPacientes, int flag) ///El flag indica si se llama desde el administrador (=1) o administrativo (=0)
{
    if (arbolPacientes != NULL)
    {
        printf("\n*** Listado de Practicas por Ingreso del Paciente ***\n");
        muestraUnPacienteResumido(arbolPacientes->datosPaciente);

        nodoIngreso * seguidoraIngresos = arbolPacientes->listaIngresos;

        while (seguidoraIngresos)
        {
            nodoPracticaXIngreso *practicasXIngreso = seguidoraIngresos->listaPracticasXIngreso;

            if (practicasXIngreso == NULL && seguidoraIngresos->ingreso.eliminado == 0)
            {
                printf("\nEl paciente no tiene practicas activas en el ingreso N%c%d.\n", 248, seguidoraIngresos->ingreso.numeroIngreso);
                puts("--------------------------------------\n");
            }
            else
            {
                int todasLasPracticasEnBaja = 1;
                while (practicasXIngreso != NULL)
                {
                    if (flag == 1 || (flag == 0 && practicasXIngreso->practicaXIngreso.eliminado == 0))
                    {
                        mostrarUnNodoPracticaXIngreso(practicasXIngreso);
                        todasLasPracticasEnBaja = 0;

                    }
                    practicasXIngreso = practicasXIngreso->siguiente;
                }

                if (todasLasPracticasEnBaja && seguidoraIngresos->ingreso.eliminado == 0) {
                    printf("\nEl paciente no tiene practicas activas en el ingreso N%c%d.\n", 248, seguidoraIngresos->ingreso.numeroIngreso);
                } else if(seguidoraIngresos->ingreso.eliminado == 0) {
                    printf("\n*** Fin del Listado de Practicas por el Ingreso N%c%d. ***\n", 248, seguidoraIngresos->ingreso.numeroIngreso);
                    puts("----------------------------------------------\n");
                }
            }

            seguidoraIngresos = seguidoraIngresos->siguiente;
        }

        if (arbolPacientes->listaIngresos == NULL)
        {
            printf("\n*** No hay ningun ingreso para el paciente. ***\n");
            puts("----------------------------------------------\n");
        }

        system("pause");
        system("cls");

        mostrarPracticaXIngreso(arbolPacientes->izq, flag);
        mostrarPracticaXIngreso(arbolPacientes->der, flag);
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
* Función para dar de alta un ingreso con al menos una práctica de laboratorio
**/
void altaDePracticaXIngreso(nodoPaciente *arbolPacientes, int altaIngreso)
{
    int nroIngreso, nroPractica, dni, error = 0, ingresoValido = 0;
    char opcion = 0;

    do
    {
        system("cls");

        /// Leo el archivo de practicas y las cargo en una lista:
        nodoPractica * listaPracticas = inicListaPracticas();
        listaPracticas = archivoToListaPracticas(listaPracticas);

        muestraListaPracticas2(listaPracticas);

        gotoxy(0, 0);
        gotoxy(0, 2);
        printf("Cargue el numero de");
        gotoxy(0, 3);
        printf("practica que desea dar de alta: ");
        scanf("%d", &nroPractica);

        /// chequear si en caso de ingresar un numero de practica que este
        /// eliminada, avanza o no, no deberia...

        if (!existePracticaXnroPractica(nroPractica))
        {
            gotoxy(15, 8);
            printf("No existe la practica con ese numero en la base de datos.\n");
        }
        else
        {
            nodoPaciente *paciente = inicArbolPacientes();
            if (altaIngreso == 1) ///Si altaIngreso == 1, quiere decir que se llamo desde el menu de ingresos, ya tiene el DNI
            {
                paciente = buscaPaciente(arbolPacientes, arbolPacientes->datosPaciente.dni);
            }
            else ///Sino, es que se llamo del menu de practicaxIngreso y no tiene el dni
            {
                system("cls");
                Rectangulo();
                gotoxy(5, 4);
                printf("Ingrese el numero de DNI del");
                gotoxy(5, 5);
                printf("paciente al que le carga la practica: ");
                scanf("%d", &dni);
                paciente = buscaPaciente(arbolPacientes, dni);
            }
            system("cls");
            do
            {
                mostrarListadoIngresosPaciente(paciente);
                printf("Cargue el numero de ingreso: ");
                scanf("%d", &nroIngreso);
                if (!existeIngreso(paciente))
                {
                    gotoxy(15, 8);
                    printf("No existe ningun ingreso para ese paciente en la base de datos. Primero asignele uno\n");
                    error = 1;
                    ingresoValido = 1;
                }
                else
                {
                    ingresoValido = existeIngresoXnroIngreso(paciente, nroIngreso);
                    if(!ingresoValido)
                    {
                        system("cls");
                        Rectangulo();
                        gotoxy(15, 4);
                        printf("No existe el ingreso con ese numero en la base de datos.\n");
                        gotoxy(15, 5);
                        printf("Intente nuevamente con un ingreso valido.\n\n");
                        gotoxy(15, 8);
                        system("pause");
                        system("cls");

                    }
                }
            }while(!ingresoValido);

            system("cls");
            Rectangulo();
            gotoxy(15, 1);
            cabeza("Alta de Practica por Ingreso");

            if (error == 0)
            {
                /// Si es la primera vez que se usa la practica, se setea en 1 el campo tieneAlMenosUnUso:
                // Leo el archivo de practicas y las cargo en una lista:
                nodoPractica * listaPracticas = inicListaPracticas();
                listaPracticas = archivoToListaPracticas(listaPracticas);
                nodoPractica * nodoBuscado;
                // esta funcion devuelve NULL si no encontro el nodo
                nodoBuscado = buscaPracticaPorNroPractica(listaPracticas, nroPractica);
                if (nodoBuscado && !(nodoBuscado->datosPractica.tieneAlMenosUnUso))
                {
                    nodoBuscado->datosPractica.tieneAlMenosUnUso = 1;
                }
                liberarListaPracticas(listaPracticas);

                nodoIngreso *ingresoElegido = buscaIngreso(paciente->listaIngresos, nroIngreso);

                if (ingresoElegido)
                {
                    // Crear un nuevo nodo de práctica por ingreso y agregarlo a la lista
                    ingresoElegido->listaPracticasXIngreso = cargarPracticaXIngreso(
                        ingresoElegido->listaPracticasXIngreso, nroIngreso, nroPractica);

                }
                else // si el paciente no tiene ningun ingreso cargado, hay que cargar el primero:
                {
                    altaDeIngreso(paciente);
                }

                gotoxy(15, 9);
                printf("Practica por ingreso registrada con exito.\n");
            }
        }

        gotoxy(15, 11);
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

    nodoPracticaXIngreso *seg = listaPracticaXIngresos;

    while (seg != NULL) {

        if (seg->practicaXIngreso.nroPractica == nroPractica) {

            return seg;
        }
        seg = seg->siguiente;
    }

    return NULL;
}
/*
void modificarDatosPracticaXIngreso(nodoPaciente *arbolPacientes)
{
    nodoPracticaXIngreso *practicaXingresoExistente = inicListaPracticaXIngresos();

    nodoPaciente * paciente;

    int nroPractica;
    int nroDNI;
    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Registrar resultado en Practica por Ingreso");

        gotoxy(1, 4);
        printf("Ingrese el numero de practica: ");
        scanf("%d", &nroPractica);
        gotoxy(1, 5);
        printf("Ingrese el numero de DNI: ");
        scanf("%d", &nroDNI);

        paciente = buscaPaciente(arbol, nroDNI);

        if(paciente)
        {
            practicaXingresoExistente = buscaPracticaXIngreso(paciente->listaIngresos->listaPracticasXIngreso, nroPractica);

            if (practicaXingresoExistente)
            {
                do
                {
                    system("cls");
                    Rectangulo();
                    gotoxy(15, 1);
                    cabeza("Que desea modificar?");


                    gotoxy(1, 3);


                    gotoxy(1, 6);
                    printf("Ingrese un nuevo resultado: ");
                    fflush(stdin);
                    fgets(practicaXingresoExistente->practicaXIngreso.resultado, sizeof(practicaXingresoExistente->practicaXIngreso.resultado), stdin);

                    gotoxy(1, 10);
                    printf("Desea cargar registrar otro resultado? (S/N): ");
                    opcion = getch();
                    system("cls");
                }
                while (opcion == 's' || opcion == 'S');
            }
            else
            {
                gotoxy(1, 13);
                printf("El numero de practica cargado no existe.");
                getch();
            }
            system("cls");
            Rectangulo();
            gotoxy(1, 15);
            printf("Presione S para modificar otra, cualquier otra tecla para finalizar");
            opcion = getch();
            system("cls");

        }else{
            gotoxy(1,15);
            printf("No existe paciente con el dni ingresado! Quiere reintentar? (S/N)");
            opcion = getch();
        }

    }while (opcion == 's' || opcion == 'S' );
}
*/
void buscaYDaDeBajaPracticaXIngreso(nodoPracticaXIngreso *lista)
{
    int nroPractica;
    char opcion = 0;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Baja de Practica por Ingreso");
        mostrarUnNodoPracticaXIngreso(lista);
        gotoxy(15, 4);
        printf("Ingrese el numero de la practica a dar de baja: ");
        scanf("%d", &nroPractica);
        system("cls");
        nodoPracticaXIngreso *practicaXingresoExistente = buscaPracticaXIngreso(lista, nroPractica);
        Rectangulo();
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

void registrarResultadoPracticaXIngreso(nodoPaciente *arbol)
{
    nodoPracticaXIngreso *practicaXingresoExistente = inicListaPracticaXIngresos();
    nodoIngreso *ingreso = NULL;

    nodoPaciente * paciente;

    int nroPractica;
    int nroIngreso;
    int nroDNI;
    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Registrar resultado en Practica por Ingreso");

        gotoxy(1, 4);
        printf("Ingrese el numero de DNI: ");
        scanf("%d", &nroDNI);
        gotoxy(1, 5);
        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        gotoxy(1, 6);
        printf("Ingrese el numero de practica: ");
        scanf("%d", &nroPractica);

        paciente = buscaPaciente(arbol, nroDNI);

        if(paciente)
        {
            ingreso = buscaIngreso(paciente->listaIngresos, nroIngreso);

            if(ingreso)
            {

                practicaXingresoExistente = buscaPracticaXIngreso(ingreso->listaPracticasXIngreso, nroPractica);

                if (practicaXingresoExistente)
                {
                    do
                    {
                        system("cls");
                        Rectangulo();
                        gotoxy(15, 1);
                        cabeza("Registrar resultado en Practica por Ingreso");

                        gotoxy(1, 3);
                        printf("Numero de ingreso: %d", practicaXingresoExistente->practicaXIngreso.nroIngreso);

                        gotoxy(1, 4);
                        printf("Numero de practica: %d", practicaXingresoExistente->practicaXIngreso.nroPractica);

                        gotoxy(1, 6);
                        printf("Ingrese un nuevo resultado: ");
                        fflush(stdin);
                        fgets(practicaXingresoExistente->practicaXIngreso.resultado, sizeof(practicaXingresoExistente->practicaXIngreso.resultado), stdin);

                        gotoxy(1, 10);
                        printf("Desea cargar registrar otro resultado? (S/N): ");
                        opcion = getch();
                        system("cls");
                    }
                    while (opcion == 's' || opcion == 'S');
                }
                else
                {
                    gotoxy(1, 13);
                    printf("El numero de practica cargado no existe.");
                    getch();
                }


            }
            else
            {
                gotoxy(1, 13);
                printf("El numero de ingreso cargado no existe.");
                getch();
            }
            system("cls");
            Rectangulo();
            gotoxy(1, 15);
            printf("'S' para registrar otro resultado, cualquier tecla para finalizar");
            opcion = getch();
            system("cls");

        }
        else
        {
            gotoxy(1,15);
            printf("No existe paciente con el dni ingresado! Quiere reintentar? (S/N)");
            opcion = getch();
        }

    }
    while (opcion == 's' || opcion == 'S' );
}
/// SE USA EN stPaciente.c AL DAR DE BAJA A UN PACIENTE EN CASCADA:

void darDeBajaTodasLasPracticasXIngreso(nodoPracticaXIngreso * listaPracticasXIngreso)
{
    while (listaPracticasXIngreso) {
        listaPracticasXIngreso->practicaXIngreso.eliminado = 1;
        listaPracticasXIngreso = listaPracticasXIngreso->siguiente;
    }
}

void mostrarUnaPracticaXIngreso(nodoPaciente *arbol)
{
    nodoPracticaXIngreso *practicaXingresoExistente = inicListaPracticaXIngresos();
    nodoIngreso *ingreso = NULL;

    nodoPaciente * paciente;

    int nroPractica;
    int nroIngreso;
    int nroDNI;
    char opcion = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Mostrar Practica por Ingreso");

        gotoxy(1, 4);
        printf("Ingrese el numero de DNI: ");
        scanf("%d", &nroDNI);
        gotoxy(1, 5);
        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        gotoxy(1, 6);
        printf("Ingrese el numero de practica: ");
        scanf("%d", &nroPractica);

        paciente = buscaPaciente(arbol, nroDNI);

        if(paciente)
        {

            ingreso = buscaIngreso(paciente->listaIngresos, nroIngreso);

            if(ingreso)
            {
                practicaXingresoExistente = buscaPracticaXIngreso(ingreso->listaPracticasXIngreso, nroPractica);

                if (practicaXingresoExistente)
                {
                    do
                    {
                        gotoxy(1, 7);
                        printf("Numero de ingreso...........: %d", practicaXingresoExistente->practicaXIngreso.nroIngreso);
                        gotoxy(1, 8);
                        printf("Resultado...................: %s", practicaXingresoExistente->practicaXIngreso.resultado);
                        gotoxy(1, 9);
                        printf("Eliminado...................: %d <1:SI/0:NO>", practicaXingresoExistente->practicaXIngreso.eliminado);

                        gotoxy(1, 10);
                        printf("Desea ver otra practica por ingreso? (S/N): ");
                        opcion = getch();
                        system("cls");
                    }
                    while (opcion == 's' || opcion == 'S');
                }
                else
                {
                    gotoxy(1, 13);
                    printf("El numero de practica cargado no existe");
                }

                gotoxy(1, 15);
                printf("Presione S para seguir visualizando, cualquier otra tecla para finalizar");
                opcion = getch();
                system("cls");
            }
            else
            {

                gotoxy(1,15);
                printf("No existe ingreso con el numero ingresado! Quiere reintentar? (S/N)");
                opcion = getch();

            }
        }
        else
        {

            gotoxy(1,15);
            printf("No existe paciente con el dni ingresado! Quiere reintentar? (S/N)");
            opcion = getch();
        }
    }
    while (opcion == 's' || opcion == 'S');
}

int cantidadPracticasXIngreso(nodoPaciente * arbol){
    int cant = 0;
    if (arbol!=NULL){
        nodoIngreso * segIngresos = arbol->listaIngresos;
        while(segIngresos != NULL){
            segIngresos = segIngresos->siguiente;
            cant ++;
        }
    }
    return cant;
}
