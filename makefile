GRR= 20231947_20235088
nomePrograma= prova1_$(GRR)

# flags de compilação
# -Wpedantic é para garantir o padrão c23, podemos remover depois
CFLAGS = -Wall -Wextra -Werror -g -std=c23 -Wpedantic
CC = gcc-14

all: $(nomePrograma)

$(nomePrograma): main.o arvoreB.o util.o
	$(CC) -o $(nomePrograma) main.o arvoreB.o util.o $(CFLAGS)

# compilação da main
main.o: main.c arvoreB.h
	$(CC) -c $(CFLAGS) main.c

# compilação da árvore B
arvoreB.o: arvoreB.c arvoreB.h util.h
	$(CC) -c $(CFLAGS) arvoreB.c

#compilação de útil
util.o: util.c util.h arvoreB.h
	$(CC) -c $(CFLAGS) util.c

clean:
	rm -f *.o *~ $(nomePrograma)