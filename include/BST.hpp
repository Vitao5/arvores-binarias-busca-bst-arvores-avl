#ifndef BST_HPP
#define BST_HPP

#include <vector>

// ============================================================
// Árvore Binária de Busca (BST) de inteiros, sem chaves repetidas.
// Propriedade: para todo nó x, chaves da subárvore esquerda < x.chave
//              e chaves da subárvore direita > x.chave.
// ============================================================

struct NoBST {
    int chave;
    NoBST* esq;
    NoBST* dir;
    explicit NoBST(int c) : chave(c), esq(nullptr), dir(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();
    BST(const BST&) = delete;            // evita cópia rasa (dois donos dos mesmos nós)
    BST& operator=(const BST&) = delete;

    // --- Operações primitivas ---
    bool inserir(int chave);             // false se a chave já existe
    bool buscar(int chave) const;
    bool minimo(int& saida) const;       // false se árvore vazia
    bool maximo(int& saida) const;
    bool antecessor(int chave, int& saida) const;  // maior chave < chave
    bool sucessor(int chave, int& saida) const;    // menor chave > chave

    // --- Remoção (duas estratégias) ---
    bool removerPorCopia(int chave);     // copia o sucessor in-order para o nó removido
    bool removerPorFusao(int chave);     // funde a subárvore dir. na maior chave da esq.

    // --- Percursos ---
    std::vector<int> emOrdem() const;    // in-order   (E, R, D)  -> ordem crescente
    std::vector<int> preOrdem() const;   // pre-order  (R, E, D)
    std::vector<int> posOrdem() const;   // post-order (E, D, R)
    std::vector<int> porNivel() const;   // level-order (BFS com fila)

    // --- Informações ---
    int altura() const;                  // árvore vazia = -1, folha = 0
    int tamanho() const;
    bool vazia() const;

private:
    NoBST* raiz;
    int qtd;

    static void destruir(NoBST* no);
    static int alturaRec(const NoBST* no);
    static void emOrdemRec(const NoBST* no, std::vector<int>& v);
    static void preOrdemRec(const NoBST* no, std::vector<int>& v);
    static void posOrdemRec(const NoBST* no, std::vector<int>& v);
};

#endif
