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

#ifndef PGM_H
#define PGM_H

#include <stdio.h>

struct pgm {
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);
void viewPGMImage(struct pgm *pio);

#endif
