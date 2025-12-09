#include "../include/codificador.h"
#include "../include/pgm.h"
#include "../include/decodificador.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    if (argc != 4){
        printf("uso:<%s> <entrada.pgm> <bitstream.bin> <saida.pgm>",argv[0]);
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

    unsigned char **matriz = converter_para_matriz(img);

    printf("Construindo quadtree (musiquinha de elevador)(limite = %d)...\n", LIMITE);
    quadtree *arvore = construtortree(matriz, 0, 0, img.r, LIMITE);

    FILE *fp = fopen(bitstream, "wb");
    if (!fp)
    {
        perror("Erro ao criar arquivo .bit");
        return 1;
    }
    salvarArvore(arvore, fp);
    fclose(fp);

    printf("Bitstream salvo com sucesso em %s!\n", bitstream);

    FILE *f = fopen(bitstream, "rb");
    if (f==NULL){
        perror("Erro ao abrir bitstream");
        exit(1);
    }
    quadtree *mapa = reconstruirArvore(f);
    fclose(f);
        
    unsigned char *pData = malloc(colunas * linhas * sizeof(unsigned char));
    
    reconstruirImagem(mapa, pData, 0, 0, colunas,colunas);
    salvarPGM(saidaPGM, pData, colunas, linhas, valor_max);
    printf("Imagem reconstruída salva em %s\n", saidaPGM);

    for (int i = 0; i < img.r; i++){ 
        free(matriz[i]);
    }
    free(matriz);
    free(pData);
    freeTree(arvore);
    freeTree(mapa);
    free(img.pData);
    return 0;
    }