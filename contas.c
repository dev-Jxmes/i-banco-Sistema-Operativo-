#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define atrasar() sleep(ATRASO)

int termina = 0;

int contas[NUM_CONTAS];


int contaExiste(int id) {
  return (id > 0 && id <= NUM_CONTAS);
}

void inicializarContas() {
  int i;
  for (i=0; i<NUM_CONTAS; i++)
    contas[i] = 0;
}

int debitar(int id, int valor) {
  atrasar();
  if (!contaExiste(id))
    return -1;
  if (contas[id - 1] < valor)
    return -1;
  atrasar();
  contas[id - 1] -= valor;
  return 0;
}

int creditar(int id, int valor) {
  atrasar();
  if (!contaExiste(id))
    return -1;
  contas[id - 1] += valor;
  return 0;
}

int lerSaldo(int id) {
  atrasar();
  if (!contaExiste(id))
    return -1;
  return contas[id - 1];
}

void trataSignal(int sig) {
  termina = 1;
}

void simular(int anos) {
  int id, saldo, ano = 0;

  for (ano = 0; 
       ano <= anos && !termina;
       ano++) {

    printf("SIMULACAO: Ano %d\n=================\n", ano);
    for (id = 1; id<=NUM_CONTAS; id++) {
      if (ano > 0) {
        saldo = lerSaldo(id);
        creditar(id, saldo * TAXAJURO);
        saldo = lerSaldo(id);
        debitar(id, (CUSTOMANUTENCAO > saldo) ? saldo : CUSTOMANUTENCAO);
      }
      saldo = lerSaldo(id);

      while (printf("Conta %5d,\t Saldo %10d\n", id, saldo) < 0) {
        if (errno == EINTR)
          continue;
        else
          break;
      }
    }
  }

  if (termina)
    printf("Simulacao terminada por signal\n"); 
}
