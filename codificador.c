#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct quadtree {
    int raiz;
    unsigned char valor;
    struct quadtree *so, *sl, *io, *il;
} quadtree;

FILE *out, *in;
unsigned char buffer = 0;
int buffer_pos = 0;

// Escrita de bits
void escrevebit(int bit) {
    buffer = (buffer << 1) | (bit & 1);
    buffer_pos++;
    if (buffer_pos == 8) {
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

// Escrita de byte
void escrevebyte(unsigned char b) {
    if (buffer_pos != 0) { // flush parcial
        buffer <<= (8 - buffer_pos);
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
    fputc(b, out);
}

// Checagem final
void checagembits() {
    if (buffer_pos > 0) {
        buffer <<= (8 - buffer_pos);
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

// Leitura de bits
int lerbit() {
    static int bit_pos = 0;
    static unsigned char leitor_buffer = 0;

    if (bit_pos == 0) {
        int c = fgetc(in);
        if (c == EOF) return -1;
        leitor_buffer = (unsigned char)c;
        bit_pos = 8;
    }

    int bit = (leitor_buffer >> 7) & 1;
    leitor_buffer <<= 1;
    bit_pos--;
    return bit;
}

// Leitura de byte
unsigned char lerbyte() {
    return (unsigned char)fgetc(in);
}

double medianormal(unsigned char **img, int x, int y, int tamanho){
    int soma = 0;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            soma += img[x + i][y + j];
        }
    }

    return (double)soma / (tamanho * tamanho);
}


double mse(unsigned char **img, int x, int y, int tamanho, double media){
    double erro = 0;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    }

    return erro / (tamanho * tamanho);
}



quadtree* construtortree(unsigned char **img, int x, int y, int tamanho, double limite) {
    quadtree *node = malloc(sizeof(quadtree));

    double media = medianormal(img, x, y, tamanho);
    double erro  = mse(img, x, y, tamanho, media);

    if (erro <= limite || tamanho == 1) { // nó folha
        node->raiz = 0;
        node->valor = (unsigned char)(media + 0.5);
        node->so = node->sl = node->io = node->il = NULL;

        escrevebit(0);
        escrevebyte(node->valor);
        return node;
    }

    node->raiz = 1;
    escrevebit(1);

    int h = tamanho/2;
    node->so = construtortree(img, x,     y,     h, limite);
    node->sl = construtortree(img, x,     y + h, h, limite);
    node->io = construtortree(img, x + h, y,     h, limite);
    node->il = construtortree(img, x + h, y + h, h, limite);

    return node;
}