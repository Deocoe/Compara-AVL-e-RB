#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

NoRB* novo_no_rb(ArvoreRB *arvore, int chave) {
		NoRB *no = (NoRB*)malloc(sizeof(NoRB));
		no->chave = chave;
		no->cor = VERMELHO;
		no->esquerda = no->direita = no->pai = arvore->nil;
		return no;
}

ArvoreRB* criar_arvore_rb() {
		ArvoreRB *arvore = (ArvoreRB*)malloc(sizeof(ArvoreRB));
		arvore->nil = (NoRB*)malloc(sizeof(NoRB));
		arvore->nil->cor = PRETO;
		arvore->raiz = arvore->nil;
		arvore->contador_rotacoes = 0;
		return arvore;
}

void rotacao_esquerda(ArvoreRB *arvore, NoRB *x) {
		NoRB *y = x->direita;
		x->direita = y->esquerda;
		if (y->esquerda != arvore->nil) {
				y->esquerda->pai = x;
		}
		y->pai = x->pai;
		if (x->pai == arvore->nil) {
				arvore->raiz = y;
		} else if (x == x->pai->esquerda) {
				x->pai->esquerda = y;
		} else {
				x->pai->direita = y;
		}
		y->esquerda = x;
		x->pai = y;
		arvore->contador_rotacoes++;
}

void rotacao_direita(ArvoreRB *arvore, NoRB *y) {
		NoRB *x = y->esquerda;
		y->esquerda = x->direita;
		if (x->direita != arvore->nil) {
				x->direita->pai = y;
		}
		x->pai = y->pai;
		if (y->pai == arvore->nil) {
				arvore->raiz = x;
		} else if (y == y->pai->direita) {
				y->pai->direita = x;
		} else {
				y->pai->esquerda = x;
		}
		x->direita = y;
		y->pai = x;
		arvore->contador_rotacoes++;
}

void corrigir_insercao_rb(ArvoreRB *arvore, NoRB *z) {
		while (z->pai->cor == VERMELHO) {
				if (z->pai == z->pai->pai->esquerda) {
						NoRB *y = z->pai->pai->direita;
						if (y->cor == VERMELHO) {
								z->pai->cor = PRETO;
								y->cor = PRETO;
								z->pai->pai->cor = VERMELHO;
								z = z->pai->pai;
						} else {
								if (z == z->pai->direita) {
										z = z->pai;
										rotacao_esquerda(arvore, z);
								}
								z->pai->cor = PRETO;
								z->pai->pai->cor = VERMELHO;
								rotacao_direita(arvore, z->pai->pai);
						}
				} else {
						NoRB *y = z->pai->pai->esquerda;
						if (y->cor == VERMELHO) {
								z->pai->cor = PRETO;
								y->cor = PRETO;
								z->pai->pai->cor = VERMELHO;
								z = z->pai->pai;
						} else {
								if (z == z->pai->esquerda) {
										z = z->pai;
										rotacao_direita(arvore, z);
								}
								z->pai->cor = PRETO;
								z->pai->pai->cor = VERMELHO;
								rotacao_esquerda(arvore, z->pai->pai);
						}
				}
		}
		arvore->raiz->cor = PRETO;
}

void inserir_rb(ArvoreRB *arvore, int chave) {
		NoRB *z = novo_no_rb(arvore, chave);
		NoRB *y = arvore->nil;
		NoRB *x = arvore->raiz;

		while (x != arvore->nil) {
				y = x;
				if (z->chave < x->chave) {
						x = x->esquerda;
				} else {
						x = x->direita;
				}
		}

		z->pai = y;
		if (y == arvore->nil) {
				arvore->raiz = z;
		} else if (z->chave < y->chave) {
				y->esquerda = z;
		} else {
				y->direita = z;
		}

		z->esquerda = arvore->nil;
		z->direita = arvore->nil;
		z->cor = VERMELHO;

		corrigir_insercao_rb(arvore, z);
}

