// teste_str.c
// programa com testes do TAD str

#include "str.h"
#include <stdio.h>

int main()
{
  char *a = "Rábica";
  Str s = s_cria(a);
  printf("Deve escrever [%s] ", a);
  s_imprime(s);
  Str ss = s_cria_substring(s, 3, 2);
  printf("\nDeve escrever [ic] ");
  s_imprime(ss);
  s_substring(ss, s, 1, 2);
  printf("\nDeve escrever [áb] ");
  s_imprime(ss);
  if (s_tam(ss) == 2) printf("\ntamanho de 'áb' (%d) deveria ser 2\n", s_tam(ss));
  unichar teste = s_ch(s, 1);
  printf("codigo unicode de à (deve ser: 225) %u\n", teste);
  Str arq = s_cria_de_arquivo("nome");
  printf("Deve escrever Arábica: ");
  s_imprime(arq);
  putchar('\n');
  if(!s_igual(s, ss)) printf("Deu certo\n");
  int busca = s_busca_s(s, 1, ss);
  s_imprime(ss);
  putchar('\n');
  s_imprime(s);
  putchar('\n');
  printf("Deve escrever[1] %d\n", busca);
  /*
  s_substitui(ss, -2, 1, NULL);
  s_substitui(s, -7, 3, ss);
  printf("Deve escrever [áica] ");
  s_imprime(s);
  s_destroi(ss);
  s_destroi(s);
  */
 putchar('\n');
}