#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafolib.h"

int main (int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Uso improprio de entradas.\n");
        return 0;
    }
    Grafo g;
    carregarGrafo(&g, argv[1]);
    imprimirMatriz(&g);

    bool paralelo = false;
    for (int i = 0; i < g.numVertices; i++) {
        for (int j = 0; j < g.numVertices; j++) {
            if (arestasParalelas(&g, i, j)) {
                printf("\033[0;32mArestas paralelas entre os vertices %d e %d.\033[0m\n", i, j);
                paralelo = true;
            }
        }
    }
    if (!paralelo) {
        printf("\033[0;31mO grafo nao possui arestas paralelas.\033[0m\n");
    }

    return 0;
}