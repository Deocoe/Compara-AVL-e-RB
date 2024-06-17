#ifndef AVL_H
#define AVL_H

typedef struct NoAVL {
		int chave;
		struct NoAVL *esquerda;
		struct NoAVL *direita;
		int altura;
} NoAVL;

typedef struct ArvoreAVL {
		NoAVL *raiz;
		int contador_rotacoes;
} ArvoreAVL;

ArvoreAVL* criar_arvore_avl();
void inserir_avl(ArvoreAVL *arvore, int chave);
void remover_avl(ArvoreAVL *arvore, int chave);
NoAVL* buscar_avl(ArvoreAVL *arvore, int chave);
void liberar_arvore_avl(ArvoreAVL *arvore);

#endif

