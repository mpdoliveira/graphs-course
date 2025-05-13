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

    printf("Vertice\tGrau\n");
    for (int i = 0; i < g.numVertices; i++) {
        printf("\033[0;32m%d\t%d\033[0m\n", i, grauEntradaVertice(&g, i) + grauSaidaVertice(&g, i));
    }

    return 0;
}