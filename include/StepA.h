#ifndef STEPA_H
#define STEPA_H

#include <stdio.h>    //Input-Output
#include <stdlib.h>   //Standard
#include <string.h>   //Strings
#include <stdbool.h>  //Booleanos
#include <unistd.h>   //Clocks and Sleep

#define JpS sysconf(_SC_CLK_TCK) //Jiffies/seconds (clock tics)

void convertTime(int seconds, bool jiffies);
void cpuinfo(void);
void filesystem(void);
void header(void);
void imprimirDefault(void);
void kernelversion(void);
char* obtenerInfo(char* key, FILE *archivo);
void uptime(void);

#endif
