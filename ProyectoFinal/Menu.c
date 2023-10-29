#include "Menu.h"

///LOGUEO admin
int logeoAdmin(char nombre[],char contrasenia[],int contraseniaAdmin){
    stUser a;
    int flag=0;
    FILE*pArchiUser = fopen(arUser,"rb");
    if(pArchiUser!=NULL){
        while(flag==0&&(fread(&a,sizeof(stUser),1,pArchiUser))>0){
            if(strcmp(a.nombreUsuario,nombre)==0&&strcmp(a.password,contrasenia)==0&&contraseniaAdmin==123){
                flag=1;
        }
    }
    fclose(pArchiUser);
    }
return flag;
}

///LOGUEO USER
int logeoUser(char nombre[],char contrasenia[]){
    stUser a;
    int flag=0;
    FILE*pArchiUser = fopen(arUser,"rb");
    if(pArchiUser!=NULL){

        while(flag==0&&(fread(&a,sizeof(stUser),1,pArchiUser))>0){
            if(strcmp(a.nombreUsuario,nombre)==0&&strcmp(a.password,contrasenia)==0){
                flag=1;
        }
    }
    fclose(pArchiUser);
    }
return flag;
}




////////////////////////////////////////////////////////////////////////////////////////
///SWICHS DE TODOS:
////////////////////////////////////////////////////////////////////////////////////////
///Swich de MENU PRINCIPAL
void switchMenuPrincipal(int op, stCeldaUsuarios adl[],int validos){
    int i=0;

    switch(op){
        case 1:-
            menuPrincipalAdmiPrint(0,adl,validos);
            system("pause");
            system("cls");
            break;
        case 2:
            menuIngresoUserPrintf(adl,validos);
            //menuProfesionalLabPrint(adl,validos);
            system("pause");
            system("cls");
            break;
        case 3:
            menuAdministrativo(adl, validos);
            system("pause");
            system("cls || clear");
            break;
        case 4:
            system("cls");
            while(i<65){
                printf("%c",220);
                i++;
            }
            printf("\n%c\t\t\t\t\t\t\t\t%c",219,219);
            printf("\n%c\tGracias por utilizar nuestro sistema! :D\t\t%c\n",219,219);
            printf("%c\t\t\t\t\t\t\t\t%c\n",219,219);
            i=0;
            printf("%c",219);
            while(i<63){
                printf("%c",220);
                i++;
            }
            printf("%c",219);
            pasarDeAdlToArchivo(adl,validos);
            exit(-1);
            break;
        default:
            menuPrincipalPrint();
            system("pause");
            system("cls");
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////

///SWICH MENU ADMIN
void switchMenuAdmin(int op,stCeldaUsuarios a[],int validos){
    switch(op){
        case 1:
            submenuAdminUsuarioPrintf(a,validos);
            //subMenuAdminPacientePrint(a, validos);
            system("pause");
            system("cls");
            break;
        case 2:
            submenuAdminCancionPrintf();
            //subMenuAdminPersonalPrint();
            system("pause");
            system("cls");
            break;
        case 3:
            //menuGenerarInformes(a, validos);
            break;
        case 4:
            menuPrincipalPrint();
            break;
        default:
            printf("EL ADMIN NO SE ENCONTRO");
            //menuPrincipalAdmiPrint();
            system("pause");
            system("cls");
            break;
    }
}

///SWICH ADMIN SUBMENU CANCION:
void switchAdminSubCancion(int op){
    char nombreC[30];
    //int dni;

    switch(op){
        case 1:
            system("cls");
            cargaArchiCanciones();
            system("pause");
            system("cls");
            break;
        case 2:
                system("cls");
                printf("Ingrese el DNI del paciente que desee eliminar: \n");
                fflush(stdin);
                gets(nombreC);
            elimininarCancion(nombreC);
            //elimininarCancion(dni);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            menuModificacionCancionPrintf();
            //menuModificacionPersonalPrint
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
                printf("Ingrese el nombre de la cancion que desee mostrar: \n");
                fflush(stdin);
                gets(nombreC);
            ConsultaCancion(nombreC);
            system("pause");
            system("cls");
            break;
        case 5:
            OrdenarPorNoGPrintf();
            system("pause");
            system("cls");
            break;
        case 6:
            menuPrincipalAdmiPrint(1);
            break;
        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;
    }
}

///SWICH ADMIN SUBMENU USUARIO:
void switchAdminSubUsuario(int op,stCeldaUsuarios adl[],int validos){
    int idUser;
    int idgenerico=0;
    int dimension=cantUsers();
    stUser a[dimension];
    validos=passTOarchivoUsuario(a,dimension,validos);
    switch(op){
        case 1:
            system("cls");
            cargarADLmanual(adl,validos,dimension+1);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
                printf("Ingrese el id del usuario que desea eliminar: \n");
                fflush(stdin);
                scanf("%i",&idUser);
            elimininarUserADL(adl,validos,idUser);
            mostrarUsuarioADLxID(adl,validos,idUser);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            menuModificacionUsuarioPrintf(adl,validos);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
                printf("ID del Usuario a Consultar \n");
                fflush(stdin);
                scanf("%i",&idUser);
            ConsultaUserADL(adl,validos,idUser);
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            mostrarADL(adl,validos);
            //ordenarNombre(a,validos);
            //mostrarArregloUsuario(a,validos);
            system("pause");
            system("cls");
            break;
        case 6:
            menuPrincipalAdmiPrint(1);
            break;
        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
///SWITCH DIV INGRESO PESTAÑA USUARIO
void switchIngresoDivision(int op,stCeldaUsuarios adl[],int validos){
    int dim=0;
    switch(op){
        case 1:
            system("cls");
            menuPrincipalUsuarioPrint(adl,validos);
            system("pause");
            system("cls");
            break;
        case 2:
            /**
                ESTO IMPLEMENTAR EN PERFIL DE ADMINISTRADOR Y ADMINISTRATIVO.
            **/
            system("cls");
            dim=1+cantUsers();
            validos=cargarADLmanual(adl,validos,dim);///carga de ald en usuario
            pasarDeAdlToArchivo(adl,validos);

            validos=archivo2adl(adl,validos,dim);
            system("cls");
            printf("Registro Exitoso! :D \n\n");
            printf("[Confirme sus datos]\n");
            system("pause");
            system("cls");
            menuPrincipalUsuarioPrint(adl,validos);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            menuPrincipalPrint();
            system("pause");
            system("cls");
        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
///SWICH MENU USUARIO:
void switchMenuUsuario(int op,char nombreU[],stCeldaUsuarios adl[],int validos){
    int idActualUs=encontrarIDUSERxNombre(nombreU);
    int idCanPlaylist=0;
    char control='s';
    nodoArbolCancion*arbol;
    arbol=inicArbol();
    arbol=array2Arbol(arbol);
    int i;
    //mostrarADL(adl,validos);
    //system("pause");

    /**
        IMPLEMENTAR PARA EL PROFESIONAL DE LABORATORIO:
        printf("1. Registrar resultados de análisis")
        printf("2. Consultar muestras pendientes")
        SOLO DOS CASOS (POR AHORA)
    **/
    switch(op){
        case 1:
            system("cls");
            ConsultaUserADL(adl,validos,idActualUs);///buscar en adl
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            mostrarPlaylist(idActualUs);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            do{
                mostrarPosorderEnColumna(arbol);
                for(i=0;i<50;i++){
                    printf("%c",219);
                }
                printf("\n");
                printf("QUE CANCION DESEA AGREGAR A SU PLAYLIST?(ID): ");
                fflush(stdin);
                scanf("%d",&idCanPlaylist);
                cargarArchivoPlaylist(idActualUs,idCanPlaylist);
                printf("Desea seguir cargando?: S/N\n");
                fflush(stdin);
                scanf("%c",&control);
            }while(control=='s');
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            printf("\t\t\nLAS CANCIONES RECOMENDADAS POR EL PROGRAMA SON:\n\n");
            cancionesRecomendadas();
            system("pause");
            system("cls");
            break;
        case 5:
            menuPrincipalPrint(adl,validos);
            break;
        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////
///SWICH ORDENACION POR NOMBRE O GENERO(SIRVE PARA ADMINISTRADOR>SUBMENUCANCIONES>LISTADOS)
void eleccionGenONombCancion(int op){
int dimension=55;
stCancion a[dimension];
int validos=passTOarchivoCanciones(a,dimension,validos);
    switch(op){
        case 1:
            ordenarGenero(a,validos);
            mostrarArregloCanciones(a,validos);
            system("pause");
            system("cls");
            break;
        case 2:
            ordenarTitulo(a,validos);
            mostrarArregloCanciones(a,validos);
            system("pause");
            system("cls");
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////
///SWICH Modificacion:
void modificacionCancion(int op){
    char ModificarGenerico[30];
    char modificarComentarioGenerico[80];
    int generico=0;
    int idCancionesGenerico=0;
    if(op!=9){
        mostrarCanciones();
        printf("Ingrese el id de la cancion que desea modificar: \n");
        fflush(stdin);
        scanf("%d",&idCancionesGenerico);
    }
    /**
        • DNI (int)
        • Apellido y nombre (string[40])
        • Usuario (string[20)
        • Contraseña (string[20])
        • Perfil (string[20]) ¿Deberia poder cambiarse?
    **/
    switch(op){
        case 1:
            system("cls");
                printf("Ingrese el titulo nuevo: \n");
                fflush(stdin);
                gets(ModificarGenerico);
            modificarTituloCancion(ModificarGenerico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
                printf("Ingrese el nuevo nombre del artista: \n");
                fflush(stdin);
                gets(ModificarGenerico);
            modificarArtistaCancion(ModificarGenerico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
                printf("Ingresar la nueva duracion: ");
                fflush(stdin);
                scanf("%d",&generico);
            modificarDuracionCancion(generico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
                printf("Ingrese el nuevo nombre del album: \n");
                fflush(stdin);
                gets(ModificarGenerico);
            modificarAlbumCancion(ModificarGenerico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
                printf("Ingrese el nuevo año: \n");
                fflush(stdin);
                scanf("%d",&generico,idCancionesGenerico);
            modificarAnioCancion(generico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 6:
            system("cls");
                printf("Ingrese el nuevo genero: \n");
                fflush(stdin);
                gets(ModificarGenerico);
            modificarGeneroCancion(ModificarGenerico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 7:
            system("cls");
                printf("Ingrese el nuevo comentario: \n");
                fflush(stdin);
                gets(modificarComentarioGenerico);
            modificarComentarioCancion(modificarComentarioGenerico,idCancionesGenerico);
            system("pause");
            system("cls");
            break;
        case 8:
            system("cls");
                printf("Ingrese el nombre de la cancion a recuperar: \n");
                fflush(stdin);
                gets(ModificarGenerico);
            recuperarCancion(ModificarGenerico);
            system("pause");
            system("cls");
            break;
        case 9:
            system("cls");
            submenuAdminCancionPrintf();
            break;

        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;

    }
}

void modificacionUsuario(int op,stCeldaUsuarios adl[],int validos,int userModi){
    char UserGenerico[30];
    int idGenerico=userModi;
    int Generico=0;
    char genero;



    switch(op){
        case 1:
            system("cls");
                printf("Ingrese el nuevo nombre: \n");
                fflush(stdin);
                gets(UserGenerico);
            modificarNombreADL(adl,validos,UserGenerico,idGenerico);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
                printf("Ingrese la nueva contraseña: \n");
                fflush(stdin);
                gets(UserGenerico);
            modificarPasswordfADL(adl,validos,UserGenerico,idGenerico);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
                printf("Ingrese el nuevo anio de Nacimiento: \n");
                fflush(stdin);
                scanf("%d",&Generico);
            modificarAnioNADL(adl,validos,Generico,idGenerico);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
                printf("Ingrese el nuevo genero: \n");
                fflush(stdin);
                scanf("%c",&genero);
            modificarGeneroADL(adl,validos,genero,idGenerico);
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
                printf("Ingrese el nuevo pais: \n");
                fflush(stdin);
                gets(UserGenerico);
            ModificarPaisADL(adl,validos,UserGenerico,idGenerico);
            system("pause");
            system("cls");
            break;
        case 6:
            system("cls");
            elimininarUserADL(adl,validos,idGenerico);
            system("pause");
            system("cls");
            break;
        case 7:
            system("cls");
            recuperarUserADL(adl,validos,idGenerico);
            system("pause");
            system("cls");
            break;
        case 8:
            system("cls");
            submenuAdminUsuarioPrintf(adl,validos);
            break;

        default:
            system("cls");
            printf("Ingreso una opcion invalida, reintente nuevamente\n");
            system("pause");
            system("cls");
            break;
}
}
////////////////////////////////////////////////////////////////////////////////////////
///PRINTFS DE TODOS:
////////////////////////////////////////////////////////////////////////////////////////
///PRINTF MENU PRINCIPAL
void cabeza(char a[]){
    gotoxy(1,1);
    imprimirCabecera(a);
}

void imprimirCabecera(char cabecera[]){
    printf("\t\t%s     \n",cabecera);
    printf("%c", 219);
    for(int i=0;i<=70;i++){
        printf("%c",220);
    }
    printf("%c",219);
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
    gotoxy(56,15);

    char date[160];
    fGetNow(date);
    char dia[10];
    fGetDayLarge(date,dia);
    int hora=fGetHour(date);
    int minuto=fGetMinute(date);
    printf("%s %d:%d",dia,hora,minuto);

}

void RectanguloChico(){
    system("color F4");
    int lado=8;
    int base=40;
    int i=0;
    while(i<base){
        printf("%c",220);
        i++;
    }
    i=0;
    while(i<lado){
        printf("\n%c\t\t\t\t\t\t%c",219,219);
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
void menuPrincipalPrint(){

    int i=cantUsers();
    stCeldaUsuarios adl[i];
    int validos=0;
    validos=archivo2adl(adl,validos,i);
    //mostrarADL(a,validos);
    //system("pause");


    int opcion;
    system("cls");
    system("color F4");
    Rectangulo();
    cabeza("Hospital - Sistema de Gestion");
    gotoxy(15,4);
    printf("Elija su perfil");
    gotoxy(15,5);
    printf("1. Administrador");
    gotoxy(15,6);
    printf("2. Profesional de Laboratorio");
    gotoxy(15,7);
    printf("3. Administrativo");
    gotoxy(15,8);
    printf("4. Salir");
    gotoxy(15,9);

    fflush(stdin);
    scanf("%i", &opcion);
    system("cls");
    switchMenuPrincipal(opcion,adl,validos);
    system("cls");

    system("cls");
    printf("Gracias por utilizar nuestro sistema");
    pasarDeAdlToArchivo(adl,validos);
}
////////////////////////////////////////////////////////////////////////////////////////
///PRINTF INGRESO PESTAÑA USUARIO
void menuIngresoUserPrintf(stCeldaUsuarios adl[],int validos){
    int opcion;

   // do{
        system("cls");
        system("color F5");
        Rectangulo();
        cabeza("PESTANIA PROFESIONAL DE LAB.");
        gotoxy(15,4);
        printf("(1)LOGIN");
        gotoxy(15,5);
        printf("(2)SIGN IN");
        gotoxy(15,6);
        printf("(3)Volver");
        gotoxy(15,7);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switchIngresoDivision(opcion,adl,validos);
    //}while(control == 's');
    system("cls");
}
////////////////////////////////////////////////////////////////////////////////////////
///PRINTF MENU PRINCIPAL ADMIN
void menuPrincipalAdmiPrint(int log,stCeldaUsuarios adl[],int validos){
    int opcion=0;
    char nombre[30];
    char contrasenia[30];
    int contraseniaAdmin;


    system("color F5");


    Rectangulo();
    if(log==0){
    cabeza("PESTANIA ADMINISTRADOR");

    gotoxy(15,4);
    printf("USUARIO:");
    gotoxy(15,6);
    printf("CONTRASENIA:");
        gotoxy(15,8);
    printf("CONTRASENIA ADMIN:");
    gotoxy(22,4);
    fflush(stdin);
    gets(nombre);
    gotoxy(27,6);
    fflush(stdin);
    gets(contrasenia);
    gotoxy(33,8);
    fflush(stdin);
    scanf("%d",&contraseniaAdmin);

    log=logeoAdmin(nombre,contrasenia,contraseniaAdmin);
    }
    if(log==1){
        system("cls");
        Rectangulo();
        cabeza("MENU ADMINISTRADOR");
        gotoxy(15,4);
        printf("A Que Submenu Desea Acceder?:\n");
        gotoxy(15,6);
        printf("1. Gestionar pacientes\n");
        gotoxy(15,7);
        printf("2. Gestionar personal\n");
        gotoxy(15,8);
        printf("3. Generar informes");
        gotoxy(15,9);
        printf("4. Volver");
        gotoxy(15,10);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switchMenuAdmin(opcion,adl,validos);
        system("cls");
    system("cls");
    }else{
    system("cls");
    Rectangulo();
    gotoxy(1,1);
    printf("EL ADMIN NO EXISTE\n");
    gotoxy(1,2);
    system("pause");
    system("cls");
    gotoxy(0,0);

    menuPrincipalAdmiPrint(log,adl,validos);

}
    }


///PRINTF ADMIN SUBMENU USUARIO:
void submenuAdminUsuarioPrintf(stCeldaUsuarios adl[],int validos){

    char control;
    int opcion;
    do{
        system("cls");
        Rectangulo();
        cabeza("SUBMENU ADMINISTRACION PACIENTES");
        gotoxy(15,4);
        printf("Que funcion desea ejecutar:\n");
        gotoxy(15,6);
        printf("(1)ALTA\n");
        gotoxy(15,7);
        printf("(2)BAJA\n");
        gotoxy(15,8);
        printf("(3)MODIFICACION\n");
        gotoxy(15,9);
        printf("(4)CONSULTA\n");
        gotoxy(15,10);
        printf("(5)LISTADO\n");
        gotoxy(15,11);
        printf("(6)Volver\n");
        gotoxy(15,12);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switchAdminSubUsuario(opcion,adl,validos);
        //switchAdminSubPaciente(opcion,adl,validos);
        system("cls");
        printf("Desea ejecutar otra funcion de administracion de usuario?: (s/n)");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}
///PRINTF ADMIN SUBMENU CANCION:

void submenuAdminCancionPrintf(){

    char control;
    int opcion;
    do{
        system("cls");
        Rectangulo();
        cabeza("SUBMENU ADMINISTRACION PERSONAL");
        gotoxy(15,4);
        printf("Que funcion desea ejecutar:\n");
        gotoxy(15,6);
        printf("(1)ALTA\n");
        gotoxy(15,7);
        printf("(2)BAJA\n");
        gotoxy(15,8);
        printf("(3)MODIFICACION\n");
        gotoxy(15,9);
        printf("(4)CONSULTA\n");
        gotoxy(15,10);
        printf("(5)LISTADO\n");
        gotoxy(15,11);
        printf("(6)Volver\n");
        gotoxy(15,12);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switchAdminSubCancion(opcion);
        //switchAdminSubPersonal(opcion);

        system("cls");
        printf("Desea ejecutar otra funcion de administracion cancion?:(s/n) ");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}


///PRINTF MENU PRINCIPAL USUARIO:
void menuPrincipalUsuarioPrint(stCeldaUsuarios adl[],int validos){

    char control='s';
    int opcion=0;
    char nombre[30];
    char contrasenia[30];
        Rectangulo();
        cabeza("INICIO SESION");
        gotoxy(15,4);
        printf("NOMBRE:");
        gotoxy(15,6);
        printf("CONTRASENIA:");
        gotoxy(22,4);
        fflush(stdin);
        gets(nombre);
        gotoxy(27,6);
        fflush(stdin);
        gets(contrasenia);
    int Log=logeoUser(nombre,contrasenia);
    if(Log==1){
    do{
        system("cls");
        Rectangulo();
        cabeza("MENU USUARIO");
        gotoxy(15,4);
        printf("Que funcion desea ejecutar?:");
        gotoxy(15,6);
        printf("1. Registrar resultados de análisis");
        gotoxy(15,7);
        printf("2. Consultar muestras pendientes");
        gotoxy(15,8);
        printf("3. Volver\n");
        gotoxy(15, 9);

        fflush(stdin);
        scanf("%d", &opcion);
        system("cls");
        switchMenuUsuario(opcion,nombre,adl,validos);
        system("cls");
        printf("Desea ejecutar otra funcion de usuario? (s/n) ");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}
else{
    printf("EL USUARIO NO EXISTE\n");
}
}
////////////////////////////////////////////////////////////////////////////////////////
///PRINT FUNCION ORDENAR POR NOMBRE O GENERO
void OrdenarPorNoGPrintf(){

    char control;
    int opcion;
    do{
        system("cls");
        Rectangulo();
        cabeza("OPCIONES DE MUESTRA");
        gotoxy(8,4);
        printf("Como desea ordenar?:\n");
        gotoxy(8,6);
        printf("(1)Por Genero\n");
        gotoxy(8,7);
        printf("(2)Por Nombre\n");
        fflush(stdin);
        gotoxy(8,8);
        scanf("%i", &opcion);
        system("cls");
        eleccionGenONombCancion(opcion);

        system("cls");
        printf("Desea ordenar de otra forma? (s/n)");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}

////////////////////////////////////////////////////////////////////////////////////////
///PRINTF MODIFICACIONES:
void menuModificacionCancionPrintf(){

    char control;
    int opcion;
    int validacion=obtenerID();
    do{
        /**
        • DNI (int)
        • Apellido y nombre (string[40])
        • Usuario (string[20)
        • Contraseña (string[20])
        • Perfil (string[20]) ¿Deberia poder cambiarse?
        **/
        if(validacionCancionXId(validacion)==1){
        system("cls");
        Rectangulo();
        cabeza("MENU MODIFICACION CANCION");
        gotoxy(15,4);
        printf("Que desea Modificar?:\n");
        gotoxy(15,6);
        printf("(1)TITULO\n");
        gotoxy(15,7);
        printf("(2)ARTISTA\n");
        gotoxy(15,8);
        printf("(3)DURACION\n");
        gotoxy(15,9);
        printf("(4)ALBUM\n");
        gotoxy(15,10);
        printf("(5)ANIO\n");
        gotoxy(15,11);
        printf("(6)GENERO\n");
        gotoxy(15,12);
        printf("(7)COMENTARIO\n");
        gotoxy(15,13);
        printf("(8)RECUPERAR\n");
        gotoxy(15,14);
        printf("(9)VOLVER\n");
        gotoxy(15,15);
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        modificacionCancion(opcion);
        }
        system("cls");
        printf("Desea ejecutar otra modificacion? (s/n)");
        printf("%c\n",control=getch());
    }while(control == 's');
    system("cls");
}

void menuModificacionUsuarioPrintf(stCeldaUsuarios adl[],int validos){

    char control;
    int opcion=0;
    int validacion=obtenerID();
    do{
        if(ValidacionUsuarioXIdADL(validacion,adl,validos)==1){
        system("cls");
        Rectangulo();
        gotoxy(15,4);
        cabeza("MENU MODIFICACION USUARIO");
        gotoxy(15,6);
        printf("Que desea Modificar?:");
        gotoxy(15,7);
        printf("(1)NOMBRE");
        gotoxy(15,8);
        printf("(2)PASSWORD");
        gotoxy(15,9);
        printf("(3)ANIO NACIMIENTO");
        gotoxy(15,10);
        printf("(4)GENERO");
        gotoxy(15,11);
        printf("(5)PAIS");
        gotoxy(15,12);
        printf("(6)ELIMINAR");
        gotoxy(15,13);
        printf("(7)RECUPERAR");
        gotoxy(15,14);
        printf("(8)VOLVER");
        gotoxy(15,15);

        fflush(stdin);
        scanf("%d", &opcion);
        system("cls");
        modificacionUsuario(opcion,adl,validos,validacion);
        }

        system("cls");
        printf("Desea ejecutar otra funcion de modificacion de usuario? (s/n)");
        printf("%c\n", control = getch());

    }while(control == 's');
    system("cls");
}

int obtenerID(){
    int IDGen=0;
    printf("Ingrese el ID de Cancion/Usuario que desee modificar: ");
    fflush(stdin);
    scanf("%d",&IDGen);
return IDGen;
}
const char* daysLarge[]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};

int fGetDayOfWeek(char date[]){
    char day[2];
    int dayNumber=0;
    int i;
    if(strlen(date)>0){
        for(i=11;i<12;i++){
            day[i-11]=date[i];
        }
        day[i-11]='\0';
        dayNumber=atoi(day);
    }
    return dayNumber;
}

void fStrStr(char o[], char d[], int desde, int cant){
    int i;
    if(strlen(o)>=(desde+cant)){
        for(i=desde;i<(desde+cant)-1;i++){
            d[i-desde]=o[i];
        }
       d[i-desde+1]='\0';
    }
}
void fGetDayLarge(char date[],char day[]){
    if(strlen(date)>0){
        strcpy(day,daysLarge[fGetDayOfWeek(date)]);
    }
}

int fGetHour(char date[]){
    char hour[3];
    int hourNumber=0;
    int i;
    if(strlen(date)>0){
        for(i=13;i<15;i++){
            hour[i-13]=date[i];
        }
        hour[i-13]='\0';
        hourNumber=atoi(hour);
    }
    return hourNumber;
}

int fGetMinute(char date[]){
    char minute[3];
    int minuteNumber=0;
    int i;
    if(strlen(date)>0){
        for(i=16;i<18;i++){
            minute[i-16]=date[i];
        }
        minute[i-16]='\0';
        minuteNumber=atoi(minute);
    }
    return minuteNumber;
}

void fGetNow(char date[]){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(date,128,"%Y-%m-%d-%w %H:%M:%S",tlocal);
}

