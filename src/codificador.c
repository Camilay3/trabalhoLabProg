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

double mediaSimples(unsigned char **img, int x, int y, int altura, int largura) {
    int soma = 0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) soma += img[x + i][y + j];
    }
    return (double)soma / (altura * largura);
}

double mse(unsigned char **img, int x, int y, int altura, int largura, double media) {
    double erro = 0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    }
    return erro / (altura * largura);
}

quadtree *construtorTree(unsigned char **img, int x, int y, int altura, int largura, double limite) {
    quadtree *node = malloc(sizeof(quadtree));
    if (!node) {
        perror("Erro ao alocar memória do quadtree");
        exit(3);
    }

    if (altura <= 0 || largura <= 0) {
        node->raiz = 0;
        node->valor = 0;
        node->no = node->ne = node->so = node->se = NULL;
        return node;
    }

    double media = mediaSimples(img, x, y, altura, largura);
    double erro = mse(img, x, y, altura, largura, media);

    if (erro <= limite || (altura == 1 && largura == 1)) {
        node->raiz = 0;
        node->valor = (unsigned char)(media + 0.5);
        node->no = node->ne = node->so = node->se = NULL;
        return node;
    }

    node->raiz = 1;
    int ha = altura / 2;
    int wa = largura / 2;

    node->no = construtorTree(img, x, y, ha, wa, limite);
    node->ne = construtorTree(img, x, y + wa, ha, largura - wa, limite);
    node->so = construtorTree(img, x + ha, y, altura - ha, wa, limite);
    node->se = construtorTree(img, x + ha, y + wa, altura - ha, largura - wa, limite);

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
