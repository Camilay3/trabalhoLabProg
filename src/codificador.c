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
#include <math.h>
#include "../include/struct.h"
#include "../include/pgm.h"
#include "../include/codificador.h"
#include "../include/manipuladorDeBits.h"

unsigned char **converterParaMatriz(struct pgm img) {
    unsigned char **matriz = malloc(img.r * sizeof(unsigned char *));
    if (!matriz){
        perror("Erro alocar memória da matriz");
        exit(1);
    }

    for (int i = 0; i < img.r; i++) {
        if (!(matriz[i] = malloc(img.c * sizeof(unsigned char)))) {
            perror("Erro alocar memória da matriz(linha)");
            exit(2);
        }
        for (int j = 0; j < img.c; j++) matriz[i][j] = img.pData[i * img.c + j];
    }
    return matriz;
}

double mediaSimples(unsigned char **img, int x, int y, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) soma += img[x + i][y + j];
    }
    return (double)soma / (tamanho * tamanho);
}

double mse(unsigned char **img, int x, int y, int tamanho, double media) {
    double erro = 0;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    }
    return erro / (tamanho * tamanho);
}

quadtree *construtorTree(unsigned char **img, int x, int y, int tamanho, double limite) {
    quadtree *node = malloc(sizeof(quadtree));
    if (!node) {
        perror("Erro ao alocar memória do quadtree");
        exit(3);
    }

    double media = mediaSimples(img, x, y, tamanho);
    double erro = mse(img, x, y, tamanho, media);

    if (erro <= limite || tamanho == 1) {
        node->raiz = 0;
        node->valor = (unsigned char)(media + 0.5);
        node->no = node->ne = node->so = node->se = NULL;
        return node;
    }

    node->raiz = 1;
    int h = tamanho / 2;
    
    node->no = construtorTree(img, x, y, h, limite);
    node->ne = construtorTree(img, x, y + h, h, limite);
    node->so = construtorTree(img, x + h, y, h, limite);
    node->se = construtorTree(img, x + h, y + h, h, limite);

    return node;
}

void salvarArvore(quadtree *n) {
    if (!n) return;

    if (n->raiz == 0){
        escrevebit(0);
        escrevebyte(n->valor);
        return;
    }

    escrevebit(1);
    salvarArvore(n->no);
    salvarArvore(n->ne);
    salvarArvore(n->so);
    salvarArvore(n->se);
}

void freeTree(quadtree *n) {
    if (!n) return;
    freeTree(n->no);
    freeTree(n->ne);
    freeTree(n->so);
    freeTree(n->se);
    free(n);
}
