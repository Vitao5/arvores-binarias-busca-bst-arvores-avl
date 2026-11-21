// Exercício 3 — AVL e rotações (adaptado de HackerRank, "Self Balancing Tree")
// Insere N chaves em uma AVL e informa raiz, altura, quantas rotações de cada
// tipo foram necessárias e a árvore final por níveis.
//
// Entrada : N e depois N inteiros distintos.
// Saída   : Raiz, Altura, Rotacoes (EE, DD, ED, DE) e Por nivel.
#include <cstdio>
#include <vector>
#include "AVL.hpp"

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    AVL arvore;
    for (int i = 0; i < n; i++) {
        int x;
        if (scanf("%d", &x) != 1) return 0;
        arvore.inserir(x);      // insere e rebalanceia os ancestrais: O(log N)
    }
    std::vector<int> niveis = arvore.porNivel();   // o primeiro elemento é a raiz
    const EstatisticasAVL& e = arvore.estatisticas();
    printf("Raiz: %d\n", niveis.empty() ? -1 : niveis[0]);
    printf("Altura: %d\n", arvore.altura());
    printf("Rotacoes: EE=%d DD=%d ED=%d DE=%d\n", e.rotEE, e.rotDD, e.rotED, e.rotDE);
    printf("Por nivel:");
    for (size_t i = 0; i < niveis.size(); i++) printf(" %d", niveis[i]);
    printf("\n");
    return 0;
}
