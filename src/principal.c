#include "codificador.h"
#include "pgm.h"
#include "decodificador.h"
#include <stdio.h>
int main(int argc,char **argv){

//verificação
    if(argc != 4){
        pritf("uso:<%s> <entrada.pgm> <bitstream.bin> <saida.pgm>");
        exit(1);
    }

//leitor
FILE *entrada = argv[1];
void readPGMImage(pio, entrada);

//codificador
// int main(int argc, char *argv[]) {
//     if (argc != 4) {
//         printf("Uso: %s <entrada.pgm> <saida.bit> <limite>\n", argv[0]);
//         return 1;
//     }

//     char *entradaPGM = argv[1];
//     char *saidaBIT = argv[2];
//     double limite = atof(argv[3]);

//     struct pgm img;
//     readPGMImage(&img, entradaPGM);

//     if (img.r != img.c) {
//         fprintf(stderr, "Erro: imagem precisa ser quadrada!\n");
//         free(img.pData);
//         return 1;
//     }

//     unsigned char **matriz = converter_para_matriz(img);

//     printf("Construindo quadtree (limite = %.2f)...\n", limite);
//     quadtree *arvore = construtortree(matriz, 0, 0, img.r, limite);

//     FILE *fp = fopen(saidaBIT, "wb");
//     if (!fp) {
//         perror("Erro ao criar arquivo .bit");
//         return 1;
//     }
//     salvarArvore(arvore, fp);
//     fclose(fp);

//     printf("Bitstream salvo com sucesso em %s!\n", saidaBIT);

//     // liberar memória
//     for (int i = 0; i < img.r; i++)
//         free(matriz[i]);
//     free(matriz);
//     freeTree(arvore);
//     free(img.pData);

//     return 0;
// }


    //decodificador
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
    quadtree *mapa = reconstruirArvore(fp);
    fclose(fp);
    unsigned char *pData = malloc(colunas * linhas * sizeof(unsigned char));
    unsigned char **mat = malloc (linhas * sizeof(unsigned char*));
    for (int i = 0; i < linhas; i++) {
        *(mat +i) = pData + (i * colunas);
    }
    reconstruirImagem(mapa, mat, 0, 0, colunas);
    salvarPGM(saidaPGM, pData, colunas, linhas, valor_max);
    printf("Imagem reconstruída salva em %s\n", saidaPGM);
    free(mat);
    free(pData);
    return 0;
}