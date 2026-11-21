#ifndef AVL_HPP
#define AVL_HPP

#include <vector>

// ============================================================
// Árvore AVL de inteiros (BST balanceada por altura), sem repetidos.
// Invariante: para todo nó, |FB| <= 1, com FB = h(esq) - h(dir).
// Altura: árvore vazia = -1, folha = 0.
// ============================================================

struct NoAVL {
    int chave;
    int altura;          // altura armazenada no nó (evita recalcular)
    NoAVL* esq;
    NoAVL* dir;
    explicit NoAVL(int c) : chave(c), altura(0), esq(nullptr), dir(nullptr) {}
};

// Contadores de rotações, úteis para estudo e para o exercício 3.
struct EstatisticasAVL {
    int rotEE = 0;   // caso Esquerda-Esquerda -> rotação simples à direita
    int rotDD = 0;   // caso Direita-Direita   -> rotação simples à esquerda
    int rotED = 0;   // caso Esquerda-Direita  -> rotação dupla (esq. no filho, dir. no nó)
    int rotDE = 0;   // caso Direita-Esquerda  -> rotação dupla (dir. no filho, esq. no nó)
};

class AVL {
public:
    AVL();
    ~AVL();
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    bool inserir(int chave);
    bool remover(int chave);
    bool buscar(int chave) const;
    bool minimo(int& saida) const;
    bool maximo(int& saida) const;

    std::vector<int> emOrdem() const;
    std::vector<int> preOrdem() const;
    std::vector<int> posOrdem() const;
    std::vector<int> porNivel() const;

    int altura() const;
    int tamanho() const;
    bool vazia() const;
    bool valida() const;                 // confere BST + alturas + |FB| <= 1 em todos os nós
    const EstatisticasAVL& estatisticas() const { return stats; }

private:
    NoAVL* raiz;
    int qtd;
    EstatisticasAVL stats;

    static int h(const NoAVL* n);                 // altura (nulo = -1)
    static int fb(const NoAVL* n);                // h(esq) - h(dir)
    static void atualizar(NoAVL* n);              // recalcula n->altura

    NoAVL* rotDir(NoAVL* y);                      // rotação simples à direita
    NoAVL* rotEsq(NoAVL* x);                      // rotação simples à esquerda
    NoAVL* balancear(NoAVL* n);                   // aplica o caso correto, se FB = +-2

    NoAVL* inserirRec(NoAVL* n, int chave, bool& ok);
    NoAVL* removerRec(NoAVL* n, int chave, bool& ok);

    static void destruir(NoAVL* n);
    static void emOrdemRec(const NoAVL* n, std::vector<int>& v);
    static void preOrdemRec(const NoAVL* n, std::vector<int>& v);
    static void posOrdemRec(const NoAVL* n, std::vector<int>& v);
    static bool validaRec(const NoAVL* n, long long lo, long long hi, int& alt);
};

#endif
