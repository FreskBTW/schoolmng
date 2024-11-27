#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del Alumno
typedef struct Alumno {
    int id;
    char nombre[50];
    float calificaciones[3];
    float calificacion_final;
    struct Alumno *siguiente;
} Alumno;

// Funcion para calcular la calificacion final
float calcularCalificacionFinal(float calificaciones[3]) {
    return (calificaciones[0] + calificaciones[1] + calificaciones[2]) / 3.0;
}

// Crear un nuevo nodo para la lista enlazada
Alumno* crearAlumno(int id, char nombre[], float calificaciones[]) {
    Alumno *nuevo = (Alumno*)malloc(sizeof(Alumno));
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    for (int i = 0; i < 3; i++) {
        nuevo->calificaciones[i] = calificaciones[i];
    }
    nuevo->calificacion_final = calcularCalificacionFinal(calificaciones);
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agregar un alumno a la lista enlazada
void agregarAlumno(Alumno **lista, Alumno *nuevo) {
    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        Alumno *actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Mostrar la lista de alumnos
void mostrarAlumnos(Alumno *lista) {
    printf("ID\tNombre\t\tParcial 1\tParcial 2\tParcial 3\tFinal\n");
    printf("---------------------------------------------------------------------\n");
    while (lista != NULL) {
        printf("%d\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n", lista->id, lista->nombre, 
               lista->calificaciones[0], lista->calificaciones[1], 
               lista->calificaciones[2], lista->calificacion_final);
        lista = lista->siguiente;
    }
}

// Guardar la lista de alumnos en un archivo
void guardarEnArchivo(Alumno *lista) {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo para guardar (con extension): ");
    scanf(" %[^\n]s", nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    while (lista != NULL) {
        fprintf(archivo, "%d,%s,%.2f,%.2f,%.2f,%.2f\n", lista->id, lista->nombre, 
                lista->calificaciones[0], lista->calificaciones[1], 
                lista->calificaciones[2], lista->calificacion_final);
        lista = lista->siguiente;
    }
    fclose(archivo);
    printf("Datos guardados exitosamente en '%s'.\n", nombreArchivo);
}

// Buscar un alumno por ID
Alumno* buscarAlumno(Alumno *lista, int id) {
    while (lista != NULL) {
        if (lista->id == id) {
            return lista;
        }
        lista = lista->siguiente;
    }
    return NULL;
}

// Obtener el siguiente ID unico
int obtenerSiguienteID(Alumno *lista) {
    int maxID = 0;
    while (lista != NULL) {
        if (lista->id > maxID) {
            maxID = lista->id;
        }
        lista = lista->siguiente;
    }
    return maxID + 1;
}

// Menu principal
int main() {
    Alumno *listaAlumnos = NULL;
    int opcion;
    int idContador = 1; // Para generar IDs unicos

    do {
        printf("\n--- Gestion de Alumnos ---\n");
        printf("1. Agregar Alumno\n");
        printf("2. Mostrar Alumnos\n");
        printf("3. Buscar Alumno por ID\n");
        printf("4. Guardar Alumnos en Archivo\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                char nombre[50];
                float calificaciones[3];
                printf("Ingrese el nombre del alumno: ");
                scanf(" %[^\n]s", nombre);
                printf("Ingrese las calificaciones de los 3 parciales: ");
                for (int i = 0; i < 3; i++) {
                    scanf("%f", &calificaciones[i]);
                }
                Alumno *nuevo = crearAlumno(idContador++, nombre, calificaciones);
                agregarAlumno(&listaAlumnos, nuevo);
                break;
            }
            case 2:
                mostrarAlumnos(listaAlumnos);
                break;
            case 3: {
                int id;
                printf("Ingrese el ID del alumno a buscar: ");
                scanf("%d", &id);
                Alumno *alumno = buscarAlumno(listaAlumnos, id);
                if (alumno) {
                    printf("\nAlumno encontrado:\n");
                    printf("ID: %d\nNombre: %s\n", alumno->id, alumno->nombre);
                    printf("Parcial 1: %.2f, Parcial 2: %.2f, Parcial 3: %.2f\n",
                           alumno->calificaciones[0], alumno->calificaciones[1],
                           alumno->calificaciones[2]);
                    printf("Calificacion final: %.2f\n", alumno->calificacion_final);
                } else {
                    printf("No se encontro un alumno con ID %d.\n", id);
                }
                break;
            }
            case 4:
                guardarEnArchivo(listaAlumnos);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);

    return 0;
}
