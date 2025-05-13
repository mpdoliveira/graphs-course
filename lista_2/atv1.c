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

    unsigned int opcao = 0;
    do {
        printf("Escolha uma opcao:\n");
        printf("(1) Verificar adjacencia de vertices.\n");
        printf("(2) Verificar adjacencia de arestas.\n");
        printf("(3) Sair.\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int v1, v2;
            printf("Insira dois vertices: ");
            scanf("%d %d", &v1, &v2);
            if (verticesAdjacentes(&g, v1, v2)) {
                printf("\033[0;32mOs vertices sao adjacentes.\033[0m\n");
            }
            else {
                printf("\033[0;31mOs vertices nao sao adjacentes.\033[0m\n");
            }
        }
        else if (opcao == 2) {
            Aresta a1, a2;
            scanf("%d:%d %d:%d", &a1.v1, &a1.v2, &a2.v1, &a2.v2);
            if (arestasAdjacentes(&g, a1, a2)) {
                printf("\033[0;32mAs arestas sao adjacentes.\033[0m\n");
            }
            else {
                printf("\033[0;31mAs arestas nao sao adjacentes.\033[0m\n");
            }
        }
        else if (opcao == 3) {
            break;
        }

    } while (opcao != 3);

    return 0;
}