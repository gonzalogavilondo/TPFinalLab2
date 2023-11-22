#include "menu.h"

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
                    printf(" 1 -> Profesional de laboratorio: Tecnico\n");
                    gotoxy(2, 10);
                    printf(" 2 -> Profesional de laboratorio: Bioquimico\n");

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
                            printf("Ingreso un numero no valido. Por favor, reintente.");
                            error = 1;
                            numeroPerfil = 0;
                        }
                    }

                    if (strcmp(tipoEmpleadoEjecuta, "Administrador") == 0 && error == 0)
                    {
                        if (numeroPerfil != 1 && numeroPerfil != 2 && numeroPerfil != 3 && numeroPerfil != 4)
                        {
                            gotoxy(2, 15);
                            printf("Ingreso un numero no valido. Por favor, reintente.");
                            numeroPerfil = 0;
                        }
                    }
                }

                switch (numeroPerfil)
                {
                case 1:
                    strcpy(nuevoEmpleado.perfil, "Tecnico");
                    break;
                case 2:
                    strcpy(nuevoEmpleado.perfil, "Bioquimico");
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
                    printf("Ingreso una opcion no valida. Por favor, reintente.");
                }
            }
            while (opcion != 'S' && opcion != 'N');


        }else{
            opcion = 'N';
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
                printf("Ingreso una opcion no valida, reintente por favor.\n");
            }
        } while (opcion != 'S' && opcion != 'N');
        }else{
            opcion = 'N';
        }
     }while (opcion == 'S');

}

