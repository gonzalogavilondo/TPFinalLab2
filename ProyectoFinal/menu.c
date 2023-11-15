#include "menu.h"

///PRINTF MENU PRINCIPAL
void submenuManejoEmpleados() {
    char control = 's';;
    int opcion;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Manejo de empleados");
        gotoxy(15, 4);
        printf("Que funcion desea ejecutar?\n");
        gotoxy(15, 5);
        printf("(1) ALTA\n");
        gotoxy(15, 6);
        printf("(2) BAJA\n");
        gotoxy(15, 7);
        printf("(3) MODIFICACIÓN\n");
        gotoxy(15, 8);
        printf("(4) CONSULTA\n");
        gotoxy(15, 9);
        printf("(5) LISTADO\n");
        gotoxy(15, 10);
        printf("(6) Volver\n");
        gotoxy(15, 11);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
            case 1: menuAltaDeEmpleado("Administrador"); break;
            case 2: menuBajaDeEmpleado("Administrador"); break;
            // Agregar otros casos según sea necesario

            case 6:
                control = 'n';  // Salir del bucle si se selecciona '6' para volver
                break;

            default:
                printf("Opción no válida. Por favor, reintente.\n");
                break;

        }

    } while (control == 's' || control == 'S');

    system("cls");
}
void menuAltaDeEmpleado(char tipoEmpleadoEjecuta[]) {
    stEmpleado nuevoEmpleado;
    char opcion = 0;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("ALTA DE EMPLEADO");

        gotoxy(2, 4);
        printf("Ingrese el DNI del empleado:                    ('0' para volver)");
        gotoxy(30, 4);
        scanf("%d", &nuevoEmpleado.dni);
        if (nuevoEmpleado.dni != 0)
        {
            if (existeDNIEnEmpleados(nuevoEmpleado.dni) == 1)
            {
                gotoxy(2, 13);
                printf("El empleado ya está cargado en el sistema!\n");
            }
            else
            {
                nuevoEmpleado.eliminado = 0;

                gotoxy(2, 5);
                printf("Ingrese apellido y nombre: ");
                fflush(stdin);
                gotoxy(30, 5);
                gets(nuevoEmpleado.apellidoYNombre);

                int existe = 0;
                do
                {
                    char usuarioAux[20];
                    gotoxy(2, 6);
                    printf("Ingrese el Usuario: ");
                    fflush(stdin);
                    gotoxy(30, 6);
                    gets(usuarioAux);
                    existe = existeUsuarioEnEmpleados(usuarioAux);
                    if (existe == 0)
                    {
                        strcpy(nuevoEmpleado.usuario, usuarioAux);
                    }
                    else
                    {
                        gotoxy(2, 15);
                        printf("El usuario ingresado ya está en el sistema. Ingrese uno diferente.");
                    }
                }
                while (existe != 0);

                gotoxy(2, 7);
                printf("Ingrese la contraseña: ");
                fflush(stdin);
                gotoxy(30, 7);
                gets(nuevoEmpleado.contrasenia);

                int numeroPerfil = 0;
                while (numeroPerfil == 0)
                {
                    int error = 0;
                    gotoxy(2, 8);
                    printf("Ingrese el nro del perfil:\n");
                    gotoxy(2, 9);
                    printf(" 1 -> Profesional de laboratorio: Técnico\n");
                    gotoxy(2, 10);
                    printf(" 2 -> Profesional de laboratorio: Bioquímico\n");

                    if (strcmp(tipoEmpleadoEjecuta, "Administrador") == 0)
                    {
                        gotoxy(2, 11);
                        printf(" 3 -> Administrativo\n");
                        gotoxy(2, 12);
                        printf(" 4 -> Administrador\n");
                    }

                    fflush(stdin);
                    gotoxy(30, 8);
                    scanf("%d", &numeroPerfil);

                    if (strcmp(tipoEmpleadoEjecuta, "Administrativo") == 0)
                    {
                        if (numeroPerfil != 1 && numeroPerfil != 2)
                        {
                            gotoxy(2, 15);
                            printf("Ingresó un número no válido. Por favor, reintente.");
                            error = 1;
                            numeroPerfil = 0;
                        }
                    }

                    if (strcmp(tipoEmpleadoEjecuta, "Administrador") == 0 && error == 0)
                    {
                        if (numeroPerfil != 1 && numeroPerfil != 2 && numeroPerfil != 3 && numeroPerfil != 4)
                        {
                            gotoxy(2, 15);
                            printf("Ingresó un número no válido. Por favor, reintente.");
                            numeroPerfil = 0;
                        }
                    }
                }

                switch (numeroPerfil)
                {
                case 1:
                    strcpy(nuevoEmpleado.perfil, "Técnico");
                    break;
                case 2:
                    strcpy(nuevoEmpleado.perfil, "Bioquímico");
                    break;
                case 3:
                    strcpy(nuevoEmpleado.perfil, "Administrativo");
                    break;
                case 4:
                    strcpy(nuevoEmpleado.perfil, "Administrador");
                    break;
                }

                int guardado = guardarEmpleadoEnArchivo(nuevoEmpleado);

                system("cls");

                if (guardado == 0)
                {
                    gotoxy(1, 1);
                    printf("El empleado se guardó correctamente!\n");
                    gotoxy(2, 1);
                    mostrarEmpleado(nuevoEmpleado);
                }
                else
                {
                    gotoxy(15, 2);
                    printf("Error en la apertura del archivo. Comuníquese con sistemas.\n");
                }
            }

            do
            {
                gotoxy(2, 15);
                printf("Si quiere cargar otro empleado, presione 'S' o para salir 'N'.");
                opcion = toupper(getch());

                if (opcion != 'S' && opcion != 'N')
                {
                    gotoxy(2, 13);
                    printf("Ingresó una opción no válida. Por favor, reintente.");
                }
            }
            while (opcion != 'S' && opcion != 'N');

        }
        }while (opcion == 'S');

    }
