#ifndef RB_H
#define RB_H

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRB {
		int chave;
		Cor cor;
		struct NoRB *esquerda, *direita, *pai;
} NoRB;

typedef struct ArvoreRB {
		NoRB *raiz;
		NoRB *nil;
		int contador_rotacoes;
} ArvoreRB;

ArvoreRB* criar_arvore_rb();
void inserir_rb(ArvoreRB *arvore, int chave);
void remover_rb(ArvoreRB *arvore, int chave);
NoRB* buscar_rb(ArvoreRB *arvore, int chave);
void liberar_arvore_rb(ArvoreRB *arvore);

#endif
