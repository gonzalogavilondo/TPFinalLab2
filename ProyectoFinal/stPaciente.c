#include "stPaciente.h"
#include "stIngreso.h"

void menuProvisorioGestionarPacientes(){
    char opcion = 0;

    /// para opciones de GESTIONAR PACIENTES:
    nodoPaciente * arbolPacientes = inicArbolPacientes();

    do {

        system("cls");
        printf("\n              Menu provisorio para 'Gestionar pacientes':");
        printf("\n\n                                          1. Dar de alta a un paciente.");
        printf("\n                                          2. Modificar los datos de un paciente.");
        printf("\n                                          3. Dar de baja un paciente.");

        printf("\n\n\n                                     Para probar \"GESTIONAR PACIENTES\":");
        printf("\n\n                                          4. Mostrar arbol de pacientes.");
        printf("\n                                          5. Guardar arbol en un archivo binario.");
        printf("\n                                          6. Cargar datos de los pacientes del archivo en un arbol(si se uso la opcion 1,");
        printf("\n                                             se sobreescriben los datos).");

        printf("\n\n                                          ESC para finalizar...");
        opcion = getch();
        system("cls");


        switch (opcion) {
            case ESC:
                // finaliza el programa...
                break;

                     // GESTION PACIENTES:

            case 49: // opcion 1: Dar de alta a un paciente.

                arbolPacientes = altaDePacientes(arbolPacientes);

                break;
            case 50: // opcion 2: Modificar los datos de un paciente.

                if (arbolPacientes) {
                    arbolPacientes = modificarDatosPaciente(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();

                break;
            case 51: // opcion 3: Dar de baja un paciente.

                if (arbolPacientes) {

                    buscaYDaDeBajaPaciente(arbolPacientes);

                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();

                break;

                     // Para probar "GESTIONAR PACIENTES":

            case 52: // opcion 4: Mostrar arbol de pacientes.

                if (arbolPacientes) {
                    printf("\n Arbol de pacientes, ordenado por dni:\n\n");
                    inorderPacientes(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();

                break;

            case 53: // opcion 5: Guardar arbol en un archivo binario.

                if (arbolPacientes) {

                    guardaArbolPacientesEnArchivo(arbolPacientes);

                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();

                break;

            case 54: // opcion 6: Cargar datos de los pacientes del archivo en un arbol(si se uso la opcion 1, se sobreescriben los datos).

                if (arbolPacientes) {
                    liberarArbolPacientes(arbolPacientes);
                    arbolPacientes = inicArbolPacientes();
                }

                arbolPacientes = archivoToArbolPacientes(arbolPacientes);

                textoPresioneCualquierTecla();

                break;

            default:
                // opcion incorrecta, se vuelve a mostrar el menu
                break;
        }

    } while (opcion != ESC);
}

/// Se usa en varias partes:

void textoPresioneCualquierTecla(){
    printf("\n\n Presione cualquier tecla para continuar...");
    getch();
}

/// FUNCIONES PARA LA OPCION 1:

nodoPaciente * inicArbolPacientes(){
    return NULL;
}

nodoIngreso * inicListaIngresos(){
    return NULL;
}

// el arbol tiene que estar ordenado por dni para esta funcion:
int existeElPaciente(nodoPaciente * arbolPacientes, int dni){ // 0 si no lo encuentra, 1 si encuentra el dni en el arbolPacientes

    int result = 0;

    if (arbolPacientes) {
        if (dni == arbolPacientes->datosPaciente.dni) {

            result = 1;

        } else {

            if (dni < arbolPacientes->datosPaciente.dni) {
                result = existeElPaciente(arbolPacientes->izq, dni);
            } else {
                result = existeElPaciente(arbolPacientes->der, dni);
            }

        }
    }

    return result;
}

nodoPaciente * crearNodoArbolPaciente(stPaciente datosStPaciente){
    nodoPaciente * nodoNuevo = (nodoPaciente *) malloc(sizeof(nodoPaciente));

    nodoNuevo->datosPaciente = datosStPaciente;
    nodoNuevo->listaIngresos = inicListaIngresos();
    nodoNuevo->der = NULL;
    nodoNuevo->izq = NULL;

    return nodoNuevo;
}

nodoPaciente * insertarPaciente(nodoPaciente * arbolPacientes, stPaciente nuevoPaciente){

    if (!arbolPacientes) {
        arbolPacientes = crearNodoArbolPaciente(nuevoPaciente);
    } else {

        if (nuevoPaciente.dni > arbolPacientes->datosPaciente.dni) {
            arbolPacientes->der = insertarPaciente(arbolPacientes->der, nuevoPaciente);
        } else {
            arbolPacientes->izq = insertarPaciente(arbolPacientes->izq, nuevoPaciente);
        }

    }

    return arbolPacientes;
}

nodoPaciente * altaDePacientes(nodoPaciente * arbolPacientes){
    char opcion = 0;
    int dni;
    stPaciente nuevoPaciente;

    do {

        printf("\n Ingrese el DNI del paciente: ");
        scanf("%d", &dni);

        if (existeElPaciente(arbolPacientes, dni)) {
            printf("\n El paciente ya esta registrado en la base de datos. Puede modificar sus datos desde la opcion 2 del menu anterior.");
        } else {

            printf("\n Ingrese apellido y nombre: ");
            fflush(stdin);
            gets(nuevoPaciente.apellidoNombre);

            printf("\n Ingrese la edad: ");
            scanf("%d", &nuevoPaciente.edad);

            printf("\n Ingrese la direccion donde vive: ");
            fflush(stdin);
            gets(nuevoPaciente.direccion);

            printf("\n Ingrese el telefono: ");
            fflush(stdin);
            gets(nuevoPaciente.telefono);

            nuevoPaciente.eliminado = 0;
            nuevoPaciente.dni = dni;

            arbolPacientes = insertarPaciente(arbolPacientes, nuevoPaciente);

            system("cls");
            printf("\n Paciente cargado.");

        }

        printf("\n\n Para cargar otro paciente presione cualquier tecla, ESC para finalizar...");
        opcion = getch();
        system("cls");

    } while (opcion != ESC);

    return arbolPacientes;
}

/// FUNCIONES PARA LA OPCION 2:

void muestraUnPaciente(stPaciente datosPaciente){

    printf(" Apellido y nombre: %s", datosPaciente.apellidoNombre);
    printf("\n Direccion: %s", datosPaciente.direccion);
    printf("\n Dni: %d", datosPaciente.dni);
    printf("\n Edad: %d", datosPaciente.edad);
    printf("\n Telefono: %s", datosPaciente.telefono);
    printf("\n Eliminado: %d", datosPaciente.eliminado);
    printf("\n =====================\n");

}

nodoPaciente * encontrarMinimoDni(nodoPaciente* arbolPacientes){
    while (arbolPacientes->izq) {
        arbolPacientes = arbolPacientes->izq;
    }
    return arbolPacientes;
}

nodoPaciente * eliminarNodoArbolPacientes(nodoPaciente * arbolPacientes, int dniPaciente){

    if (arbolPacientes == NULL) {
        return NULL;
    }

    /// Buscar el nodo que se desea eliminar en el subárbol izquierdo o derecho
    if (dniPaciente < arbolPacientes->datosPaciente.dni) {

        arbolPacientes->izq = eliminarNodoArbolPacientes(arbolPacientes->izq, dniPaciente);

    } else if (dniPaciente > arbolPacientes->datosPaciente.dni) {

        arbolPacientes->der = eliminarNodoArbolPacientes(arbolPacientes->der, dniPaciente);

    } else {

        /// el nodo a eliminar ha sido encontrado (NO FUE NI MENOR NI MAYOR)
        /// Caso 1: Nodo sin hijos o un solo hijo (los mas sencillos)
        if (arbolPacientes->izq == NULL) {

            nodoPaciente * temp = arbolPacientes->der;
            free(arbolPacientes);
            return temp;

        } else if (arbolPacientes->der == NULL) {

            nodoPaciente * temp = arbolPacientes->izq;
            free(arbolPacientes);
            return temp;

        }

        /// Caso 2: Nodo con dos hijos
        /// Encontrar el sucesor inmediato (nodo más a la izquierda en el subárbol derecho)
        nodoPaciente * temp = encontrarMinimoDni(arbolPacientes->der); ///funcion complementaria...

        /// Copiar el dni del sucesor inmediato al nodo actual
        arbolPacientes->datosPaciente.dni = temp->datosPaciente.dni;

        /// Eliminar el sucesor inmediato
        arbolPacientes->der = eliminarNodoArbolPacientes(arbolPacientes->der, temp->datosPaciente.dni);

    }

    return arbolPacientes;
}

// el arbol tiene que estar ordenado por dni para esta funcion:
nodoPaciente * buscaPaciente(nodoPaciente * arbolPacientes, int dni){ // NULL si no lo encuentra, el nodo del paciente si lo encuentra

    nodoPaciente * nodoBuscado = inicArbolPacientes();

    if (arbolPacientes) {
        if (dni == arbolPacientes->datosPaciente.dni) {

            nodoBuscado = arbolPacientes;

        } else {

            if (dni < arbolPacientes->datosPaciente.dni) {
                nodoBuscado = buscaPaciente(arbolPacientes->izq, dni);
            } else {
                nodoBuscado = buscaPaciente(arbolPacientes->der, dni);
            }

        }
    }

    return nodoBuscado;
}

void textoDniNoEnBaseDeDatos(){
    printf("\n El dni ingresado no esta registrado en la base de datos.");
}

nodoPaciente * modificarDatosPaciente(nodoPaciente * arbolPacientes){

    nodoPaciente * paciente;

    int dni;
    printf("\n Ingrese el dni del paciente: ");
    scanf("%d", &dni);

    paciente = buscaPaciente(arbolPacientes, dni);

    if (paciente) {

        stPaciente pacienteAux;
        pacienteAux = paciente->datosPaciente;
        char opcion;

        do {
            system("cls");
            printf("\n");
            muestraUnPaciente(pacienteAux);

            printf("\n Que dato desea modificar? Ingrese una opcion:");
            printf("\n\n                1. Apellido y nombre");
            printf("\n                2. Edad");
            printf("\n                3. Dni");
            printf("\n                4. Direccion");
            printf("\n                5. Telefono");
            opcion = getch();
            system("cls");

            switch (opcion) {
                case 49:

                    printf("\n Ingrese apellido y nombre: ");
                    fflush(stdin);
                    gets(pacienteAux.apellidoNombre);
                    break;
                case 50:

                    printf("\n Ingrese la edad: ");
                    scanf("%d", &pacienteAux.edad);
                    break;
                case 51:

                    printf("\n Ingrese el dni: ");
                    scanf("%d", &dni);

                    if (existeElPaciente(arbolPacientes, dni) && dni!=paciente->datosPaciente.dni) {
                        printf("\n\n El dni ingresado ya esta registrado en la base de datos.");
                        textoPresioneCualquierTecla();
                    } else {
                        pacienteAux.dni = dni;
                    }

                    break;
                case 52:

                    printf("\n Ingrese la direccion: ");
                    fflush(stdin);
                    gets(pacienteAux.direccion);
                    break;
                case 53:

                    printf("\n Ingrese el telefono: ");
                    fflush(stdin);
                    gets(pacienteAux.telefono);
                    break;
                default:
                    // opcion incorrecta, se vuelve a mostrar el menu
                    break;
            }

            if (49 <= opcion && opcion <= 53) {
                system("cls");
                printf("\n Desea modificar algun otro dato del cliente? En ese caso presione cualquier tecla, para finalizar presione ESC.");
                opcion = getch();
            }

        } while (opcion != ESC);

        // si se cambio el dni, elimino el nodo y lo vuelvo a insertar, asi el arbol se mantiene el orden por dni
        if (paciente->datosPaciente.dni != pacienteAux.dni) {

            arbolPacientes = eliminarNodoArbolPacientes(arbolPacientes, paciente->datosPaciente.dni);
            arbolPacientes = insertarPaciente(arbolPacientes, pacienteAux);

        } else {
            paciente->datosPaciente = pacienteAux;
        }

        system("cls");
        printf("\n Se ha modificado el paciente.");

    } else {
        textoDniNoEnBaseDeDatos();
    }

    return arbolPacientes;
}

/// FUNCIONES PARA LA OPCION 3:

void buscaYDaDeBajaPaciente(nodoPaciente * arbolPacientes){

    int dni;
    printf("\n Ingrese el dni del paciente a dar de baja: ");
    scanf("%d", &dni);

    nodoPaciente * paciente = buscaPaciente(arbolPacientes, dni);

    if (paciente) {
        paciente->datosPaciente.eliminado = 1;
        printf("\n Se dio de baja al paciente.");
    } else {
        printf("\n");
        textoDniNoEnBaseDeDatos();
    }
}

/// FUNCIONES PARA LA OPCION 4:

void inorderPacientes(nodoPaciente * arbolPacientes){
    if (arbolPacientes) {
        inorderPacientes(arbolPacientes->izq);
        muestraUnPaciente(arbolPacientes->datosPaciente);
        inorderPacientes(arbolPacientes->der);
    }
}

/// FUNCIONES PARA LA OPCION 5:

void imprimePacientesInorderEnArchivo(nodoPaciente * arbolPacientes, FILE * archi){

    if (arbolPacientes) {
        imprimePacientesInorderEnArchivo(arbolPacientes->izq, archi);

        stPaciente paciente;
        strcpy(paciente.apellidoNombre, arbolPacientes->datosPaciente.apellidoNombre);
        strcpy(paciente.direccion, arbolPacientes->datosPaciente.direccion);
        strcpy(paciente.telefono, arbolPacientes->datosPaciente.telefono);
        paciente.dni = arbolPacientes->datosPaciente.dni;
        paciente.edad = arbolPacientes->datosPaciente.edad;
        paciente.eliminado = arbolPacientes->datosPaciente.eliminado;

        fwrite(&paciente, sizeof(stPaciente), 1, archi);

        imprimePacientesInorderEnArchivo(arbolPacientes->der, archi);
    }

}

void guardaArbolPacientesEnArchivo(nodoPaciente * arbolPacientes){

    FILE * archi = fopen(ARCHIVO_PACIENTES, "wb");

    if (archi) {

        imprimePacientesInorderEnArchivo(arbolPacientes, archi);

        printf("\n Se guardaron los datos en el archivo.");
        fclose(archi);
    } else {
        printf("\n Hubo un problema al intentar guardar los datos en un archivo.");
    }

}

/// FUNCIONES PARA LA OPCION 6:

void liberarArbolPacientes(nodoPaciente * arbolPacientes){

    if (arbolPacientes) {
        liberarArbolPacientes(arbolPacientes->izq);
        liberarArbolPacientes(arbolPacientes->der);
        free(arbolPacientes);
    }
}

nodoPaciente * archivoToArbolPacientes(nodoPaciente * arbolPacientes){

    FILE * archi = fopen(ARCHIVO_PACIENTES, "rb");

    if (archi) {

        stPaciente paciente;

        while (fread(&paciente, sizeof(stPaciente), 1, archi) > 0) {
            arbolPacientes = insertarPaciente(arbolPacientes, paciente);
        }

        printf("\n Se cargaron los datos.");
        fclose(archi);
    } else {
        printf("\n Hubo un problema al intentar abrir el archivo.");
    }

    return arbolPacientes;
}




















