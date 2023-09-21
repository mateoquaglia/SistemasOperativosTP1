
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

void print_json(const char *key, const char *value, int first) {
    if (!first) {
        printf(",\n");
    }
    printf("\"%s\": \"%s\"", key, value);
}

void file_descriptors_json(int pid) {
    DIR *descriptor;
    struct dirent *entry;
    struct stat mystats;
    int first = 1;

    char direccion[100];
    char linea[300];
    char *path;

    sprintf(direccion, "/proc/%d/fd", pid);

    descriptor = opendir(direccion);

    printf("{\n");
    while ((entry = readdir(descriptor))) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            sprintf(linea, "/proc/%d/fd/%s", pid, entry->d_name);

            stat(linea, &mystats);

            path = malloc(mystats.st_size + 1);

            print_json("Descriptor", entry->d_name, first);
            print_json("Permissions", (mystats.st_mode & S_IRUSR) ? "r" : "- ", 0);
            print_json("Type", (S_ISDIR(mystats.st_mode)) ? "Directory" : "File", 0);
            print_json("Path", linea, 0);
            first = 0;
            free(path);
        }
    }
    printf("\n}\n");
    closedir(descriptor);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s -j <pid>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-j") != 0) {
        fprintf(stderr, "Opción no válida: %s\n", argv[1]);
        return 1;
    }

    int pid = atoi(argv[2]);
    if (pid <= 0) {
        fprintf(stderr, "PID no válido: %d\n", pid);
        return 1;
    }

    file_descriptors_json(pid);

    return 0;
}
