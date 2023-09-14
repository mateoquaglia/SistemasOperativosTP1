# SistemasOperativosTP1
Con el desarrollo del siguiente Trabajo Práctico (TP), se busca:
- Realizar un primer programa en C para GNU/Linux.
- Aprender a compilar con GNU gcc, debuggear con GNU gdb.
- Dirigir el proceso de compilación a través de GNU Make.
-
- Aprender sobre /proc: qué es, qué información contiene, cómo se puede utilizar.
Introducción
Este trabajo práctico consta en la elaboración de un programa en lenguaje C sobre
GNU/Linux. El trabajo se divide en soluciones incrementales.
1
Desarrollo
Step: A rdproc, versión inicial
Crear la siguiente aplicación, llamada rdproc
Escriba una versión inicial del programa que inspeccione las variables del kernel a
través de /proc e informe por stdout:
● Tipo y modelo de CPU, número de cores, caché L1 y l2
● Versión de Kernel.
● Tiempo transcurrido desde que se inició el sistema operativo, con el formato
dd:hh:mm:ss.
● Lista de filesystems soportados por el kernel.
● Lista de particiones con su correspondiente tipo de filesystem (ej: / ext4)
También se pide incluir una cabecera donde se indique el nombre de la máquina y la fecha y
hora actual.
Step B: Command line arguments
Escriba una segunda versión del programa que imprima la misma información que la versión
por defecto, pero en caso de invocarse con la opción -s, agrega la siguiente estadísticas del
sistema:
● Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle.
● Cantidad de cambios de contexto.
● Número de procesos creados desde el inicio del sistema.
Step C: Polling
La tercera parte involucra imprimir todo lo de las versiones anteriores, pero cuando se
invoca con la opción -l <interval> <duration> imprime además:
● Número de peticiones a disco realizadas.
● Cantidad de memoria configurada en el hardware.
● Cantidad de memoria disponible.
● Lista de los promedios de carga de 1 minuto.
Así por ejemplo rdproc -l 2 100 mostrará el promedio de carga de 1 minuto por 100
segundos tomando muestras en intervalos de 2 segundos. El comando rdproc -l a b, lee los
datos indicados arriba (peticiones de disco, cantidades de memoria, promedios de carga) de
/proc, y los imprime repetidamente cada a segundos; esto se repite hasta que hayan pasado
b segundos.
Por ejemplo:
2
$ rdproc -l 5 15
Peticiones a disco: 12345
Memoria disponible / total: 1000000 / 8000000
Promedio de carga en el último minuto: 0.88
[Pausa de 5 segundos]
Peticiones a disco: 12348
Memoria disponible / total: 2000000 / 8000000
Promedio de carga en el último minuto: 0.82
[Pausa de 5 segundos]
Peticiones a disco: 12645
Memoria disponible / total: 500000 / 8000000
Promedio de carga en el último minuto: 0.98
[Pausa de 5 segundos]
Peticiones a disco: 99995
Memoria disponible / total: 300000 / 8000000
Promedio de carga en el último minuto: 1.07
En particular, noten que el promedio de carga de un minuto es un valor que el sistema
provee ya calculado, no es algo que ustedes tengan que calcular.
Notar que cada opción incluye a la otra, por lo que rdproc -s -l 2 100 no debería ser aceptado
y en tales casos resulta útil imprimir por la salida estándar un resumen de las opciones
aceptadas.
Step D: Process
Agregar a rdproc, la siguiente opción -p <pid>. Con esta nueva opción, además, se imprime
información sobre los file descriptors a los que tiene acceso un proceso en particular.
Agregar la opción -f <pid>, para imprimir los límites de archivos abiertos para un cierto
proceso.
Finalmente, agregar la opción -t para imprimir el kernel stack trace actual de un cierto
proceso. Imprimir solamente el nombre del símbolo.
Ejemplo de ejecución
% rdproc -p 123
<rdproc previous info>
<permits> <file type> <path to fd>
...
<permits> <file type> <path to fd>
3
Testing
1) Testear con un programa que abra un archivo y se quede en un loop infinito.
2) Utilizando shell:
Primero, se puede conseguir el process ID usando el comando ps:
% ps aux | grep processName
Opcionalmente, se puede instalar y utilizar el command pidof:
% pidof processName
Luego, podemos acceder a /proc/<id>/fd
Finalmente, un comando que resume esta consigna:
% lsof -a -p <pid>
3) Testear la opción -f con el comando ‘ulimit’.
Step E: JSON format
Este último punto consiste en agregar la opción -j, que puede ser combinada con
cualquiera de los puntos anteriores, de tal manera que imprime la información en formato
JSON. Por ejemplo para al llamar a rdproc -j, producirá una salida del siguiente estilo:
{
"cpu_type": "GenuineIntel",
"cpu_model": "Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz",
"kerner_version": "Linux pegaso 5.8.8-arch1-1",
"number_of_threads": 8
....
....
}
Para esto utilice la librería de Dave Gamble que la puede encontrar en su repositorio de
github junto con su documentación