#include "Usuarios.h"

///ordenacion usuario
int passTOarchivoUsuario(stUser b[],int dimension,int validos){
    int i=0;
    stUser a;

    FILE*archiUsuario=fopen(arUser,"rb");
    if(archiUsuario!=NULL){
        while(fread(&a,sizeof(stUser),1,archiUsuario)>0&&i<dimension){
            b[i]=a;
            i++;
        }
        fclose(archiUsuario);
    }
    return i;
}


int posMenorNombre (stUser a[], int pos, int cant)
{

    int i = pos+1;
    int posMenor=pos;
    char menorNombre[40];
    strcpy(menorNombre,a[pos].nombreUsuario);

    while(i<cant){
        if(strcmpi(menorNombre,a[i].nombreUsuario)>0){
            strcpy(menorNombre,a[i].nombreUsuario);
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}

void ordenarNombre(stUser a[], int cant)
{
    int i=0;
    int menor;
    stUser aux;

    while(i<cant)
    {
        menor = posMenorNombre(a,i,cant);
        aux=a[menor];
        a[menor]=a[i];
        a[i]=aux;
        i++;
    }
}

///==========FUNCIONES USUARIO===========
///CARGAR USUARIO
void CargarArchiUsuario(){
    stUser a;
    int flag=0;
    int opcion=0;
    a.idUsuario=buscaUltimoIdUsuario();
    while(opcion!=27){
        system("cls");
        a.Ueliminado=0;
        a.idUsuario++;
        printf("<<<<<<CARGA USUARIO>>>>>>\n");
        while(flag==0){
            printf("\nIngrese el nombre del Usuario: ");
            fflush(stdin);
            gets(a.nombreUsuario);
                if(validacionUsuario(a.nombreUsuario)==1){
                    printf("El Usuario ya se encuentra en el sistema, intente nuevamente");
                }else{
                    flag=1;
                }
            }
            printf("\nIngrese su contrasenia: ");
            fflush(stdin);
            scanf("%s",a.password);
            printf("\nIngrese su anio de nacimiento: ");
            fflush(stdin);
            scanf("%i",&a.anioNacimiento);
            printf("\nCual es su genero(H/M): ");
            fflush(stdin);
            scanf("%c",&a.genero);
            printf("\nIngrese su pais de nacimiento: ");
            fflush(stdin);
            scanf("%s",a.pais);
            guardarUser(a);
            printf("\nESC para salir\n");
            fflush(stdin);
            opcion=getch();
            flag=0;
        }
}
///GUARDAR USUARIO
void guardarUser(stUser a){
    FILE*pArchUsuario = fopen(arUser,"ab");
    if(pArchUsuario!=NULL){
        fwrite(&a,sizeof(stUser),1,pArchUsuario);
        fclose(pArchUsuario);
    }
}
///BUSCAR ULTIMO ID
int buscaUltimoIdUsuario(){
    stUser a;
    int idusuario=-1;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        fseek(pArchUsuario,sizeof(stUser)*(-1),SEEK_END);
        if(fread(&a,sizeof(stUser),1,pArchUsuario)>0){
              idusuario=a.idUsuario;
              }
              fclose(pArchUsuario);
    }
    return idusuario;
}
///Validacion Usuario
int validacionUsuario(char nuevoUser[]){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario=fopen(arUser,"rb");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
            if((strcmp(a.nombreUsuario,nuevoUser))==0)
                flag=1;
        }
    }
    return flag;
}
///MOSTRAR USUARIO
void mostrarUsers(){
    stUser a;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        while(fread(&a,sizeof(stUser),1,pArchUsuario)>0){
            MuestraUnUserCualquiera(a);
    }
    fclose(pArchUsuario);
}
}
/*
///MUESTRA UN USUARIO
void  MuestraUnUser(stUser a){
    if(a.Ueliminado==0){
    printf("==========================================\n");
    printf("Id:.........%d\n",a.idUsuario);
    printf("Nombre:.....%s\n",a.nombreUsuario);
    printf("Password:...%s\n",a.password);
    printf("anio:.......%d\n",a.anioNacimiento);
    printf("genero:.....%c\n",a.genero);
    printf("pais:.......%s\n",a.pais);
    printf("Estado:.....%i\n",a.Ueliminado);
    printf("Validos P:..%i\n",a.validosPlaylist);
    printf("==========================================\n");
}
}

///MOSTRAR USERS
void mostrarUsers(){
    stUser a;
    FILE*pArchUser=fopen(arUser,"rb");
    if(pArchUser!=NULL){
        while(fread(&a,sizeof(stUser),1,pArchUser)>0){
            MuestraUnUser(a);
    }
    fclose(pArchUser);
}
}
*/
///MUESTRA UN USER
void  MuestraUnUser(stUser a){
    if(a.Ueliminado==0){
    printf("==========================================\n");
    printf("Id:.........%d\n",a.idUsuario);
    printf("Nombre:.....%s\n",a.nombreUsuario);
    printf("Password:...%s\n",a.password);
    printf("anio:.......%d\n",a.anioNacimiento);
    printf("genero:.....%c\n",a.genero);
    printf("pais:.......%s\n",a.pais);
    printf("Estado:.....%i\n",a.Ueliminado);
    printf("==========================================\n");
}
}
void  MuestraUnUserCualquiera(stUser a){
    printf("==========================================\n");
    printf("Id:.........%d\n",a.idUsuario);
    printf("Nombre:.....%s\n",a.nombreUsuario);
    printf("Password:...%s\n",a.password);
    printf("anio:.......%d\n",a.anioNacimiento);
    printf("genero:.....%c\n",a.genero);
    printf("pais:.......%s\n",a.pais);
    printf("Estado:.....%i\n",a.Ueliminado);
    printf("==========================================\n");
}
///MOSTRAR USUARIO ELIMINADO:
void mostrarUsersEliminado(){
    stUser a;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        while(fread(&a,sizeof(stUser),1,pArchUsuario)>0){
            MuestraUnUserEliminado(a);
    }
     fclose(pArchUsuario);
}
}
void  MuestraUnUserEliminado(stUser a){
    if (a.Ueliminado==1){
    printf("==========================================\n");
    printf("Id:.........%d\n",a.idUsuario);
    printf("Nombre:.....%s\n",a.nombreUsuario);
    printf("Password:...%s\n",a.password);
    printf("anio:.......%d\n",a.anioNacimiento);
    printf("genero:.....%c\n",a.genero);
    printf("pais:.......%s\n",a.pais);
    printf("Estado:.....%i\n",a.Ueliminado);
    printf("==========================================\n");
    }
}
///FUNCIONES USUARIO TIPEO:
void elimininarUser(char nUsuario[]){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0 && (fread(&a,sizeof(stUser),1,pArchiUsuario)>0)){
                if(strcmp(a.nombreUsuario,nUsuario)==0){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    a.Ueliminado=1;
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
                }
    }
    fclose(pArchiUsuario);
    }
     if(flag==0){
        system("cls");
        printf("[*ERROR*] \nEl usuario no existe!...\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
///MOSTRAR PLAYLIST
void mostrarPlaylist(int idUsuario){
stUser a;
stCancion b;
int flag=0;
int i=0;
    FILE*archiUsuario=fopen(arUser,"rb");
    FILE*archiCan=fopen(arCanciones,"rb");
    if(archiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,archiUsuario)>0){
            if(a.idUsuario==idUsuario){
                    if(archiCan!=NULL){
                        while(i<a.validosPlaylist&&fread(&b,sizeof(stCancion),1,archiCan)>0){
                               // printf("%d",a.validosPlaylist);
                                    ConsultaCancionxID(a.playlist[i]);
                                    //fseek(archiCan,sizeof(stCancion)*(-1),SEEK_CUR);
                                   // printf("%d",a.validosPlaylist);
                                    //muestraUnaCancion(b);
                                    i++;
                            }
                            flag=1;
                            fclose(archiCan);
                        }
                    }
            }
        }
            fclose(archiUsuario);
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MODIFICACIONES DE USUARIO

///NOMBRE
void modificarNombreUsuario(char nombreN[],int idIngresado){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(a.idUsuario==idIngresado){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    strcpy(a.nombreUsuario,nombreN);
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
    }
    }
        fclose(pArchiUsuario);
}
}

