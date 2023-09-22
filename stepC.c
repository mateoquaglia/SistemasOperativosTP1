#include "StepC.h"

/**
información del disco 
 */
void memstats(int a, int b)
{
  char path_avg[] = "/proc/loadavg";
  char path_mem[] = "/proc/meminfo";
  char path_disk[] = "/proc/diskstats";

  float min;
  char *memtotal, *memavailable, *peticiones;
  int total, available, petitions;

  int veces = b/a;

  for(int i = 0; i < veces; i++)
  {
    FILE *disk = fopen(path_disk,"r");

    char linea[1000];

    fclose(disk);

    sscanf(peticiones,"%*d %*d %*s %d", &petitions);

    FILE *mem = fopen(path_mem,"r");
    memtotal = obtenerInfo("MemTotal", mem);
    memavailable = obtenerInfo("MemAvailable", mem);
    fclose(mem);

    sscanf(memtotal,"%d", &total);
    sscanf(memavailable,"%d", &available);

    FILE *avg = fopen(path_avg,"r");
    fscanf(avg, "%f", &min);
    fclose(avg);

    printf("Peticiones a disco: %d\n", petitions);
    printf("Memoria disponible / total: %d / %d\n",
          available, total);
    printf("carga en el último minuto: %.2f\n", min);
    printf("[Pausa de %d segundos]\n\n", a);
    sleep(a);
  }
}
