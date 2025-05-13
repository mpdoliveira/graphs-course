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

    if (completo(&g)) {
        printf("\033[0;32mO grafo e completo.\033[0m\n");
    }
    else {
        printf("\033[0;31mO grafo nao e completo.\033[0m\n");
    }
    return 0;
}