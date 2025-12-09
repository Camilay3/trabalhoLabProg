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

#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include "struct.h"

quadtree* reconstruirArvore(FILE *bitstream);
void reconstruirImagem(quadtree *q,unsigned char *img, int x, int y, int tamanho,int colunas);
int salvarPGM(const char *nome,unsigned char *pData,int colunas, int linhas,int valor_max);

#endif
