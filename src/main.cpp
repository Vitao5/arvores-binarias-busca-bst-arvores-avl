// Demonstração das duas estruturas (usada também como roteiro da apresentação).
#include <cstdio>
#include <vector>
#include "BST.hpp"
#include "AVL.hpp"

static void imprimir(const char* rotulo, const std::vector<int>& v) {
    printf("%-12s:", rotulo);
    for (size_t i = 0; i < v.size(); i++) printf(" %d", v[i]);
    printf("\n");
}

int main() {
    printf("=== BST: inserindo 50 30 70 20 40 60 80 ===\n");
    BST b;
    int chavesB[] = {50, 30, 70, 20, 40, 60, 80};
    for (int c : chavesB) b.inserir(c);
    imprimir("in-order", b.emOrdem());
    imprimir("pre-order", b.preOrdem());
    imprimir("post-order", b.posOrdem());
    imprimir("level-order", b.porNivel());
    int s, a;
    if (b.sucessor(40, s) && b.antecessor(40, a))
        printf("antecessor(40)=%d  sucessor(40)=%d  altura=%d\n", a, s, b.altura());
    b.removerPorCopia(50);
    imprimir("apos rem 50", b.porNivel());

    printf("\n=== BST degenerada: inserindo 1..7 em ordem ===\n");
    BST lista;
    for (int i = 1; i <= 7; i++) lista.inserir(i);
    printf("altura=%d (N-1 = pior caso O(N))\n", lista.altura());

    printf("\n=== AVL: inserindo 1..7 em ordem ===\n");
    AVL t;
    for (int i = 1; i <= 7; i++) t.inserir(i);
    imprimir("level-order", t.porNivel());
    printf("altura=%d  valida=%s\n", t.altura(), t.valida() ? "sim" : "nao");
    const EstatisticasAVL& e = t.estatisticas();
    printf("rotacoes: EE=%d DD=%d ED=%d DE=%d\n", e.rotEE, e.rotDD, e.rotED, e.rotDE);

    printf("\n=== AVL: casos duplos ===\n");
    AVL ed; ed.inserir(30); ed.inserir(10); ed.inserir(20);   // ED
    imprimir("ED -> nivel", ed.porNivel());
    AVL de; de.inserir(10); de.inserir(30); de.inserir(20);   // DE
    imprimir("DE -> nivel", de.porNivel());
    return 0;
}
