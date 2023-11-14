#include "stEmpleado.h"

void submenuManejoEmpleados(){

    char control;
    int opcion;
    do{
        system("cls");
        Rectangulo();
        gotoxy(15,1);
        cabeza("Menejo de empleados");
        gotoxy(15,4);
        printf("Que funcion desea ejecutar:\n");
        gotoxy(15,5);
        printf("(1)ALTA\n");
        gotoxy(15,6);
        printf("(2)BAJA\n");
        gotoxy(15,7);
        printf("(3)MODIFICACION\n");
        gotoxy(15,8);
        printf("(4)CONSULTA\n");
        gotoxy(15,9);
        printf("(5)LISTADO\n");
        gotoxy(15,10);
        printf("(6)Volver\n");
        gotoxy(15,11);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");


        switch(opcion)
            case 1: menuAltaDeEmpleado("Administrador");

        system("cls");
        printf("Desea ejecutar otra funcion?: (s/n)");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}

void menuAltaDeEmpleado(char tipoEmpleadoEjecuta[]){
    stEmpleado nuevoEmpleado;
    char opcion = 0;
    int dniNuevoEmpleado;
    do {
        system("cls");
        Rectangulo();
        printf("ALTA DE EMPLEADO\n");
        printf("\nIngrese el DNI del empleado: ");
        scanf("%d", &dniNuevoEmpleado);
        if (existeDNIEnEmpleados(dniNuevoEmpleado) == 1) {
            printf("\nEl empleado ya esta cargado en el sistema!\n");
        }else{
            nuevoEmpleado.dni = dniNuevoEmpleado;
            nuevoEmpleado.eliminado = 0;

            printf("\nIngrese apellido y nombre: ");
            fflush(stdin);
            gets(nuevoEmpleado.apellidoYNombre);

            int existe = 0;
            do{
                char usuarioAux[20];
                printf("\nIngrese el Usuario: ");
                fflush(stdin);
                gets(usuarioAux);
                existe = existeUsuarioEnEmpleados(usuarioAux);
                if(existe == 0){
                    strcpy(nuevoEmpleado.usuario, usuarioAux);
                }else{
                    printf("El usuario que ingreso ya esta en sistema. Ingrese uno distinto.");
                }
            }while(existe != 0);

            printf("\nIngrese la contrasenia: ");
            fflush(stdin);
            gets(nuevoEmpleado.contrasenia);


            int numeroPerfil = 0;
            while(numeroPerfil == 0){
                int error = 0;
                printf("\nIngrese el numero del perfil:");
                printf("\n 1 -> Profesiona de laboratorio: Tecnico");
                printf("\n 2 -> Profesiona de laboratorio: Bioquimico");
                if (strcmp(tipoEmpleadoEjecuta,"Administrador") == 0){
                    printf("\n 3 -> Administrativo");
                    printf("\n 4 -> Administrador");
                }

                printf("\n");


                fflush(stdin);
                scanf("%d", &numeroPerfil);
                if (strcmp(tipoEmpleadoEjecuta,"Administrativo") == 0){
                    if(numeroPerfil != 1 && numeroPerfil != 2){
                        printf("\nIngreso un numero no valido, reintente por favor.");
                        printf("\n");
                        error = 1;
                        numeroPerfil = 0;
                    }
                }
                if (strcmp(tipoEmpleadoEjecuta,"Administrador") == 0 && error == 0){
                    if(numeroPerfil != 1 && numeroPerfil != 2 && numeroPerfil != 3 && numeroPerfil != 4){
                    printf("\n Ingreso un numero no valido, reintente por favor.");
                    printf("\n");
                    numeroPerfil = 0;
                    }
                }
            }

            switch(numeroPerfil){
                case 1: strcpy(nuevoEmpleado.perfil, "Tecnico");break;
                case 2: strcpy(nuevoEmpleado.perfil, "Bioquimico");break;
                case 3: strcpy(nuevoEmpleado.perfil, "Administrativo");break;
                case 4: strcpy(nuevoEmpleado.perfil, "Administrador");break;

            }


            int guardado = guardarEmpleadoEnArchivo(nuevoEmpleado);

            if(guardado == 0){
                system("cls");
                printf("\nEl emplead@ se guardo correctamente!");
                mostrarEmpleado(nuevoEmpleado);
            }else{
                printf("\nError en la apertura del archivo. Comuniquese con sistemas");
            }
            system("pause");
            system("cls");
        }

        do{
            printf("\nSi quiere cargar otro empleado presione 'S' o para salir 'N'.");
            opcion = getch();
            system("cls");
            toupper(opcion);
            if(opcion != 'S' && opcion != 'N'){
                printf("\nIngreso una opcion no valida, reintente por favor.");
            }
        }while(opcion != 'S' && opcion != 'N');

    } while (opcion == 'S');
}
//Si existe el empleado en el sistema la funcion retorna un 1, si no existe retorna un 0 (BUSCA POR DNI)
int existeDNIEnEmpleados(int dniEmpleado){
    FILE * pArchiEmpleados = fopen(arEmpleados, "rb");
    stEmpleado e;
    if (pArchiEmpleados != NULL){
        while(fread(&e, sizeof(stEmpleado),1,pArchiEmpleados) > 0){
            if (e.dni == dniEmpleado){
                return 1;
            }
        }
        fclose(pArchiEmpleados);
    }
    return 0;
}
//Si existe el empleado en el sistema la funcion retorna un 1, si no existe retorna un 0 (BUSCA POR NOMBRE DE USUARIO)
int existeUsuarioEnEmpleados(char usuario[]){
    FILE * pArchiEmpleados = fopen(arEmpleados, "rb");
    stEmpleado e;
    if (pArchiEmpleados != NULL){
        while(fread(&e, sizeof(stEmpleado),1,pArchiEmpleados) > 0){
            if (strcmp(e.usuario,usuario) == 0){
                return 1;
            }
        }
        fclose(pArchiEmpleados);
    }
    return 0;
}
int guardarEmpleadoEnArchivo(stEmpleado e){
    FILE * pArchiEmpleados = fopen(arEmpleados, "ab");
    if(pArchiEmpleados != NULL){
        fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleados);
        fclose(pArchiEmpleados);
    }else{
        return 1;
    }
    return 0;
}

