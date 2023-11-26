#include "stPaciente.h"
#include "stIngreso.h"
#include "stPracticaXIngreso.h"
#include "menu.h"

/// Se usa en varias partes:

void textoPresioneCualquierTecla(){
    printf("\n\n Presione cualquier tecla para continuar...");
    fflush(stdin);
    getch();
}

void textoPresioneCualquierTecla2(){
    printf("Presione cualquier tecla para continuar...");
    fflush(stdin);
    getch();
}

/// MENU PRINCIPAL GESTION DE PACIENTES:

void submenuGestionPacientes(nodoPaciente * arbolPacientes, int flag){

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
        gotoxy(15, 6);
        printf("(1) Ver datos de un paciente en particular\n");
        gotoxy(15, 7);
        printf("(2) Modificar datos de un paciente\n");
        gotoxy(15, 8);
        printf("(3) Alta de un paciente\n");
        gotoxy(15, 9);
        printf("(4) Dar de baja a un paciente\n");
        gotoxy(15, 10);
        printf("(5) Ver listado de pacientes\n");
        gotoxy(15, 11);
        printf("(6) Volver\n");
        gotoxy(15, 12);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
            case 1: // Ver datos de un paciente en particular
                submenuBuscaPacienteYMuestraDatos(arbolPacientes, flag);
                break;
            case 2: // Modificar datos de un paciente
                submenuModificarDatosPaciente(arbolPacientes, flag);
                break;
            case 3: // Alta de un paciente
                arbolPacientes = altaDePaciente(arbolPacientes);
                break;
            case 4: // Dar de baja a un paciente
                submenuDarDeBajaUnPaciente(arbolPacientes, flag);
                break;
            case 5: // Ver listado de pacientes
                submenuElijeOrdenamientoPacientes(arbolPacientes, flag);
                break;

            case 6:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    system("cls");

}

/// FUNCIONES OPCION 1 DEL MENU 'submenuGestionPacientes':

void submenuBuscaPacienteYMuestraDatos(nodoPaciente * arbolPacientes, int flag){

    int dni = consultaDniYVerifica();

    if (dni) {

        nodoPaciente * paciente = buscaPaciente(arbolPacientes, dni);

        if (paciente && (flag || (!flag && !(paciente->datosPaciente.eliminado)))) {

            printf("\n");
            muestraUnPaciente(paciente->datosPaciente);
            textoPresioneCualquierTecla();

        } else {
            printf("\n");
            textoDniNoEnBaseDeDatos();
        }

    }
}

