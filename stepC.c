#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/vfs.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

// Función para obtener la cantidad de memoria configurada en el hardware
unsigned long long getMemoryTotal() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        perror("Error al obtener información del sistema");
        exit(EXIT_FAILURE);
    }
    return si.totalram * si.mem_unit;
}

// Función para obtener la cantidad de memoria disponible
unsigned long long getMemoryAvailable() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        perror("Error al obtener información del sistema");
        exit(EXIT_FAILURE);
    }
    return si.freeram * si.mem_unit;
}

// Función para obtener el número de peticiones a disco realizadas
unsigned long long getDiskRequests() {
    FILE *diskstatsFile = fopen("/proc/diskstats", "r");
    if (diskstatsFile == NULL) {
        perror("Error al abrir /proc/diskstats");
        exit(EXIT_FAILURE);
    }

    unsigned long long diskRequests = 0;
    char line[256];
    while (fgets(line, sizeof(line), diskstatsFile) != NULL) {
        // Analizar el archivo /proc/diskstats para obtener información de peticiones a disco
        // Aquí debes implementar la lógica para analizar el archivo y calcular las peticiones a disco.
    }

    fclose(diskstatsFile);
    return diskRequests;
}

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-l") != 0) {
        printf("Uso: rdproc -l <interval> <duration>\n");
        return EXIT_FAILURE;
    }

    int interval = atoi(argv[2]);
    int duration = atoi(argv[3]);
    time_t startTime = time(NULL);

    while (1) {
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= duration) {
            break;
        }

        unsigned long long diskRequests = getDiskRequests();
        unsigned long long memoryTotal = getMemoryTotal();
        unsigned long long memoryAvailable = getMemoryAvailable();
        double loadAverage = getloadavg(NULL, 1);  // Obtiene el promedio de carga de 1 minuto

        printf("Peticiones a disco: %llu\n", diskRequests);
        printf("Memoria disponible / total: %llu / %llu\n", memoryAvailable, memoryTotal);
        printf("Promedio de carga en el último minuto: %.2lf\n", loadAverage);

        sleep(interval);
    }

    return 0;
}
