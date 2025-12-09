#include "../include/codificador.h"
#include "../include/pgm.h"
#include "../include/decodificador.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("uso:<%s> <entrada.pgm> <bitstream.bin> <saida.pgm>", argv[0]);
        exit(1);
    }
    const char *inputPGM = argv[1];
    const char *bitstream = argv[2];
    const char *saidaPGM = argv[3];

    struct pgm img;
    readPGMImage(&img, (char *)inputPGM);

    int colunas = img.c;
    int linhas = img.r;
    int valor_max = img.mv;

    unsigned char **matriz = converterParaMatriz(img);

    printf("Construindo quadtree (musiquinha de elevador)(limite = %.4f)...\n", LIMITE);
    quadtree *arvore = construtorTree(matriz, 0, 0, img.r, LIMITE);

    out = fopen(bitstream, "wb");
    if (!out) {
        perror("Erro ao criar arquivo .bit");
        return 1;
    }
    buffer = 0;
    buffer_pos = 0;
    salvarArvore(arvore);
    checagembits();
    fclose(out);

    printf("Bitstream salvo com sucesso em %s!\n", bitstream);

    FILE *f = fopen(bitstream, "rb");
    if (!f) {
        perror("Erro ao abrir bitstream");
        return 1;
    }
    quadtree *mapa = reconstruirArvore(f);
    fclose(f);

    unsigned char *pData = malloc(colunas * linhas * sizeof(unsigned char));
    reconstruirImagem(mapa, pData, 0, 0, colunas,colunas);
    salvarPGM(saidaPGM, pData, colunas, linhas, valor_max);
    printf("Imagem reconstruída salva em %s\n", saidaPGM);

    for (int i = 0; i < img.r; i++)free(matriz[i]);
    free(matriz);
    free(pData);
    freeTree(arvore);
    freeTree(mapa);
    free(img.pData);
    return 0;
}
