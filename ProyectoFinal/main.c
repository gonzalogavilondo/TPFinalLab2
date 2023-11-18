#include "stIngreso.h"
#include "stEmpleado.h"
#include "stPractica.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"
#include "menu.h"

int main()
{
//    submenuManejoEmpleados();
//
//    probando la parte de pacientes:
//    menuProvisorioGestionarPacientes();
//    probando la parte de practicas:
//    menuProvisorioGestionarPracticas();

    ///Pruebo generar un archivo de ingresos
    generarArchivoBinIngresos("ingresos.dat");
    nodoIngreso* ingresos = crearListaIngresos("ingresos.dat");
    mostrarIngreso(ingresos);


    return 0;
}
