#include <stdio.h>
#include <stdlib.h>
typedef struct lista
{
    int info;
    struct lista *prox;
} Lista;

typedef struct pilha
{
    Lista *topo;
} Pilha;

Pilha *criaPilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}
int pilha_vazia(Pilha *pi)
{
    if (pi->topo == NULL)
        return 1;
    return 0;
}

void push(Pilha *pi, int valor)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = pi->topo;
    pi->topo = novo;
}
int pop(Pilha *pi)
{
    Lista *t;
    int v;
    if (pilha_vazia(pi))
    {
        printf("Pilha vazia.\n");
        exit(1);
    } /* aborta programa */   
    t = pi->topo;
    v = t->info;
    pi->topo = t->prox;

    free(t);
    return v;
    
}

int tamanhoPilha(Pilha *pi)
{
    int cont = 0;
    Lista *t = pi->topo;
    if (pi == NULL)
        return 0;
    while (t != NULL)
    {
        cont++;
        t = t->prox;
    }
    return cont;
}

void imprimePilha(Pilha *pi)
{
    Lista *t;
    for (t = pi->topo; t != NULL; t = t->prox)
    {
        printf("Info %d\n", t->info);
    }
}
int stackPop(Pilha *pi)
{
    return pi->topo->info;
}
void pilha_libera(Pilha *pi)
{
    Lista *q = pi->topo;
    while (q != NULL)
    {
        Lista *t = q->prox;
        free(q);
        q = t;
    }
    free(pi);
}