// Exercício 1 — Árvore Binária de Busca (adaptado de Beecrowd 1195)
// Para cada caso de teste: insere N chaves em uma BST (na ordem dada)
// e imprime os percursos pré-ordem, em ordem e pós-ordem.
//
// Entrada : C (casos); para cada caso, N e depois N inteiros distintos.
// Saída   : "Case i:" seguido das linhas Pre.:, In..: e Post:, e uma linha em branco.
#include <cstdio>
#include <vector>
#include "BST.hpp"

// Imprime "rotulo: a b c" sem espaço sobrando no final.
static void imprimir(const char* rotulo, const std::vector<int>& v) {
    printf("%s", rotulo);
    for (size_t i = 0; i < v.size(); i++) printf(" %d", v[i]);
    printf("\n");
}

int main() {
    int casos;
    if (scanf("%d", &casos) != 1) return 0;
    for (int c = 1; c <= casos; c++) {
        int n;
        if (scanf("%d", &n) != 1) return 0;
        BST arvore;
        for (int i = 0; i < n; i++) {
            int x;
            if (scanf("%d", &x) != 1) return 0;
            arvore.inserir(x);              // O(h) por inserção
        }
        printf("Case %d:\n", c);
        imprimir("Pre.:", arvore.preOrdem());   // raiz, esquerda, direita
        imprimir("In..:", arvore.emOrdem());    // esquerda, raiz, direita (ordenado)
        imprimir("Post:", arvore.posOrdem());   // esquerda, direita, raiz
        printf("\n");
    }
    return 0;
}
