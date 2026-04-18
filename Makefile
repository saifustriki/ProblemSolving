CC = gcc
CFLAGS = -O2 -Wall
EXEC = simulateur

all: $(EXEC)

$(EXEC): main.c tri.c tri.h
	$(CC) $(CFLAGS) -o $(EXEC) main.c tri.c

run: $(EXEC)
	mkdir -p resultats
	./$(EXEC)

clean:
	rm -f $(EXEC) resultats/resultats.csv
