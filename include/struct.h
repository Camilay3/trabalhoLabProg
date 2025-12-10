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

#ifndef STRUCT_H
#define STRUCT_H
typedef struct quadtree {
    int raiz;                        
    unsigned char valor;             
    struct quadtree *no, *ne, *so, *se;  
} quadtree;

#endif
