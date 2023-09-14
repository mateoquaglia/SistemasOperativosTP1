#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getSystemInfo() {
    // Leer la versión del kernel desde /proc/version
    FILE *kernelFile = fopen("/proc/version", "r");
    if (kernelFile == NULL) {
        perror("Error al abrir /proc/version");
        exit(EXIT_FAILURE);
    }

    char kernelInfo[256];
    if (fgets(kernelInfo, sizeof(kernelInfo), kernelFile) != NULL) {
        printf("Versión del Kernel: %s", kernelInfo);
    }

    fclose(kernelFile);

    // Leer información de la CPU desde /proc/cpuinfo
    FILE *cpuinfoFile = fopen("/proc/cpuinfo", "r");
    if (cpuinfoFile == NULL) {
        perror("Error al abrir /proc/cpuinfo");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), cpuinfoFile) != NULL) {
        if (strstr(line, "model name") != NULL) {
            printf("Tipo y modelo de CPU: %s", line);
        } else if (strstr(line, "cpu cores") != NULL) {
            printf("Número de cores: %s", line);
        } else if (strstr(line, "cache size") != NULL) {
            printf("Tamaño de caché L1 y L2: %s", line);
        }
    }

    fclose(cpuinfoFile);
}

int main() {
    getSystemInfo();
    return 0;
}
