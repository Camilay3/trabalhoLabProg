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

#include <stdio.h>
#include <stdlib.h>
#include "../include/struct.h"
#include "../include/pgm.h"
#include "../include/decodificador.h"
#include "../include/codificador.h"
#include "../include/manipuladorDeBits.h"

quadtree *reconstruirArvore(FILE *bitstream){
    int tipo = lerbit(bitstream);
    if (tipo == -1) {
        fprintf(stderr, "Erro: fim inesperado no bitstream.\n");
        return NULL;
    }

    quadtree *n = malloc(sizeof(quadtree));
    if (n == NULL){
        perror("Erro ao alocar memória");
        return NULL;
    }

    n->no = n->ne = n->so = n->se = NULL;

    if (tipo == 0){
        n->raiz = 0;
        int v = lerbyte(bitstream);
        if (v == EOF) {
            fprintf(stderr, "Erro: valor de folha ausente.\n");
            free(n);
            return NULL;
        }
        n->valor = (unsigned char)v;
        return n;
    } else if (tipo == 1){
        n->raiz = 1;
        n->no = reconstruirArvore(bitstream);
        n->ne = reconstruirArvore(bitstream);
        n->so = reconstruirArvore(bitstream);
        n->se = reconstruirArvore(bitstream);
        return n;
    } else{
        fprintf(stderr, "Erro: byte inválido na árvore: %d\n", tipo);
        free(n);
        return NULL;
    }
}

void reconstruirImagem(quadtree *q,unsigned char *img, int x, int y, int tamanho,int colunas){
    if (q == NULL) return;
    if (q->raiz == 0) {
        colorirBloco(img, x, y, tamanho, q->valor,colunas);
        return;
    }
    int h = tamanho / 2;
    if(q->raiz ==1){ 
        reconstruirImagem(q->no, img, x,     y,     h,colunas);
        reconstruirImagem(q->ne, img, x,     y + h, h,colunas);
        reconstruirImagem(q->so, img, x + h, y,     h,colunas); 
        reconstruirImagem(q->se, img, x + h, y + h, h,colunas);
    }
}

void colorirBloco(unsigned char *img,int x, int y, int tam,unsigned char valor,int colunas){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            *(img + (x + i) * colunas + (y + j)) = valor;
        }
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
