#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "grafolib.h"

// Inicializa o grafo com número de vértices e zera a matriz de adjacência
void inicializarGrafo(Grafo* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adjMatrix[i][j] = 0;
            g->pesoMatrix[i][j] = 0;
        }
    }
}

// Adiciona uma aresta entre dois vértices
void adicionarAresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices) {
        g->adjMatrix[origem][destino]++;
    } else {
        printf("Erro: vértices fora do intervalo.\n");
    }
}

// Adiciona uma aresta entre dois vértices
void adicionarPesoAresta(Grafo* g, int origem, int destino, int peso) {
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices && 
         g->adjMatrix[origem][destino] > 0 ) {
       g->pesoMatrix[origem][destino] = peso;

    } else {
        printf("Erro: vértices fora do intervalo ou não existe aresta.\n");
    }
}

void removeAresta(Grafo *g, int origem, int destino){
    if (origem >= 0 && destino >= 0 && origem < g->numVertices && destino < g->numVertices) {
        if (g->adjMatrix[origem][destino] != 0){
            g->adjMatrix[origem][destino] = 0;
            g->pesoMatrix[origem][destino] = 0;
        }
        else{
            printf("Erro: vértices não pertence ao grafo.\n");    
        }    
    } else {
        printf("Erro: vértices fora do intervalo.\n");
    }
}

// Exibe a matriz de adjacência
void imprimirMatriz(Grafo* g) {
    printf("Matriz de Adjacencia:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Exibe a matriz de peso
void imprimirMatrizPeso(Grafo* g) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->pesoMatrix[i][j]);
        }
        printf("\n");
    }
}

// Encontra o vértice com a menor distância ainda não incluído no conjunto de visitados
int menorDistancia(int dist[], int visitado[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Implementação do algoritmo de Dijkstra
int* dijkstra(Grafo *g, int origem) {
    // dist[i] será a menor distância da origem até o vértice i
    int *dist = (int*) malloc (g->numVertices*sizeof(int)); 
    // visitado[i] será verdadeiro (1) se o vértice i já foi incluído no caminho mínimo
    int *visitado = (int*) malloc (g->numVertices*sizeof(int));

    // Inicializa todas as distâncias como infinito e os visitados como falso
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
    }

    dist[origem] = 0;

    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < g->numVertices - 1; count++) {
        int u = menorDistancia(dist, visitado, g->numVertices);

        visitado[u] = 1;

        // Atualiza os valores de distância dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < g->numVertices; v++)
            if (!visitado[v] && g->pesoMatrix[u][v] && dist[u] != INT_MAX 
                && dist[u] + g->pesoMatrix[u][v] < dist[v])
                dist[v] = dist[u] + g->pesoMatrix[u][v];
    } 
    return dist;  
}

void imprimeDistancia(int dist[], int V){ 
// Imprime os resultados
 printf("Vértice \t Distância da Origem\n");
 for (int i = 0; i < V; i++)
     printf("%d \t\t %d\n", i, dist[i]);
 }

void carregarGrafo(Grafo *g, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    //Inicializa grafo
    int numVertices;
    fscanf(f, "%d", &numVertices);
    inicializarGrafo(g, numVertices);
    
    //Lê e armazena arestas do arquivo 
    int u, v, peso;
    while (fscanf(f, "%d %d %d", &u, &v, &peso) != EOF) {
        adicionarAresta(g, u, v);
        adicionarPesoAresta(g, u, v, peso);
    }
    fclose(f);
 }

bool arestaExiste(Grafo *g, Aresta a) {
    if (a.v1 >= g->numVertices || a.v2 >= g->numVertices) {
        return false;
    }
    if (g->adjMatrix[a.v1][a.v2]) {
        return true;
    }
    return false;
}

bool verticesAdjacentes(Grafo *g, int v1, int v2) {
    if (g->adjMatrix[v1][v2]) {
        return true;
    }
    return false;
}

bool arestasAdjacentes(Grafo *g, Aresta a1, Aresta a2) {
    if (arestaExiste(g, a1) && arestaExiste(g, a2)) {
        if (a1.v1 == a2.v1 || a1.v1 == a2.v2 || a1.v2 == a2.v1 || a1.v2 == a2.v2) {
            return true;
        }
    }
    return false;
}

bool arestasParalelas(Grafo *g, int v1, int v2) {
    if (g->adjMatrix[v1][v2] && g->adjMatrix[v2][v1]) {
        return true;
    }
    if (g->adjMatrix[v1][v2] > 1 || g->adjMatrix[v2][v1] > 1) {
        return true;
    }
    return false;
}

unsigned int numLacos(Grafo *g) {
    unsigned int numLacos = 0;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[i][i]) {
            numLacos += g->adjMatrix[i][i];
        }
    }
    return numLacos;
}

unsigned int grauEntradaVertice (Grafo *g, int v) {
    unsigned int grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
        grau += g->adjMatrix[i][v];
    }
    return grau;
}

unsigned int grauSaidaVertice (Grafo *g, int v) {
    unsigned int grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
        grau += g->adjMatrix[v][i];
    }
    return grau;
}

bool completo (Grafo *g) {
    Aresta a;
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            a.v1 = i;
            a.v2 = j;
            if (!arestaExiste(g, a) && i != j) {
                return false;
            }
        }
    }
    return true;
}

void subgrafoInduzido(Grafo *og, Grafo *sub, int *v, int num_v) {
    inicializarGrafo(sub, num_v);

    // Verifica cada par de vértices no subconjunto
    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            int vi = v[i];
            int vj = v[j];
            if (og->adjMatrix[vi][vj]) {
                adicionarAresta(sub, i, j); // Usa índices locais (0 a tamanho-1)
                sub->pesoMatrix[i][j] = og->pesoMatrix[vi][vj]; // se quiser manter peso
            }
        }
    }
}

void dfsDireto(Grafo *g, int v, bool *visitado) {
    visitado[v] = true;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[v][i] && !visitado[i]) {
            dfsDireto(g, i, visitado);
        }
    }
}

void dfsInverso(Grafo *g, int v, bool *visitado) {
    visitado[v] = true;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[i][v] && !visitado[i]) {
            dfsInverso(g, i, visitado);
        }
    }
}


void imprimirFecho(const char *tipo, bool *visitado, int n) {
    printf("%s: ", tipo);
    for (int i = 0; i < n; i++) {
        if (visitado[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