void subMenuModificacionDeEmpleado(char tipoEmpleadoEjecuta[]){

    char control;
    int opcion;
    int dniModificar;
    //char op;
    int numeroPerfil = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(1,1);
        cabeza("MENU MODIFICACION EMPLEADO");
        gotoxy(2,4);
        printf("Ingrese el dni del empleado a modificar:           ('0' para volver)");
        gotoxy(42,4);
        scanf("%d", &dniModificar);
        if(dniModificar != 0){
            if (existeDNIEnEmpleados(dniModificar) == 0){
            gotoxy(1, 13);
            printf("El empleado no esta cargado en el sistema!\n");
            gotoxy(1,17);
            system("pause");
            }
            else
            {
                do
                {
                    stEmpleado empleadoAux = traerEmpleadoXDNI(dniModificar);
                    system("cls");
                    Rectangulo();
                    gotoxy(1,1);
                    cabeza("MENU MODIFICACION EMPLEADO");
                    gotoxy(1,3);
                    printf("Nombre: %s |DNI: %d |  Usuario:%s", empleadoAux.apellidoYNombre, empleadoAux.dni, empleadoAux.usuario);
                    gotoxy(1,4);
                    printf("Contrasenia: %s |Perfil: %s |Eliminado: %d", empleadoAux.contrasenia,empleadoAux.perfil, empleadoAux.eliminado);
                    gotoxy(15,6);
                    printf("Que desea Modificar?");
                    gotoxy(15,7);
                    printf("(1)APELLIDO Y NOMBRE");
                    gotoxy(15,8);
                    printf("(2)DNI");
                    gotoxy(15,9);
                    printf("(3)USUARIO");
                    gotoxy(15,10);
                    printf("(4)PERFIL");
                    gotoxy(15,11);
                    printf("(5)CONTRASENIA");
                    gotoxy(15,12);
                    printf("(6)ESTADO");
                    gotoxy(15,13);
                    printf("(7)VOLVER");
                    gotoxy(15,14);
                    fflush(stdin);
                    scanf("%d", &opcion);
                    system("cls");


                    char ModificarGenerico[30];
                    //int generico=0;
                    int modificarDni=0;
                    system("cls");
                    Rectangulo();
                    gotoxy(1,1);
                    cabeza("MENU MODIFICACION EMPLEADO");
                    gotoxy(1,3);
                    printf("Nombre: %s |DNI: %d |  Usuario:%s", empleadoAux.apellidoYNombre, empleadoAux.dni, empleadoAux.usuario);
                    gotoxy(1,4);
                    printf("Contrasenia: %s |Perfil: %s |Eliminado: %d", empleadoAux.contrasenia,empleadoAux.perfil, empleadoAux.eliminado);

                    switch(opcion)
                    {
                    case 1:
                        gotoxy(1,6);
                        printf("Ingrese el nuevo nombre:");
                        fflush(stdin);
                        gets(ModificarGenerico);

                        modificarNombreEmpleadoXDNI(ModificarGenerico, dniModificar);
                        gotoxy(1,15);
                        printf("Nombre cambiado con exito!");
                        gotoxy(1,17);
                        system("pause");
                        break;
                    case 2:
                        gotoxy(1,6);
                        printf("Ingrese el nuevo DNI:");
                        fflush(stdin);
                        gotoxy(22, 6);
                        scanf("%d", &modificarDni);

                        if (modificarDni != 0)
                        {
                            if (existeDNIEnEmpleados(modificarDni) != 0)
                            {
                                gotoxy(1, 15);
                                printf("El DNI ingresado ya esta en el sistema! Intente nuevamente.\n");
                                gotoxy(1,17);
                                system("pause");
                            }
                            else{
                                modificarDNIEmpleadoXUsuario(modificarDni,dniModificar);
                                dniModificar = modificarDni;
                                gotoxy(1,15);
                                printf("DNI cambiado con exito!");
                                gotoxy(1,17);
                                system("pause");

                            }
                        }
                        break;
                    case 3:
                        gotoxy(1,6);
                        printf("El nuevo usuario:");
                        fflush(stdin);
                        gotoxy(19, 6);
                        gets(ModificarGenerico);


                        if (existeUsuarioEnEmpleados(ModificarGenerico) != 0)
                        {
                            gotoxy(1, 15);
                            printf("El usuario ingresado ya esta en el sistema! Intente nuevamente.\n");
                            gotoxy(1,17);
                            system("pause");
                        }
                        else
                        {
                            modificarUsuarioEmpleadoXDNI(ModificarGenerico,dniModificar);
                            gotoxy(1,15);
                            printf("Usuario cambiado con exito!");
                            gotoxy(1,17);
                            system("pause");

                        }
                        break;
                    case 4:
                        numeroPerfil = 0;
                        while (numeroPerfil == 0)
                        {
                            int error = 0;
                            gotoxy(2, 6);
                            printf("Ingrese el nro del perfil:\n");
                            gotoxy(2, 7);
                            printf(" 1 -> Profesional de laboratorio: Tecnico\n");
                            gotoxy(2, 8);
                            printf(" 2 -> Profesional de laboratorio: Bioquimico\n");

                            if (strcmp(tipoEmpleadoEjecuta, "Administrador") == 0)
                            {
                                gotoxy(2, 9);
                                printf(" 3 -> Administrativo\n");
                                gotoxy(2, 10);
                                printf(" 4 -> Administrador\n");
                            }
                            fflush(stdin);
                            gotoxy(30, 6);
                            printf("                         ");
                            gotoxy(30, 6);
                            scanf("%d", &numeroPerfil);

                            if (strcmp(tipoEmpleadoEjecuta, "Administrativo") == 0)
                            {
                                if (numeroPerfil != 1 && numeroPerfil != 2)
                                {
                                    gotoxy(2, 15);
                                    printf("Ingreso un numero no valido. Por favor, reintente.");
                                    error = 1;
                                    numeroPerfil = 0;
                                }
                            }

                            if (strcmp(tipoEmpleadoEjecuta, "Administrador") == 0 && error == 0)
                            {
                                if (numeroPerfil != 1 && numeroPerfil != 2 && numeroPerfil != 3 && numeroPerfil != 4)
                                {
                                    gotoxy(2, 15);
                                    printf("Ingreso un numero no valido. Por favor, reintente.");
                                    numeroPerfil = 0;
                                }
                            }
                        }

                        switch (numeroPerfil)
                        {
                        case 1:
                            strcpy(empleadoAux.perfil, "Tecnico");
                            break;
                        case 2:
                            strcpy(empleadoAux.perfil, "Bioquimico");
                            break;
                        case 3:
                            strcpy(empleadoAux.perfil, "Administrativo");
                            break;
                        case 4:
                            strcpy(empleadoAux.perfil, "Administrador");
                            break;
                        default:
                            numeroPerfil = 0;
                            break;
                        }

                        modificarPerfilEmpleadoXDNI(empleadoAux.perfil,dniModificar);

                        gotoxy(1,15);
                        printf("Perfil cambiado con exito!");
                        gotoxy(1,17);
                        system("pause");

                        break;
                    case 5:
                        gotoxy(1,6);
                        printf("Ingrese la nueva contrasenia:");
                        fflush(stdin);
                        gets(ModificarGenerico);

                        modificarContraseniaEmpleadoXDNI(ModificarGenerico, dniModificar);
                        gotoxy(1,15);
                        printf("Contrasenia cambiada con exito!");
                        gotoxy(1,17);
                        system("pause");
                        break;
                    case 6:
                        gotoxy(1,6);
                        printf("Desea cambiar el estado del empleado? (S/N) \n");
                        fflush(stdin);
                        char estado;
                        gotoxy(45,6);
                        scanf("%c", &estado);
                        if(estado == 's' || estado == 'S'){
                            if (empleadoAux.eliminado == 1){
                                modificarEstadoEmpleadoXDNI(0, dniModificar);
                            }else{
                                modificarEstadoEmpleadoXDNI(1, dniModificar);
                            }
                            gotoxy(1,15);
                            printf("Estado cambiado con exito!");
                            gotoxy(1,17);
                            system("pause");
                        }
                        break;
                    case 7:

                        break;


                    default:
                        break;

                    }


                }while (opcion != 7);

                do
                {
                    gotoxy(2, 15);
                    printf("Si quiere modificar otro empleado presione 'S' o para salir 'N'.\n");
                    gotoxy(69, 15);
                    control = toupper(getch());

                    if (control != 'S' && control != 'N')
                    {
                        gotoxy(2, 13);
                        printf("Ingreso una opcion no valida, reintente por favor.\n");
                    }
                }
                while(control == 'S');
            }
        }
    } while(control == 'S');
}
void subMenuConsultaDeEmpleado(char tipoEmpleadoEjecuta[]){
    stEmpleado consultaEmpleado;
    char opcion = 0;
    int dniConsulta;

    do {
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("CONSULTA DE EMPLEADO");

        gotoxy(2, 4);
        printf("Ingrese el DNI del empleado:                    ('0' para volver) ");
        gotoxy(30, 4);
        scanf("%d", &dniConsulta);

        if (dniConsulta != 0) {
            if (existeDNIEnEmpleados(dniConsulta) == 0) {
                gotoxy(2, 13);
                printf("El empleado no esta cargado en el sistema!\n");
            } else {
                consultaEmpleado = traerEmpleadoXDNI(dniConsulta);

                if (strcmp(tipoEmpleadoEjecuta, "Administrador") != 0) {
                    if (strcmp(consultaEmpleado.perfil, "Administrador") == 0 || strcmp(consultaEmpleado.perfil, "Administrativo") == 0) {
                        gotoxy(2, 13);
                        printf("No tiene permisos para dar de baja a un Administrador o Administrativo!\n");
                        continue;
                    }
                }

                gotoxy(2, 6);
                printf("Apellido y nombre:..%s", consultaEmpleado.apellidoYNombre);
                gotoxy(2, 7);
                printf("DNI:................%d", consultaEmpleado.dni);
                gotoxy(2, 8);
                printf("Usuario:............%s", consultaEmpleado.usuario);
                gotoxy(2, 9);
                printf("Contrasenia:........%s", consultaEmpleado.contrasenia);
                gotoxy(2, 10);
                printf("Perfil:.............%s", consultaEmpleado.perfil);
                gotoxy(2, 11);
                printf("Eliminado:..........%d", consultaEmpleado.eliminado);
            }
        do {
            gotoxy(2, 15);
            printf("Si quiere ver otro empleado presione 'S' o para salir 'N'.\n");
            gotoxy(69, 15);
            opcion = toupper(getch());

            if (opcion != 'S' && opcion != 'N') {
                gotoxy(2, 13);
                printf("Ingreso una opcion no valida, reintente por favor.\n");
            }
        } while (opcion != 'S' && opcion != 'N');
        }else{
            opcion = 'N';
        }
     }while (opcion == 'S');

}

