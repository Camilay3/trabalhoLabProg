CC      = gcc
CFLAGS  = -Wall -Wextra -O2

SRC     = src
INC     = include

COMMON = $(SRC)/codificador.o $(SRC)/decodificador.o $(SRC)/pgm.o $(SRC)/manipuladorDeBits.o

all: encoder decoder

encoder: $(COMMON) $(SRC)/encoder.o
	$(CC) $(CFLAGS) $^ -I$(INC) -o $@
	@echo " -- Resultado gerado: ./encoder"

decoder: $(COMMON) $(SRC)/decoder.o
	$(CC) $(CFLAGS) $^ -I$(INC) -o $@
	@echo " -- Resultado gerado: ./decoder"

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INC) -o $@

run: all
	./encoder
	./decoder

clean:
	rm -f encoder decoder *.o $(SRC)/*.o
	@echo " -- Limpeza concluída"