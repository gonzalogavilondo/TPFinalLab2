# Función principal del programa
 main():
    while True:
        printf("Hospital de Niños - Sistema de Gestión")
        printf("Elija su perfil:")
        printf("1. Administrador")
        printf("2. Profesional de Laboratorio")
        printf("3. Administrativo")
        printf("4. Salir")

        opcion = input("Seleccione una opción: ")

        if opcion == '1':
            MenuAdministrador()
        else if opcion == '2':
            MenuProfesionalLab()
        else if opcion == '3':
            MenuAdministrativo()
        else if opcion == '4':
            printf("Saliendo del sistema.")
            break
        else:
            printf("Opción no válida. Intente nuevamente.")

 MenuAdministrador():
    printf("Bienvenido, Administrador.")
    # Agregar las opciones específicas para el administrador
    # Por ejemplo:
    printf("1. Gestionar pacientes")
    printf("2. Gestionar personal")
    printf("3. Generar informes")
    printf("4. Salir")

 MenuProfesionalLab():
    printf("Bienvenido, Profesional de Laboratorio.")
    # Agregar las opciones específicas para el profesional de laboratorio
    # Por ejemplo:
    printf("1. Registrar resultados de análisis")
    printf("2. Consultar muestras pendientes")
    printf("3. Salir")

 MenuAdministrativo():
    printf("Bienvenido, Administrativo.")
    # Agregar las opciones específicas para el administrativo
    # Por ejemplo:
	printf("1. Alta de usuario")
    printf("2. Gestionar citas")
    printf("3. Facturación")
    printf("4. Salir")