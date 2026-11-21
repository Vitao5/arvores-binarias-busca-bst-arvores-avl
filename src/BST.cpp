#include "BST.hpp"
#include <queue>

BST::BST() : raiz(nullptr), qtd(0) {}

BST::~BST() { destruir(raiz); }

// Libera os nós em pós-ordem (filhos antes do pai).
void BST::destruir(NoBST* no) {
    if (!no) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

// Inserção iterativa: desce comparando até achar o ponteiro nulo certo.
// Custo: O(h)  ->  O(log N) no caso médio, O(N) no pior caso.
bool BST::inserir(int chave) {
    NoBST** p = &raiz;                   // ponteiro para o ponteiro que será preenchido
    while (*p) {
        if (chave == (*p)->chave) return false;   // sem duplicatas
        p = (chave < (*p)->chave) ? &(*p)->esq : &(*p)->dir;
    }
    *p = new NoBST(chave);
    qtd++;
    return true;
}

bool BST::buscar(int chave) const {
    const NoBST* x = raiz;
    while (x) {
        if (chave == x->chave) return true;
        x = (chave < x->chave) ? x->esq : x->dir;
    }
    return false;
}

// Mínimo = nó mais à esquerda.
bool BST::minimo(int& saida) const {
    if (!raiz) return false;
    const NoBST* x = raiz;
    while (x->esq) x = x->esq;
    saida = x->chave;
    return true;
}

// Máximo = nó mais à direita.
bool BST::maximo(int& saida) const {
    if (!raiz) return false;
    const NoBST* x = raiz;
    while (x->dir) x = x->dir;
    saida = x->chave;
    return true;
}

// Sucessor: menor chave maior que 'chave'.
// Desce a partir da raiz; toda vez que vai para a esquerda, o nó atual
// é um candidato (é maior que 'chave'). Guarda o último candidato.
bool BST::sucessor(int chave, int& saida) const {
    const NoBST* x = raiz;
    const NoBST* cand = nullptr;
    while (x) {
        if (chave < x->chave) { cand = x; x = x->esq; }
        else x = x->dir;
    }
    if (!cand) return false;
    saida = cand->chave;
    return true;
}

// Antecessor: simétrico ao sucessor.
bool BST::antecessor(int chave, int& saida) const {
    const NoBST* x = raiz;
    const NoBST* cand = nullptr;
    while (x) {
        if (chave > x->chave) { cand = x; x = x->dir; }
        else x = x->esq;
    }
    if (!cand) return false;
    saida = cand->chave;
    return true;
}

// Remoção por CÓPIA:
//  - 0 ou 1 filho: o filho (ou nulo) assume o lugar do nó.
//  - 2 filhos: copia a chave do sucessor (mínimo da subárvore direita)
//    para o nó e remove o sucessor (que tem no máximo 1 filho).
bool BST::removerPorCopia(int chave) {
    NoBST** p = &raiz;
    while (*p && (*p)->chave != chave)
        p = (chave < (*p)->chave) ? &(*p)->esq : &(*p)->dir;
    if (!*p) return false;

    NoBST* alvo = *p;
    if (!alvo->esq || !alvo->dir) {
        *p = alvo->esq ? alvo->esq : alvo->dir;
        delete alvo;
    } else {
        NoBST** ps = &alvo->dir;                 // acha o mínimo da direita
        while ((*ps)->esq) ps = &(*ps)->esq;
        NoBST* suc = *ps;
        alvo->chave = suc->chave;                // copia
        *ps = suc->dir;                          // suc não tem filho esquerdo
        delete suc;
    }
    qtd--;
    return true;
}

// Remoção por FUSÃO:
//  - 2 filhos: a subárvore direita é pendurada na maior chave da esquerda,
//    e a subárvore esquerda toma o lugar do nó removido.
//    (preserva a propriedade BST, mas tende a aumentar a altura)
bool BST::removerPorFusao(int chave) {
    NoBST** p = &raiz;
    while (*p && (*p)->chave != chave)
        p = (chave < (*p)->chave) ? &(*p)->esq : &(*p)->dir;
    if (!*p) return false;

    NoBST* alvo = *p;
    if (!alvo->esq) {
        *p = alvo->dir;
    } else if (!alvo->dir) {
        *p = alvo->esq;
    } else {
        NoBST* m = alvo->esq;                    // maior da esquerda
        while (m->dir) m = m->dir;
        m->dir = alvo->dir;                      // funde
        *p = alvo->esq;
    }
    delete alvo;
    qtd--;
    return true;
}

// ---------- Percursos em profundidade (recursivos) ----------
void BST::emOrdemRec(const NoBST* no, std::vector<int>& v) {
    if (!no) return;
    emOrdemRec(no->esq, v);
    v.push_back(no->chave);
    emOrdemRec(no->dir, v);
}
void BST::preOrdemRec(const NoBST* no, std::vector<int>& v) {
    if (!no) return;
    v.push_back(no->chave);
    preOrdemRec(no->esq, v);
    preOrdemRec(no->dir, v);
}
void BST::posOrdemRec(const NoBST* no, std::vector<int>& v) {
    if (!no) return;
    posOrdemRec(no->esq, v);
    posOrdemRec(no->dir, v);
    v.push_back(no->chave);
}

std::vector<int> BST::emOrdem() const  { std::vector<int> v; emOrdemRec(raiz, v);  return v; }
std::vector<int> BST::preOrdem() const { std::vector<int> v; preOrdemRec(raiz, v); return v; }
std::vector<int> BST::posOrdem() const { std::vector<int> v; posOrdemRec(raiz, v); return v; }

// Percurso em largura: fila FIFO, nível por nível.
std::vector<int> BST::porNivel() const {
    std::vector<int> v;
    if (!raiz) return v;
    std::queue<const NoBST*> fila;
    fila.push(raiz);
    while (!fila.empty()) {
        const NoBST* x = fila.front();
        fila.pop();
        v.push_back(x->chave);
        if (x->esq) fila.push(x->esq);
        if (x->dir) fila.push(x->dir);
    }
    return v;
}

int BST::alturaRec(const NoBST* no) {
    if (!no) return -1;
    int he = alturaRec(no->esq), hd = alturaRec(no->dir);
    return 1 + (he > hd ? he : hd);
}

int BST::altura() const { return alturaRec(raiz); }
int BST::tamanho() const { return qtd; }
bool BST::vazia() const { return raiz == nullptr; }
