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
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 72, 16};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    submenuManejoEmpleados();
//
//    probando la parte de pacientes:
//    menuProvisorioGestionarPacientes();
//    probando la parte de practicas:
//    menuProvisorioGestionarPracticas();

    ///Pruebo generar un archivo de ingresos
    //generarArchivoBinIngresos("ingresos.dat");
    //nodoIngreso* ingresos = crearListaIngresos("ingresos.dat");
    //mostrarIngreso(ingresos);


    return 0;
}