void menuBajaDeEmpleado(char tipoEmpleadoEjecuta[]) {
    stEmpleado bajaEmpleado;
    char opcion = 0;
    char confirmar = 0;
    int dniBajaEmpleado;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("BAJA DE EMPLEADO");

        gotoxy(2, 4);
        printf("Ingrese el DNI del empleado:                    ('0' para volver) ");
        gotoxy(30, 4);
        scanf("%d", &dniBajaEmpleado);

        if (dniBajaEmpleado != 0) {
            if (existeDNIEnEmpleados(dniBajaEmpleado) == 0) {
                gotoxy(2, 13);
                printf("El empleado no esta cargado en el sistema!\n");
            } else {
                bajaEmpleado = traerEmpleadoXDNI(dniBajaEmpleado);

                if (strcmp(tipoEmpleadoEjecuta, "Administrador") != 0) {
                    if (strcmp(bajaEmpleado.perfil, "Administrador") == 0 || strcmp(bajaEmpleado.perfil, "Administrativo") == 0) {
                        gotoxy(2, 13);
                        printf("No tiene permisos para dar de baja a un Administrador o Administrativo!\n");
                        continue;
                    }
                }

                gotoxy(2, 4);
                printf("El usuario a dar de baja es:              ('S' para confirmar la baja)\n");
                gotoxy(2, 6);
                printf("Apellido y nombre:..%s", bajaEmpleado.apellidoYNombre);
                gotoxy(2, 7);
                printf("DNI:................%d", bajaEmpleado.dni);
                gotoxy(2, 8);
                printf("Usuario:............%s", bajaEmpleado.usuario);
                gotoxy(2, 9);
                printf("Contrasenia:........%s", bajaEmpleado.contrasenia);
                gotoxy(2, 10);
                printf("Perfil:.............%s", bajaEmpleado.perfil);
                gotoxy(2, 11);
                printf("Eliminado:..........%d", bajaEmpleado.eliminado);

                gotoxy(30, 4);
                scanf(" %c", &confirmar);
                if (confirmar == 'S' || confirmar == 's') {
                    modificarEstadoEmpleadoXDNI(1, dniBajaEmpleado);
                    gotoxy(2, 14);
                    printf("Empleado dado de baja!");
                } else {
                    gotoxy(2, 14);
                    printf("Baja de usuario cancelada.");
                }
            }
        do {
            gotoxy(2, 15);
            printf("Si quiere dar de baja otro empleado presione 'S' o para salir 'N'.\n");
            gotoxy(69, 15);
            opcion = toupper(getch());

            if (opcion != 'S' && opcion != 'N') {
                gotoxy(2, 13);
                printf("Ingresó una opción no válida, reintente por favor.\n");
            }
        } while (opcion != 'S' && opcion != 'N');
        }
     }while (opcion == 'S');

}


/// ////////////////////////////////////////////////////////////////////////////////////////////////
///OTRAS FUNCIONES DE MENU
void imprimirCabecera(char cabecera[]){
    printf("\t\t%s     \n",cabecera);
    printf("%c", 219);
    for(int i=0;i<=70;i++){
        printf("%c",220);
    }
    printf("%c",219);
}

void cabeza(char a[]){
    imprimirCabecera(a);
}

void Rectangulo(){
    system("color F4");
    int lado=15;
    int base=73;
    int i=0;
    while(i<base){
        printf("%c",220);
        i++;
    }
    i=0;
    while(i<lado){
        printf("\n%c\t\t\t\t\t\t\t\t\t%c",219,219);
        i++;
    }
    i=0;
    printf("\n");
    printf("%c",219);
    while(i<base-2){
        printf("%c",220);
        i++;
    }
    printf("%c",219);

}
