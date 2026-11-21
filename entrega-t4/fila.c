#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct no{
    struct no *prox;
    struct no *ant;
    void *dado;
} *No;

struct fila{
    No prim;
    No ult;
    int tam_dado;
    int perc_pos;
    int n_ele;
    No perc_atual;
};

Fila f_cria(int tam_do_dado){
    Fila f = malloc(sizeof(struct fila));
    assert(f != NULL);
    f->prim = NULL;
    f->ult = NULL;
    f->perc_pos = -1;
    f->tam_dado = tam_do_dado;
    f->perc_atual = NULL;
    f->n_ele = 0;
    return f;
}

bool f_tá_vazia(Fila self){
    return self->prim == NULL;
}

void f_insere(Fila self, void *pdado){
    No novo = malloc(sizeof(struct no));
    assert(novo != NULL);
    novo->prox = NULL;
    novo->dado = malloc(self->tam_dado);
    assert(novo->dado != NULL);
    memcpy(novo->dado, pdado, self->tam_dado);
    novo->ant = self->ult;
    if(f_tá_vazia(self)) self->prim = novo;
    else self->ult->prox = novo;
    self->ult = novo;
    self->n_ele++;
    return;
}

void f_remove(Fila self, void *pdado){
    if(f_tá_vazia(self)) return;
    No remover = self->prim;
    self->prim = self->prim->prox;
    if(self->prim != NULL) self->prim->ant = NULL;
    else self->ult = NULL;
    if(pdado != NULL) memcpy(pdado, remover->dado, self->tam_dado);
    free(remover->dado);
    free(remover);
    self->n_ele--;
}

void f_destrói(Fila self){
    while(!f_tá_vazia(self)){
        f_remove(self, NULL);
    }
    free(self);
}

bool f_próximo(Fila self, void *pdado){
    if(self->perc_atual == NULL) return false;
    if(pdado != NULL) memcpy(pdado, self->perc_atual->dado, self->tam_dado);
    self->perc_atual = (self->perc_pos >= 0) ? self->perc_atual->prox : self->perc_atual->ant;
    return true;
}

void f_inicia_percurso(Fila self, int pos_inicial){
    self->perc_pos = pos_inicial;
    if(pos_inicial < 0) pos_inicial += self->n_ele;
    if(pos_inicial < 0 || pos_inicial >= self->n_ele){
        self->perc_atual = NULL;
        return;
    }
    self->perc_atual = self->prim;
    for(int i = 0; i < pos_inicial && self->perc_atual != NULL; i++)
        self->perc_atual = self->perc_atual->prox;
}