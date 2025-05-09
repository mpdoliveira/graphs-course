#ifndef GRAFOLIB_H
#define GRAFOLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOME_GRAFO 25

typedef struct No {
    int vertice;
    unsigned int paralela;
    float peso;
    No *proximo;
} No;

typedef struct Grafo {
    char nome[MAX_NOME_GRAFO];
    unsigned int num_vertices;
    bool orientado;
    No **lista_adj;
} Grafo;

// Funções principais
void inicializa_lista_adj(Grafo *g, int num_vertices, bool orientado);
void cria_aresta(Grafo *g, int origem, int destino, int peso);
void apaga_aresta(Grafo *g, int origem, int destino);
void imprime_lista_adj(Grafo *g);
void libera_lista_adj(Grafo *g);

// Funções auxiliares
No* aresta_existe(Grafo *g, int origem, int destino);
void remove_aresta_unit(No **lista_adj, int destino);
bool sao_adjacentes(Grafo *g, int origem, int destino);
unsigned int paralelas(Grafo *g);
unsigned int lacos(Grafo *g);
unsigned int grau_saida(Grafo *g, int vertice);
void grau_nao_orientado(Grafo *g);
bool eh_completo(Grafo *g);

#endif