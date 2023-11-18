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


    stEmpleado *lista;

    int validos = pasarArchivoAListaEmpleados(lista, 100, 0);


    //ordenarEmpleadoPorApellidoYNombre(lista,validos);

    for (int i = 0; i < validos; i++){
        mostrarEmpleado(lista[i]);

    }
    //submenuManejoEmpleados();
    //probando la parte de pacientes
    //menuProvisorioGestionarPacientes();

return 0;
}
