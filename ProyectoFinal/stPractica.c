#include "stPractica.h"
#include "stPaciente.h"
#include "menu.h"

/// MENU PRINCIPAL GESTION DE PRACTICAS:

void submenuGestionPracticas(){

    char control = 's';
    int opcion;

    /// Leo el archivo de practicas y las cargo en una lista:
    nodoPractica * listaPracticas = inicListaPracticas();
    listaPracticas = archivoToListaPracticas(listaPracticas);

    do {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu gestion de practicas");
        gotoxy(15, 4);
        printf("Que accion desea realizar?\n");
        gotoxy(15, 6);
        printf("(1) Ver listado de practicas\n");
        gotoxy(15, 7);
        printf("(2) Ver datos de una practica en particular\n");
        gotoxy(15, 8);
        printf("(3) Alta de practicas\n");
        gotoxy(15, 9);
        printf("(4) Modificar datos de una practica\n");
        gotoxy(15, 10);
        printf("(5) Dar de baja una practica\n");
        gotoxy(15, 11);
        printf("(6) Buscar practica por inciciales\n");
        gotoxy(15, 12);
        printf("(7) Volver\n");
        gotoxy(15, 13);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
            case 1: // Ver listado de practicas:
                muestraListaPracticas(listaPracticas);
                break;
            case 2: // Ver datos de una practica en particular:
                manejaVerModificarOBajaDePractica(listaPracticas, 3);
                break;
            case 3: // Alta de practicas:
                listaPracticas = darDeAltaPracticas(listaPracticas);
                break;
            case 4: // Modificar datos de una practica:
                manejaVerModificarOBajaDePractica(listaPracticas, 1);
                break;
            case 5: //Dar de baja una practica:
                manejaVerModificarOBajaDePractica(listaPracticas, 2);
                break;
            case 6:
                encontrarPracticasPorCadena();
                getch();
                break;
            case 7:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    if (listaPracticas) {
        guardaListaPracticasEnArchivo(listaPracticas);
        liberarListaPracticas(listaPracticas);
        listaPracticas = inicListaPracticas();
    }

    system("cls");

}

nodoPractica * inicListaPracticas(){
    return NULL;
}

void liberarListaPracticas(nodoPractica * listaPracticas){

    nodoPractica * nodoALiberar = listaPracticas;

    while (listaPracticas) {
        listaPracticas = listaPracticas->siguiente;
        free(nodoALiberar);
        nodoALiberar = listaPracticas;
    }
}

/// FUNCIONES OPCION 1 DEL MENU 'submenuGestionPracticas':

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

void muestraListaPracticas(nodoPractica * listaPracticas){

    printf("\n");
    while (listaPracticas) {
        mostrarUnNodoPractica(listaPracticas);
        listaPracticas = listaPracticas->siguiente;
    }

    textoPresioneCualquierTecla();
}

void mostrarUnNodoPractica2(nodoPractica * practica, int pos){

    if (practica) {
        gotoxy(35, pos);
        printf("Nombre practica: %s", practica->datosPractica.nombrePractica);
        gotoxy(35, pos+1);
        printf("Numero de practica: %d", practica->datosPractica.nroPractica);
        gotoxy(35, pos+2);
        printf(" =====================");
    } else {
        gotoxy(35, pos);
        printf("Nodo no valido.");
    }

}

void muestraListaPracticas2(nodoPractica * listaPracticas){

    int pos = 3;
    while (listaPracticas) {
        // solo muestra las que no esten eliminadas:
        if (!(listaPracticas->datosPractica.eliminado)) {
            mostrarUnNodoPractica2(listaPracticas, pos);
            pos = pos + 4;
        }
        listaPracticas = listaPracticas->siguiente;
    }

}

/// FUNCIONES OPCION 2, 4 Y 5 DEL MENU 'submenuGestionPracticas':

// funcion que maneja el modificar una practica (variante = 1), dar de baja una
// practica (variante = 2) y ver una practica en particular (variante = 3):
void manejaVerModificarOBajaDePractica(nodoPractica * listaPracticas, int variante){

    if (listaPracticas) {

        int opcion;
        char auxNombrePractica[30];
        int numeroPractica;
        nodoPractica * nodoBuscado = inicListaPracticas();

        do {

            Rectangulo();
            gotoxy(5, 4);
            if (variante == 1) {
                printf("Ingrese una opcion para la busqueda de la practica a modificar:");
            } else if (variante == 2) {
                printf("Ingrese una opcion para la busqueda de la practica a dar de baja:");
            } else if (variante == 3) {
                printf("Ingrese una opcion para la busqueda de la practica:");
            }

            gotoxy(15, 6);
            printf("(1) Buscar por nombre.");
            gotoxy(15, 7);
            printf("(2) Buscar por numero de practica.");
            gotoxy(15, 8);
            printf("(3) Cancelar.");
            gotoxy(15, 9);
            fflush(stdin);
            scanf("%i", &opcion);
            system("cls");

            switch (opcion) {
                case 1:

                    printf("\n Ingrese el nombre de la practica: ");
                    fflush(stdin);
                    gets(auxNombrePractica);

                    nodoBuscado = buscaPracticaPorNombre(listaPracticas, auxNombrePractica);
                    break;

                case 2:

                    printf("\n Ingrese el numero de practica: ");
                    fflush(stdin);
                    scanf("%d", &numeroPractica);

                    nodoBuscado = buscaPracticaPorNroPractica(listaPracticas, numeroPractica);
                    break;

                default:
                    // si selecciono 'Cancelar' vuelve al menu anterior, si selecciono una
                    // opcion incorrecta, se vuelve a mostrar el menu
                    break;
            }


            /// si opcion == 49, es porque se selecciono la opcion 1
            /// si opcion == 50, es porque se selecciono la opcion 2
            /// En ambos casos hay que verificar si se encontro la
            /// practica y, en ese caso, modificarla/darla de baja:
            if (opcion == 1 || opcion == 2) {

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

                        if (nodoBuscado->datosPractica.tieneAlMenosUnUso) {
                            printf("\n No se puede dar de baja la practica ya que tiene al menos 1 uso.");
                        } else {
                            nodoBuscado->datosPractica.eliminado = 1;
                            printf("\n Se dio de baja a la practica con exito.");
                        }

                    } else if (variante == 3) {

                        system("cls");
                        printf("\n");
                        mostrarUnNodoPractica(nodoBuscado);

                    }

                } else {

                    if (opcion == 1) {
                        printf("\n La practica ingresada no esta en la base de datos.");
                    } else {
                        printf("\n El numero de practica ingresado no corresponde a una practica presente en la base de datos.");
                    }

                }
                textoPresioneCualquierTecla();
                system("cls");
            }

        } while (opcion != 1 && opcion != 2 && opcion != 3);

    } else {
        printf("\n No hay practicas cargadas.");
        textoPresioneCualquierTecla();
        system("cls");
    }
}

