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

#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdio.h>
#define LIMITE 35.00 // 21.205 para imagens normais
#include "struct.h"

struct pgm;
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);

unsigned char **converterParaMatriz(struct pgm img);
double mediaSimples(unsigned char **img, int x, int y, int altura, int largura);
double mse(unsigned char **img, int x, int y, int altura, int largura, double media);
quadtree *construtorTree(unsigned char **img, int x, int y, int altura, int largura, double limite);
void salvarArvore(quadtree *n);
void freeTree(quadtree *n);

#endif
