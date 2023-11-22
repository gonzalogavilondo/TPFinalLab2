#include "persistenciaDatos.h"

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

            if (pArchiIngreso) {

                stIngreso ingreso;

                while(fread(&ingreso,sizeof(stIngreso), 1, pArchiIngreso) > 0){

                    if(paciente.dni == ingreso.dniPaciente){

                        nodoPaciente * pacienteAux = buscaPaciente(arbol, paciente.dni);
                        pacienteAux->listaIngresos = agregarNodoIngreso(pacienteAux->listaIngresos, ingreso);

                        FILE * pArchiPracticaXIngreso = fopen(ARCHIVO_PRACTICAXINGRESOS, "rb");

                        if (pArchiPracticaXIngreso) {

                            nodoIngreso * nodoIngresoBuscado = inicListaIngresos();
                            nodoIngresoBuscado = buscaIngreso(pacienteAux->listaIngresos , ingreso.numeroIngreso);


                            stPracticaXIngreso practicaXIngreso;

                            while(fread(&practicaXIngreso, sizeof(stPracticaXIngreso),1,pArchiPracticaXIngreso) > 0){

                                if(nodoIngresoBuscado->ingreso.numeroIngreso == practicaXIngreso.nroIngreso){

                                    nodoIngresoBuscado->listaPracticasXIngreso = agregarNodoPracticaXIngreso(nodoIngresoBuscado->listaPracticasXIngreso, practicaXIngreso);
                                }

                            }
                            fclose(pArchiPracticaXIngreso);

                        } else {

                            printf("\n Hubo un problema al intentar abrir el archivo de practicas por ingreso.");
                            textoPresioneCualquierTecla();

                        }
                    }
                }

                fclose(pArchiIngreso);

            } else {
                printf("\n Hubo un problema al intentar abrir el archivo de ingresos.");
                textoPresioneCualquierTecla();
            }
        }

        fclose(pArchiPacientes);
    } else {
        printf("\n Hubo un problema al intentar abrir el archivo de pacientes.");
        textoPresioneCualquierTecla();
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

            nodoPaciente * paciente;

            for (int i = 0; i<validosArre; i++)
            {

                fwrite(&arregloPacientes[i],sizeof(stPaciente),1,pArchiPacientes);

                paciente = buscaPaciente(arbol, arregloPacientes[i].dni);

                if (paciente->listaIngresos) {

                    nodoIngreso * segIngresos = paciente->listaIngresos;

                    //stIngreso ingreso;

                    FILE * pArchiIngresos = fopen(ARCHIVO_INGRESOS, "wb");

                    if(pArchiIngresos != NULL)
                    {
                        while(segIngresos != NULL)
                        {

                            fwrite(&segIngresos->ingreso,sizeof(stIngreso),1,pArchiIngresos);

                            FILE * pArchiPracitaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "wb");

                            if (pArchiPracitaXIngresos) {

                                nodoPracticaXIngreso * segPracticaXIngreso = segIngresos->listaPracticasXIngreso;

                                while (segPracticaXIngreso) {

                                    fwrite(&segPracticaXIngreso->practicaXIngreso,sizeof(stPracticaXIngreso),1,pArchiPracitaXIngresos);

                                    segPracticaXIngreso = segPracticaXIngreso->siguiente;
                                }

                                fclose(pArchiPracitaXIngresos);
                            }

                            segIngresos = segIngresos->siguiente;



//                            if(segIngresos->ingreso.dniPaciente == arregloPacientes[i].dni){
//                                fwrite(&segIngresos->ingreso,sizeof(stIngreso),1,pArchiIngresos);
//
//                                nodoPracticaXIngreso * segPracticasXIngresos = arbol->listaIngresos->listaPracticasXIngreso;
//
//                                stPracticaXIngreso practicasXIngreso;
//
//                                FILE * pArchiPracitaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "wb");
//
//                                if(pArchiPracitaXIngresos != NULL){
//                                    while(segPracticasXIngresos != NULL)
//                                    {
//                                        if(segPracticasXIngresos->practicaXIngreso.nroIngreso == segIngresos->ingreso.numeroIngreso){
//                                            fwrite(&segPracticasXIngresos,sizeof(stPracticaXIngreso),1,pArchiPracitaXIngresos);
//                                        }
//
//                                        segPracticasXIngresos = segPracticasXIngresos->siguiente;
//                                    }
//                                    fclose(pArchiPracitaXIngresos);
//                                }
//                            }
//
//                            segIngresos = segIngresos->siguiente;
                        }
                        fclose(pArchiIngresos);
                    }

                }

            }
            fclose(pArchiPacientes);
        }
    }
}
