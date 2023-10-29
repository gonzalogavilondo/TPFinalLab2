#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "time.h"
#include "Canciones.h"
#include "Usuarios.h"
#include "Menu.h"
#include "ADL(Usuarios).h"

void passar();


int main()
{

    menuPrincipalPrint();
    //CargarArchiUsuario();
/*
    int i=cantUsers();
    stCeldaUsuarios a[i];
    int validos=0;

    validos=archivo2adl(a,validos,i);
    validos=cargarADLmanual(a,validos,i+1);
    printf("%d",validos);
    mostrarADL(a,validos);
    pasarDeAdlToArchivo(a,validos);

    mostrarArchivoPlaylist();
*/
    //mostrarNodo(a[2].listaDeCanciones);
    //mostrarUsers();
    return 0;
}
