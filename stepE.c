#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

//  obtener info del sistema en formato JSON
void printJSONFormat() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        perror("Error al obtener información del sistema");
        exit(EXIT_FAILURE);
    }

    printf("{\n");
    printf("\"cpu_type\": \"CPU\",\n");  
    printf("\"cpu_model\": \"Intel i7 6700\",\n");  
    printf("\"kernel_version\": \"%s\",\n", sysinfo.version);
    printf("\"number_of_threads\": %ld,\n", si.procs);
    printf("}\n");
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-j") == 0) {
        printJSONFormat();
    } else {
        printf("Uso: rdproc -j\n");
    }

    return 0;
}
