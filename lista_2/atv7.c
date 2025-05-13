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

    int subconjunto[MAX_VERTICES];
    unsigned int numVerticesSub;
    printf("Insira o numero de vertices de S:\n");
    scanf("%d", &numVerticesSub);
    printf("Insira os vertices do subconjunto: ");
    for (int i = 0; i < numVerticesSub; i++) {
        scanf("%d", &subconjunto[i]);
        if (subconjunto[i] < 0 || subconjunto[i] >= g.numVertices) {
            printf("Vertice invalido: %d\n", subconjunto[i]);
            return 1;
        }
    }

    Grafo gInduzido;
    subgrafoInduzido(&g, &gInduzido, subconjunto, numVerticesSub);

    printf("\nSubgrafo induzido por S:\n");
    imprimirMatriz(&gInduzido);
    
    return 0;
}