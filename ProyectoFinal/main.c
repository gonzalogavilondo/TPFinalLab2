#include "stIngreso.h"
#include "stEmpleado.h"
#include "stPractica.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"
#include "persistenciaDatos.h"
#include "menu.h"
#include <windows.h>

HANDLE wHnd;


int main()
{
    ///Inicializamos el arbol a cargar
    nodoPaciente * arbolPacientes = inicArbolPacientes();

    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 120, 25};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    ///Levantamos todos los datos en el arbol
    arbolPacientes = abrirArbolInicioPrograma(arbolPacientes);

    ///Ejecutamos el programa
    menuPrincipal(arbolPacientes);

    ///Persistencia de datos de la ejecucion del programa
    salvarArbolFinPrograma(arbolPacientes);

    return 0;
}
