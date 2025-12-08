#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>

typedef struct quadtree {
    int raiz;
    unsigned char valor;
    struct quadtree *no, *ne, *so, *se;
} quadtree;

quadtree* reconstruirArvore(FILE *bitstream);
void reconstruirImagem(quadtree *q,unsigned char **img, int x, int y, int tamanho);
int salvarPGM(const char *nome,unsigned char *pData,int colunas, int linhas,int valor_max);

#endif