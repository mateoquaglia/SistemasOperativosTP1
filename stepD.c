#include "StepD.h"
/*
 * permisos, tipo de archivo y el path de los file descriptors 
 */
void file_descriptors(int pid)
{
  DIR *descriptor;
  struct dirent *entry;
  struct stat mystats;

  int files = 0;
  char direccion[100];
  char linea[300];
  char *path;

  sprintf(direccion,"/proc/%d/fd",pid);

  descriptor = opendir(direccion);

  /* Para cada entrada del directorio imprime lo pedido en el enunciado */
  while( (entry=readdir(descriptor)) )
  {
    if(files >= 2) /* Las dos primeras son los directorios actual y padre */
    {
      /* Toma el file descriptor, genera los stats y el path */
      sprintf(linea,"/proc/%d/fd/%s",pid,entry->d_name);

      stat(linea, &mystats);

      path = malloc(mystats.st_size + 1); // reservo dinamicamente memoria para almacenar el camino

      /*  lectura, escritura y ejecución */
      printf( (mystats.st_mode & S_IRUSR) ? "r" : "-");
      printf( (mystats.st_mode & S_IWUSR) ? "w" : "-");
      printf( (mystats.st_mode & S_IXUSR) ? "x" : "-");
      printf( (mystats.st_mode & S_IRGRP) ? "r" : "-");
      printf( (mystats.st_mode & S_IWGRP) ? "w" : "-");
      printf( (mystats.st_mode & S_IXGRP) ? "x" : "-");
      printf( (mystats.st_mode & S_IROTH) ? "r" : "-");
      printf( (mystats.st_mode & S_IWOTH) ? "w" : "-");
      printf( (mystats.st_mode & S_IXOTH) ? "x" : "-");

      /* tipo de archivo */
      switch (mystats.st_mode & S_IFMT)
      {
        case S_IFBLK:  printf(" BLK "); break; /* Block */
        case S_IFCHR:  printf(" CHR "); break; /* Character */
        case S_IFDIR:  printf(" DIR "); break; /* Directory */
        case S_IFIFO:  printf(" FIF "); break; /* FIFO/pipe */
        case S_IFLNK:  printf(" LNK "); break; /* Symbolic link */
        case S_IFREG:  printf(" REG "); break; /* Regular file */
        case S_IFSOCK: printf(" SOK "); break; /* Socket */
        default:       printf(" ??? "); break; /* Unknown */
      }
      readlink(linea,path,100);
      printf("%s\n", path);

      printf("\n");
    }
    files++;
  }
  closedir(descriptor);
}
/*
 * limites del proceso 
 */
void limits(int pid)
{
  char limits[45];
  sprintf(limits,"/proc/%d/limits",pid);

  FILE *limites = fopen(limits,"r");

  int soft,hard;
  char *linea;

  linea = obtenerInfo("Max open files",limites);
  fclose(limites);

  sscanf(linea, "%*s %*s %d %d", &soft, &hard);

  printf("Soft limits / Hard limits: %d / %d\n", soft, hard);
}
/*
 * stack trace 
 */
void stack(int pid)
{
  char stack[45];
  sprintf(stack,"sudo cat /proc/%d/stack",pid);

  char linea[1000];

  FILE *trace = popen(stack,"r");

  printf("%s\n", "Kernel Stack Trace:\n");

  while (fgets(linea, sizeof linea, trace) != NULL)
  {
    /* Toma la primer línea, ignorando el primer string */
    sscanf(linea,"%*s %s", linea);

    /* Si hay un +, elimina desde esa posición hasta el final */
    if(strchr(linea,'+'))
    {
      /* Guarda la posición para acortar el string */
      int len = (int) (strchr(linea,'+')-linea);
      memmove(linea,linea,len);
      linea[len] = '\0';
    }
    printf("%s\n", linea);
  }
  fclose(trace);
}
