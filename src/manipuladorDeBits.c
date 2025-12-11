/**************************************************************************
Avaliação 04: Trabalho Final | 04.505.23 − 2025.2 − Prof. Daniel Ferreira
___________________________________________________________________________

Aluno: Andrey Pereira
Matrícula: 20251045050038
Compilador: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
___________________________________________________________________________
 
Aluno: Camila Azevedo
Matrícula: 20251045050089
Compilador: gcc (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0
___________________________________________________________________________

Aluno: Mariana Silva
Matrícula: 20251045050321
Compilador: gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
___________________________________________________________________________

Aluno: Mateus Pinheiro
Matrícula: 20251045050348
Compilador: gcc (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/manipuladorDeBits.h"

FILE *out = NULL;
unsigned char buffer = 0;
int buffer_pos = 0;

void escrevebit(int bit) {
    buffer = (buffer << 1) | (bit & 1);
    buffer_pos++;
    if (buffer_pos == 8) {
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

void escrevebyte(unsigned char b) {
    for(int i =7; i>= 0;i--){
        int bit = (b >> i )& 1;
        escrevebit(bit);
    }
}

void checagembits() {
    if (buffer_pos > 0) {
        buffer <<= (8 - buffer_pos);
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

int lerbit(FILE *in) {
    static unsigned char rbuffer = 0;
    static int rbuffer_pos = 0;

    if (rbuffer_pos == 0) {
        int c = fgetc(in);
        if (c == EOF) return -1;
        rbuffer = (unsigned char)c;
        rbuffer_pos = 8;
    }

    int bit = (rbuffer >> (rbuffer_pos - 1)) & 1;
    rbuffer_pos--;
    return bit;
}

unsigned char lerbyte(FILE *in) {
    unsigned char b = 0;
    for (int i = 0; i < 8; i++) {
        int bit = lerbit(in);
        if (bit == -1) {
            fprintf(stderr, "Erro: fim inesperado no bitstream ao ler byte.\n");
            exit(1);
        }
        b = (b << 1) | (bit & 1);
    }
    return b;
}
