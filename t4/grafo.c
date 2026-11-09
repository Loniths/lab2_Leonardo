#include "grafo.h"
#include "fila.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct grafo{
    int tam_nó, tam_aresta;
    int n_nós;
    void **nós;
    void ***arestas;
    int consulta_nó;
    bool consulta_partindo;
    int consulta_pos;
};

Grafo g_cria(int tam_nó, int tam_aresta){
    Grafo novo = malloc(sizeof(struct grafo));
    if(novo == NULL) return NULL;
    novo->tam_nó = tam_nó;
    novo->tam_aresta = tam_aresta;
    novo->n_nós = 0;
    novo->nós = NULL;
    novo->arestas = NULL;
    novo->consulta_nó = -1;
    novo->consulta_partindo = false;
    novo->consulta_pos = 0;
    return novo;
}

int g_insere_nó(Grafo self, void *p_dado){
    int tam_antigo = self->n_nós;
    self->n_nós++;
    self->nós = realloc(self->nós, self->n_nós * sizeof(void *));
    assert(self->nós != NULL);
    self->nós[tam_antigo] = malloc(self->tam_nó);
    memcpy(self->nós[tam_antigo], p_dado, self->tam_nó);
    self->arestas = realloc(self->arestas, self->n_nós * sizeof(void **));
    assert(self->arestas != NULL);
    self->arestas[tam_antigo] = calloc(self->n_nós, sizeof(void *));
    for(int i = 0; i < tam_antigo; i++){
        self->arestas[i] = realloc(self->arestas[i], self->n_nós * sizeof(void *));
        assert(self->arestas[i] != NULL);
        self->arestas[i][tam_antigo] = NULL;
    }
    return tam_antigo;
}

int g_num_nós(Grafo self){
    return self->n_nós;
}

void *g_valor_do_nó(Grafo self, int nó){
    return self->nós[nó];
}

void g_altera_valor_do_nó(Grafo self, int nó, void *pdado){
    memcpy(self->nós[nó], pdado, self->tam_nó);
}

void g_altera_valor_da_aresta(Grafo self, int nó_origem, int nó_destino, void *pdado){
    if(pdado == NULL){
        free(self->arestas[nó_origem][nó_destino]);
        self->arestas[nó_origem][nó_destino] = NULL;
        return;
    }
    if(self->arestas[nó_origem][nó_destino] == NULL) self->arestas[nó_origem][nó_destino] = malloc(self->tam_aresta);
    memcpy(self->arestas[nó_origem][nó_destino], pdado, self->tam_aresta);
}

void *g_valor_da_aresta(Grafo self, int nó_origem, int nó_destino){
    return self->arestas[nó_origem][nó_destino];
}

static void inicializa_consulta(Grafo self, int nó_origem){
    self->consulta_nó = nó_origem;
    self->consulta_pos = 0;
}

void g_arestas_que_partem(Grafo self, int nó_origem){
    inicializa_consulta(self, nó_origem);
    self->consulta_partindo = true;
}

void g_arestas_que_chegam(Grafo self, int nó_origem){
    inicializa_consulta(self, nó_origem);
    self->consulta_partindo = false;
}

void *g_próxima_aresta(Grafo self, int *p_nó_vizinho){
    if(self->consulta_nó == -1) return NULL;
    if(self->consulta_partindo){
        for(int i = self->consulta_pos; i < self->n_nós; i++){
            if(self->arestas[self->consulta_nó][i] != NULL){
                if(p_nó_vizinho != NULL) *p_nó_vizinho = i;
                self->consulta_pos = i + 1;
                return self->arestas[self->consulta_nó][i];
            }
        }
    }
    else{
            for(int i = self->consulta_pos; i < self->n_nós; i++){
            if(self->arestas[i][self->consulta_nó] != NULL){
                if(p_nó_vizinho != NULL) *p_nó_vizinho = i;
                self->consulta_pos = i + 1;
                return self->arestas[i][self->consulta_nó];
            }
        }
    }
    return NULL;
}


static void calcula_graus(Grafo self, int *graus, int nó){
    g_arestas_que_partem(self, nó);
    int chegada;
    while(g_próxima_aresta(self, &chegada) != NULL){
        graus[chegada]++;
    }
}

Fila g_ordem_topológica(Grafo self){
    int *graus = calloc(self->n_nós, sizeof(int));
    for(int i = 0; i < self->n_nós; i++) calcula_graus(self, graus, i);
    Fila pronto = f_cria(sizeof(int));
    Fila resultado = f_cria(sizeof(int));
    for(int i = 0; i < self->n_nós; i++){
        if(graus[i] == 0) f_insere(pronto, &i);
    }
    int contador = 0;
    while(!f_tá_vazia(pronto)){
        int partindo;
        f_remove(pronto, &partindo);
        f_insere(resultado, &partindo);
        contador++;
        g_arestas_que_partem(self, partindo);
        int chegada;
        while(g_próxima_aresta(self, &chegada) != NULL){
            graus[chegada]--;
            if(graus[chegada] == 0) f_insere(pronto, &chegada);
        }
    }
    free(graus);
    f_destrói(pronto);
    if(contador < self->n_nós){
        f_destrói(resultado);
        return f_cria(sizeof(int));
    }
    return resultado;
}

bool g_tem_ciclo(Grafo self){
    Fila teste = g_ordem_topológica(self);
    if(f_tá_vazia(teste) && self->n_nós > 0){
        f_destrói(teste);
        return true;
    }
    f_destrói(teste);
    return false;
}

void g_destrói(Grafo self){
    for(int i = 0; i < self->n_nós; i++){
        for(int j = 0; j < self->n_nós; j++){
            free(self->arestas[i][j]);
        }
        free(self->arestas[i]);
    }
    for(int i = 0; i < self->n_nós; i++){
        free(self->nós[i]);
    }
    free(self->arestas);
    free(self->nós);
    free(self);
}

void g_remove_nó(Grafo self, int nó){
    free(self->nós[nó]);
    for(int i = 0; i < self->n_nós; i++){
        free(self->arestas[nó][i]);
        if(i != nó) free(self->arestas[i][nó]);
    }
    free(self->arestas[nó]);
    memmove(&self->nós[nó], &self->nós[nó + 1], (self->n_nós - nó - 1) * sizeof(void *));
    memmove(&self->arestas[nó], &self->arestas[nó + 1], (self->n_nós - nó - 1) * sizeof(void *));
    for(int i = 0; i < (self->n_nós - 1); i++){
        memmove(&self->arestas[i][nó], &self->arestas[i][nó + 1], (self->n_nós - nó - 1) * sizeof(void *));
    }
    self->n_nós--;
    if(self->n_nós == 0){
        free(self->nós);
        self->nós = NULL;
        free(self->arestas);
        self->arestas = NULL;
    }
    else{
        self->nós = realloc(self->nós, (self->n_nós) * sizeof(void *));
        self->arestas = realloc(self->arestas, (self->n_nós) * sizeof(void *));
        for(int i = 0; i < self->n_nós; i++) self->arestas[i] = realloc(self->arestas[i], (self->n_nós) * sizeof(void **));
    }
}