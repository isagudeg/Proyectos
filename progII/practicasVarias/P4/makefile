#opciones de compilación, muestra todos los warnings (-Wall)
#usamos compilador gcc
CC=gcc -Wall

#carpeta de los archivos las cabeceras
HEADER_FILES_DIR = ./headerFiles

#opciones de compilación, indica dónde están los archivos .h
INCLUDES = -I $(HEADER_FILES_DIR)

#nombre del ejecutable o archivo de salida
OUTPUT = ejecutable

#ficheros .h. Si hay varios, se enumeran con su path completo
#LIB_HEADERS contiene la lista de archivos de cabecera.
LIB_HEADERS = $(HEADER_FILES_DIR)/cambio.h $(HEADER_FILES_DIR)/vectordinamico.h

#archivos fuentes
SRCS = main.c cambio.c vectordinamico.c

#ficheros .o: todos los .o con un análogo .c en SRCS, archivos objeto que se generarán a partir de los archivos fuente.
OBJS = $(SRCS:.c=.o)

#regla 1 (dependencia de los .o)
#compila el ejecutable a partir de los archivos objeto.
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

#regla 2 (genera los .o cuando es necesario, dependencia de los .c y .h)
#$@ es el nombre del fichero que se genera con la regla (.o)
#$< es el nombre del primer prerrequisito (el archivo .c cuyo .o se está generando)
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

# regla 3 que borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT)

#regla 4 que borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f *.o *~




