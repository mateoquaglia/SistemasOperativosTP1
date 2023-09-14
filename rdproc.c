#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Declaraciones de funciones
void getSystemInfo();
void getSystemStats();
void getDiskStats();
void getProcessInfo(int pid);
void getProcessFileDescriptors(int pid);
void getProcessLimits(int pid);
void getProcessStackTrace(int pid);
void printJSONFormat();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Implementa el Step A: Obtener información básica del sistema.
        getSystemInfo();
    } else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        // Implementa el Step B: Mostrar estadísticas del sistema.
        getSystemStats();
    } else if (argc == 2 && strcmp(argv[1], "-j") == 0) {
        // Implementa el Step E: Mostrar información en formato JSON.
        printJSONFormat();
    } else if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        // Implementa el Step D: Mostrar información sobre un proceso.
        int pid = atoi(argv[2]);
        getProcessInfo(pid);
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        // Implementa la opción -f aquí.
        int pid = atoi(argv[2]);
        getProcessLimits(pid);
    } else if (argc == 4 && strcmp(argv[1], "-l") == 0) {
        // Implementa el Step C: Mostrar información en intervalos.
        int interval = atoi(argv[2]);
        int duration = atoi(argv[3]);
        // Implementa la opción -l con intervalo y duración.
    } else {
        // Manejo de argumentos inválidos o combinaciones no permitidas.
        printf("Uso: rdproc [opciones]\n");
    }

    return 0;
}

void getSystemInfo() {
    // Implementa la obtención de información del sistema según el Step A.
}

void getSystemStats() {
    // Implementa la obtención de estadísticas del sistema según el Step B.
}

void getDiskStats() {
    // Implementa la obtención de estadísticas de disco según sea necesario.
}

void getProcessInfo(int pid) {
    // Implementa la obtención de información del proceso según el Step D.
}

void getProcessFileDescriptors(int pid) {
    // Implementa la obtención de file descriptors del proceso según sea necesario.
}

void getProcessLimits(int pid) {
    // Implementa la obtención de límites de archivos abiertos del proceso según sea necesario.
}

void getProcessStackTrace(int pid) {
    // Implementa la obtención de stack trace del proceso según sea necesario.
}

void printJSONFormat() {
    // Implementa la impresión de información en formato JSON según el Step E.
}
