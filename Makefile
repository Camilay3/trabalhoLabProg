CC      = gcc
CFLAGS  = -Wall -Wextra -O2

SRC     = src
INC     = include

MAIN    = $(wildcard $(SRC)/main.c $(SRC)/principal.c)

SRCS    = $(filter-out $(MAIN), $(wildcard $(SRC)/*.c))

MODULOS = $(patsubst $(SRC)/%.c, %.o, $(SRCS))

TARGET  = TrabalhoLabProg

all: $(TARGET)

$(TARGET): $(MODULOS) $(MAIN:.c=.o)
	$(CC) $(CFLAGS) $^ -I$(INC) -o $@
	@echo " -- Resultado gerado: ./$(TARGET)"

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INC) -o $@

run: all
	./$(TARGET)
 
clean:
	rm -f $(TARGET) *.o $(SRC)/*.o
	@echo " -- Limpeza concluída"