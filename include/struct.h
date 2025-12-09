#ifndef STRUCT_H
#define STRUCT_H
typedef struct quadtree {
    int raiz;                        
    unsigned char valor;             
    struct quadtree *no, *ne, *so, *se;  
} quadtree;

#endif