void subMenuListadosDeEmpleado(char tipoEmpleadoEjecuta[]){

    char control = '\0';
    int opcion;
    //char op;
    //int numeroPerfil = 0;

    do
    {
        system("cls");
        Rectangulo();
        gotoxy(1,1);
        cabeza("MENU LISTADOS DE EMPLEADO");
        gotoxy(15,6);
        printf("Como desea traer la lista de empleados?");
        gotoxy(15,7);
        printf("(1)Ordenado por Apellido y nombre");
        gotoxy(15,8);
        /*printf("(2)Ordenado por DNI");
        gotoxy(15,9);
        printf("(3)Ordenado por Usuario");
        gotoxy(15,10);
        printf("(4)Ordenado por perfil");
        gotoxy(15,11);
        printf("(5)Selccionar un perfil");
        gotoxy(15,12);
        printf("(6)Seleccionar un estado");
        gotoxy(15,13);*/
        printf("(2)VOLVER");
        gotoxy(15,9);
        fflush(stdin);
        scanf("%d", &opcion);
        system("cls");

        stEmpleado arregloEmpleados[1000];
        int validos = pasarArchivoAArregloEmpleados(arregloEmpleados, 1000, 0);
        int i;

        switch(opcion)
        {
        case 1:
            i = 0;
            gotoxy(1,1);
            printf("LISTADO POR APELIIDO Y NOMBRE");
            gotoxy(1,3);
            ordenarPorApellidoYNombre(arregloEmpleados,validos);
            while(i < validos)
            {
                mostrarEmpleado(arregloEmpleados[i]);
                i++;
            }

            system("pause");

            break;
        case 2:
            opcion = 2;
            break;
       /* case 3:
            listaEmpleadosXUsuario();
            break;
        case 4:
            listaEmpleadosXPerfil();
            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;*/


        default:
            break;

        }


    } while (opcion != 2);

    while(control == 'S');
}

