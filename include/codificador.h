#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdio.h>
#include <math.h>
#define LIMITE 10.0
#include "struct.h"

extern FILE *out;
extern unsigned char buffer;
extern int buffer_pos;

struct pgm;
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);

void escrevebit(int bit);
void escrevebyte(unsigned char b);
void checagembits(void);

int lerbit(FILE *in);
unsigned char lerbyte(FILE *in);

unsigned char **converter_para_matriz(struct pgm img);
double media_simples(unsigned char **img, int x, int y, int tamanho);
double mse(unsigned char **img, int x, int y, int tamanho, double media);
double gradiente(unsigned char **img, int x, int y, int tamanho);
quadtree *construtortree(unsigned char **img, int x, int y,int tamanho, double limiteMSE);
void salvarArvore(quadtree *n);
void freeTree(quadtree *n);

#endif
