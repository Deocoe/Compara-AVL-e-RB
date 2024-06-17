#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int max(int a, int b) {
		return (a > b) ? a : b;
}

int altura(NoAVL *no) {
		if (no == NULL)
				return 0;
		return no->altura;
}

NoAVL* novo_no(int chave) {
		NoAVL *no = (NoAVL*)malloc(sizeof(NoAVL));
		no->chave = chave;
		no->esquerda = NULL;
		no->direita = NULL;
		no->altura = 1; // Novo nó é inicialmente adicionado na folha
		return no;
}

NoAVL* rotacao_direita(NoAVL *y) {
		NoAVL *x = y->esquerda;
		NoAVL *T2 = x->direita;

		// Realizar rotação
		x->direita = y;
		y->esquerda = T2;

		// Atualizar alturas
		y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
		x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

		return x;
}

NoAVL* rotacao_esquerda(NoAVL *x) {
		NoAVL *y = x->direita;
		NoAVL *T2 = y->esquerda;

		// Realizar rotação
		y->esquerda = x;
		x->direita = T2;

		// Atualizar alturas
		x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
		y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

		return y;
}

int fator_balanceamento(NoAVL *no) {
		if (no == NULL)
				return 0;
		return altura(no->esquerda) - altura(no->direita);
}

NoAVL* inserir_no(NoAVL* no, int chave, int *contador_rotacoes) {
		if (no == NULL)
				return novo_no(chave);

		if (chave < no->chave)
				no->esquerda = inserir_no(no->esquerda, chave, contador_rotacoes);
		else if (chave > no->chave)
				no->direita = inserir_no(no->direita, chave, contador_rotacoes);
		else
				return no;

		no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

		int balance = fator_balanceamento(no);

		if (balance > 1 && chave < no->esquerda->chave) {
				(*contador_rotacoes)++;
				return rotacao_direita(no);
		}

		if (balance < -1 && chave > no->direita->chave) {
				(*contador_rotacoes)++;
				return rotacao_esquerda(no);
		}

		if (balance > 1 && chave > no->esquerda->chave) {
				no->esquerda = rotacao_esquerda(no->esquerda);
				(*contador_rotacoes)++;
				return rotacao_direita(no);
		}

		if (balance < -1 && chave < no->direita->chave) {
				no->direita = rotacao_direita(no->direita);
				(*contador_rotacoes)++;
				return rotacao_esquerda(no);
		}

		return no;
}

NoAVL* remover_no(NoAVL* raiz, int chave, int *contador_rotacoes) {
		if (raiz == NULL)
				return raiz;

		if (chave < raiz->chave)
				raiz->esquerda = remover_no(raiz->esquerda, chave, contador_rotacoes);
		else if (chave > raiz->chave)
				raiz->direita = remover_no(raiz->direita, chave, contador_rotacoes);
		else {
				if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
						NoAVL *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

						if (temp == NULL) {
								temp = raiz;
								raiz = NULL;
						} else
								*raiz = *temp;
						free(temp);
				} else {
						NoAVL* temp = raiz->direita;
						while (temp->esquerda != NULL)
								temp = temp->esquerda;
						raiz->chave = temp->chave;
						raiz->direita = remover_no(raiz->direita, temp->chave, contador_rotacoes);
				}
		}

		if (raiz == NULL)
				return raiz;

		raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

		int balance = fator_balanceamento(raiz);

		if (balance > 1 && fator_balanceamento(raiz->esquerda) >= 0) {
				(*contador_rotacoes)++;
				return rotacao_direita(raiz);
		}

		if (balance > 1 && fator_balanceamento(raiz->esquerda) < 0) {
				raiz->esquerda = rotacao_esquerda(raiz->esquerda);
				(*contador_rotacoes)++;
				return rotacao_direita(raiz);
		}

		if (balance < -1 && fator_balanceamento(raiz->direita) <= 0) {
				(*contador_rotacoes)++;
				return rotacao_esquerda(raiz);
		}

		if (balance < -1 && fator_balanceamento(raiz->direita) > 0) {
				raiz->direita = rotacao_direita(raiz->direita);
				(*contador_rotacoes)++;
				return rotacao_esquerda(raiz);
		}

		return raiz;
}

NoAVL* buscar_avl(ArvoreAVL *arvore, int chave) {
		NoAVL *atual = arvore->raiz;
		while (atual != NULL && atual->chave != chave) {
				if (chave < atual->chave)
						atual = atual->esquerda;
				else
						atual = atual->direita;
		}
		return atual;
}

ArvoreAVL* criar_arvore_avl() {
		ArvoreAVL *arvore = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
		arvore->raiz = NULL;
		arvore->contador_rotacoes = 0;
		return arvore;
}

void inserir_avl(ArvoreAVL *arvore, int chave) {
		arvore->raiz = inserir_no(arvore->raiz, chave, &arvore->contador_rotacoes);
}

void remover_avl(ArvoreAVL *arvore, int chave) {
		arvore->raiz = remover_no(arvore->raiz, chave, &arvore->contador_rotacoes);
}

void liberar_no(NoAVL *no) {
		if (no == NULL)
				return;
		liberar_no(no->esquerda);
		liberar_no(no->direita);
		free(no);
}

void liberar_arvore_avl(ArvoreAVL *arvore) {
		liberar_no(arvore->raiz);
		free(arvore);
}
