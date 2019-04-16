#include "entradaSaida.h"
#ifndef PARADIGMA
#define PARADIGMA

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial);
int submatrizValida(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz);
int guloso(int **mat, int tamanhoMatriz, Ponto* inicial);
int Minimo(int x,int y,int z);
int dinamica(int **matriz,int tamanhoMatriz,Ponto* inicial);
#endif
