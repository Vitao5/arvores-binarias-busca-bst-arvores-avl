# Árvores BST e AVL em C++

**Integrantes:** Victor, Lucas Carvalho, Samuel e Lucas Santana

Implementação própria de **Árvore Binária de Busca (BST)** e **Árvore AVL** para o Seminário 3 de Estrutura de Dados II (IFTM, ADS).

## Estrutura

```
include/   BST.hpp, AVL.hpp          declarações das classes
src/       BST.cpp, AVL.cpp, main.cpp implementação e demonstração
testes/    testes.cpp                testes aleatórios contra std::set
exercicios/ ex1..ex3 (.cpp) + entradas/saídas de exemplo
Makefile
```

## Como compilar e executar

```
make all          # compila tudo em bin/
make teste        # roda os testes automáticos
./bin/demo        # demonstração (percursos, degeneração, rotações)
./bin/ex1 < exercicios/ex1_entrada.txt
./bin/ex2 < exercicios/ex2_entrada.txt
./bin/ex3 < exercicios/ex3_entrada.txt
```

Requer `g++` com suporte a C++17 e `make`.

## O que está implementado

**BST**: inserção, busca, mínimo, máximo, antecessor, sucessor, remoção por cópia, remoção por fusão, percursos in-order, pre-order, post-order e level-order, altura e tamanho.

**AVL**: inserção e remoção com rebalanceamento, fator de balanceamento `FB = h(esq) - h(dir)`, rotações simples (EE, DD) e duplas (ED, DE), contadores de rotações por tipo, percursos, e `valida()` que confere BST, alturas e `|FB| <= 1`.

## Complexidade

| Operação | BST médio | BST pior caso | AVL |
|---|---|---|---|
| Busca / inserção / remoção | O(log N) | O(N) | O(log N) |
| Percursos | O(N) | O(N) | O(N) |

## Exercícios

1. `ex1_percursos.cpp` — Beecrowd 1195 (percursos de uma BST)
2. `ex2_remocao.cpp` — LeetCode 450 adaptado (remoção em BST)
3. `ex3_avl_rotacoes.cpp` — HackerRank "Self Balancing Tree" adaptado (AVL e rotações)