void corrigir_remocao_rb(ArvoreRB *arvore, NoRB *x) {
		while (x != arvore->raiz && x->cor == PRETO) {
				if (x == x->pai->esquerda) {
						NoRB *w = x->pai->direita;
						if (w->cor == VERMELHO) {
								w->cor = PRETO;
								x->pai->cor = VERMELHO;
								rotacao_esquerda(arvore, x->pai);
								w = x->pai->direita;
						}
						if (w->esquerda->cor == PRETO && w->direita->cor == PRETO) {
								w->cor = VERMELHO;
								x = x->pai;
						} else {
								if (w->direita->cor == PRETO) {
										w->esquerda->cor = PRETO;
										w->cor = VERMELHO;
										rotacao_direita(arvore, w);
										w = x->pai->direita;
								}
								w->cor = x->pai->cor;
								x->pai->cor = PRETO;
								w->direita->cor = PRETO;
								rotacao_esquerda(arvore, x->pai);
								x = arvore->raiz;
						}
				} else {
						NoRB *w = x->pai->esquerda;
						if (w->cor == VERMELHO) {
								w->cor = PRETO;
								x->pai->cor = VERMELHO;
								rotacao_direita(arvore, x->pai);
								w = x->pai->esquerda;
						}
						if (w->direita->cor == PRETO && w->esquerda->cor == PRETO) {
								w->cor = VERMELHO;
								x = x->pai;
						} else {
								if (w->esquerda->cor == PRETO) {
										w->direita->cor = PRETO;
										w->cor = VERMELHO;
										rotacao_esquerda(arvore, w);
										w = x->pai->esquerda;
								}
								w->cor = x->pai->cor;
								x->pai->cor = PRETO;
								w->esquerda->cor = PRETO;
								rotacao_direita(arvore, x->pai);
								x = arvore->raiz;
						}
				}
		}
		x->cor = PRETO;
}

void substituir_no_rb(ArvoreRB *arvore, NoRB *u, NoRB *v) {
		if (u->pai == arvore->nil) {
				arvore->raiz = v;
		} else if (u == u->pai->esquerda) {
				u->pai->esquerda = v;
		} else {
				u->pai->direita = v;
		}
		v->pai = u->pai;
}

NoRB* minimo_rb(ArvoreRB *arvore, NoRB *x) {
		while (x->esquerda != arvore->nil) {
				x = x->esquerda;
		}
		return x;
}

void remover_rb(ArvoreRB *arvore, int chave) {
		NoRB *z = buscar_rb(arvore, chave);
		if (z == arvore->nil) {
				return;
		}

		NoRB *y = z;
		NoRB *x;
		Cor cor_original_y = y->cor;

		if (z->esquerda == arvore->nil) {
				x = z->direita;
				substituir_no_rb(arvore, z, z->direita);
		} else if (z->direita == arvore->nil) {
				x = z->esquerda;
				substituir_no_rb(arvore, z, z->esquerda);
		} else {
				y = minimo_rb(arvore, z->direita);
				cor_original_y = y->cor;
				x = y->direita;
				if (y->pai == z) {
						x->pai = y;
				} else {
						substituir_no_rb(arvore, y, y->direita);
						y->direita = z->direita;
						y->direita->pai = y;
				}
				substituir_no_rb(arvore, z, y);
				y->esquerda = z->esquerda;
				y->esquerda->pai = y;
				y->cor = z->cor;
		}

		if (cor_original_y == PRETO) {
				corrigir_remocao_rb(arvore, x);
		}
		free(z);
}

NoRB* buscar_rb(ArvoreRB *arvore, int chave) {
		NoRB *no = arvore->raiz;
		while (no != arvore->nil && chave != no->chave) {
				if (chave < no->chave) {
						no = no->esquerda;
				} else {
						no = no->direita;
				}
		}
		return no;
}

void liberar_no_rb(ArvoreRB *arvore, NoRB *no) {
		if (no != arvore->nil) {
				liberar_no_rb(arvore, no->esquerda);
				liberar_no_rb(arvore, no->direita);
				free(no);
		}
}

void liberar_arvore_rb(ArvoreRB *arvore) {
		liberar_no_rb(arvore, arvore->raiz);
		free(arvore->nil);
		free(arvore);
}