nodoPaciente * inicArbolPacientes(){
    return NULL;
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

void muestraUnPaciente(stPaciente datosPaciente){

    printf(" Apellido y nombre: %s", datosPaciente.apellidoNombre);
    printf("\n Direccion: %s", datosPaciente.direccion);
    printf("\n Dni: %d", datosPaciente.dni);
    printf("\n Edad: %d", datosPaciente.edad);
    printf("\n Telefono: %s", datosPaciente.telefono);
    printf("\n Eliminado: %d", datosPaciente.eliminado);
    printf("\n =====================\n");

}

void textoDniNoEnBaseDeDatos(){

    system("cls");
    Rectangulo();

    gotoxy(10, 4);
    printf("El dni ingresado no esta registrado en la base de datos.");
    gotoxy(10, 7);
    printf("Presione cualquier tecla para continuar...");
    fflush(stdin);
    getch();

}

/// FUNCIONES OPCION 2 DEL MENU 'submenuGestionPacientes':

void submenuModificarDatosPaciente(nodoPaciente * arbolPacientes, int flag){

    int dni = consultaDniYVerifica();

    if (dni) {

        nodoPaciente * paciente = buscaPaciente(arbolPacientes, dni);

        if (paciente && (flag || (!flag && !(paciente->datosPaciente.eliminado)))) {

            int seModificoTrue = 0;
            stPaciente pacienteAux;
            pacienteAux = paciente->datosPaciente;
            int opcion;
            char opcionSalida = 0;

            do {
                system("cls");
                Rectangulo();
                muestraUnPacienteEnRectangulo(pacienteAux, flag);

                opcion = 0;
                gotoxy(15, 8);
                printf("Que dato desea modificar? Ingrese una opcion:\n");
                gotoxy(15, 9);
                printf("(1) Apellido y nombre\n");
                gotoxy(15, 10);
                printf("(2) Edad\n");
                gotoxy(15, 11);
                printf("(3) Dni\n");
                gotoxy(15, 12);
                printf("(4) Direccion\n");
                gotoxy(15, 13);
                printf("(5) Telefono\n");
                gotoxy(15, 14);
                fflush(stdin);
                scanf("%i", &opcion);
                system("cls");

                if (1 <= opcion && opcion <= 5 && opcion != 3) {
                    seModificoTrue = 1;
                }

                switch (opcion) {
                    case 1:
                        printf("\n Ingrese apellido y nombre: ");
                        fflush(stdin);
                        gets(pacienteAux.apellidoNombre);
                        break;
                    case 2:
                        printf("\n Ingrese la edad: ");
                        fflush(stdin);
                        scanf("%d", &pacienteAux.edad);
                        break;
                    case 3:
//                        printf("\n Ingrese el dni: ");
//                        fflush(stdin);
//                        scanf("%d", &dni);

                        dni = consultaDniYVerifica();

                        if (dni) {
                            if (existeElPaciente(arbolPacientes, dni) && dni!=paciente->datosPaciente.dni) {
                                printf("\n\n El dni ingresado ya esta registrado en la base de datos.");
                                textoPresioneCualquierTecla();
                            } else {
                                seModificoTrue = 1;
                                pacienteAux.dni = dni;
                            }
                        }
                        break;
                    case 4:
                        printf("\n Ingrese la direccion: ");
                        fflush(stdin);
                        gets(pacienteAux.direccion);
                        break;
                    case 5:
                        printf("\n Ingrese el telefono: ");
                        fflush(stdin);
                        gets(pacienteAux.telefono);
                        break;

                    default:
                        // opcion incorrecta, se repite el menu
                        break;
                }

                if (1 <= opcion && opcion <= 5) {
                    system("cls");
                    Rectangulo();
                    gotoxy(5, 5);
                    printf("Desea modificar algun otro dato del paciente? En ese caso");
                    gotoxy(5, 6);
                    printf("presione cualquier tecla, para finalizar presione ESC.");
                    fflush(stdin);
                    opcionSalida = getch();
                }

            } while (opcionSalida != ESC);

            // si se cambio el dni, elimino el nodo y lo vuelvo a insertar, asi el arbol mantiene el orden por dni
            if (paciente->datosPaciente.dni != pacienteAux.dni) {

                arbolPacientes = eliminarNodoArbolPacientes(arbolPacientes, paciente->datosPaciente.dni);
                arbolPacientes = insertarPaciente(arbolPacientes, pacienteAux);

            } else {
                paciente->datosPaciente = pacienteAux;
            }

            if (seModificoTrue) {

                system("cls");
                Rectangulo();
                gotoxy(12,5);
                printf("Se ha modificado el paciente.");
                gotoxy(12,7);
                textoPresioneCualquierTecla2();

            }

        } else {
            textoDniNoEnBaseDeDatos();
        }

    }
}

void muestraUnPacienteEnRectangulo(stPaciente datosPaciente, int flag){

    gotoxy(1, 1);
    printf("  Apellido y nombre: %s", datosPaciente.apellidoNombre);
    gotoxy(1, 2);
    printf("  Direccion: %s", datosPaciente.direccion);
    gotoxy(1, 3);
    printf("  Dni: %d", datosPaciente.dni);
    gotoxy(1, 4);
    printf("  Edad: %d", datosPaciente.edad);
    gotoxy(1, 5);
    printf("  Telefono: %s", datosPaciente.telefono);

    // si es administrador, se muestra el campo 'eliminado':
    if (flag) {
        gotoxy(1, 6);
        printf("  Eliminado: %d", datosPaciente.eliminado);
    }

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

nodoPaciente * encontrarMinimoDni(nodoPaciente* arbolPacientes){
    while (arbolPacientes->izq) {
        arbolPacientes = arbolPacientes->izq;
    }
    return arbolPacientes;
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

nodoPaciente * crearNodoArbolPaciente(stPaciente datosStPaciente){
    nodoPaciente * nodoNuevo = (nodoPaciente *) malloc(sizeof(nodoPaciente));

    nodoNuevo->datosPaciente = datosStPaciente;
    nodoNuevo->listaIngresos = inicListaIngresos();
    nodoNuevo->der = NULL;
    nodoNuevo->izq = NULL;

    return nodoNuevo;
}

/// FUNCIONES OPCION 3 DEL MENU 'submenuGestionPacientes':

nodoPaciente * altaDePaciente(nodoPaciente * arbolPacientes){
    int dni = consultaDniYVerifica();

    if (dni) {

        if (existeElPaciente(arbolPacientes, dni)) {
            printf("\n El paciente ya esta registrado en la base de datos. Puede modificar sus datos desde la opcion 2 del menu anterior.");
        } else {
            stPaciente nuevoPaciente;

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
    }

    return arbolPacientes;
}

// 'consultaDniYVerifica' consulta y verifica el DNI. Si éste resulta
// válido, lo devuelve, caso contrario, devuelve 0:
int consultaDniYVerifica(){

    char dni[9];
    int dniValido;
    int enteroDni;
    int longitudCadena;
    char opcion;

    do {

        opcion = 1;
        dniValido = 1;
        enteroDni = 0;
        printf("\n Ingrese el DNI del paciente: ");
        fflush(stdin);
        gets(dni);

        // si ingresó un dni de mas de 8 digitos, se pisó el '\0' de la cadena
        // de caracteres. Ingresa al else de este if, setea dniValido en 0 y repone
        // el '\0':
        if (dni[8] == '\0') {

            longitudCadena = strlen(dni);

            // para que sea un DNI válido tiene que ser mayor a 99.999,
            // entonces la cadena ingresada tiene que tener mas de 5
            // caracteres, caso contrario ya se que es un DNI no valido:
            if (longitudCadena > 5) {

                // este for chequea que la cadena de caracteres ingresada tenga solo
                // dígitos, y no se hayan ingresado letras, caracteres especiales o espacios:
                for (int i=0; i<longitudCadena; i++) {

                    if ( !isdigit(dni[i]) ) {
                        dniValido = 0;
                        enteroDni = 0;
                        i=10;
                    }
                }

                if (dniValido) {

                    // en este punto se que la cadena de caracteres ingresada tiene
                    // solo números. Este for pasa la cadena de caracteres a un número
                    // entero:
                    for (int i=0; i<longitudCadena; i++) {

                        // dni[i]-48 pasa del caracter al numero en int:
                        enteroDni += ( (int) pow(10, longitudCadena-i-1) ) * (dni[i]-48);
                    }

                    // a este if no debería llegar con un número mayor/igual a 100.000.000,
                    // ni menor/igual a 99.999, pero supongo que no esta de mas la validación:
                    if (enteroDni<=99999 || enteroDni>=100000000) {

                        dniValido = 0;
                        enteroDni = 0;
                    }
                }

            } else {
                dniValido = 0;
                enteroDni = 0;
            }

        } else {
            dniValido = 0;
            enteroDni = 0;
            dni[8] = '\0';
        }

        // Si el DNI resulta incorrecto, consulto al usuario si quiere seguir o cancelar:
        if (!dniValido) {
            printf("\n\n Error, debe ingresar un DNI valido. Asegurese de no\n ingresar espacios, letras o numeros negativos.");
            printf("\n\n Si el error persiste, comuniquese con el area de TI.\n Presione cualquier tecla para continuar, ESC para cancelar...");
            fflush(stdin);
            opcion = getch();
        }

        system("cls");

    } while (!dniValido && opcion != ESC);

    return enteroDni;
}

/// FUNCIONES OPCION 4 DEL MENU 'submenuGestionPacientes':

void submenuDarDeBajaUnPaciente(nodoPaciente * arbolPacientes, int flag){

    int dni = consultaDniYVerifica();

    if (dni) {

        nodoPaciente * paciente = buscaPaciente(arbolPacientes, dni);

        if (paciente) {

            // si el paciente ya estaba dado de baja, se informa al usuario,
            // sea administrador o administrativo:
            if ( !(paciente->datosPaciente.eliminado) ) {

                char opcion;

                // este do-while es la pantalla de confirmacion en la baja del paciente:
                do {

                    Rectangulo();
                    muestraUnPacienteEnRectangulo(paciente->datosPaciente, flag);
                    gotoxy(15, 8);
                    printf("Esta seguro que desea dar de baja al paciente?");
                    gotoxy(15, 9);
                    printf("Presione S para confirmar, N para cancelar...");
                    fflush(stdin);
                    opcion = getch();

                    opcion = toupper(opcion);

                    system("cls");

                } while (opcion != 83 && opcion != 78); // el ASCII en 'opcion' va a llegar con 83 si presionó
                                                        // 's' o 'S' o con 78 si presiono 'n' o 'N'

                if (opcion == 83) {

                    // Es baja del paciente en cascada, es decir, da de baja primero las practicas
                    // x ingreso asociadas, el ingreso en cuestion en cada iteracion de ingresos y
                    // por ultimo da de baja al paciente:

                    nodoIngreso * auxListaIngresos = paciente->listaIngresos;

                    while (auxListaIngresos) {
                        darDeBajaTodasLasPracticasXIngreso(auxListaIngresos->listaPracticasXIngreso);
                        auxListaIngresos->ingreso.eliminado = 1;
                        auxListaIngresos = auxListaIngresos->siguiente;
                    }

                    paciente->datosPaciente.eliminado = 1;
                    printf("\n Se dio de baja al paciente.");
                    textoPresioneCualquierTecla();

                }

            } else {
                printf("\n El paciente ya habia sido dado de baja con anterioridad.");
                textoPresioneCualquierTecla();
            }

        } else {
            printf("\n");
            textoDniNoEnBaseDeDatos();
        }

    }
}

/// FUNCIONES OPCION 5 DEL MENU 'submenuGestionPacientes':

void submenuElijeOrdenamientoPacientes(nodoPaciente * arbolPacientes, int flag){

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
                inorderPacientes(arbolPacientes, flag);
                break;
            case 2: // Pacientes ordenados por apellido
                imprimePacientesOrdenadosPorApellido(arbolPacientes, flag);
                break;

            default:
                // se selecciono una opcion no valida o la 3 'Volver'
                break;
        }

    } else {
        printf("\n No hay pacientes cargados en la base de datos.");
    }

    if (opcion == 1 || opcion == 2 || !arbolPacientes) {
        textoPresioneCualquierTecla();
    }

    system("cls");

}

void inorderPacientes(nodoPaciente * arbolPacientes, int flag){
    if (arbolPacientes) {
        inorderPacientes(arbolPacientes->izq, flag);

        if (flag || (!flag && !(arbolPacientes->datosPaciente.eliminado))) {
            muestraUnPaciente(arbolPacientes->datosPaciente);
        }

        inorderPacientes(arbolPacientes->der, flag);
    }
}

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

void muestraArregloPacientes(stPaciente arregloPacientes[], int validosArre, int flag){
    for (int i = 0; i<validosArre; i++) {
        if (flag || (!flag && !(arregloPacientes[i].eliminado))) {
            muestraUnPaciente(arregloPacientes[i]);
        }
    }
}

void imprimePacientesOrdenadosPorApellido(nodoPaciente * arbolPacientes, int flag){

    stPaciente * arregloPacientes = arbolPacientesToArreglo(arbolPacientes);
    printf("\n Listado de pacientes, ordenados por apellido:\n\n");
    muestraArregloPacientes(arregloPacientes, cantidadNodosArbolPacientes(arbolPacientes), flag);

}

/// FUNCIONES PARA MANEJO DE ARCHIVO PACIENTES:

void liberarArbolPacientes(nodoPaciente * arbolPacientes){

    if (arbolPacientes) {
        liberarArbolPacientes(arbolPacientes->izq);
        liberarArbolPacientes(arbolPacientes->der);
        free(arbolPacientes);
    }
}

///FUNCIONES QUE LAS USA INGRESOS:

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

void muestraUnPacienteResumido(stPaciente datosPaciente){

    printf("\n*** Datos del Paciente ***\n");
    printf("Apellido y nombre: %s\n", datosPaciente.apellidoNombre);
    printf("DNI: %d\n", datosPaciente.dni);
    printf("Telefono: %s\n", datosPaciente.telefono);
    puts("-------------------------");

}

///FUNCIONES QUE LAS USA PRACTICAXINGRESO:

int existeIngresoXnroIngreso(nodoPaciente *arbolPacientes, int nroIngresoBuscar){
    if (arbolPacientes == NULL)
    {
        return 0; // No existe el número de ingreso en el árbol
    }

    if (arbolPacientes->listaIngresos != NULL)
    {
        nodoIngreso *ingresos = arbolPacientes->listaIngresos;
        while (ingresos != NULL) {
            if (nroIngresoBuscar == ingresos->ingreso.numeroIngreso && ingresos->ingreso.eliminado != 1)
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

int existeIngreso(nodoPaciente *arbolPacientes) {
    if (arbolPacientes == NULL) {
        return 0; // No existe el número de ingreso en el árbol
    }

    if (arbolPacientes->listaIngresos != NULL) {
        nodoIngreso *ingresos = arbolPacientes->listaIngresos;
        while (ingresos != NULL) {
            if (ingresos->ingreso.eliminado != 1) {
                return 1; // Se encontró un numero de ingreso, sino no hay ninguno
            }
            else
            {
                return 0;
            }
            ingresos = ingresos->siguiente;
        }
    }

    // Buscar en los subárboles izquierdo y derecho
    if (arbolPacientes->izq) {
        return existeIngreso(arbolPacientes->izq);
    }
    if (arbolPacientes->der) {
        return existeIngreso(arbolPacientes->der);
    }

    return 0; // No se encontraron ingresos
}