/// ////////////////////////////////////////////////////////////////////////////////////////////////
///LOGUEO Empleado
int inicioDeSesionEmpleado(char usuario[],char contrasenia[]){
    stEmpleado e;
    int flag=0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"rb");
    if(pArchiEmpleado!=NULL){
                printf("%s\n",usuario);
                printf("%s\n",contrasenia);
                printf("==================\n");

        while(flag==0&&(fread(&e,sizeof(stEmpleado),1,pArchiEmpleado))>0){
            if(strcmp(e.usuario,usuario)==0&&strcmp(e.contrasenia,contrasenia)==0){
                printf("%s\n",e.usuario);
                printf("%s\n",e.contrasenia);
                flag=1;
        }
    }
    fclose(pArchiEmpleado);
    }
return flag;
}
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

void Rectangulo() {
    // Establecer el color del fondo a negro y el texto a amarillo
    color(0); // Fondo negro
    color(7); // Texto amarillo

    int lado = 15;
    int base = 73;
    int i = 0;

    while (i < base) {
        printf("%c", 220);
        i++;
    }
    i = 0;

    while (i < lado) {
        printf("\n%c\t\t\t\t\t\t\t\t\t%c", 219, 219);
        i++;
    }

    i = 0;
    printf("\n");
    printf("%c", 219);

    while (i < base - 2) {
        printf("%c", 220);
        i++;
    }

    printf("%c", 219);
}





