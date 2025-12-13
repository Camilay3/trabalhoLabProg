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

#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include "struct.h"

quadtree* reconstruirArvore(FILE *bitstream);
void colorirBloco(unsigned char *img, int x, int y, int altura, int largura, unsigned char valor, int colunas);
void reconstruirImagem(quadtree *q, unsigned char *img, int x, int y, int altura, int largura, int colunas);
int salvarPGM(const char *nome,unsigned char *pData,int colunas, int linhas,int valor_max);

#endif
