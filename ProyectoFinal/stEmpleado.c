#include "stEmpleado.h"


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
stEmpleado traerEmpleadoXDNI(int dni){
    FILE * pArchiEmpleados = fopen(arEmpleados, "rb");
    stEmpleado e;
    stEmpleado eaux;
    int encontrado = 0;
    if (pArchiEmpleados != NULL){
        while((fread(&e, sizeof(stEmpleado),1,pArchiEmpleados) > 0) && encontrado == 0){
            if (e.dni == dni){
                eaux = e;
                encontrado = 1;
            }
        }
        fclose(pArchiEmpleados);
    }
    return eaux;
}
void mostrarEmpleado(stEmpleado e){
    printf("\n================================================");
    printf("\nApellido y nombre:..%s", e.apellidoYNombre);
    printf("\nDNI:................%d", e.dni);
    printf("\nUsuario:............%s", e.usuario);
    printf("\nContrasenia:........%s", e.contrasenia);
    printf("\nPerfil:.............%s", e.perfil);
    printf("\nEliminado:..........%d", e.eliminado);
    printf("\n================================================");
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
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    strcpy(e.usuario,usuarioNuevo);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
///ANTES DE LLAMAR A ESTA FUNCION VALIDAR SI YA EXISTE EL DNI EN EL ARCHIVO!!!!
void modificarDNIEmpleadoXUsuario(int dniNuevo,int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    e.dni = dniNuevo;
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
void modificarNombreEmpleadoXDNI(char nombreNuevo[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    strcpy(e.apellidoYNombre,nombreNuevo);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
void modificarContraseniaEmpleadoXDNI(char contrasenia[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    strcpy(e.contrasenia,contrasenia);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
void modificarPerfilEmpleadoXDNI(char perfil[],int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    strcpy(e.perfil,perfil);
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
void modificarEstadoEmpleadoXDNI(int estado,int dni){
    stEmpleado e;
    int modificado = 0;
    FILE*pArchiEmpleado = fopen(arEmpleados,"r+b");
    if(pArchiEmpleado != NULL){
        while(modificado == 0 && fread(&e,sizeof(stEmpleado),1,pArchiEmpleado) > 0){
                if(e.dni == dni){
                    fseek(pArchiEmpleado,-((long)sizeof(stEmpleado)),SEEK_CUR);
                    e.eliminado = estado;
                    fwrite(&e,sizeof(stEmpleado),1,pArchiEmpleado);
                    modificado = 1;
        }
    }
    fclose(pArchiEmpleado);
    }
}
int pasarArchivoAArregloEmpleados(stEmpleado e[],int dimension,int validos)
{
    int i=0;
    stEmpleado empleadoAux;

    FILE*archiEmpleados=fopen(arEmpleados,"rb");
    if(archiEmpleados!=NULL){
        while(fread(&empleadoAux,sizeof(stEmpleado),1,archiEmpleados)>0&&i<dimension){
            e[i]=empleadoAux;
            i++;
        }
        fclose(archiEmpleados);
    }
    return i;
}

///LOGUEO
int inicioDeSesion(char usuario[], char contrasenia[], char tipoMenu[]){
    stEmpleado empleado;
    int encontrado = 0;
    FILE * pArchiEmpleado = fopen(arEmpleados,"rb");

    if (pArchiEmpleado) {

        while(encontrado == 0 && (fread(&empleado, sizeof(stEmpleado), 1, pArchiEmpleado))>0){
            if(strcmp(empleado.usuario, usuario)==0 && strcmp(empleado.contrasenia, contrasenia)==0 && strcmp(empleado.perfil, tipoMenu)==0 && empleado.eliminado==0){
                encontrado = 1;
            }
        }

        fclose(pArchiEmpleado);
    }

    return encontrado;
}

// Ordenar el arreglo
int compararPorApellidoYNombre(const void *a, const void *b) {
    const stEmpleado *empleadoA = (const stEmpleado*)a;
    const stEmpleado *empleadoB = (const stEmpleado*)b;

    return strcmp(empleadoA->apellidoYNombre, empleadoB->apellidoYNombre);
}

void ordenarPorApellidoYNombre(stEmpleado arreglo[], int numEmpleados) {
    qsort(arreglo, numEmpleados, sizeof(stEmpleado), compararPorApellidoYNombre);
}
