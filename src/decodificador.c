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

#include <stdio.h>
#include <stdlib.h>
#include "include/pgm.h"
#include "include/decodificador.h"
typedef struct quadtree {
    int raiz;                        
    unsigned char valor;             
    struct quadtree *no, *ne, *so, *se;
} quadtree;
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
void colorirBloco(unsigned char **img,int x, int y, int tam,unsigned char valor){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            img[x + i][y + j] = valor;
        }
    }

}
void reconstruirImagem(quadtree *q,unsigned char **img, int x, int y, int tamanho)
{
    if (q == NULL){ 
        return;
    }
    if (q->raiz == 0) {
        colorirBloco(img, x, y, tamanho, q->valor);
        return;
    }
    int h = tamanho / 2;
    if(q -> raiz ==1){ 
        reconstruirImagem(q->no, img, x,     y,     h);
        reconstruirImagem(q->ne, img, x,     y + h, h);
        reconstruirImagem(q->so, img, x + h, y,     h); 
        reconstruirImagem(q->se, img, x + h, y + h, h);
    }
}
int salvarPGM(const char *nome,unsigned char *pData,int colunas, int linhas,int valor_max){
    FILE *fp = fopen(nome, "wb");
    if (fp == NULL) {
        perror("Erro ao criar PGM");
        return 1;
    }
    fprintf(fp, "P5\n%d %d\n%d\n", colunas, linhas, valor_max);

    fwrite(pData, 1, colunas * linhas, fp);

    fclose(fp);
    return 0;
}
