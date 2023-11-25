#include "persistenciaDatos.h"

nodoPaciente* abrirArbolInicioPrograma(nodoPaciente* arbol) {
    ///Inicializamos el contador
    cantidadIngresosArchivo();

    FILE* pArchiPacientes = fopen(ARCHIVO_PACIENTES, "rb");


    if (pArchiPacientes) { // Si da false, hubo un problema al intentar abrir el archivo de pacientes, o el mismo no existia.

        stPaciente paciente;

        while (fread(&paciente, sizeof(stPaciente), 1, pArchiPacientes) > 0) {
            // Insertar paciente en el árbol
            arbol = insertarPaciente(arbol, paciente);

            FILE* pArchiIngreso = fopen(ARCHIVO_INGRESOS, "rb");

            if (pArchiIngreso) { // Si da false, hubo un problema al intentar abrir el archivo de ingresos, o el mismo no existia.

                stIngreso ingreso;

                while (fread(&ingreso, sizeof(stIngreso), 1, pArchiIngreso) > 0) {

                    if (paciente.dni == ingreso.dniPaciente) {
                        // Insertar ingreso en el paciente
                        nodoPaciente* pacienteAux = buscaPaciente(arbol, paciente.dni);
                        pacienteAux->listaIngresos = agregarNodoIngreso(pacienteAux->listaIngresos, ingreso);

                        FILE* pArchiPracticaXIngreso = fopen(ARCHIVO_PRACTICAXINGRESOS, "rb");

                        if (pArchiPracticaXIngreso) { // Si da false, hubo un problema al intentar abrir el archivo de practicas por ingreso, o el mismo no existia.

                            nodoIngreso * nodoIngresoBuscado = inicListaIngresos();
                            nodoIngresoBuscado = buscaIngreso(pacienteAux->listaIngresos, ingreso.numeroIngreso);

                            if (nodoIngresoBuscado) {

                                stPracticaXIngreso practicaXIngreso;

                                while (fread(&practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngreso) > 0) {
                                    if (nodoIngresoBuscado->ingreso.numeroIngreso == practicaXIngreso.nroIngreso) {
                                        // Insertar practicaXIngreso en la lista
                                        nodoIngresoBuscado->listaPracticasXIngreso = agregarNodoPracticaXIngreso(nodoIngresoBuscado->listaPracticasXIngreso, practicaXIngreso);
                                    }
                                }

                            }

                            fclose(pArchiPracticaXIngreso);
                        }

                    }

                }

                fclose(pArchiIngreso);
            }

        }

        fclose(pArchiPacientes);
    }

    return arbol;
}


void salvarArbolFinPrograma(nodoPaciente *arbol) {

    if (arbol) {

        FILE *pArchiPacientes = fopen(ARCHIVO_PACIENTES, "wb");

        if (pArchiPacientes) { // Si da false, hubo un problema al intentar abrir/crear el archivo de pacientes.

            stPaciente *arregloPacientes = arbolPacientesToArreglo(arbol);
            int validosArre = cantidadNodosArbolPacientes(arbol);
            nodoPaciente * paciente;

            for (int i = 0; i < validosArre; i++) {

                fwrite(&arregloPacientes[i], sizeof(stPaciente), 1, pArchiPacientes);

                paciente = inicArbolPacientes();
                paciente = buscaPaciente(arbol, arregloPacientes[i].dni);

                if (paciente && paciente->listaIngresos) {

                    FILE * pArchiIngresos = fopen(ARCHIVO_INGRESOS, "wb");

                    if (pArchiIngresos) { // Si da false, hubo un problema al intentar abrir/crear el archivo de ingresos.

                        nodoIngreso *segIngresos = paciente->listaIngresos;

                        while (segIngresos) {

                            fwrite(&segIngresos->ingreso,sizeof(stIngreso),1,pArchiIngresos);
                            FILE * pArchiPracitaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "wb");

                            if (pArchiPracitaXIngresos) { // Si da false, hubo un problema al intentar abrir/crear el archivo de practicasXIngreso.

                                nodoPracticaXIngreso *segPracticaXIngreso = segIngresos->listaPracticasXIngreso;

                                while (segPracticaXIngreso) {
                                    fwrite(&segPracticaXIngreso->practicaXIngreso,sizeof(stPracticaXIngreso),1,pArchiPracitaXIngresos);
                                    segPracticaXIngreso = segPracticaXIngreso->siguiente;
                                }

                                fclose(pArchiPracitaXIngresos);

                            } else {
                                printf("\n Hubo un problema al intentar abrir/crear el archivo de practicas por ingreso para guardar los datos.\n");
                                printf("\n Presione cualquier tecla para continuar...");
                                getch();
                            }

                            segIngresos = segIngresos->siguiente;
                        }

                        fclose(pArchiIngresos);

                    } else {
                        printf("\n Hubo un problema al intentar abrir/crear el archivo de ingresos para guardar los datos.\n");
                        printf("\n Presione cualquier tecla para continuar...");
                        getch();
                    }
                }
            }

        fclose(pArchiPacientes);

        } else {
            printf("\n Hubo un problema al intentar abrir/crear el archivo de pacientes para guardar los datos.\n");
            printf("\n Presione cualquier tecla para continuar...");
            getch();
        }

    }
}
