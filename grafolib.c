#include <stdio.h>
#include <stdlib.h>
#include "grafolib.h"

void carrega_grafo(Grafo *g, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    int origem, destino;
    while (fscanf(arquivo, "%d %d", &origem, &destino) == 2) {
        // Verifica se os vértices são válidos
        if (origem >= g->num_vertices || destino >= g->num_vertices || origem < 0 || destino < 0) {
            printf("Aresta inválida: %d -> %d\n", origem, destino);
            continue;
        }
        cria_aresta(g, origem, destino, 0); // peso 0 padrão
    }

    fclose(arquivo);
    printf("Grafo carregado com sucesso a partir de %s.\n", nome_arquivo);
}

void inicializa_lista_adj (Grafo *g, int num_vertices, bool orientado) {
    g->num_vertices = num_vertices;
    g->orientado = orientado;
    g->lista_adj = malloc(sizeof(No) * g->num_vertices);
    for (int i = 0; i < g->num_vertices; i++) {
        g->lista_adj[i] = NULL;
    }
}

No* aresta_existe (Grafo *g, int origem, int destino) {
    No *n = g->lista_adj[origem];
    while (n != NULL) {
        if (n->vertice == destino) {
            return n;
        }
        n = n->proximo;
    }
    return NULL;
}

void cria_aresta (Grafo *g, int origem, int destino, int peso) {
    // Adiciona paralela se aresta já existir.
    No* temp = aresta_existe(g, origem, destino);
    if (temp != NULL) {
        temp->paralela++;
        // Adiciona paralela na aresta inversa se grafo não ordenado.
        if(!g->orientado) {
            No* temp = aresta_existe(g, destino, origem);
            if (temp != NULL) {
                temp->paralela++;
            } 
        }
        printf("Aresta criada com sucesso.\n");
        return;
    }
    
    // Adiciona aresta nova.
    No *novo_no = malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro na alocação de momória.\n");
        return;
    }
    novo_no->vertice = destino;
    novo_no->peso = peso;
    novo_no->paralela = 0;
    novo_no->proximo = g->lista_adj[origem];
    g->lista_adj[origem] = novo_no;
    
    // Adiciona aresta inversa se grafo não ordenado
    if (!g->orientado) {
        No *novo_no = malloc(sizeof(No));
        if (novo_no == NULL) {
            printf("Erro na alocação de momória.\n");
            return;
        }
        novo_no->vertice = origem;
        novo_no->proximo = g->lista_adj[destino];
        g->lista_adj[destino] = novo_no;
    }
    printf("Aresta criada com sucesso.\n");
}

void remove_aresta_unit (No **lista_adj, int destino) {
    No *anterior = NULL;
    No *atual = *lista_adj;

    while (atual != NULL) {
        if (atual->vertice == destino) {
            if (anterior == NULL) {
                *lista_adj = atual->proximo;
            }
            else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void apaga_aresta (Grafo *g, int origem, int destino) {
    // Verifica se aresta existe.
    if (aresta_existe(&g, origem, destino) == NULL) {
        printf("Aresta não existe.\n");
        return;
    }

    // Remove aresta.
    remove_aresta_unit(&g->lista_adj[origem], destino);
    // Remove aresta inversa se grafo não ordenado.
    if (!g->orientado) {
        remove_aresta_unit(&g->lista_adj[destino], origem);
    }
    printf("Aresta apagada com sucesso.\n");
}

void imprime_lista_adj (Grafo *g) {
    // Imprime título da aresta e cabeçalho das colunas.
    printf("Tabela de ajacência - grafo %s\n", g->nome);
    printf("Vértice:\t\tIncidências:\n");

    // Imprime lista de adjacência.
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d\t\t", i);
        No *temp = g->lista_adj[i];
        while (temp != NULL) {
            printf("%d ", temp->vertice);
            temp = temp->proximo;
        } 
        printf("\n");
    }
}

void libera_lista_adj (Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *apagar = g->lista_adj[i];
        while (apagar != NULL) {
            No *temp = apagar->proximo;
            free(apagar);
            apagar = temp;
        }
    }
}

bool sao_adjacentes (Grafo *g, int origem, int destino) {
    No *n = g->lista_adj[origem];
    while (n != NULL) {
        if (n->vertice == destino) {
            printf("Os vértices %d e %d são adjacentes.\n", origem, destino);
            return true;
        }
    }
    if (g->orientado) {
        n = g->lista_adj[destino];
        while (n != NULL) {
            if (n->vertice == origem) {
                printf("Os vértices %d e %d são adjacentes.\n", origem, destino);
                return true;
            }
        }
    }
    return false;
}

unsigned int paralelas (Grafo *g) {
    unsigned int num_paralelas = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        No *n = g->lista_adj[i];
        while (n != NULL) {
            num_paralelas += n->paralela;
        }
    }
    if (num_paralelas) {
        printf("O grafo %s possui %d arestas paralelas.\n", g->nome, num_paralelas);
    }
    return num_paralelas;
}

unsigned int lacos (Grafo *g) {
    unsigned int num_lacos = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        if (aresta_existe(g, i, i)) {
            num_lacos++;
        }
    }
    if (num_lacos) {
        printf("O grafo %s possui %d laços.\n", g->nome, num_lacos);
    }
    return num_lacos;
}

unsigned int grau_saida (Grafo *g, int vertice) {
    unsigned int grau = 0;
    No *n = g->lista_adj[vertice];
    while (n != NULL) {
        if (n->vertice == vertice) {
            grau += 2 + n->paralela * 2; // +2 laço para cada laço 
        }
        else {
            grau += 1 + n->paralela;
        }
    }
    return grau;
}

void grau_nao_orientado (Grafo *g) {
    printf("Graus por vértice, grafo não orientado:\n");
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vértice %d, grau %d\n", i, grau_saida(g, i));
    }
}

bool eh_completo (Grafo *g) {
    bool completo = true;
    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = 0; j < g->num_vertices; j++) {
            if (!aresta_existe(g, i, j)) {
                completo = false;
                break;
            }
        }
    }
    return completo;
}

int **cria_matriz_adj(Grafo *g) {
    int **matriz_adj = malloc(g->num_vertices * sizeof(int *));
    if (matriz_adj == NULL) {
        printf("Falha na alocação de memória.\n");
        return NULL;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        matriz_adj[i] = malloc(g->num_vertices * sizeof(int));
        if (matriz_adj[i] == NULL) {
            printf("Falha na alocação de memória.\n");
            // Libera memória previamente alocada
            for (int j = 0; j < i; j++) {
                free(matriz_adj[j]);
            }
            free(matriz_adj);
            return NULL;
        }

        // Inicializa a linha com 0 (sem arestas)
        for (int j = 0; j < g->num_vertices; j++) {
            matriz_adj[i][j] = 0;
        }
    }

    // Preenche a matriz com base na lista de adjacência
    for (int i = 0; i < g->num_vertices; i++) {
        No *temp = g->lista_adj[i];
        while (temp != NULL) {
            matriz_adj[i][temp->vertice] = 1;
            temp = temp->proximo;
        }
    }

    return matriz_adj;
}

