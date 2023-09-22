#include "StepA.h"
void cpuinfo(void)
{
  char *tipo, *modelo;

  char path_info[] = "/proc/cpuinfo";


  FILE *archivo = fopen(path_info,"r");

  tipo = obtenerInfo("vendor_id", archivo);
  modelo = obtenerInfo("model name", archivo);
  fclose(archivo);

  printf("\nInformación del CPU:\n");
  printf(" - Tipo: %s\n - Modelo: %s\n",
        tipo, modelo);
}

void convertTime(int time, bool jiffies)
{
  int dias, horas, minutos, segundos;
  int JpS= 100; 
  if(jiffies) time = time/JpS;

  dias = time / 86400;
  horas = (time % 86400) / 3600;
  minutos = (time % 3600) / 60;
  segundos = (time % 3600) % 60;

  printf("%02d D, %02d:%02d:%02d\n", dias, horas, minutos, segundos);
}

void filesystem(void)
{
  char path_files[] = "/proc/filesystems";
 FILE *files = fopen(path_files,"r");
 int contador = 0;
 char linea[1000];

  while (fgets(linea, sizeof linea, files) != NULL) contador++;
  fclose(files);

  printf("Cantidad de archivos soportados: %d\n", contador);
}

void header(void)
{
  char *nombre;
  char *fecha, *hora;

  char path_time[] = "/proc/driver/rtc";
  char path_nombre[] = "/proc/sys/kernel/hostname";
  FILE *nombre_file = fopen(path_nombre,"r");
  char linea[100];

  nombre = fgets(linea,sizeof linea, nombre_file);
  nombre[strlen(nombre)-1] = 0; 
  fclose(nombre_file);

  FILE *time = fopen(path_time, "r");

  hora = obtenerInfo("rtc_time", time);
  fecha = obtenerInfo("rtc_date", time);
  fclose(time);

  printf("%s %s %s\n", nombre, fecha, hora);
}
void imprimirDefault(void)
{
  header();
  cpuinfo();
  kernelversion();
  uptime();
  filesystem();
}

void kernelversion(void)
{
  char path_kernel[] = "/proc/sys/kernel/osrelease";

  FILE *kernel = fopen(path_kernel,"r");
  char *version;
  char linea[100];
  version = fgets(linea, sizeof linea, kernel);
  fclose(kernel);
  printf(" - Version de kernel: %s\n", version);
}

char* obtenerInfo(char* key, FILE *archivo)
{
  char *valor;
  char *resultado;

  char linea[1000];

  while (fgets(linea, sizeof linea, archivo) != NULL)
  {
    if(strncmp(linea, key, strlen(key)) == 0)
    {   
      if(strchr(linea, ':') != NULL)
      {
        valor = strchr(linea, ':');
        valor += 2;
        resultado = strdup(valor);
      } else
      {
        valor = strchr(linea, ' ');
        resultado = strdup(valor);
      }
      int len = strlen(resultado);  
    }
  }
  return resultado;
}
void uptime(void)
{
  char path_uptime[] = "/proc/uptime";

  FILE *tiempo = fopen(path_uptime,"r");

  int uptime;

  fscanf(tiempo,"%d",&uptime);

  fclose(tiempo);

  convertTime(uptime,false);
}