void submenuManejoEmpleados() {
    char control = 's';
    int opcion;

    do {
        opcion = 0;
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
        printf("(3) MODIFICACION\n");
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
            case 3: subMenuModificacionDeEmpleado("Administrador"); break;
            case 4: subMenuConsultaDeEmpleado("Administrador"); break;
            case 5: subMenuListadosDeEmpleado("Administrador"); break;

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

void submenuManejoIngresos(nodoPaciente *arbolPaciente, int flag)
{
    char control = 's';
    int opcion;

    do
    {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Manejo de ingresos");
        gotoxy(15, 4);
        printf("Que funcion desea ejecutar?\n");
        gotoxy(15, 5);
        printf("(1) ALTA\n");
        gotoxy(15, 6);
        printf("(2) MODIFICACION\n");
        gotoxy(15, 7);
        printf("(3) BAJA\n");
        gotoxy(15, 8);
        printf("(4) CONSULTAR LISTADO\n");  // Nueva opción
        gotoxy(15, 9);
        printf("(5) VOLVER\n");  // Ajusta las opciones según sea necesario
        gotoxy(15, 10);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                // Realizar alta de ingreso
                altaDeIngreso(arbolPaciente);
                break;

            case 2:
                // Realizar modificación de ingreso
                modificarDatosIngreso(arbolPaciente);
                break;

            case 3:
                // Realizar baja de ingreso
                buscaYDaDeBajaIngreso(arbolPaciente);
                break;

            case 4:
                // Mostrar listado de ingresos
                mostrarListadoGralIngresos(arbolPaciente, flag);
                system("pause");
                system("cls");
                break;

            case 5:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    system("cls");
}

void submenuManejoPracticasXIngreso(nodoPaciente *arbolPacientes, int flag)
{
    char control = 's';
    int opcion;

    do
    {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Manejo de practicas por ingreso");
        gotoxy(15, 4);
        printf("Que funcion desea ejecutar?\n");
        gotoxy(15, 5);
        printf("(1) ALTA\n");
        gotoxy(15, 6);
        printf("(2) MODIFICACION\n");
        gotoxy(15, 7);
        printf("(3) BAJA\n");
        gotoxy(15, 8);
        printf("(4) CONSULTAR LISTADO\n");
        gotoxy(15, 9);
        printf("(5) VOLVER\n");
        gotoxy(15, 10);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                // Realizar alta de práctica por ingreso
                altaDePracticaXIngreso(arbolPacientes, 0);
                break;

            case 2:
                // Realizar modificación de práctica por ingreso
                //listaPracticaXIngresos = modificarDatosPracticaXIngreso(listaPracticaXIngresos);
                break;

            case 3:
                // Realizar baja de práctica por ingreso
                //buscaYDaDeBajaPracticaXIngreso(listaPracticaXIngresos);
                break;
            case 4:
                mostrarPracticaXIngreso(arbolPacientes, flag); //El flag indica si se llama del menu de administrador o administrativo. flag = 1 (Administrador)/flag = 0 (Administrativo)
            break;

            case 5:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    system("cls");
}
void submenuTecnico(nodoPaciente* arbol)
{
    char control = 's';
    int opcion;
    //int dni;
    //nodoPaciente * paciente;

    do
    {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu Tecnico de laboratorio");
        gotoxy(15, 4);
        printf("Que desea realizar?");
        gotoxy(15, 5);
        printf("(1) Registrar resultado de analisis");
        gotoxy(15, 6);
        printf("(2) Consultar muestra");
        gotoxy(15, 7);
        printf("(3) VOLVER\n");
        gotoxy(15, 8);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                registrarResultadoPracticaXIngreso(arbol);
                break;

            case 2:
                mostrarUnaPracticaXIngreso(arbol);

                break;
            case 3:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    system("cls");
}

void submenuAdministrativo(nodoPaciente * arbolPacientes)
{
    char control = 's';
    int opcion;

    do
    {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu Administrativo");
        gotoxy(15, 4);
        printf("Que desea gestionar?\n");
        gotoxy(15, 5);
        printf("(1) Gestionar Pacientes\n");
        gotoxy(15, 6);
        printf("(2) Gestionar Citas\n");
        gotoxy(15, 7);
        printf("(3) Gestionar personal\n");
        gotoxy(15, 8);
        printf("(4) Gestionar Practicas por Ingreso\n");
        gotoxy(15, 9);
        printf("(5) VOLVER\n");
        gotoxy(15, 10);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion)
        {
            case 1:
                // Gestionar pacientes
                submenuGestionPacientes(arbolPacientes);
                break;

            case 2:
                // Gestionar citas
                submenuManejoIngresos(arbolPacientes, 0);
                break;

            case 3:
                // Gestionar personal
                submenuManejoEmpleados("Administrativo");
                break;
            case 4:
                // Gestionar prácticas por ingreso
                submenuManejoPracticasXIngreso(arbolPacientes, 0);
                break;

            case 5:
                control = 'n';
                break;

            default:
                control = 's';
                break;
        }

    } while (control == 's' || control == 'S');

    system("cls");
}

void submenuAdministrador(nodoPaciente * arbolPacientes){

    char control = 's';
    int opcion;

    do {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu Administrador");
        gotoxy(15, 4);
        printf("Que desea gestionar?\n");
        gotoxy(15, 6);
        printf("(1) Gestionar pacientes\n");
        gotoxy(15, 7);
        printf("(2) Gestionar personal\n");
        gotoxy(15, 8);
        printf("(3) Gestionar ingresos\n");
        gotoxy(15, 9);
        printf("(4) Gestionar practicas\n");
        gotoxy(15, 10);
        printf("(5) Gestionar practicas por ingreso\n");
        gotoxy(15, 11);
        printf("(6) Volver\n");
        gotoxy(15, 12);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
            case 1: //Gestionar pacientes
                submenuGestionPacientes(arbolPacientes);
                break;
            case 2:
                submenuManejoEmpleados("Administrador");
                break;
            case 3: //Gestionar ingresos
                submenuManejoIngresos(arbolPacientes, 1);
                break;
            case 4:
                submenuGestionPracticas();
                break;
            case 5:
                submenuManejoPracticasXIngreso(arbolPacientes, 1);
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

///MENU PRINCIPAL
void menuPrincipal(nodoPaciente* arbol){
    char control = 's';
    int opcion;
    char empleadoEjecuta[20];

    do {
        opcion = 0;
        system("cls");
        Rectangulo();
        gotoxy(15, 1);
        cabeza("Menu principal");
        gotoxy(15, 4);
        printf("Como desea ingresar?\n");
        gotoxy(15, 5);
        printf("(1) TECNICO DE LABORATORIO\n");
        gotoxy(15, 6);
        printf("(2) ADMINISTRATIVO\n");
        gotoxy(15, 7);
        printf("(3) ADMINISTRADOR\n");
        gotoxy(15, 8);
        printf("(4) SALIR\n");
        gotoxy(15, 9);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");

        switch (opcion) {
            case 1: strcpy(empleadoEjecuta, "Tecnico");
                    menuIngresoUserPrintf(empleadoEjecuta, arbol); break;
            case 2: strcpy(empleadoEjecuta, "Administrativo");
                    menuIngresoUserPrintf(empleadoEjecuta, arbol); break;
            case 3: strcpy(empleadoEjecuta, "Administrador");
                    menuIngresoUserPrintf(empleadoEjecuta, arbol); break;

            case 4:
                control = 'n';
                break;

            default:
                control = 's';
                break;

        }

    } while (control == 's' || control == 'S');
}

///PRINTF INGRESO (EMPLEADO)
void menuIngresoUserPrintf(char tipoMenu[], nodoPaciente* arbol){
    char usuario[20];
    char contrasenia[20];
    gotoxy(0,0);
    printf("Inicio de sesion!");
    gotoxy(0,2);
    printf("Usuario:");
    gotoxy(0,3);
    printf("Contrasenia:");
    gotoxy(13,2);
    fflush(stdin);
    gets(usuario);
    gotoxy(13,3);
    fflush(stdin);
    gets(contrasenia);

    int correcto = inicioDeSesion(usuario, contrasenia, tipoMenu);


    if (correcto == 1)
    {
        if(strcmp(tipoMenu,"Tecnico")==0){
            submenuTecnico(arbol);
        }else{
            if(strcmp(tipoMenu,"Administrativo")==0){
                submenuAdministrativo(arbol);
            }else{
                if(strcmp(tipoMenu,"Administrador")==0){
                    submenuAdministrador(arbol);
                }
            }
        }
    }else{
        gotoxy(0,5);
        printf("Error inicio de sesion\n");
        gotoxy(0,6);
        system("pause");
    }
}
