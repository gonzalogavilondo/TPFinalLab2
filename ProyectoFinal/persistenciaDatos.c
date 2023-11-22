#include "persistenciaDatos.h"

nodoPaciente* abrirArbolInicioPrograma(nodoPaciente* arbol) {
    FILE* pArchiPacientes = fopen(ARCHIVO_PACIENTES, "rb");

    if (pArchiPacientes) {
        stPaciente paciente;

        while (fread(&paciente, sizeof(stPaciente), 1, pArchiPacientes) > 0) {
            arbol = insertarPaciente(arbol, paciente);

            FILE* pArchiIngreso = fopen(ARCHIVO_INGRESOS, "rb");

            if (pArchiIngreso) {
                stIngreso ingreso;

                while (fread(&ingreso, sizeof(stIngreso), 1, pArchiIngreso) > 0) {
                    if (paciente.dni == ingreso.dniPaciente) {
                        nodoPaciente* pacienteAux = buscaPaciente(arbol, paciente.dni);
                        pacienteAux->listaIngresos = agregarNodoIngreso(pacienteAux->listaIngresos, ingreso);

                        FILE* pArchiPracticaXIngreso = fopen(ARCHIVO_PRACTICAXINGRESOS, "rb");

                        if (pArchiPracticaXIngreso) {
                            nodoIngreso* nodoIngresoBuscado = buscaIngreso(pacienteAux->listaIngresos, ingreso.numeroIngreso);

                            stPracticaXIngreso practicaXIngreso;
                            while (fread(&practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngreso) > 0) {
                                if (nodoIngresoBuscado && nodoIngresoBuscado->ingreso.numeroIngreso == practicaXIngreso.nroIngreso) {
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
void salvarArbolFinPrograma(nodoPaciente *arbol) {
    if (arbol == NULL) {
        return; // Verificar si el árbol está vacío
    }

    FILE *pArchiPacientes = fopen(ARCHIVO_PACIENTES, "wb");
    if (pArchiPacientes == NULL) {
        return; // Manejar el error si no se puede abrir el archivo
    }

    stPaciente *arregloPacientes = arbolPacientesToArreglo(arbol);
    int validosArre = cantidadNodosArbolPacientes(arbol);

    for (int i = 0; i < validosArre; i++) {
        fwrite(&arregloPacientes[i], sizeof(stPaciente), 1, pArchiPacientes);

        nodoPaciente *paciente = buscaPaciente(arbol, arregloPacientes[i].dni);

        if (paciente && paciente->listaIngresos) {
            nodoIngreso *segIngresos = paciente->listaIngresos;

            FILE *pArchiIngresos = fopen(ARCHIVO_INGRESOS, "ab"); // Cambio a modo append

            if (pArchiIngresos != NULL) {
                while (segIngresos != NULL) {
                    fwrite(&segIngresos->ingreso, sizeof(stIngreso), 1, pArchiIngresos);

                    FILE *pArchiPracticaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "ab"); // Cambio a modo append

                    if (pArchiPracticaXIngresos != NULL) {
                        nodoPracticaXIngreso *segPracticaXIngreso = segIngresos->listaPracticasXIngreso;

                        while (segPracticaXIngreso != NULL) {
                            fwrite(&segPracticaXIngreso->practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngresos);
                            segPracticaXIngreso = segPracticaXIngreso->siguiente;
                        }

                        fclose(pArchiPracticaXIngresos); // Cerrar el archivo después de escribir
                    }

                    segIngresos = segIngresos->siguiente;
                }

                fclose(pArchiIngresos); // Cerrar el archivo después de escribir
            }
        }
    }

    fclose(pArchiPacientes); // Cerrar el archivo al finalizar
}
