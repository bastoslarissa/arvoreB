GRR= 20231947
nomePrograma= prova1_$(GRR)

# flags de compilação
# -Wpedantic é para garantir o padrão c23, podemos remover depois
CFLAGS = -Wall -Wextra -Werror -g -std=c23 -Wpedantic
CC = gcc

all: $(nomePrograma)

$(nomePrograma): main.o arvoreB.o
	$(CC) -o $(nomePrograma) main.o arvoreB.o $(CFLAGS)

# compilação da main
main.o: main.c arvoreB.h
	$(CC) -c $(CFLAGS) main.c

# compilação da árvore B
arvoreB.o: arvoreB.c arvoreB.h
	$(CC) -c $(CFLAGS) arvoreB.c

clean:
	rm -f *.o *~ $(nomePrograma)