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
#include <math.h>
#include "../include/struct.h"
#include "../include/pgm.h"
#include "../include/codificador.h"

FILE *out = NULL;
unsigned char buffer = 0;
int buffer_pos = 0;


// Escreve 1 bit
void escrevebit(int bit) {
    buffer = (buffer << 1) | (bit & 1);
    buffer_pos++;
    if (buffer_pos == 8) {
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

// Escreve 1 byte
void escrevebyte(unsigned char b) {
    for(int i =7; i>= 0;i--){
        int bit = (b >> i )& 1;
        escrevebit(bit);
    }
}

// Finaliza escrita, grava último byte parcial
void checagembits() {
    if (buffer_pos > 0) {
        buffer <<= (8 - buffer_pos);
        fputc(buffer, out);
        buffer = 0;
        buffer_pos = 0;
    }
}

// Lê 1 bit do bitstream
int lerbit(FILE *in) {
    static unsigned char rbuffer = 0;
    static int rbuffer_pos = 0;

    if (rbuffer_pos == 0) {
        int c = fgetc(in);
        if (c == EOF)
            return -1; // sinaliza fim de arquivo
        rbuffer = (unsigned char)c;
        rbuffer_pos = 8;
    }

    int bit = (rbuffer >> (rbuffer_pos - 1)) & 1;
    rbuffer_pos--;
    return bit;
}

// Lê 1 byte do bitstream
unsigned char lerbyte(FILE *in) {
    unsigned char b = 0;
    for (int i = 0; i < 8; i++) {
        int bit = lerbit(in);
        if (bit == -1) {
            fprintf(stderr, "Erro: fim inesperado no bitstream ao ler byte.\n");
            exit(1);
        }
        b = (b << 1) | (bit & 1);
    }
    return b;
}


unsigned char **converter_para_matriz(struct pgm img)
{
    unsigned char **matriz = malloc(img.r * sizeof(unsigned char *));
    if (!matriz)
    {
        perror("malloc matriz");
        exit(1);
    }

    for (int i = 0; i < img.r; i++)
    {
        matriz[i] = malloc(img.c * sizeof(unsigned char));
        if (!matriz[i])
        {
            perror("malloc linha");
            exit(1);
        }
        for (int j = 0; j < img.c; j++)
            matriz[i][j] = img.pData[i * img.c + j];
    }
    return matriz;
}
// Funções do codificador (quadtree)
double media_simples(unsigned char **img, int x, int y, int tamanho)
{
    int soma = 0;
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            soma += img[x + i][y + j];
    return (double)soma / (tamanho * tamanho);
}
double mse(unsigned char **img, int x, int y, int tamanho, double media)
{
    double erro = 0;
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    }
    return erro / (tamanho * tamanho);
}
quadtree *construtortree(unsigned char **img, int x, int y, int tamanho, double limite)
{
    quadtree *node = malloc(sizeof(quadtree));
    if (!node)
    {
        perror("malloc quadtree");
        exit(1);
    }

    double media = media_simples(img, x, y, tamanho);
    double erro = mse(img, x, y, tamanho, media);

    if (erro <= limite || tamanho <= 1)
    {
        node->raiz = 0;
        node->valor = (unsigned char)(media + 0.5);
        node->no = node->ne = node->so = node->se = NULL;
        return node;
    }

    node->raiz = 1;
    int h = tamanho / 2;

    node->no = construtortree(img, x, y, h, limite);
    node->ne = construtortree(img, x, y + h, h, limite);
    node->so = construtortree(img, x + h, y, h, limite);
    node->se = construtortree(img, x + h, y + h, h, limite);

    return node;
}
// Salvar árvore em bitstream
void salvarArvore(quadtree *n)
{
    if (!n)
        return;

    if (n->raiz == 0)
    {
        escrevebit(0);      // folha
        escrevebyte(n->valor); // valor
        return;
    }

    escrevebit(1); // nó interno
    salvarArvore(n->no);
    salvarArvore(n->ne);
    salvarArvore(n->so);
    salvarArvore(n->se);
}
// Liberar memória da árvore
void freeTree(quadtree *n)
{
    if (!n)
        return;
    freeTree(n->no);
    freeTree(n->ne);
    freeTree(n->so);
    freeTree(n->se);
    free(n);
}