void mostrarEmpleado(stEmpleado e){
    printf("\nApellido y nombre:..%s", e.apellidoYNombre);
    printf("\nDNI:................%d", e.dni);
    printf("\nUsuario:............%s", e.usuario);
    printf("\nContrasenia:........%s", e.contrasenia);
    printf("\nPerfil:.............%s", e.perfil);
    printf("\nEliminado:..........%d", e.eliminado);
    printf("\n");
}
///Funciones para modificar empleado
///ANTES DE LLAMAR A ESTA FUNCION VALIDAR SI YA EXISTE EL USUARIO EN EL ARCHIVO!!!!
void modificarUsuarioEmpleadoXDNI(char usuarioNuevo[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,sizeof(stEmpleado)*(-1),SEEK_CUR);
                    strcpy(e.usuario,usuarioNuevo);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
    return modificado;
}
///ANTES DE LLAMAR A ESTA FUNCION VALIDAR SI YA EXISTE EL DNI EN EL ARCHIVO!!!!
void modificarDNIEmpleadoXUsuario(int dniNuevo,char usuario[]){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(strcmp(e.usuario,usuario)==0){
                    fseek(pArchiEmpleado,sizeof(stEmpleado)*(-1),SEEK_CUR);
                    e.dni = dniNuevo;
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
    return modificado;
}
void modificarNombreEmpleadoXDNI(char nombreNuevo[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,sizeof(stEmpleado)*(-1),SEEK_CUR);
                    strcpy(e.apellidoYNombre,nombreNuevo);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
    return modificado;
}
void modificarContraseniaEmpleadoXDNI(char contrasenia[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,sizeof(stEmpleado)*(-1),SEEK_CUR);
                    strcpy(e.contrasenia,contrasenia);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
    return modificado;
}
void modificarPerfilEmpleadoXDNI(char perfil[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,sizeof(stEmpleado)*(-1),SEEK_CUR);
                    strcpy(e.perfil,perfil);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
    return modificado;
}

