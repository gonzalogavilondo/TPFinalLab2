#include "stPractica.h"

void menuProvisorioGestionarPracticas(){
    char opcion = 0;

    /// para opciones de GESTIONAR PRACTICAS:
    nodoPractica * listaPracticas = inicListaPracticas();

    do {

        system("cls");
        printf("\n              Menu provisorio para 'Gestionar practicas':");
        printf("\n\n                                          1. Dar de alta a una practica.");
        printf("\n                                          AUN NO 2. Modificar los datos de una practica.");
        printf("\n                                          AUN NO 3. Dar de baja una practica.");

        printf("\n\n\n                                     Para probar \"GESTIONAR PRACTICAS\":");
        printf("\n\n                                          AUN NO 4. Mostrar lista practicas.");
        printf("\n                                          AUN NO 5. Guardar lista en un archivo binario.");
        printf("\n                                          AUN NO 6. Cargar datos de las practicas del archivo en una lista.");

        printf("\n\n                                          ESC para finalizar...");
        opcion = getch();
        system("cls");

//        GESTIONAR PRACTICAS: Alta_de_practica, Modificacion_de_practica, Baja_de_practica, SubMenuConsultar_practicas

        switch (opcion) {
            case ESC:
                // finaliza el programa...
                break;

                     // GESTION PRACTICAS:

            case 49: // opcion 1: Dar de alta a una practica.

                listaPracticas = darDeALtaPracticas(listaPracticas);

                break;
            case 50: // opcion 2: Modificar los datos de una practica.



                break;
            case 51: // opcion 3: Dar de baja una practica.



                break;

                     // Para probar "GESTIONAR PRACTICAS":

            case 52: // opcion 4: Mostrar lista practicas.



                break;

            case 53: // opcion 5:



                break;

            case 54: // opcion 6:



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

int existePractica(nodoPractica * listaPracticas, char nombrePractica[]){

    int existe = 0;

    while (listaPracticas && !existe) {

        if (strcmpi(listaPracticas->datosPractica.nombrePractica, nombrePractica) == 0) {
            existe = 1;
        }

        listaPracticas = listaPracticas->siguiente;
    }

    return existe;

}

nodoPractica * darDeALtaPracticas(nodoPractica * listaPracticas){

    char opcion;
    stPractica nuevaPractica;

    do {

        printf("\n Ingrese el nombre de la practica: ");
        fflush(stdin);
        gets(nuevaPractica.nombrePractica);

        if (existePractica(listaPracticas, nuevaPractica.nombrePractica)) {
            printf("\n La practica ingresada ya existe en la base de datos.");
        } else {
            nuevaPractica.eliminado = 0;
            nuevaPractica.nroPractica = tamanioListaPracticas(listaPracticas) + 1;

            listaPracticas = agregaNodoPracticaOrdenadoXNombre(listaPracticas, crearNodoPractica(nuevaPractica));
            printf("\n Se agrego la practica.");
        }

        printf("\n\n Presione cualquier tecla para agregar otra practica, ESC para finalizar...");
        opcion = getch();
        system("cls");

    } while (opcion != ESC);


    return listaPracticas;
}



















