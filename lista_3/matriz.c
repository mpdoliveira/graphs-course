#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
/// matriz adjacência e algorimo Bellman Ford
#define MAX_VERTICES 100

typedef struct
{
    int numVertices;
    // int peso;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int pesoMatrix[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Inicializa o grafo com número de vértices e zera a matriz de adjacência
void inicializarGrafo(Grafo *g, int numVertices)
{
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            g->adjMatrix[i][j] = 0;
            g->pesoMatrix[i][j] = 0;
        }
    }
}

// Adiciona uma aresta entre dois vértices
void adicionarAresta(Grafo *g, int origem, int destino)
{
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices)
    {
        g->adjMatrix[origem][destino] = 1;
        // g->adjMatrix[destino][origem] = 1; // Para grafo não direcionado
    }
    else
    {
        printf("Erro: vértices fora do intervalo.\n");
    }
}
// Adiciona uma aresta entre dois vértices
void adicionarPesoAresta(Grafo *g, int origem, int destino, int peso)
{
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices &&
        g->adjMatrix[origem][destino] == 1)
    {
        // g->adjMatrix[destino][origem] = 1; // Para grafo não direcionado
        g->pesoMatrix[origem][destino] = peso;
    }
    else
    {
        printf("Erro: vértices fora do intervalo ou não existe aresta.\n");
    }
}

// remove aresta
void removeAresta(Grafo *g, int origem, int destino)
{
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices)
    {
        if (g->adjMatrix[origem][destino] == 1)
        {
            g->adjMatrix[origem][destino] = 0;
            //  g->adjMatrix[destino][origem] = 0; // Para grafo não direcionado
            g->pesoMatrix[origem][destino] = 0;
        }
        else
        {
            printf("Erro: vértices não pertence ao grafo.\n");
        }
    }
    else
    {
        printf("Erro: vértices fora do intervalo.\n");
    }
}

// Exibe a matriz de adjacência
void imprimirMatriz(Grafo *g)
{
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < g->numVertices; i++)
    {
        for (int j = 0; j < g->numVertices; j++)
        {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Exibe a matriz de peso
void imprimirMatrizPeso(Grafo *g)
{
    printf("Matriz de Peso :\n");
    for (int i = 0; i < g->numVertices; i++)
    {
        for (int j = 0; j < g->numVertices; j++)
        {
            printf("%d ", g->pesoMatrix[i][j]);
        }
        printf("\n");
    }
}

int *vetorPred(Grafo *g, int v)
{
    int k = 0;
    int *pred = (int *)malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++)
    {
        pred[i] = -1;
    }
    for (int j = 0; j < g->numVertices; j++)
    {
        if (g->adjMatrix[j][v] == 1)
        {
            pred[k] = j;
            k++;
        }
    }
    return pred;
}

int grauVertice (Grafo *g, int v) {
    int grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
        grau += g->adjMatrix[i][v];
    }
    return grau;
}