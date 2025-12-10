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

#ifndef MANIPULADOR_H
#define MANIPULADOR_H

#include <stdio.h>

extern FILE *out;
extern unsigned char buffer;
extern int buffer_pos;

void escrevebit(int bit);
void escrevebyte(unsigned char b);
void checagembits(void);
int lerbit(FILE *in);
unsigned char lerbyte(FILE *in);

#endif
