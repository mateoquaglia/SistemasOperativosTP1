#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

// Función para obtener información de file descriptors de un proceso
void getProcessFileDescriptors(int pid) {
    char fdPath[PATH_MAX];
    snprintf(fdPath, sizeof(fdPath), "/proc/%d/fd", pid);

    printf("File Descriptors del Proceso %d:\n", pid);
    DIR *dir = opendir(fdPath);
    if (dir == NULL) {
        perror("Error al abrir el directorio de file descriptors");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

// Función para obtener límites de archivos abiertos de un proceso
void getProcessLimits(int pid) {
    char limitsPath[PATH_MAX];
    snprintf(limitsPath, sizeof(limitsPath), "/proc/%d/limits", pid);

    printf("Límites de Archivos Abiertos del Proceso %d:\n", pid);
    FILE *limitsFile = fopen(limitsPath, "r");
    if (limitsFile == NULL) {
        perror("Error al abrir el archivo de límites");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), limitsFile) != NULL) {
        printf("%s", line);
    }

    fclose(limitsFile);
}

// Función para obtener el stack trace del kernel de un proceso
void getProcessStackTrace(int pid) {
    char stackTracePath[PATH_MAX];
    snprintf(stackTracePath, sizeof(stackTracePath), "/proc/%d/stack", pid);

    printf("Stack Trace del Proceso %d:\n", pid);
    FILE *stackTraceFile = fopen(stackTracePath, "r");
    if (stackTraceFile == NULL) {
        perror("Error al abrir el archivo de stack trace");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), stackTraceFile) != NULL) {
        printf("%s", line);
    }

    fclose(stackTraceFile);
}

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        int pid = atoi(argv[2]);
        getProcessFileDescriptors(pid);
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        int pid = atoi(argv[2]);
        getProcessLimits(pid);
    } else if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        int pid = getpid();  // Cambiar para usar el PID deseado
        getProcessStackTrace(pid);
    } else {
        printf("Uso:\n");
        printf("rdproc -p <pid> : Mostrar file descriptors de un proceso\n");
        printf("rdproc -f <pid> : Mostrar límites de archivos abiertos de un proceso\n");
        printf("rdproc -t       : Mostrar stack trace del kernel del proceso actual\n");
    }

    return 0;
}

/* Función para obtener información sobre un proceso
void getProcessInfo(int pid) {
    char procPath[256];
    snprintf(procPath, sizeof(procPath), "/proc/%d/status", pid);

    FILE *statusFile = fopen(procPath, "r");
    if (statusFile == NULL) {
        perror("Error al abrir el archivo /proc/<pid>/status");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), statusFile) != NULL) {
        // Procesa y muestra la información del proceso según tus necesidades
        printf("%s", line);
    }

    fclose(statusFile);
}

// Función para obtener límites de archivos abiertos para un proceso
void getProcessLimits(int pid) {
    struct rlimit rlim;
    if (getrlimit(RLIMIT_NOFILE, &rlim) != 0) {
        perror("Error al obtener límites de archivos abiertos");
        exit(EXIT_FAILURE);
    }

    printf("Límites de archivos abiertos para el proceso %d:\n", pid);
    printf("Valor suave: %ld\n", rlim.rlim_cur);
    printf("Valor máximo: %ld\n", rlim.rlim_max);
}

// Función para obtener el stack trace del kernel del proceso
void getProcessStackTrace(int pid) {
    void *array[10];  // Tamaño del array ajustable según tus necesidades
    size_t size;

    size = backtrace(array, sizeof(array) / sizeof(void *));
    char **strings = backtrace_symbols(array, size);
    if (strings == NULL) {
        perror("Error al obtener el stack trace");
        exit(EXIT_FAILURE);
    }

    printf("Stack trace del kernel para el proceso %d:\n", pid);
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", strings[i]);
    }

    free(strings);
}

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        int pid = atoi(argv[2]);
        getProcessInfo(pid);
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        int pid = atoi(argv[2]);
        getProcessLimits(pid);
    } else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        int pid = atoi(argv[2]);
        getProcessStackTrace(pid);
    } else {
        printf("Uso: rdproc -p <pid> | -f <pid> | -t <pid>\n");
    }

    return 0;
}
*/