// devuelve NULL si no encuentra la practica, el nodo de la practica en caso de encontrarla:
nodoPractica * buscaPracticaPorNombre(nodoPractica * listaPracticas, char nombreBusqueda[]){

    while (listaPracticas && strcmpi(listaPracticas->datosPractica.nombrePractica, nombreBusqueda) != 0) {
        listaPracticas = listaPracticas->siguiente;
    }

    return listaPracticas;
}

// devuelve NULL si no encuentra la practica, el nodo de la practica en caso de encontrarla:
nodoPractica * buscaPracticaPorNroPractica(nodoPractica * listaPracticas, int numeroPractica){

    while (listaPracticas && listaPracticas->datosPractica.nroPractica != numeroPractica) {
        return listaPracticas;
    }

    return NULL;
}

/// FUNCIONES OPCION 3 DEL MENU 'submenuGestionPracticas':

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
            nuevaPractica.tieneAlMenosUnUso = 0;
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

int tamanioListaPracticas(nodoPractica * listaPracticas){
    int tamanio = 0;

    while (listaPracticas) {
        tamanio++;
        listaPracticas = listaPracticas->siguiente;
    }

    return tamanio;
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

nodoPractica * agregarPracticaPpio(nodoPractica * listaPracticas, nodoPractica * nuevoNodo){

    if(listaPracticas) {
        nuevoNodo->siguiente = listaPracticas;
        listaPracticas = nuevoNodo;
    }else{
        listaPracticas = nuevoNodo;
    }
    return listaPracticas;

}

nodoPractica * crearNodoPractica(stPractica nuevaPractica){
    nodoPractica * nodoNuevo = (nodoPractica *) malloc(sizeof(nodoPractica));

    nodoNuevo->datosPractica = nuevaPractica;
    nodoNuevo->siguiente = NULL;

    return nodoNuevo;
}

/// FUNCIONES PARA MANEJO DE ARCHIVO PRACTICAS:

void guardaListaPracticasEnArchivo(nodoPractica * listaPracticas){

    FILE * archi = fopen(ARCHIVO_PRACTICAS, "wb");

    if (archi) {

        while (listaPracticas) {
            fwrite(&listaPracticas->datosPractica, sizeof(stPractica), 1, archi);
            listaPracticas = listaPracticas->siguiente;
        }

        fclose(archi);

    } else {
        printf("\n Hubo un problema al intentar guardar los datos de practicas en un archivo.");
        textoPresioneCualquierTecla();
    }
}

nodoPractica * archivoToListaPracticas(nodoPractica * listaPracticas){

    FILE *archi = fopen(ARCHIVO_PRACTICAS, "rb");

    stPractica practica;

    if (archi) {

        while (fread(&practica, sizeof(stPractica), 1, archi)>0) {
            listaPracticas = agregaNodoPracticaOrdenadoXNombre(listaPracticas, crearNodoPractica(practica));
        }

    } else {
        printf("\n Hubo un error al intentar abrir el archivo de practicas.");
        textoPresioneCualquierTecla();
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
void encontrarPracticasPorCadena() {
    FILE *archivo;
    archivo = fopen(ARCHIVO_PRACTICAS, "rb"); // Abre el archivo en modo lectura binaria

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cadenaBuscada[30];
    printf("Ingrese una cadena para buscar practicas: ");
    scanf("%29s", cadenaBuscada);

    stPractica practica;
    size_t longitudCadena = strlen(cadenaBuscada);
    while (fread(&practica, sizeof(stPractica), 1, archivo) == 1) {
        if (practica.eliminado == 0 && strncmp(practica.nombrePractica, cadenaBuscada, longitudCadena) == 0) {
            printf("\n=====================================\n");
            printf("Numero de Practica: %d\nNombre: %s\n", practica.nroPractica, practica.nombrePractica);
        }
    }
    printf("=====================================\n");
    fclose(archivo);
}
