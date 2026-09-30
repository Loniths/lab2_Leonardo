#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct no *No;

struct no{
    no *prox;
    no *ant;
    void *dado;
}

struct fila{
    No prim;
    int tam_do_dado;
}

Fila f_cria(int tam_do_dado){
    Fila f = malloc(sizeof(struct fila));
    f->prim = NULL;
    f->tam_do_dado = tam_do_dado;
    return f;
}

void f_insere(Fila self, void *pdado){
    if(f->prim == NULL){
        f->prim = malloc(sizeof(struct no));
        assert(f->prim != NULL);
        f->prim->prox = NULL;
        f->prim->ant = NULL;
        f->prim->dado = malloc(f->tam_do_dado);
        assert(f->prim->dado != NULL);
        *(f->prim->dado) = *pdado;
        return;
    }
    No guia = f->prim;
    while(guia->prox != NULL) guia = guia->prox;
    guia->prox = malloc(sizeof(struct no));
    assert(guia->prox != NULL);
    guia->prox->ant = guia;
    guia->prox->prox = self->prim;
    guia->prox->dado = malloc(f->tam_do_dado);
    *(guia->prox->dado) = *pdado;
    return;
}

bool f_ta_vazia(Fila self){
    return self->prox == NULL;
}

void f_remove(Fila self, void *pdado){
    No remover = self->prim;
    self->prim = self->prim->prox;
    self->prim->ant = NULL;
    if(pdado != NULL) pdado = remover->dado;
    else free(remover->dado);
    free(remover);
}

void f_destroi(Fila self){
    while(!f_ta_vazia(self)){
        f_remove(self, NULL);
    }
    free(self);
}

bool f_proximo(Fila self, void *pdado){
    assert(self->prim != NULL);
    No guia = self->prim;
    while(guia)
}
