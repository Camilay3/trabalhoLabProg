#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include "struct.h"


quadtree* reconstruirArvore(FILE *bitstream);
void reconstruirImagem(quadtree *q,unsigned char *img, int x, int y, int tamanho,int colunas);
int salvarPGM(const char *nome,unsigned char *pData,int colunas, int linhas,int valor_max);

#endif