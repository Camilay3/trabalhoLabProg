#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdio.h>
#define LIMITE 20
#include "struct.h"

struct pgm;
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);


unsigned char **converter_para_matriz(struct pgm img);

double media_simples(unsigned char **img, int x, int y, int tamanho);
double mse(unsigned char **img, int x, int y, int tamanho, double media);


quadtree *construtortree(unsigned char **img, int x, int y,int tamanho, double limite);

void salvarArvore(quadtree *n, FILE *fp);


void freeTree(quadtree *n);

#endif
