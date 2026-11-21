// Testes automáticos: compara BST e AVL contra std::set em operações aleatórias
// e confere os invariantes da AVL a cada passo.
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include "BST.hpp"
#include "AVL.hpp"

static int falhas = 0;
#define CHECK(cond) do { if (!(cond)) { printf("FALHOU: %s (linha %d)\n", #cond, __LINE__); falhas++; } } while (0)

static std::vector<int> paraVetor(const std::set<int>& s) { return std::vector<int>(s.begin(), s.end()); }

int main() {
    srand(12345);
    // ---- BST (remoção por cópia) e BST (remoção por fusão) vs std::set ----
    for (int modo = 0; modo < 2; modo++) {
        BST b; std::set<int> ref;
        for (int i = 0; i < 20000; i++) {
            int k = rand() % 500, op = rand() % 3;
            if (op < 2) { CHECK(b.inserir(k) == ref.insert(k).second); }
            else {
                bool r = modo == 0 ? b.removerPorCopia(k) : b.removerPorFusao(k);
                CHECK(r == (ref.erase(k) == 1));
            }
            if (i % 500 == 0) CHECK(b.emOrdem() == paraVetor(ref));
        }
        CHECK(b.emOrdem() == paraVetor(ref));
        CHECK(b.tamanho() == (int)ref.size());
        for (int k = 0; k < 500; k++) {
            CHECK(b.buscar(k) == (ref.count(k) == 1));
            int s, a;
            auto it = ref.upper_bound(k);
            CHECK(b.sucessor(k, s) == (it != ref.end()));
            if (it != ref.end()) CHECK(s == *it);
            auto lo = ref.lower_bound(k);
            CHECK(b.antecessor(k, a) == (lo != ref.begin()));
            if (lo != ref.begin()) CHECK(a == *std::prev(lo));
        }
    }
    // ---- AVL vs std::set, com validação de invariantes ----
    AVL t; std::set<int> ref;
    for (int i = 0; i < 50000; i++) {
        int k = rand() % 2000, op = rand() % 3;
        if (op < 2) { CHECK(t.inserir(k) == ref.insert(k).second); }
        else        { CHECK(t.remover(k) == (ref.erase(k) == 1)); }
        if (!t.valida()) { printf("AVL invalida no passo %d\n", i); falhas++; break; }
    }
    CHECK(t.emOrdem() == paraVetor(ref));
    CHECK(t.tamanho() == (int)ref.size());
    // ---- Pior caso: 1..N em ordem ----
    AVL c; BST d;
    for (int i = 1; i <= 1000; i++) { c.inserir(i); d.inserir(i); }
    CHECK(c.altura() <= 10 && c.valida());      // ~1,44 log2(N)
    CHECK(d.altura() == 999);
    printf(falhas ? "Testes: %d falha(s)\n" : "Todos os testes passaram\n", falhas);
    return falhas != 0;
}
