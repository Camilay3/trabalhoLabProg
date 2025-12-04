#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct quadtree {
    int raiz;
    unsigned char valor;
    struct quadtree *no, *ne, *so, *se;
} quadtree;


double media_simples(unsigned char **img, int x, int y, int tamanho){
    int soma = 0;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            soma += img[x + i][y + j];
        }
    }

    return (double)soma / (tamanho * tamanho);
}


double mse(unsigned char **img, int x, int y, int tamanho, double media){
    double erro = 0;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    }

    return erro / (tamanho * tamanho);
}


quadtree* construtortree(unsigned char **img, int x, int y, int tamanho, double limite){
    quadtree *node = malloc(sizeof(quadtree));
    if(!node){
        perror("malloc");
        exit(1);
    }

    double media = media_simples(img, x, y, tamanho);
    double erro  = mse(img, x, y, tamanho, media);

    // NÓ FOLHA
    if (erro <= limite || tamanho == 1){
        node->raiz = 0;               // folha
        node->valor = (unsigned char)(media + 0.5);
        node->no = node->ne = node->so = node->se = NULL;
        //bitsream()
        return node;
    }

    // NÓ INTERNO - dividir
    node->raiz = 1;
    //bitstream()
    int h = tamanho / 2;
    node->no = construtortree(img, x,     y,     h, limite);
    node->ne = construtortree(img, x,     y + h, h, limite);
    node->so = construtortree(img, x + h, y,     h, limite);
    node->se = construtortree(img, x + h, y + h, h, limite);

    return node;
}