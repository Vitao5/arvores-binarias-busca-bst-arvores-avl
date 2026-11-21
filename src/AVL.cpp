#include "AVL.hpp"
#include <queue>

AVL::AVL() : raiz(nullptr), qtd(0) {}
AVL::~AVL() { destruir(raiz); }

void AVL::destruir(NoAVL* n) {
    if (!n) return;
    destruir(n->esq);
    destruir(n->dir);
    delete n;
}

int AVL::h(const NoAVL* n) { return n ? n->altura : -1; }

// Fator de balanceamento: FB = h(esq) - h(dir).
// FB > 0: pende para a esquerda | FB < 0: pende para a direita.
int AVL::fb(const NoAVL* n) { return n ? h(n->esq) - h(n->dir) : 0; }

void AVL::atualizar(NoAVL* n) {
    int he = h(n->esq), hd = h(n->dir);
    n->altura = 1 + (he > hd ? he : hd);
}

/* Rotação simples à direita (caso EE):
         y                x
        / \              / \
       x   C    ==>     A   y
      / \                  / \
     A   B                B   C
*/
NoAVL* AVL::rotDir(NoAVL* y) {
    NoAVL* x = y->esq;
    y->esq = x->dir;      // B muda de pai
    x->dir = y;
    atualizar(y);         // y ficou abaixo: atualiza primeiro
    atualizar(x);
    return x;             // nova raiz da subárvore
}

// Rotação simples à esquerda (caso DD): espelho da anterior.
NoAVL* AVL::rotEsq(NoAVL* x) {
    NoAVL* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualizar(x);
    atualizar(y);
    return y;
}

// Verifica o FB do nó e corrige com a rotação adequada.
//   FB = +2 e FB(esq) >= 0 -> EE: rotação simples à direita
//   FB = +2 e FB(esq) <  0 -> ED: rotação esq. no filho + dir. no nó
//   FB = -2 e FB(dir) <= 0 -> DD: rotação simples à esquerda
//   FB = -2 e FB(dir) >  0 -> DE: rotação dir. no filho + esq. no nó
NoAVL* AVL::balancear(NoAVL* n) {
    atualizar(n);
    int f = fb(n);
    if (f > 1) {
        if (fb(n->esq) >= 0) {            // EE (>= 0 cobre o caso de remoção com FB(filho)=0)
            stats.rotEE++;
            return rotDir(n);
        }
        stats.rotED++;                    // ED
        n->esq = rotEsq(n->esq);
        return rotDir(n);
    }
    if (f < -1) {
        if (fb(n->dir) <= 0) {            // DD
            stats.rotDD++;
            return rotEsq(n);
        }
        stats.rotDE++;                    // DE
        n->dir = rotDir(n->dir);
        return rotEsq(n);
    }
    return n;
}

// Inserção recursiva: insere como na BST e, na volta da recursão,
// atualiza altura e rebalanceia cada ancestral. Custo O(log N).
NoAVL* AVL::inserirRec(NoAVL* n, int chave, bool& ok) {
    if (!n) { ok = true; return new NoAVL(chave); }
    if (chave < n->chave)      n->esq = inserirRec(n->esq, chave, ok);
    else if (chave > n->chave) n->dir = inserirRec(n->dir, chave, ok);
    else { ok = false; return n; }
    return ok ? balancear(n) : n;
}

// Remoção: igual à BST (sucessor in-order quando há 2 filhos),
// mas rebalanceando todos os ancestrais na volta. Pode exigir
// mais de uma rotação ao longo do caminho até a raiz.
NoAVL* AVL::removerRec(NoAVL* n, int chave, bool& ok) {
    if (!n) { ok = false; return nullptr; }
    if (chave < n->chave)      n->esq = removerRec(n->esq, chave, ok);
    else if (chave > n->chave) n->dir = removerRec(n->dir, chave, ok);
    else {
        ok = true;
        if (!n->esq || !n->dir) {
            NoAVL* filho = n->esq ? n->esq : n->dir;
            delete n;
            return filho;               // filho já está balanceado
        }
        NoAVL* s = n->dir;              // sucessor = mínimo da direita
        while (s->esq) s = s->esq;
        n->chave = s->chave;
        bool ignorar;
        n->dir = removerRec(n->dir, s->chave, ignorar);
    }
    return balancear(n);
}

bool AVL::inserir(int chave) {
    bool ok = false;
    raiz = inserirRec(raiz, chave, ok);
    if (ok) qtd++;
    return ok;
}

bool AVL::remover(int chave) {
    bool ok = false;
    raiz = removerRec(raiz, chave, ok);
    if (ok) qtd--;
    return ok;
}

bool AVL::buscar(int chave) const {
    const NoAVL* x = raiz;
    while (x) {
        if (chave == x->chave) return true;
        x = (chave < x->chave) ? x->esq : x->dir;
    }
    return false;
}

bool AVL::minimo(int& saida) const {
    if (!raiz) return false;
    const NoAVL* x = raiz;
    while (x->esq) x = x->esq;
    saida = x->chave;
    return true;
}

bool AVL::maximo(int& saida) const {
    if (!raiz) return false;
    const NoAVL* x = raiz;
    while (x->dir) x = x->dir;
    saida = x->chave;
    return true;
}

void AVL::emOrdemRec(const NoAVL* n, std::vector<int>& v) {
    if (!n) return;
    emOrdemRec(n->esq, v); v.push_back(n->chave); emOrdemRec(n->dir, v);
}
void AVL::preOrdemRec(const NoAVL* n, std::vector<int>& v) {
    if (!n) return;
    v.push_back(n->chave); preOrdemRec(n->esq, v); preOrdemRec(n->dir, v);
}
void AVL::posOrdemRec(const NoAVL* n, std::vector<int>& v) {
    if (!n) return;
    posOrdemRec(n->esq, v); posOrdemRec(n->dir, v); v.push_back(n->chave);
}

std::vector<int> AVL::emOrdem() const  { std::vector<int> v; emOrdemRec(raiz, v);  return v; }
std::vector<int> AVL::preOrdem() const { std::vector<int> v; preOrdemRec(raiz, v); return v; }
std::vector<int> AVL::posOrdem() const { std::vector<int> v; posOrdemRec(raiz, v); return v; }

std::vector<int> AVL::porNivel() const {
    std::vector<int> v;
    if (!raiz) return v;
    std::queue<const NoAVL*> fila;
    fila.push(raiz);
    while (!fila.empty()) {
        const NoAVL* x = fila.front();
        fila.pop();
        v.push_back(x->chave);
        if (x->esq) fila.push(x->esq);
        if (x->dir) fila.push(x->dir);
    }
    return v;
}

int AVL::altura() const { return h(raiz); }
int AVL::tamanho() const { return qtd; }
bool AVL::vazia() const { return raiz == nullptr; }

// Verificação independente: propriedade BST (intervalo lo..hi),
// altura armazenada correta e |FB| <= 1 em todos os nós.
bool AVL::validaRec(const NoAVL* n, long long lo, long long hi, int& alt) {
    if (!n) { alt = -1; return true; }
    if (n->chave <= lo || n->chave >= hi) return false;
    int he, hd;
    if (!validaRec(n->esq, lo, n->chave, he)) return false;
    if (!validaRec(n->dir, n->chave, hi, hd)) return false;
    alt = 1 + (he > hd ? he : hd);
    int f = he - hd;
    return n->altura == alt && f >= -1 && f <= 1;
}

bool AVL::valida() const {
    int a;
    return validaRec(raiz, -(1LL << 40), (1LL << 40), a);
}
