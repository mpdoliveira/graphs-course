#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafolib.h"

int main() {
    Grafo g;
    carregarGrafo(&g, "grafo.txt");

    int v;
    printf("Digite o vertice para calcular os fechos transitivos: ");
    scanf("%d", &v);

    if (v < 0 || v >= g.numVertices) {
        printf("Vértice invalido!\n");
        return 1;
    }

    // Fecho transitivo direto
    bool *visitadoDireto = calloc(g.numVertices, sizeof(bool));
    dfsDireto(&g, v, visitadoDireto);
    imprimirFecho("Fecho transitivo direto", visitadoDireto, g.numVertices);

    // Fecho transitivo inverso
    bool *visitadoInverso = calloc(g.numVertices, sizeof(bool));
    dfsInverso(&g, v, visitadoInverso);
    imprimirFecho("Fecho transitivo inverso", visitadoInverso, g.numVertices);

    free(visitadoDireto);
    free(visitadoInverso);

    return 0;
}