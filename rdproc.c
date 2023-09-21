#include "StepA.h"
#include "StepB.h"
#include "StepC.h"
#include "StepD.h"
#include <getopt.h>   //Opciones

/* Declaracion de variables */
const char* nombre_programa;
int a = 0, b = 0, pid = 0; //Intervalos dados en los argumentos

/* Imprime las opciones disponibles en caso de recibir una no válida. */
void print_uso(FILE* stream, int exit_code)
{
  fprintf (stream, "Uso: %s [opcion] [argumento]\n", nombre_programa);
  fprintf (stream,
    "Opciones:\n"
    " -s      --stats      - Muestra los tiempos del CPU.\n"
    " -l a b  --list a b   - Muestra 'a' veces durante 'b' segundos las\n"
    "                        estadísitcas del disco y la memoria repetidamente\n"
    "                        por el intervalo indicado.\n"
    " -p pid  --pid pid    - Muestra info sobre los file descriptors del\n"
    "                        proceso 'pid'.\n"
    " -f pid  --files pid  - Muesta los límites de archivos abiertos para un\n"
    "                        proceso 'pid'.\n"
    " -t pid  --trace pid  - Muestra el kernel stack trace acutal del\n"
    "                        proceso 'pid'. Necesita privilegios root.\n");
  exit (exit_code);
}

int main(int argc, char* argv[])
{
  /* Declaracion de variables */
  int opcion;

  /* Declaracion de las opciones, version corta y larga */
  const char* const short_options = "sl:p:f:t:";

  const struct option long_options[] =
  {
    {     "stats",   0,  NULL, 's' },
    {      "list",   2,  NULL, 'l' },
    {       "pid",   1,  NULL, 'p' },
    {     "files",   1,  NULL, 'f' },
    {     "trace",   1,  NULL, 't' },
    {        NULL,   0,  NULL,  0  }
  };

  nombre_programa = argv[0];

  /* Analiza la opcion ingrasada */
  do
  {
    if(argc > 4) print_uso(stderr,1);

    sscanf(argv[argc-1],"%d",&pid);



    opcion = getopt_long(argc, argv, short_options, long_options, NULL);

    if(argc == 1) imprimirDefault();
    else
    {
      switch (opcion)
      {
        /* En caso de ser s, muestra adicionalmente los stats del CPU */
        case 's':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          cputimes();
          break;

        /* En caso de ser l, muestra adicionalmente los stats del disco */
        case 'l':
          sscanf(argv[2], "%d", &a);
          sscanf(argv[3], "%d", &b);

          if(a > b)
          {
        
            printf("------ 'a' > 'b' -----\n\n");
            abort();
          }

          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          memstats(a,b);
          break;

        /* En caso de ser p, muestra también información sobre el proceso */
        case 'p':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          file_descriptors(pid);
          break;

        /* Si se pasa f, se muestran los límites de archihvos abiertos */
        case 'f':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          limits(pid);
          break;

        /* Si es t, se muestra también el stack trace del kernel */
        case 't':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          stack(pid);
          break;

        /* Ninguna valida, muestra las opciones posibles y termina el programa */
        case '?':
          print_uso(stderr,1);

        case -1:
          break;

        /* Ninguna de las anteriores, termino el programa */
        default:
          abort();
      }
      break;
    }
  } while(opcion != -1);

  return EXIT_SUCCESS;
}
