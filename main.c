#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "entradaSaida.h"
#include "paradigma.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag){
    int tamanhoMatriz = calculaTamanhoMatriz(arq->entrada);
    int **mat = leituraArqEntrada(arq->entrada, tamanhoMatriz);

    fclose(arq->entrada);

    int maior = 0, clock = 0, sub_matriz;
    Ponto inicial;

    double utime_ant, utime_pos, stime_ant, stime_pos;
    contaTempoProcessador(&utime_ant, &stime_ant);
    maior = forcaBruta(mat, tamanhoMatriz, &inicial);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
    imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

    contaTempoProcessador(&utime_ant, &stime_ant);
    maior = guloso(mat, tamanhoMatriz, &inicial);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
    imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

    contaTempoProcessador(&utime_ant, &stime_ant);
    maior = dinamica(mat, tamanhoMatriz, &inicial);
    contaTempoProcessador(&utime_pos, &stime_pos);
    imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
    imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

    liberaPonteiros(arq, mat, tamanhoMatriz);
  }
}
