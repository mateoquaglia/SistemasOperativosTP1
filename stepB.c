#include "StepB.h"

void cputimes(void)
{
  char path_times[] = "/proc/stat";

  FILE *stat = fopen(path_times,"r");

  int user, nice, system, idle;
  int context, processes;

  char *cpu, *contexto, *procesos;

  cpu = obtenerInfo("cpu", stat);
  contexto = obtenerInfo("ctxt", stat);
  procesos = obtenerInfo("processes", stat);

  fclose(stat);
  sscanf(cpu,"%d %d %d %d",&user,&nice,&system,&idle);
  sscanf(contexto, "%d", &context);
  sscanf(procesos, "%d", &processes);

  printf("Cantidad de tiempo de CPU utilizado por:\n");
  printf(" - Usuario: ");
  convertTime(user,true);
  printf(" - Usuario (baja prioridad): ");
  convertTime(nice,true);
  printf(" - Sistema: ");
  convertTime(system,true);
  printf(" - Idle: ");
  convertTime(idle,true);

  printf("\nCantidad de cambios de contexto: %d\n", context);
  printf("Cantidad de procesos creados: %d\n", processes);
}
