# SistemasOperativosTP1# 
Con el desarrollo del siguiente Trabajo Práctico (TP), se busca:
- Realizar un primer programa en C para GNU/Linux.
- Aprender a compilar con GNU gcc, debuggear con GNU gdb.
- Dirigir el proceso de compilación a través de GNU Make.
- Aprender sobre /proc: qué es, qué información contiene, cómo se puede utilizar.
  Introducción
  Este trabajo práctico consta en la elaboración de un programa en lenguaje C sobre
  GNU/Linux. El trabajo se divide en soluciones incrementales.

# Notas a tener en cuenta:

 - para ejecutar el programa se debe abrir como adminstrador en la carpeta de instalacion con "sudo gcc rdproc.c stepA.c  stepB.c stepC.c stepD.c -o rdproc"
   luego se puede ejecutar la seccion deseada por ejemplo "sudo ./rdproc -s"
 - se opto por realizar el codigo seccionado, separando los .c y las librerias .h para mayor comodidad
 - se opto por separar rdproc.c y rdproc.c stepA.c  stepB.c stepC.c stepD.c puesto que se intento de otras formas y no se lograba lo requerido
 - no se logro desarrollar por completo el stepE, no logro cumplir los objetivos con el archivo json
