#include "stIngreso.h"
#include "stEmpleado.h"
#include "stPractica.h"
#include "stPracticaXIngreso.h"
#include "stPaciente.h"
#include "menu.h"
#include <windows.h>

HANDLE wHnd;
nodoPaciente * abrirArbolInicioPrograma(nodoPaciente * arbol);
void salvarArbolFinPrograma(nodoPaciente * arbol);

int main()
{
    ///Inicializamos el arbol a cargar
    nodoPaciente * arbolPacientes = inicArbolPacientes();

    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 72, 16};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    //arbolPacientes = archivoToArbolPacientes(arbolPacientes);
    arbolPacientes = abrirArbolInicioPrograma(arbolPacientes);

    menuPrincipal(arbolPacientes);

    salvarArbolFinPrograma(arbolPacientes);

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

nodoPaciente * abrirArbolInicioPrograma(nodoPaciente * arbol)
{

    FILE * pArchiPacientes = fopen(ARCHIVO_PACIENTES, "rb");

    if (pArchiPacientes)
    {

        stPaciente paciente;

        while (fread(&paciente, sizeof(stPaciente), 1, pArchiPacientes) > 0)
        {
            arbol = insertarPaciente(arbol, paciente);

            FILE * pArchiIngreso = fopen(ARCHIVO_INGRESOS, "rb");

            stIngreso ingreso;

            while(fread(&ingreso,sizeof(stIngreso), 1, pArchiIngreso) > 0)
            {
                if(paciente.apellidoNombre == ingreso.dniPaciente)
                {
                    arbol->listaIngresos = agregarNodoIngreso(arbol->listaIngresos,ingreso);

                    FILE * pArchiPracticaXIngreso = fopen(ARCHIVO_PRACTICAXINGRESOS, "rb");

                    stPracticaXIngreso practicaXIngreso;

                    while(fread(&practicaXIngreso, sizeof(stPracticaXIngreso),1,pArchiPracticaXIngreso) > 0)
                    {
                        if(arbol->listaIngresos->listaPracticasXIngreso->practicaXIngreso.nroPractica == practicaXIngreso.nroPractica)
                        {
                            arbol->listaIngresos->listaPracticasXIngreso = agregarNodoPracticaXIngreso(arbol->listaIngresos->listaPracticasXIngreso, practicaXIngreso);
                        }

                    }
                    fclose(pArchiPracticaXIngreso);
                }
            }
            fclose(pArchiIngreso);
        }

        printf("\n Se cargaron los datos.");
        fclose(pArchiPacientes);
    } else {
        printf("\n Hubo un problema al intentar abrir el archivo.");
    }

    return arbol;
}

void salvarArbolFinPrograma(nodoPaciente * arbol)
{
    stPaciente * arregloPacientes = arbolPacientesToArreglo(arbol);
    int validosArre = cantidadNodosArbolPacientes(arbol);
    if (arbol)
    {
        FILE * pArchiPacientes = fopen(ARCHIVO_PACIENTES, "wb");
        if(pArchiPacientes != NULL)
        {
            for (int i = 0; i<validosArre; i++)
            {
                fwrite(&arregloPacientes[i],sizeof(stPaciente),1,pArchiPacientes);

                nodoIngreso * segIngresos = arbol->listaIngresos;

                stIngreso ingreso;

                FILE * pArchiIngresos = fopen(ARCHIVO_INGRESOS, "wb");

                if(pArchiIngresos != NULL)
                {
                    while(segIngresos != NULL)
                    {
                        if(segIngresos->ingreso.dniPaciente == arregloPacientes[i].dni){
                        fwrite(&segIngresos->ingreso,sizeof(stIngreso),1,pArchiIngresos);

                        nodoPracticaXIngreso * segPracticasXIngresos = arbol->listaIngresos->listaPracticasXIngreso;

                        stPracticaXIngreso practicasXIngreso;

                        FILE * pArchiPracitaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "wb");

                        if(pArchiPracitaXIngresos != NULL)
                        {
                            while(segPracticasXIngresos != NULL)
                            {
                                if(segPracticasXIngresos->practicaXIngreso.nroIngreso == segIngresos->ingreso.numeroIngreso){
                                    fwrite(&segPracticasXIngresos,sizeof(stPracticaXIngreso),1,pArchiPracitaXIngresos);
                                }
                            }
                        }
                        fclose(pArchiPracitaXIngresos);
                        }
                    }
                }
                fclose(pArchiIngresos);
            }
        }
        fclose(pArchiPacientes);
    }
}
