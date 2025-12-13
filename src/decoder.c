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

#include "../include/decodificador.h"
#include "../include/pgm.h"
#include "../include/manipuladorDeBits.h"
#include "../include/codificador.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("\nUso: %s <bitstream.bin> <saida.pgm>\n", argv[0]);
        exit(1);
    }
    const char *bitstream = argv[1];
    const char *saidaPGM = argv[2];

    FILE *f = fopen(bitstream, "rb");
    if (!f) {
        perror("Erro ao abrir bitstream");
        return 1;
    }

    int colunas, linhas, valor_max;
    if (fread(&colunas, sizeof(int), 1, f) != 1 ||
        fread(&linhas, sizeof(int), 1, f) != 1 ||
        fread(&valor_max, sizeof(int), 1, f) != 1) {
        fprintf(stderr, "Erro: metadados ausentes ou corrompidos no bitstream\n");
        fclose(f);
        return 1;
    }

    quadtree *mapa = reconstruirArvore(f);
    fclose(f);

    if (!mapa) {
        fprintf(stderr, "Erro ao reconstruir árvore a partir do bitstream\n");
        return 1;
    }

    unsigned char *pData = malloc((size_t)colunas * linhas * sizeof(unsigned char));
    if (!pData) {
        perror("Erro alocar memória para imagem");
        freeTree(mapa);
        return 1;
    }

    reconstruirImagem(mapa, pData, 0, 0, linhas, colunas, colunas);
    salvarPGM(saidaPGM, pData, colunas, linhas, valor_max);
    printf("Imagem reconstruída salva em %s\n", saidaPGM);

    free(pData);
    freeTree(mapa);
    return 0;
}
