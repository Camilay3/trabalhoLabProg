/**************************************************************************
Alunos: 
	- Camila Azevedo
	- Mariana Silva
	- Andrey Pereira
	- Mateus Pinheiro

Avaliacao 04: Trabalho Final
04.505.23 − 2025.2 − Prof. Daniel Ferreira
Compilador: gcc (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0
***************************************************************************************/

#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdio.h>
#define LIMITE 21.205
#include "struct.h"

struct pgm;
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);

unsigned char **converterParaMatriz(struct pgm img);
double mediaSimples(unsigned char **img, int x, int y, int tamanho);
double mse(unsigned char **img, int x, int y, int tamanho, double media);
quadtree *construtorTree(unsigned char **img, int x, int y,int tamanho, double limite);
void salvarArvore(quadtree *n);
void freeTree(quadtree *n);

#endif
