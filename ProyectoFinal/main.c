#include "stIngreso.h"
#include "stEmpleado.h"
#include "stPractica.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"
#include "menu.h"
#include <windows.h>

HANDLE wHnd;

int main()
{
    ///Inicializamos el arbol a cargar
    nodoPaciente * arbolPacientes = inicArbolPacientes();

    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 72, 16};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    arbolPacientes = archivoToArbolPacientes(arbolPacientes);
    menuPrincipal(arbolPacientes);

//    submenuManejoEmpleados();
//
//    probando la parte de pacientes:
//    menuProvisorioGestionarPacientes();
//    probando la parte de practicas:
//    menuProvisorioGestionarPracticas();

    ///Pruebo generar un archivo de ingresos
//    generarArchivoBinIngresos(ARCHIVO_INGRESOS);
//    nodoIngreso* ingresos = crearListaIngresos(ARCHIVO_INGRESOS);
//    mostrarIngreso(ingresos);

    return 0;
}
