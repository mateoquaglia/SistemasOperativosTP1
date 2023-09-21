#include "StepA.h"
#include "StepB.h"
#include "StepC.h"
#include "StepD.h"
#include <getopt.h>  

const char* nombre_programa;
int a = 0, b = 0, pid = 0; //Intervalos 

void print_uso(FILE* stream, int exit_code)
{
  fprintf (stream, "Uso: %s [opcion] [argumento]\n", nombre_programa);
  fprintf (stream,
    "Opciones:\n"
    " -s      --stats      - tiempos del CPU.\n"
    " -l a b  --list a b   -estadísitcas del disco y la memoria repetidamente\n"                    
    "                        por el intervalo a  b.\n"
    " -p pid  --pid pid    - Muestra info sobre los file descriptors del\n"
    "                        proceso 'pid'.\n"
    " -f pid  --files pid  - Muesta los límites de archivos abiertos para un\n"
    "                        proceso 'pid'.\n"
    " -t pid  --trace pid  - stack trace acutal del proceso 'pid'.\n");
                         
  exit (exit_code);
}

int main(int argc, char* argv[])
{
  int opcion;
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
        case 's':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          cputimes();
          break;
        case 'l':
          sscanf(argv[2], "%d", &a);
          sscanf(argv[3], "%d", &b);

          if(a > b)
          {

            printf("------ 'a' > 'b' no se puede-----\n\n");
            abort();
          }
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          memstats(a,b);
          break;

        case 'p':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          file_descriptors(pid);
          break;
        case 'f':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          limits(pid);
          break;
        case 't':
          imprimirDefault();
          printf("\n|---------------------------------------------------|\n\n");
          stack(pid);
          break;
        case '?':
          print_uso(stderr,1);

        case -1:
          break;

        default:
          abort();
      }
      break;
    }
  } while(opcion != -1);

  return EXIT_SUCCESS;
}
