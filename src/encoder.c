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

#include "../include/codificador.h"
#include "../include/pgm.h"
#include "../include/manipuladorDeBits.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("\nUso: %s <entrada.pgm> <bitstream.bin>\n", argv[0]);
        exit(1);
    }
    const char *inputPGM = argv[1];
    const char *bitstream = argv[2];

    struct pgm img;
    readPGMImage(&img, (char *)inputPGM);

    int colunas = img.c;
    int linhas = img.r;
    int valor_max = img.mv;

    unsigned char **matriz = converterParaMatriz(img);

    printf("Construindo quadtree (limite = %.4f)...\n", LIMITE);
    quadtree *arvore = construtorTree(matriz, 0, 0, linhas, colunas, LIMITE);

    out = fopen(bitstream, "wb");
    if (!out) {
        perror("Erro ao criar arquivo .bit");
        return 1;
    }

    if (fwrite(&colunas, sizeof(int), 1, out) != 1 ||
        fwrite(&linhas, sizeof(int), 1, out) != 1 ||
        fwrite(&valor_max, sizeof(int), 1, out) != 1) {
        perror("Erro ao escrever metadados no bitstream");
        fclose(out);
        return 1;
    }

    buffer = 0;
    buffer_pos = 0;
    salvarArvore(arvore);
    checagembits();
    fclose(out);

    printf("Bitstream salvo com sucesso em %s!\n", bitstream);

    for (int i = 0; i < img.r; i++) free(matriz[i]);
    free(matriz);
    freeTree(arvore);
    free(img.pData);
    return 0;
}
