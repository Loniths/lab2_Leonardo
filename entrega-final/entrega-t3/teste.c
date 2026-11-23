// teste_calc.c
// testes rápidos pra calculadora (calc.h)

#include "calc.h"
#include "str.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static int total = 0;
static int falhas = 0;

// roda calculadora(expr) e compara com o resultado esperado
static void T(const char *expr, const char *esperado)
{
    total++;

    Str e = s_cria(expr);
    Str r = calculadora(e);
    char *obtido = s_strc(r);

    if(strcmp(obtido, esperado) == 0){
        printf("ok      \"%s\" -> \"%s\"\n", expr, obtido);
    }
    else{
        falhas++;
        printf("FALHOU  \"%s\" -> \"%s\" (esperado \"%s\")\n", expr, obtido, esperado);
    }

    free(obtido);
    s_destroi(e);
    s_destroi(r);
}

int main(void)
{
    // operações básicas
    T("2+3", "5");
    T("10-4", "6");
    T("3*4", "12");
    T("10/2", "5");
    T("2^3", "8");

    // precedência (* e / antes de + e -)
    T("2+3*4", "14");
    T("2*3+4", "10");
    T("10-2*3", "4");

    // associatividade à esquerda
    T("10-3-2", "5");     // (10-3)-2, não 10-(3-2)
    T("10/2/5", "1");     // (10/2)/5, não 10/(2/5)
    T("2^3^2", "64");     // (2^3)^2, não 2^(3^2)

    // parênteses
    T("(2+3)*4", "20");
    T("2*(3+4)", "14");
    T("((2+3))", "5");    // parênteses aninhados

    // erros estruturais
    T("(2+3", "#ERRO falta )");
    T("2+3)", "#ERRO falta (");
    T("+", "#ERRO faltam operandos");
    T("2 3", "#ERRO expressão inválida");  // dois operandos, nenhum operador
    T("2 @ 3", "#ERRO token inválido");    // '@' não é operador nem operando
    T("10/0", "#ERRO divisão por zero");

    // variáveis
    T("x = 5", "5");
    T("x + 1", "6");
    T("y = x * 2", "10");
    T("y", "10");               // variável sozinha deve resolver pro valor
    T("z = w = 7", "7");        // atribuição encadeada
    T("z", "7");
    T("w", "7");
    T("nao_existe", "#ERRO variável indefinida");
    T("5 = 3", "#ERRO lado esquerdo de = não é uma variável");

    printf("\n%d testes, %d falhas\n", total, falhas);
    return falhas != 0;
}