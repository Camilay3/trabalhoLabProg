#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

typedef struct quadtree {
    int raiz;                        
    unsigned char valor;             
    struct quadtree *no, *ne, *so, *se;
} quadtree;

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("Uso: %s <input.pgm> <bitstream> <saida.pgm>\n", argv[0]);
        return 1;
    }

    const char *inputPGM   = argv[1];
    const char *bitstream  = argv[2];
    const char *saidaPGM   = argv[3];

    struct pgm img;
    readPGMImage(&img, (char*)inputPGM);

    int colunas   = img.c;
    int linhas   = img.r;
    int valor_max = img.mv;

    FILE *fp = fopen(bitstream, "rb");
    if (!fp) {
        perror("Erro ao abrir bitstream");
        return 1;
    }

    //função reconstruir arvore

    quadtree *mapa = reconstruirArvore(fp);
    fclose(fp);

    unsigned char *pData = malloc(colunas * linhas * sizeof(unsigned char));
    unsigned char **mat = malloc (linhas * sizeof(unsigned char*));
    for (int i = 0; i < linhas; i++) {
        *(mat +i) = pData + (i * colunas);
    }

    //funçaõ reconstruir imagem

    //função salvar pgm

    printf("Imagem reconstruída salva em %s\n", saidaPGM);
    free(mat);
    free(pData);
    return 0;
}

quadtree* reconstruirArvore(FILE *bitstream)
{
    int tipo = fgetc(bitstream);
    if (tipo == EOF) {
        fprintf(stderr, "Erro: fim inesperado no bitstream.\n");
        return NULL;
    }

    quadtree *n = malloc(sizeof(quadtree));
    if (!n) {
        perror("malloc");
        return NULL;
    }

    n->no = n->ne = n->so = n->se = NULL;

    if (tipo == 0 || tipo == '0') { //ver se essa verificação é necessaria
        
        n->raiz = 0;
        int v = fgetc(bitstream);
        if (v == EOF) {
            fprintf(stderr, "Erro: valor de folha ausente.\n");
            free(n);
            return NULL;
        }
        n->valor = (unsigned char)v;
        return n;
    }
    else if (tipo == 1 || tipo == '1') {

        n->raiz = 1;
        n->no = reconstruirArvore(bitstream);
        n->ne = reconstruirArvore(bitstream);
        n->so = reconstruirArvore(bitstream);
        n->se = reconstruirArvore(bitstream);
        return n;
    }
    else {
        fprintf(stderr, "Erro: byte inválido na árvore: %d\n", tipo);
        free(n);
        return NULL;
    }
}
