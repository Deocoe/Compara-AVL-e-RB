#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RB.h"

void gerar_chaves_aleatorias(int *chaves, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        chaves[i] = rand() % (n * 10);
    }
}

void testar_insercao_rb(ArvoreRB *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        inserir_rb(arvore, chaves[i]);
    }
}

void testar_remocao_rb(ArvoreRB *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        remover_rb(arvore, chaves[i]);
    }
}

void testar_busca_rb(ArvoreRB *arvore, int *chaves, int n) {
    for (int i = 0; i < n; i++) {
        buscar_rb(arvore, chaves[i]);
    }
}

int main() {
    int N = 10000; // Número de chaves para teste
    int M = 1000; // Número de buscas aleatórias para teste

    ArvoreRB *arvore = criar_arvore_rb();
    int *chaves = (int*)malloc(N * sizeof(int));
    int *chaves_aleatorias = (int*)malloc(M * sizeof(int));

    for (int i = 0; i < N; i++) {
        chaves[i] = i + 1;
    }
    gerar_chaves_aleatorias(chaves_aleatorias, M);

    clock_t inicio, fim;

    // Testar inserção
    inicio = clock();
    testar_insercao_rb(arvore, chaves, N);
    fim = clock();
    printf("Tempo de inserção: %.8f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Rotações durante inserção: %d\n", arvore->contador_rotacoes);

    // Testar remoção
    inicio = clock();
    testar_remocao_rb(arvore, chaves, N);
    fim = clock();
    printf("Tempo de remoção: %.8f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Rotações durante remoção: %d\n", arvore->contador_rotacoes);

    // Testar busca
    inicio = clock();
    testar_busca_rb(arvore, chaves_aleatorias, M);
    fim = clock();
    printf("Tempo de busca: %.8f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    free(chaves);
    free(chaves_aleatorias);
    liberar_arvore_rb(arvore);

    return 0;
}
