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
#include "pgm.h"
#include "codificador.h"

// -----------------------------
// Estruturas
// -----------------------------

// -----------------------------
// Funções PGM
// -----------------------------
void readPGMImage(struct pgm *pio, char *filename) {
    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "rb"))) {
        perror("Erro ao abrir PGM");
        exit(1);
    }

    if ((ch = getc(fp)) != 'P') {
        puts("Imagem não está no formato PGM");
        exit(2);
    }

    pio->tipo = getc(fp) - '0';
    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#') {
        while ((ch = getc(fp)) != '\n');
    }

    fseek(fp, -1, SEEK_CUR);

    fscanf(fp, "%d %d", &pio->c, &pio->r);
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 1, SEEK_CUR);

    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));
    if (!pio->pData) {
        perror("malloc pData");
        exit(1);
    }

    if (pio->tipo == 5) { // PGM binário
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
    } else if (pio->tipo == 2) { // PGM ASCII
        for (int k = 0; k < pio->r * pio->c; k++)
            fscanf(fp, "%hhu", pio->pData + k);
    } else {
        puts("Formato PGM não suportado");
        exit(1);
    }

    fclose(fp);
}

void writePGMImage(struct pgm *pio, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao salvar PGM");
        exit(1);
    }

    fprintf(fp, "P5\n%d %d\n%d\n", pio->c, pio->r, pio->mv);
    fwrite(pio->pData, sizeof(unsigned char), pio->c * pio->r, fp);
    fclose(fp);
}

// -----------------------------
// Função auxiliar: converte pData → matriz 2D
// -----------------------------
unsigned char **converter_para_matriz(struct pgm img) {
    unsigned char **matriz = malloc(img.r * sizeof(unsigned char *));
    if (!matriz) {
        perror("malloc matriz");
        exit(1);
    }

    for (int i = 0; i < img.r; i++) {
        matriz[i] = malloc(img.c * sizeof(unsigned char));
        if (!matriz[i]) {
            perror("malloc linha");
            exit(1);
        }
        for (int j = 0; j < img.c; j++)
            matriz[i][j] = img.pData[i * img.c + j];
    }
    return matriz;
}

// -----------------------------
// Funções do codificador (quadtree)
// -----------------------------
double media_simples(unsigned char **img, int x, int y, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            soma += img[x + i][y + j];
    return (double)soma / (tamanho * tamanho);
}

double mse(unsigned char **img, int x, int y, int tamanho, double media) {
    double erro = 0;
    for (int i = 0; i < tamanho; i++){ 
        for (int j = 0; j < tamanho; j++) {
            double dif = img[x + i][y + j] - media;
            erro += dif * dif;
        }
    return erro / (tamanho * tamanho);
}

quadtree *construtortree(unsigned char **img, int x, int y, int tamanho, double limite) {
    quadtree *node = malloc(sizeof(quadtree));
    if (!node) {
        perror("malloc quadtree");
        exit(1);
    }

    double media = media_simples(img, x, y, tamanho);
    double erro = mse(img, x, y, tamanho, media);

    if (erro <= limite || tamanho == 1) {
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

// -----------------------------
// Salvar árvore em bitstream
// -----------------------------
void salvarArvore(quadtree *n, FILE *fp) {
    if (!n) return;

    if (n->raiz == 0) {
        fputc(0, fp);          // folha
        fputc(n->valor, fp);   // valor
        return;
    }

    fputc(1, fp); // nó interno
    salvarArvore(n->no, fp);
    salvarArvore(n->ne, fp);
    salvarArvore(n->so, fp);
    salvarArvore(n->se, fp);
}

// -----------------------------
// Liberar memória da árvore
// -----------------------------
void freeTree(quadtree *n) {
    if (!n) return;
    freeTree(n->no);
    freeTree(n->ne);
    freeTree(n->so);
    freeTree(n->se);
    free(n);
}

// -----------------------------
// MAIN
// -----------------------------
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <entrada.pgm> <saida.bit> <limite>\n", argv[0]);
        return 1;
    }

    char *entradaPGM = argv[1];
    char *saidaBIT = argv[2];
    double limite = atof(argv[3]);

    struct pgm img;
    readPGMImage(&img, entradaPGM);

    if (img.r != img.c) {
        fprintf(stderr, "Erro: imagem precisa ser quadrada!\n");
        free(img.pData);
        return 1;
    }

    unsigned char **matriz = converter_para_matriz(img);

    printf("Construindo quadtree (limite = %.2f)...\n", limite);
    quadtree *arvore = construtortree(matriz, 0, 0, img.r, limite);

    FILE *fp = fopen(saidaBIT, "wb");
    if (!fp) {
        perror("Erro ao criar arquivo .bit");
        return 1;
    }
    salvarArvore(arvore, fp);
    fclose(fp);

    printf("Bitstream salvo com sucesso em %s!\n", saidaBIT);

    // liberar memória
    for (int i = 0; i < img.r; i++)
        free(matriz[i]);
    free(matriz);
    freeTree(arvore);
    free(img.pData);

    return 0;
}