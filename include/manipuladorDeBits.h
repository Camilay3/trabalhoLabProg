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
