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
