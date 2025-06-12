#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.c"

int subconjuntoAtual[8];

int main() {
    Grafo g;
    inicializarGrafo(&g, 8);
    adicionarAresta(&g, 0, 1);
    adicionarAresta(&g, 0, 2);
    adicionarAresta(&g, 0, 3);
    adicionarAresta(&g, 4, 5);
    adicionarAresta(&g, 5, 6);
    adicionarAresta(&g, 6, 7);
    adicionarAresta(&g, 7, 4);

    return 0;
}

bool ehClique (Grafo *g, int* sub) {
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = i + 1; j < g->numVertices; j++) {
            if (g->adjMatrix[i][j] == 0) {
                return false
            }
        }
    }
    return true;
}

bool ehIndependente (Grafo *g, int *sub) {
    
}

void gerarSubconjuntos(int pos, int atual) {
    if (pos == N) {
        // Agora permite subconjuntos com 1 elemento
        if (ehClique(subconjuntoAtual, atual) && atual > tamClique) {
            tamClique = atual;
            for (int i = 0; i < atual; i++)
                melhorClique[i] = subconjuntoAtual[i];
        }
        if (ehIndependente(subconjuntoAtual, atual) && atual > tamIndep) {
            tamIndep = atual;
            for (int i = 0; i < atual; i++)
                melhorIndep[i] = subconjuntoAtual[i];
        }
        return;
    }

    // incluir o vértice atual no subconjunto
    subconjuntoAtual[atual] = pos;
    gerarSubconjuntos(pos + 1, atual + 1);

    // não incluir o vértice atual no subconjunto
    gerarSubconjuntos(pos + 1, atual);
}