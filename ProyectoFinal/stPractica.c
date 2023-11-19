#include "stPractica.h"
#include "stPaciente.h"

void menuProvisorioGestionarPracticas(){
    char opcion = 0;

    /// para opciones de GESTIONAR PRACTICAS:
    nodoPractica * listaPracticas = inicListaPracticas();

    do {

        system("cls");
        printf("\n              Menu provisorio para 'Gestionar practicas':");
        printf("\n\n                                          1. Dar de alta practicas.");
        printf("\n                                          2. Modificar el nombre de una practica.");
        printf("\n                                          3. Dar de baja una practica.");

        printf("\n\n\n                                     Para probar \"GESTIONAR PRACTICAS\":");
        printf("\n\n                                          4. Mostrar lista practicas.");
        printf("\n                                          5. Guardar lista en un archivo binario.");
        printf("\n                                          6. Cargar datos de las practicas del archivo en una lista(si se uso la opcion 1,");
        printf("\n                                             se sobreescriben los datos).");

        printf("\n\n                                          ESC para finalizar...");
        fflush(stdin);
        opcion = getch();
        system("cls");


        switch (opcion) {
            case ESC:
                // finaliza el programa...
                break;

            case 49: // opcion 1: Dar de alta practicas.

                listaPracticas = darDeAltaPracticas(listaPracticas);
                break;

            case 50: // opcion 2: Modificar el nombre de una practica.

                if (listaPracticas) {
                    manejaModificarOBajaDePractica(listaPracticas, 1);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                    textoPresioneCualquierTecla();
                }
                break;

            case 51: // opcion 3: Dar de baja una practica.

                if (listaPracticas) {
                    manejaModificarOBajaDePractica(listaPracticas, 2);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                    textoPresioneCualquierTecla();
                }
                break;


    // Para probar "GESTIONAR PRACTICAS":

            case 52: // opcion 4: Mostrar lista practicas.

                if (listaPracticas) {
                    printf("\n Lista de practicas, ordenada por nombre:\n\n");
                    muestraListaPacientes(listaPracticas);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;

            case 53: // opcion 5: Guardar lista en un archivo binario.

                if (listaPracticas) {
                    guardaListaPracticasEnArchivo(listaPracticas);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;

            case 54: // opcion 6: Cargar datos de las practicas del archivo en una lista(si se uso la opcion 1, se sobreescriben los datos).

                if (listaPracticas) {
                    liberarListaPracticas(listaPracticas);
                    listaPracticas = inicListaPracticas();
                }

                listaPracticas = archivoToListaPracticas(listaPracticas);

                textoPresioneCualquierTecla();
                break;

            default:
                // opcion incorrecta, se vuelve a mostrar el menu
                break;
        }

    } while (opcion != ESC);
}

/// FUNCIONES PARA LA OPCION 1:

nodoPractica * inicListaPracticas(){
    return NULL;
}

nodoPractica * crearNodoPractica(stPractica nuevaPractica){
    nodoPractica * nodoNuevo = (nodoPractica *) malloc(sizeof(nodoPractica));

    nodoNuevo->datosPractica = nuevaPractica;
    nodoNuevo->siguiente = NULL;

    return nodoNuevo;
}

int tamanioListaPracticas(nodoPractica * listaPracticas){
    int tamanio = 0;

    while (listaPracticas) {
        tamanio++;
        listaPracticas = listaPracticas->siguiente;
    }

    return tamanio;
}

nodoPractica * agregarPracticaPpio(nodoPractica * listaPracticas, nodoPractica * nuevoNodo){

    if(listaPracticas) {
        nuevoNodo->siguiente = listaPracticas;
        listaPracticas = nuevoNodo;
    }else{
        listaPracticas = nuevoNodo;
    }
    return listaPracticas;

}

nodoPractica * agregaNodoPracticaOrdenadoXNombre(nodoPractica * listaPracticas, nodoPractica * nuevoNodo){

    nodoPractica * auxiliar = listaPracticas;
    nodoPractica * seguidora = listaPracticas;

    if (listaPracticas == NULL || strcmpi(auxiliar->datosPractica.nombrePractica, nuevoNodo->datosPractica.nombrePractica)>0) {

        listaPracticas = agregarPracticaPpio(listaPracticas, nuevoNodo);

    } else {

        while(auxiliar!=NULL && strcmpi(auxiliar->datosPractica.nombrePractica, nuevoNodo->datosPractica.nombrePractica)<0){
            seguidora = auxiliar;
            auxiliar = auxiliar->siguiente;
        }
        seguidora->siguiente = nuevoNodo;
        nuevoNodo->siguiente = auxiliar;

    }

    return listaPracticas;
}

// devuelve NULL si no encuentra la practica, el nodo de la practica en caso de encontrarla:
nodoPractica * buscaPracticaPorNombre(nodoPractica * listaPracticas, char nombreBusqueda[]){

    while (listaPracticas && strcmpi(listaPracticas->datosPractica.nombrePractica, nombreBusqueda) != 0) {
        listaPracticas = listaPracticas->siguiente;
    }

    return listaPracticas;
}

nodoPractica * darDeAltaPracticas(nodoPractica * listaPracticas){

    char opcion;
    stPractica nuevaPractica;

    do {

        printf("\n Ingrese el nombre de la practica: ");
        fflush(stdin);
        gets(nuevaPractica.nombrePractica);

        if (buscaPracticaPorNombre(listaPracticas, nuevaPractica.nombrePractica)) {
            printf("\n La practica ingresada ya existe en la base de datos.");
        } else {
            nuevaPractica.eliminado = 0;
            nuevaPractica.nroPractica = tamanioListaPracticas(listaPracticas) + 1;

            listaPracticas = agregaNodoPracticaOrdenadoXNombre(listaPracticas, crearNodoPractica(nuevaPractica));
            printf("\n Se agrego la practica.");
        }

        printf("\n\n Presione cualquier tecla para agregar otra practica, ESC para finalizar...");
        fflush(stdin);
        opcion = getch();
        system("cls");

    } while (opcion != ESC);


    return listaPracticas;
}

/// FUNCIONES PARA LA OPCION 2 Y 3:

// devuelve NULL si no encuentra la practica, el nodo de la practica en caso de encontrarla:
nodoPractica * buscaPracticaPorNroPractica(nodoPractica * listaPracticas, int numeroPractica){

    while (listaPracticas && listaPracticas->datosPractica.nroPractica != numeroPractica) {
        listaPracticas = listaPracticas->siguiente;
    }

    return listaPracticas;
}

// funcion que maneja el modificar (variante = 1) o dar de baja (variante = 2) una practica:
void manejaModificarOBajaDePractica(nodoPractica * listaPracticas, int variante){

    if (listaPracticas) {

        char opcion;
        char auxNombrePractica[30];
        int numeroPractica;
        nodoPractica * nodoBuscado = inicListaPracticas();

        do {

            if (variante == 1) {
                printf("\n Ingrese una opcion para la busqueda de la practica a modificar:");
            } else if (variante == 2) {
                printf("\n Ingrese una opcion para la busqueda de la practica a dar de baja:");
            }

            printf("\n\n                           1. Buscar por nombre.");
            printf("\n                           2. Buscar por numero de practica.");
            printf("\n\n                           ESC para cancelar.");
            fflush(stdin);
            opcion = getch();
            system("cls");

            switch (opcion) {
                case ESC:
                    // regresa al menu anterior de gestion de practicas
                    break;

                case 49:

                    printf("\n Ingrese el nombre de la practica: ");
                    fflush(stdin);
                    gets(auxNombrePractica);

                    nodoBuscado = buscaPracticaPorNombre(listaPracticas, auxNombrePractica);
                    break;

                case 50:

                    printf("\n Ingrese el numero de practica: ");
                    fflush(stdin);
                    scanf("%d", &numeroPractica);

                    nodoBuscado = buscaPracticaPorNroPractica(listaPracticas, numeroPractica);
                    break;

                default:
                    // opcion incorrecta, se vuelve a mostrar el menu
                    break;
            }


            /// si opcion == 49, es porque se selecciono la opcion 1
            /// si opcion == 50, es porque se selecciono la opcion 2
            /// En ambos casos hay que verificar si se encontro la
            /// practica y, en ese caso, modificarla/darla de baja:
            if (opcion == 49 || opcion == 50) {

                /// si nodoBuscado != NULL se encontro la practica
                /// que se quiere modificar/dar de baja:
                if (nodoBuscado) {

                    if (variante == 1) {

                        system("cls");
                        printf("\n");
                        mostrarUnNodoPractica(nodoBuscado);

                        printf("\n Ingrese el nuevo nombre de la practica: ");
                        fflush(stdin);
                        gets(auxNombrePractica);



                        /// Se chequea que el nuevo nombre de la practica no este ya cargado la base de datos. La segunda
                        /// condicion es para ver si se le esta intentando poner el mismo nombre que ya tiene, en ese caso
                        /// se permite el cambio:
                        if (buscaPracticaPorNombre(listaPracticas, auxNombrePractica) && strcmpi(nodoBuscado->datosPractica.nombrePractica, auxNombrePractica) != 0) {
                            printf("\n La practica ingresada ya esta registrada en la base de datos, no se puede realizar el cambio.");
                        } else {
                            strcpy(nodoBuscado->datosPractica.nombrePractica, auxNombrePractica);
                            printf("\n Se modifico el nombre de la practica con exito.");
                        }

                    } else if (variante == 2) {

                        nodoBuscado->datosPractica.eliminado = 1;
                        printf("\n Se dio de baja a la practica con exito.");

                    }

                } else {

                    if (opcion == 49) {
                        printf("\n La practica ingresada no esta en la base de datos.");
                    } else {
                        printf("\n El numero de practica ingresado no corresponde a una practica presente en la base de datos.");
                    }

                }
                textoPresioneCualquierTecla();
            }

            system("cls");

        } while (opcion != ESC && opcion != 49 && opcion != 50);

    }
}

/// FUNCIONES PARA LA OPCION 4:

void mostrarUnNodoPractica(nodoPractica * practica){

    if (practica) {
        printf(" Nombre practica: %s", practica->datosPractica.nombrePractica);
        printf("\n Numero de practica: %d", practica->datosPractica.nroPractica);
        printf("\n Eliminado: %d", practica->datosPractica.eliminado);
    } else {
        printf("\n Nodo no valido.");
    }

    printf("\n =====================\n");
}

void muestraListaPacientes(nodoPractica * listaPracticas){

    while (listaPracticas) {
        mostrarUnNodoPractica(listaPracticas);
        listaPracticas = listaPracticas->siguiente;
    }
}

/// FUNCIONES PARA LA OPCION 5:

void guardaListaPracticasEnArchivo(nodoPractica * listaPracticas){

    FILE * archi = fopen(ARCHIVO_PRACTICAS, "wb");

    if (archi) {

        while (listaPracticas) {
            fwrite(&listaPracticas->datosPractica, sizeof(stPractica), 1, archi);
            listaPracticas = listaPracticas->siguiente;
        }

        fclose(archi);
        printf("\n Se guardaron los datos en el archivo.");

    } else {
        printf("\n Hubo un problema al intentar guardar los datos en un archivo.");
    }
}

/// FUNCIONES PARA LA OPCION 6:

void liberarListaPracticas(nodoPractica * listaPracticas){

    nodoPractica * nodoALiberar = listaPracticas;

    while (listaPracticas) {
        listaPracticas = listaPracticas->siguiente;
        free(nodoALiberar);
        nodoALiberar = listaPracticas;
    }
}

nodoPractica * archivoToListaPracticas(nodoPractica * listaPracticas){

    FILE *archi = fopen(ARCHIVO_PRACTICAS, "rb");

    stPractica practica;

    if (archi) {

        while (fread(&practica, sizeof(stPractica), 1, archi)>0) {
            listaPracticas = agregaNodoPracticaOrdenadoXNombre(listaPracticas, crearNodoPractica(practica));
        }

        fclose(archi);
        printf("\n Se cargo el archivo con exito.");

    } else {
        printf("\n Hubo un error al intentar abrir el archivo.");
    }

    return listaPracticas;
}

/// SE USA EN stPracticaXIngreso.c:

int existePracticaXnroPractica(int nroPracticaBuscar)
{
    FILE *archivo = fopen(ARCHIVO_PRACTICAS, "rb");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 0; // Indicar que no se encontró debido a un error
    }

    stPractica practicaActual;

    while (fread(&practicaActual, sizeof(stPractica), 1, archivo) == 1)
    {
        if (practicaActual.nroPractica == nroPracticaBuscar)
        {
            fclose(archivo);
            return 1; // Se encontró la practica con el nro de practica
        }
    }

    fclose(archivo);
    return 0; // No se encontró el registro
}
