///CONTRASENIA
void modificarContraseniaUsuario(char passN[],int idIngresado){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(a.idUsuario==idIngresado){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    strcpy(a.password,passN);
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
    }
    }
    fclose(pArchiUsuario);

}
}
///ANIO DE NACIMIENTO
void ModifAnioNacimiento(int anioN,int idIngresado){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(a.idUsuario==idIngresado){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    a.anioNacimiento=anioN;
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
    }
    }
        fclose(pArchiUsuario);
}
}
///GENERO
void Modificargenero(char sexo,int idIngresado){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(a.idUsuario==idIngresado){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    a.genero=sexo;
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
    }
    }
    fclose(pArchiUsuario);
}
}
///PAIS
void ModificarPais(char paisN[],int idIngresado){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(a.idUsuario==idIngresado){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    strcpy(a.pais,paisN);
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
    }
    }
    fclose(pArchiUsuario);
}
}

///RECUPERAR USUARIO
void recuperarUser(char nUsuario[]){
    stUser a;
    int flag=0;
    FILE*pArchiUsuario = fopen(arUser,"r+b");
    if(pArchiUsuario!=NULL){
        printf("%s--",nUsuario);
        printf("%s\n",a.nombreUsuario);
        while(flag==0 && fread(&a,sizeof(stUser),1,pArchiUsuario)>0){
                if(strcmp(a.nombreUsuario,nUsuario)==0){
                    fseek(pArchiUsuario,sizeof(stUser)*(-1),SEEK_CUR);
                    a.Ueliminado=0;
                    fwrite(&a,sizeof(stUser),1,pArchiUsuario);
                    flag=1;
                }
    }
    fclose(pArchiUsuario);
    }
     if(flag==0){
        system("cls");
        printf("[*ERROR*] \nEl usuario ya existe!...\n");
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
///CONSULTA USER
void ConsultaUser(int id){
    stUser a;
    int flag=0;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchUsuario)>0){
           if(id==a.idUsuario){
                MuestraUnUser(a);
                flag=1;
        }
    }
    fclose(pArchUsuario);
    }
}
void ConsultaUserXName(char nombre[]){
    stUser a;
    int flag=0;
    FILE*pArchUsuarios=fopen(arUser,"rb");
    if(pArchUsuarios!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchUsuarios)>0){
           if(strcmp(nombre,a.nombreUsuario)==0){
                MuestraUnUser(a);
                flag=1;
        }
    }
    fclose(pArchUsuarios);
    }
}

int ValidacionUsuarioXId(int id){
    stUser a;
    int flag=0;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchUsuario)>0){
           if(id==a.idUsuario){
                flag=1;
        }
    }
    fclose(pArchUsuario);
    }
    return flag;
}

///ENCONTRAR ID USER
int encontrarIDUSERxNombre(char nombre[]){
    stUser a;
    int flag=0;
    int id=0;
    FILE*pArchUsuario=fopen(arUser,"rb");
    if(pArchUsuario!=NULL){
        while(flag==0&&fread(&a,sizeof(stUser),1,pArchUsuario)>0){
           if(strcmp(nombre,a.nombreUsuario)==0){

                id=a.idUsuario;
                flag=1;
        }
    }
    fclose(pArchUsuario);
    }
    printf("%d",id);
    return id;
}
int cantUsers(){
    FILE*pArchUser=fopen("User.dat","rb");
    int i=0;
    if(pArchUser){
        stUser u;
        while(fread(&u,sizeof(stUser),1,pArchUser)>0){
            i++;
    }
    }
return i;
}



