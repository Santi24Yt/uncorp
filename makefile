# Compilador
CC = gcc
# Flags del compilador
CFLAGS = -lpdcurses -lm -I./include/ -std=c89
# FLags de desarrollo
DEVFLAGS = -Wall -Wextra -Werror
# Archivos fuente
SOURCES = ./src/*.c
# Archivos ejecutables
BINS = ./bin
# Archivos de debug
DEBUGS = ./debug

# Los comandos que se ejecutan por default al poner solo `make`
all: createdirs clean defassets compile gitignore run

# Comandos que se ejecutan al hacer `make dev`
dev: createdirs cleanpg defassets lspflags compiledev gitignore

# Crear directorio de ejecutables
bindir:
	mkdir -p $(BINS)

debugdir:
	mkdir -p $(DEBUGS)

# Crear directorios
createdirs: bindir debugdir

# Compilar los archivos fuente con el compilador y las flags, la salida será el archivo `game`
compile:
	$(CC) $(SOURCES) $(CFLAGS) -o $(BINS)/game

# Compilar con flags dev
compiledev:
	$(CC) $(SOURCES) $(CFLAGS) $(DEVFLAGS) -o $(BINS)/game

# Ejecutar el programa
run:
	DEBUGFILE="$(DEBUGS)/$(shell date +%s)-debug.log"; $(BINS)/game 2> $$DEBUGFILE

# Limpiar la version anterior y el debug aunque no existan
clean:
	(rm -f $(BINS)/game && rm -f $(DEBUGS)/*) || true

# Limpiar la versión anterior sin quitar el debug
cleanpg:
	rm -f $(BINS)/game || true

# Esto es necesario para que el lsp de clangd incluya los headers propios que se incluyen también al compilar
lspflags:
	echo $(CFLAGS) $(DEVFLAGS) | sed "s/ /\n/g" > compile_flags.txt

# Crear el .gitignore
gitignore:
	echo "$(BINS)/*" "$(DEBUGS)/*" | sed "s/\.\///g" | sed "s/ /\n/g" > .gitignore && echo "*.dmp" >> .gitignore && echo "*.zzz" >> .gitignore

defassets:
	./defineassets.sh
