#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Funciones para obtener información del sistema y procesos
void getSystemInfo();
void getProcessInfo(int pid);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Implementar el Step A aquí: Obtener información básica del sistema.
        getSystemInfo();
    } else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        // Implementar el Step B aquí: Mostrar estadísticas del sistema.
        // Implementar la opción -s.
    } else if (argc == 4 && strcmp(argv[1], "-l") == 0) {
        // Implementar el Step C aquí: Mostrar información con opción -l.
        int interval = atoi(argv[2]);
        int duration = atoi(argv[3]);
        // Implementar la opción -l con interval y duration.
    } else if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        // Implementar el Step D aquí: Mostrar información sobre un proceso.
        int pid = atoi(argv[2]);
        // Implementar la opción -p con el pid especificado.
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        // Implementar la opción -f aquí.
        int pid = atoi(argv[2]);
        // Implementar la opción -f con el pid especificado.
    } else if (argc == 2 && strcmp(argv[1], "-j") == 0) {
        // Implementar el Step E aquí: Mostrar información en formato JSON.
        // Implementar la opción -j.
    } else {
        // Manejo de argumentos inválidos o combinaciones no permitidas.
        printf("Uso: rdproc [opciones]\n");
    }

    return 0;
}

void getSystemInfo() {
    // Implementar la obtención de información del sistema según el Step A.
}

void getProcessInfo(int pid) {
    // Implementar la obtención de información de un proceso según el Step D.
}
