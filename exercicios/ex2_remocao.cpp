// Exercício 2 — Remoção em BST (adaptado de LeetCode 450, "Delete Node in a BST")
// Constrói uma BST, executa uma sequência de remoções (por cópia do sucessor)
// e mostra o resultado de cada uma, além da árvore final.
//
// Entrada : N, N chaves a inserir; M, M chaves a remover.
// Saída   : para cada remoção "Remover k: ok" ou "Remover k: nao encontrada";
//           depois "Em ordem: ..." e "Por nivel: ..." da árvore final.
#include <cstdio>
#include <vector>
#include "BST.hpp"

static void imprimir(const char* rotulo, const std::vector<int>& v) {
    printf("%s", rotulo);
    for (size_t i = 0; i < v.size(); i++) printf(" %d", v[i]);
    printf("\n");
}

int main() {
    int n, m;
    if (scanf("%d", &n) != 1) return 0;
    BST arvore;
    for (int i = 0; i < n; i++) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        arvore.inserir(x);
    }
    if (scanf("%d", &m) != 1) return 0;
    for (int i = 0; i < m; i++) {
        int k;
        if (scanf("%d", &k) != 1) return 0;
        // 0 ou 1 filho: o filho sobe; 2 filhos: copia o sucessor e remove o sucessor.
        bool removeu = arvore.removerPorCopia(k);
        printf("Remover %d: %s\n", k, removeu ? "ok" : "nao encontrada");
    }
    imprimir("Em ordem:", arvore.emOrdem());
    imprimir("Por nivel:", arvore.porNivel());
    return 0;
}
