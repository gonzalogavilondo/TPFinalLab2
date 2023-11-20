#include "stPaciente.h"
#include "stIngreso.h"
#include "menu.h"

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
        printf("\n                                          4. Ver datos de un paciente en particular.");

        printf("\n\n\n                                     Para probar \"GESTIONAR PACIENTES\":");
        printf("\n\n                                          5. Mostrar arbol de pacientes.");
        printf("\n                                          6. Guardar arbol en un archivo binario.");
        printf("\n                                          7. Cargar datos de los pacientes del archivo en un arbol(si se uso la opcion 1,");
        printf("\n                                             se sobreescriben los datos).");

        printf("\n\n                                          ESC para finalizar...");
        fflush(stdin);
        opcion = getch();
        system("cls");


        switch (opcion) {
            case ESC:
                // finaliza el programa...
                break;

            case 49: // opcion 1: Dar de alta a un paciente.

                arbolPacientes = altaDePaciente(arbolPacientes);

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
                    darDeBajaUnPaciente(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;

            case 52: // opcion 4: Ver datos de un paciente en particular.

                if (arbolPacientes) {
                    buscaPacienteYMuestraDatos(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;


    // Para probar "GESTIONAR PACIENTES":

            case 53: // opcion 5: Mostrar arbol de pacientes.

                if (arbolPacientes) {
                    printf("\n Arbol de pacientes, ordenado por dni:\n\n");
                    inorderPacientes(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;

            case 54: // opcion 6: Guardar arbol en un archivo binario.

                if (arbolPacientes) {
                    guardaArbolPacientesEnArchivo(arbolPacientes);
                } else {
                    printf("\n La estructura esta vacia, primera debe cargarla.");
                }

                textoPresioneCualquierTecla();
                break;

            case 55: // opcion 7: Cargar datos de los pacientes del archivo en un arbol(si se uso la opcion 1, se sobreescriben los datos).

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

/// MENUS DE GESTION DE CLIENTES:

//if (arbolPacientes) {
//    buscaPacienteYMuestraDatos(arbolPacientes);
//} else {
//    printf("\n La estructura esta vacia, primera debe cargarla.");
//}
//
//textoPresioneCualquierTecla();

//void submenuBuscarYVerUnPaciente(nodoPaciente * arbolPacientes){
//
//    int opcion;
//
//        opcion = 0;
//        system("cls");
//        Rectangulo();
//        gotoxy(15, 4);
//        printf("Seleccione una opcion:\n");
//        gotoxy(15, 5);
//        printf("(1) Pacientes ordenados por dni\n");
//        gotoxy(15, 6);
//        printf("(2) Pacientes ordenados por apellido\n");
//        gotoxy(15, 7);
//        printf("(3) Volver\n");
//        gotoxy(15, 8);
//        fflush(stdin);
//        scanf("%i", &opcion);
//        system("cls");
//
//        if (arbolPacientes) {
//
//            switch (opcion) {
//                case 1: // Pacientes ordenados por dni
//                    printf("\n Listado de pacientes, ordenados por dni:\n\n");
//                    inorderPacientes(arbolPacientes);
//                    break;
//                case 2: // Pacientes ordenados por apellido
//                    imprimePacientesOrdenadosPorApellido(arbolPacientes);
//                    break;
//
//                default:
//                    // se selecciono una opcion no valida o la 3 'Volver'
//                    break;
//            }
//
//        } else {
//            printf("\n No hay clientes cargados en la base de datos.");
//        }
//
//        if (opcion == 1 || opcion == 2 || !arbolPacientes) {
//            textoPresioneCualquierTecla();
//        }
//
//    system("cls");
//
//}

void submenuElijeOrdenamientoPacientes(nodoPaciente * arbolPacientes){

    int opcion;

        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 4);
        printf("Seleccione una opcion:\n");
        gotoxy(15, 5);
        printf("(1) Pacientes ordenados por dni\n");
        gotoxy(15, 6);
        printf("(2) Pacientes ordenados por apellido\n");
        gotoxy(15, 7);
        printf("(3) Volver\n");
        gotoxy(15, 8);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        if (arbolPacientes) {

            switch (opcion) {
                case 1: // Pacientes ordenados por dni
                    printf("\n Listado de pacientes, ordenados por dni:\n\n");
                    inorderPacientes(arbolPacientes);
                    break;
                case 2: // Pacientes ordenados por apellido
                    imprimePacientesOrdenadosPorApellido(arbolPacientes);
                    break;

                default:
                    // se selecciono una opcion no valida o la 3 'Volver'
                    break;
            }

        } else {
            printf("\n No hay clientes cargados en la base de datos.");
        }

        if (opcion == 1 || opcion == 2 || !arbolPacientes) {
            textoPresioneCualquierTecla();
        }

    system("cls");

}

void submenuGestionPacientes(nodoPaciente * arbolPacientes){

    char control = 's';
    int opcion;

    do {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu gestion de pacientes");
        gotoxy(15, 4);
        printf("Que accion desea realizar?\n");
        gotoxy(15, 5);
        printf("(1) (aun no implementado) Ver datos de un paciente en particular\n");
        gotoxy(15, 6);
        printf("(2) (aun no implementado) Modificar datos de un paciente\n");
        gotoxy(15, 7);
        printf("(3) Alta de un paciente\n");
        gotoxy(15, 8);
        printf("(4) (aun no implementado) Dar de baja a un paciente\n");
        gotoxy(15, 9);
        printf("(5) Ver listado de pacientes\n");
        gotoxy(15, 10);
        printf("(6) Volver\n");
        gotoxy(15, 11);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
//            case 1: // Ver datos de un paciente en particular
//                submenuBuscarYVerUnPaciente(arbolPacientes);
//                break;
//            case 2: // Modificar datos de un paciente
//
//                break;
            case 3: // Alta de un paciente
                arbolPacientes = altaDePaciente(arbolPacientes);
                break;
//            case 4: // Dar de baja a un paciente
//
//                break;
            case 5: // Ver listado de pacientes
                submenuElijeOrdenamientoPacientes(arbolPacientes);
                break;

            case 6:
                control = 'n';
                break;

            default:
                control = 'n';
                break;

        }

    } while (control == 's' || control == 'S');

    system("cls");

}

/// Se usa en varias partes:

void textoPresioneCualquierTecla(){
    printf("\n\n Presione cualquier tecla para continuar...");
    fflush(stdin);
    getch();
}

/// FUNCIONES PARA LA OPCION 1:

nodoPaciente * inicArbolPacientes(){
    return NULL;
}

// existeElPaciente: el arbol tiene que estar ordenado por dni para esta funcion
// devuelve 0 si no lo encuentra, 1 si encuentra el dni en el arbolPacientes:
int existeElPaciente(nodoPaciente * arbolPacientes, int dni){

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

nodoPaciente * altaDePaciente(nodoPaciente * arbolPacientes){
    int dni;
    stPaciente nuevoPaciente;

    printf("\n Ingrese el DNI del paciente: ");
    fflush(stdin);
    scanf("%d", &dni);

    if (existeElPaciente(arbolPacientes, dni)) {
        printf("\n El paciente ya esta registrado en la base de datos. Puede modificar sus datos desde la opcion 2 del menu anterior.");
    } else {

        printf("\n Ingrese apellido y nombre en formato \"Apellido, Nombre\": ");
        fflush(stdin);
        gets(nuevoPaciente.apellidoNombre);

        printf("\n Ingrese la edad: ");
        fflush(stdin);
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

    textoPresioneCualquierTecla();

    return arbolPacientes;
}

/// FUNCIONES PARA LA OPCION 2:

void muestraUnPacienteResumido(stPaciente datosPaciente){

    printf("\n*** Datos del Paciente ***\n");
    printf("Apellido y nombre: %s\n", datosPaciente.apellidoNombre);
    printf("DNI: %d\n", datosPaciente.dni);
    printf("Telefono: %s\n", datosPaciente.telefono);
    puts("-------------------------");

}

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

// buscaPaciente: El arbol tiene que estar ordenado por dni para esta funcion.
// Devuelve el nodo del paciente si lo encuentra, caso contrario devuelve NULL:
nodoPaciente * buscaPaciente(nodoPaciente * arbolPacientes, int dni){

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

int existeIngresoXnroIngreso(nodoPaciente *arbolPacientes, int nroIngresoBuscar)
{
    if (arbolPacientes == NULL)
    {
        return 0; // No existe el número de ingreso en el árbol
    }

    if (arbolPacientes->listaIngresos != NULL)
    {
        nodoIngreso *ingresos = arbolPacientes->listaIngresos;
        while (ingresos != NULL) {
            if (nroIngresoBuscar == ingresos->ingreso.numeroIngreso)
            {
                return 1; // Se encontró el número de ingreso en la lista
            }
            ingresos = ingresos->siguiente;
        }
    }

    // Buscar en los subárboles izquierdo y derecho
    if (nroIngresoBuscar < arbolPacientes->datosPaciente.dni)
    {
        return existeIngresoXnroIngreso(arbolPacientes->izq, nroIngresoBuscar);
    }
    else
    {
        return existeIngresoXnroIngreso(arbolPacientes->der, nroIngresoBuscar);
    }
}


void textoDniNoEnBaseDeDatos(){
    printf("\n El dni ingresado no esta registrado en la base de datos.");
}

nodoPaciente * textoIngreseDNILuegoBuscaPaciente(nodoPaciente * arbolPacientes, int * dni){

    printf("\n Ingrese el dni del paciente: ");
    fflush(stdin);
    scanf("%d", dni);

    nodoPaciente * nodoBuscado = buscaPaciente(arbolPacientes, *dni);

    return nodoBuscado;
}

nodoPaciente * modificarDatosPaciente(nodoPaciente * arbolPacientes){

    int dni;

    nodoPaciente * paciente = textoIngreseDNILuegoBuscaPaciente(arbolPacientes, &dni);

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
            fflush(stdin);
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
                    fflush(stdin);
                    scanf("%d", &pacienteAux.edad);
                    break;
                case 51:

                    printf("\n Ingrese el dni: ");
                    fflush(stdin);
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
                fflush(stdin);
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

void darDeBajaUnPaciente(nodoPaciente * arbolPacientes){

    int dni;

    nodoPaciente * paciente = textoIngreseDNILuegoBuscaPaciente(arbolPacientes, &dni);

    if (paciente) {
        paciente->datosPaciente.eliminado = 1;
        printf("\n Se dio de baja al paciente.");
    } else {
        printf("\n");
        textoDniNoEnBaseDeDatos();
    }
}

/// FUNCIONES PARA LA OPCION 4:

//nodoPaciente * textoIngreseDNILuegoBuscaPaciente2(nodoPaciente * arbolPacientes){
//
//    int opcion;
//
//        opcion = 0;
//        system("cls");
//        Rectangulo();
//        gotoxy(15, 4);
//        printf("Seleccione una opcion:\n");
//        gotoxy(15, 5);
//        printf("(1) Pacientes ordenados por dni\n");
//        gotoxy(15, 6);
//        printf("(2) Pacientes ordenados por apellido\n");
//        gotoxy(15, 7);
//        printf("(3) Volver\n");
//        gotoxy(15, 8);
//        fflush(stdin);
//        scanf("%i", &opcion);
//        system("cls");
//
//        if (arbolPacientes) {
//
//            switch (opcion) {
//                case 1: // Pacientes ordenados por dni
//                    printf("\n Listado de pacientes, ordenados por dni:\n\n");
//                    inorderPacientes(arbolPacientes);
//                    break;
//                case 2: // Pacientes ordenados por apellido
//                    imprimePacientesOrdenadosPorApellido(arbolPacientes);
//                    break;
//
//                default:
//                    // se selecciono una opcion no valida o la 3 'Volver'
//                    break;
//            }
//
//        } else {
//            printf("\n No hay clientes cargados en la base de datos.");
//        }
//
//        if (opcion == 1 || opcion == 2 || !arbolPacientes) {
//            textoPresioneCualquierTecla();
//        }
//
//    system("cls");
//
//}

//nodoPaciente * textoIngreseDNILuegoBuscaPaciente(nodoPaciente * arbolPacientes, int * dni){
//
//    printf("\n Ingrese el dni del paciente: ");
//    fflush(stdin);
//    scanf("%d", dni);
//
//    nodoPaciente * nodoBuscado = buscaPaciente(arbolPacientes, *dni);
//
//    return nodoBuscado;
//}

void buscaPacienteYMuestraDatos(nodoPaciente * arbolPacientes){

    int dni;
    nodoPaciente * paciente = textoIngreseDNILuegoBuscaPaciente(arbolPacientes, &dni);

    if (paciente) {

        system("cls");
        printf("\n");
        muestraUnPaciente(paciente->datosPaciente);

    } else {
        printf("\n");
        textoDniNoEnBaseDeDatos();
    }
}

/// FUNCIONES PARA LA OPCION 5:

void inorderPacientes(nodoPaciente * arbolPacientes){
    if (arbolPacientes) {
        inorderPacientes(arbolPacientes->izq);
        muestraUnPaciente(arbolPacientes->datosPaciente);
        inorderPacientes(arbolPacientes->der);
    }
}

/// FUNCIONES PARA LA OPCION 6:

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

/// FUNCIONES PARA LA OPCION 7:

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

///FUNCION QUE LA USA INGRESOS:

// Función para buscar un registro por DNI en el archivo:
int existePacienteXDNI(int dniBuscar)
{
    FILE *archivo = fopen(ARCHIVO_PACIENTES, "rb");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 0; // Indicar que no se encontró debido a un error
    }

    stPaciente pacienteActual;

    while (fread(&pacienteActual, sizeof(stPaciente), 1, archivo) == 1)
    {
        if (pacienteActual.dni == dniBuscar)
        {
            fclose(archivo);
            return 1; // Se encontró el registro con el DNI dado
        }
    }

    fclose(archivo);
    return 0; // No se encontró el registro con el DNI dado
}

/// NUEVAS:

int cantidadNodosArbolPacientes(nodoPaciente * arbolPacientes){

    int total = 0;

    if (arbolPacientes) {
        total += cantidadNodosArbolPacientes(arbolPacientes->izq);
        total += cantidadNodosArbolPacientes(arbolPacientes->der);
        total++;
    }

    return total;
}

void pacienteToArregloOrdenadoXApellidoNombre(stPaciente * arreglo, int validosArre, stPaciente datosPaciente){

    if (validosArre) {

        validosArre--;
        while(validosArre>=0 && strcmp(datosPaciente.apellidoNombre, arreglo[validosArre].apellidoNombre)<0){
            arreglo[validosArre+1] = arreglo[validosArre];
            validosArre--;
        }
        arreglo[validosArre+1] = datosPaciente;

    } else {
        arreglo[0] = datosPaciente;
    }
}

void recorreArbolEIngresaEnArregloXApellidoNombre(nodoPaciente * arbolPacientes, stPaciente * arreglo, int * validosArre){
    if (arbolPacientes) {
        recorreArbolEIngresaEnArregloXApellidoNombre(arbolPacientes->izq, arreglo, validosArre);

        pacienteToArregloOrdenadoXApellidoNombre(arreglo, *validosArre, arbolPacientes->datosPaciente);
        *validosArre = *validosArre + 1;

        recorreArbolEIngresaEnArregloXApellidoNombre(arbolPacientes->der, arreglo, validosArre);
    }
}

stPaciente * arbolPacientesToArreglo(nodoPaciente * arbolPacientes){

    int validosArre = cantidadNodosArbolPacientes(arbolPacientes);
    stPaciente * arreglo = (stPaciente *) malloc(validosArre * sizeof(stPaciente));
    validosArre = 0;

    recorreArbolEIngresaEnArregloXApellidoNombre(arbolPacientes, arreglo, &validosArre);

    return arreglo;
}

void muestraArregloPacientes(stPaciente arregloPacientes[], int validosArre){
    for (int i = 0; i<validosArre; i++) {
        muestraUnPaciente(arregloPacientes[i]);
    }
}

void imprimePacientesOrdenadosPorApellido(nodoPaciente * arbolPacientes){

    stPaciente * arregloPacientes = arbolPacientesToArreglo(arbolPacientes);
    printf("\n Listado de pacientes, ordenados por apellido:\n\n");
    muestraArregloPacientes(arregloPacientes, cantidadNodosArbolPacientes(arbolPacientes));

}
















