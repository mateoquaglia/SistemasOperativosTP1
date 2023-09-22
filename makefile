# Compilador con sus flags
CC=gcc
CFLAGS= -Wall -pedantic -I$(IDIR)

# Directorios a utilizar
IDIR =./include
ODIR=obj

# Dependencias
_DEPS = StepA.h StepB.h StepC.h StepD.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Objetos
_OBJ = StepA.o StepB.o StepC.o StepD.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Compila las dependencias
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compila el programa principal
rdproc: rdproc.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Elimina los objetos creados
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ rdproc
