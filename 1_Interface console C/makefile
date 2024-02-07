CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Liste des fichiers source
SRC = main.c board.c

# Liste des fichiers objet générés à partir des fichiers source
OBJ = $(SRC:.c=.o)

# Nom du fichier exécutable
EXEC = GobletGobblers1

# Règle par défaut pour construire l'exécutable
all: $(EXEC)

# Règle pour l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Règle générique pour construire les fichiers objets à partir des fichiers source
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)
