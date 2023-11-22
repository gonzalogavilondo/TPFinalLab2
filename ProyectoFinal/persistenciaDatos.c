#include "persistenciaDatos.h"

nodoPaciente* abrirArbolInicioPrograma(nodoPaciente* arbol) {
    FILE* pArchiPacientes = fopen(ARCHIVO_PACIENTES, "rb");

    if (!pArchiPacientes) {
        perror("Hubo un problema al intentar abrir el archivo de pacientes");
        return arbol;
    }

    stPaciente paciente;

    while (fread(&paciente, sizeof(stPaciente), 1, pArchiPacientes) > 0) {
        arbol = insertarPaciente(arbol, paciente);
        printf("Paciente insertado: DNI %d\n", paciente.dni);

        FILE* pArchiIngreso = fopen(ARCHIVO_INGRESOS, "rb");

        if (!pArchiIngreso) {
            perror("Hubo un problema al intentar abrir el archivo de ingresos");
            fclose(pArchiPacientes);
            return arbol;
        }

        stIngreso ingreso;

        while (fread(&ingreso, sizeof(stIngreso), 1, pArchiIngreso) > 0) {
            if (paciente.dni == ingreso.dniPaciente) {
                nodoPaciente* pacienteAux = buscaPaciente(arbol, paciente.dni);
                pacienteAux->listaIngresos = agregarNodoIngreso(pacienteAux->listaIngresos, ingreso);
                printf("Ingreso asociado a paciente: Nro. %d\n", ingreso.numeroIngreso);

                FILE* pArchiPracticaXIngreso = fopen(ARCHIVO_PRACTICAXINGRESOS, "rb");

                if (!pArchiPracticaXIngreso) {
                    perror("Hubo un problema al intentar abrir el archivo de practicas por ingreso");
                    fclose(pArchiIngreso);
                    fclose(pArchiPacientes);
                    return arbol;
                }

                nodoIngreso* nodoIngresoBuscado = buscaIngreso(pacienteAux->listaIngresos, ingreso.numeroIngreso);

                stPracticaXIngreso practicaXIngreso;
                while (fread(&practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngreso) > 0) {
                    if (nodoIngresoBuscado && nodoIngresoBuscado->ingreso.numeroIngreso == practicaXIngreso.nroIngreso) {
                        nodoIngresoBuscado->listaPracticasXIngreso = agregarNodoPracticaXIngreso(nodoIngresoBuscado->listaPracticasXIngreso, practicaXIngreso);
                        printf("Practica por ingreso agregada\n");
                    }
                }

                fclose(pArchiPracticaXIngreso);
            }
        }

        fclose(pArchiIngreso);
    }

    fclose(pArchiPacientes);
    return arbol;
}



//void salvarArbolFinPrograma(nodoPaciente *arbol) {
//    if (arbol == NULL) {
//        return; // Verificar si el árbol está vacío
//    }
//
//    FILE *pArchiPacientes = fopen(ARCHIVO_PACIENTES, "wb");
//    if (pArchiPacientes == NULL) {
//        return; // Manejar el error si no se puede abrir el archivo
//    }
//
//    stPaciente *arregloPacientes = arbolPacientesToArreglo(arbol);
//    int validosArre = cantidadNodosArbolPacientes(arbol);
//
//    for (int i = 0; i < validosArre; i++) {
//        fwrite(&arregloPacientes[i], sizeof(stPaciente), 1, pArchiPacientes);
//
//        nodoPaciente *paciente = buscaPaciente(arbol, arregloPacientes[i].dni);
//
//        if (paciente && paciente->listaIngresos) {
//            nodoIngreso *segIngresos = paciente->listaIngresos;
//
//            FILE *pArchiIngresos = fopen(ARCHIVO_INGRESOS, "ab"); // Cambio a modo append
//
//            if (pArchiIngresos != NULL) {
//                while (segIngresos != NULL) {
//                    fwrite(&segIngresos->ingreso, sizeof(stIngreso), 1, pArchiIngresos);
//
//                    FILE *pArchiPracticaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "ab"); // Cambio a modo append
//
//                    if (pArchiPracticaXIngresos != NULL) {
//                        nodoPracticaXIngreso *segPracticaXIngreso = segIngresos->listaPracticasXIngreso;
//
//                        while (segPracticaXIngreso != NULL) {
//                            fwrite(&segPracticaXIngreso->practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngresos);
//                            segPracticaXIngreso = segPracticaXIngreso->siguiente;
//                        }
//
//                        fclose(pArchiPracticaXIngresos); // Cerrar el archivo después de escribir
//                    }
//
//                    segIngresos = segIngresos->siguiente;
//                }
//
//                fclose(pArchiIngresos); // Cerrar el archivo después de escribir
//            }
//        }
//    }
//
//    fclose(pArchiPacientes); // Cerrar el archivo al finalizar
//}

void salvarArbolFinPrograma(nodoPaciente *arbol) {
    if (arbol == NULL) {
        return; // Verificar si el árbol está vacío
    }

    FILE *pArchiPacientes = fopen(ARCHIVO_PACIENTES, "wb");
    FILE *pArchiIngresos = fopen(ARCHIVO_INGRESOS, "wb");
    FILE *pArchiPracticaXIngresos = fopen(ARCHIVO_PRACTICAXINGRESOS, "wb");

    if (pArchiPacientes == NULL || pArchiIngresos == NULL || pArchiPracticaXIngresos == NULL) {
        // Manejar el error si no se pueden abrir los archivos
        // Cerrar los archivos y devolver o imprimir un mensaje de error
        if (pArchiPacientes != NULL) {
            fclose(pArchiPacientes);
        }
        if (pArchiIngresos != NULL) {
            fclose(pArchiIngresos);
        }
        if (pArchiPracticaXIngresos != NULL) {
            fclose(pArchiPracticaXIngresos);
        }
        return;
    }

    stPaciente *arregloPacientes = arbolPacientesToArreglo(arbol);
    int validosArre = cantidadNodosArbolPacientes(arbol);

    for (int i = 0; i < validosArre; i++) {
        if (fwrite(&arregloPacientes[i], sizeof(stPaciente), 1, pArchiPacientes) != 1) {
            // Manejar el error si no se pudo escribir correctamente en ARCHIVO_PACIENTES
            break;
        }

        nodoPaciente *paciente = buscaPaciente(arbol, arregloPacientes[i].dni);

        if (paciente && paciente->listaIngresos) {
            nodoIngreso *segIngresos = paciente->listaIngresos;

            while (segIngresos != NULL) {
                if (fwrite(&segIngresos->ingreso, sizeof(stIngreso), 1, pArchiIngresos) != 1) {
                    // Manejar el error si no se pudo escribir correctamente en ARCHIVO_INGRESOS
                    break;
                }

                nodoPracticaXIngreso *segPracticaXIngreso = segIngresos->listaPracticasXIngreso;

                while (segPracticaXIngreso != NULL) {
                    if (fwrite(&segPracticaXIngreso->practicaXIngreso, sizeof(stPracticaXIngreso), 1, pArchiPracticaXIngresos) != 1) {
                        // Manejar el error si no se pudo escribir correctamente en ARCHIVO_PRACTICAXINGRESOS
                        break;
                    }
                    segPracticaXIngreso = segPracticaXIngreso->siguiente;
                }

                segIngresos = segIngresos->siguiente;
            }
        }
    }

    fclose(pArchiPacientes);
    fclose(pArchiIngresos);
    fclose(pArchiPracticaXIngresos);
}
