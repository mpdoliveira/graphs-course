#ifndef GRAFOLIB_H
#define GRAFOLIB_H

#include <stdbool.h>

#define MAX_VERTICES 100

// Estrutura para representar o grafo
typedef struct {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int pesoMatrix[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Estrutura para representar uma aresta
typedef struct {
    int v1;
    int v2;
} Aresta;

// Funções de manipulação do grafo
void inicializarGrafo(Grafo* g, int numVertices);
void adicionarAresta(Grafo* g, int origem, int destino);
void adicionarPesoAresta(Grafo* g, int origem, int destino, int peso);
void removeAresta(Grafo *g, int origem, int destino);
void imprimirMatriz(Grafo* g);
void imprimirMatrizPeso(Grafo* g);
void subgrafoInduzido(Grafo *og, Grafo *sub, int *v, int num_v);
void dfsDireto(Grafo *g, int v, bool *visitado);
void dfsInverso(Grafo *g, int v, bool *visitado);
void imprimirFecho(const char *tipo, bool *visitado, int n);

// Funções do algoritmo de Dijkstra
int* dijkstra(Grafo *g, int origem);
void imprimeDistancia(int dist[], int V);

// Funções de carregamento e verificação
void carregarGrafo(Grafo *g, const char* nomeArquivo);
bool arestaExiste(Grafo *g, Aresta a);
bool verticesAdjacentes(Grafo *g, int v1, int v2);
bool arestasAdjacentes(Grafo *g, Aresta a1, Aresta a2);
bool arestasParalelas(Grafo *g, int v1, int v2);
bool completo (Grafo *g);
unsigned int numLacos(Grafo *g);
unsigned int grauEntradaVertice (Grafo *g, int v);
unsigned int grauSaidaVertice (Grafo *g, int v);

#endif // GRAFOLIB_H
