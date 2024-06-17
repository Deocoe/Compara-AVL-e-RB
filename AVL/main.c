#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#define N 10000
#define M 1000

void gerar_chaves_aleatorias(int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        chaves[i] = rand() % (2 * n);
    }
}

void testar_insercao_avl(ArvoreAVL *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        inserir_avl(arvore, chaves[i]);
    }
}

void testar_remocao_avl(ArvoreAVL *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        remover_avl(arvore, chaves[i]);
    }
}

void testar_busca_avl(ArvoreAVL *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        buscar_avl(arvore, chaves[i]);
    }
}

int main() {
    srand(time(NULL));

    ArvoreAVL *arvore = criar_arvore_avl();
    int *chaves = (int*)malloc(N * sizeof(int));
    int *chaves_aleatorias = (int*)malloc(M * sizeof(int));

    for (int i = 0; i < N; i++) {
        chaves[i] = i + 1;
    }
    gerar_chaves_aleatorias(chaves_aleatorias, M);

    clock_t inicio, fim;

    // Testar inserção
    inicio = clock();
    testar_insercao_avl(arvore, chaves, N);
    fim = clock();
    printf("Tempo de inserção: %.2f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Rotações durante inserção: %d\n", arvore->contador_rotacoes);

    // Testar remoção
    inicio = clock();
    testar_remocao_avl(arvore, chaves, N);
    fim = clock();
    printf("Tempo de remoção: %.2f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Rotações durante remoção: %d\n", arvore->contador_rotacoes);

    // Testar busca
    inicio = clock();
    testar_busca_avl(arvore, chaves_aleatorias, M);
    fim = clock();
    printf("Tempo de busca: %.2f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    free(chaves);
    free(chaves_aleatorias);
    liberar_arvore_avl(arvore);

    return 0;
}

