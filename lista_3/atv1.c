#include <stdio.h>
#include <stdlib.h>
#include "Pilha.c"
#include "matriz.c"

int main() {
    Grafo g;
    inicializarGrafo(&g, 6);
    adicionarAresta(&g, 0, 1);
    adicionarAresta(&g, 0, 3);
    adicionarAresta(&g, 1, 2);
    adicionarAresta(&g, 1, 4);
    adicionarAresta(&g, 2, 4);
    adicionarAresta(&g, 3, 2);
    adicionarAresta(&g, 4, 5);
    imprimirMatriz(&g);

    int graus[g.numVertices];
    for (int i = 0; i < g.numVertices; i++) {
        graus[i] = grauVertice(&g, i);
    }

    int khanFinal = 0;
    Pilha *p = criaPilha();
    int resultado[g.numVertices];

    while (khanFinal < 6) {
        for (int i = 0; i < g.numVertices; i++) {
            if (graus[i] == 0) {
                push(p, i);
                graus[i] = -1;
            }
        }

        resultado[khanFinal] = pop(p);
        
        for (int i = 0; i < g.numVertices; i++) {
            if (g.adjMatrix[resultado[khanFinal]][i] == 1) {
                graus[i]--;
            }
        }

        khanFinal++;
    }
    for (int i = 0; i < g.numVertices; i++) {
        printf("%d\n", resultado[i]);
    }

    return 0;
}