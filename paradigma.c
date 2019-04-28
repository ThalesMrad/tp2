#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"
#include "entradaSaida.h"

#define FORCABRUTA 1
#define GULOSO 2
#define DINAMICA 3

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial){
  int maior = 0, sub_matriz;
  for (int i=0; i<tamanhoMatriz; i++){                          //percorre toda a matriz,
    for (int j=0; j<tamanhoMatriz; j++){                        //checando as maiores submatrizes possíveis em cada ponto
      if ((sub_matriz = submatrizPossivel(i, j, mat, maior, tamanhoMatriz)) > maior) {
        maior = sub_matriz;
        inicial->x = i;
        inicial->y = j;
      }
    }
  }
  if (maior == 0){                              //se não houver 1 na matriz, retorna o ponto (-1,-1)
    inicial->x = -1;
    inicial->y = -1;
  }
  return maior;
}

int submatrizPossivel(int i, int j, int **mat, int maior, int tamanhoMatriz){
  int range = maior + 1;                      // esta atribuição poupa tempo ao nao calcular submatrizes menor do que
                                              // a maior submatriz que o algortimo ja possui
  while (range + i <= tamanhoMatriz && range + j <= tamanhoMatriz) {
                                              // pega a maior submatriz possivel a partir do ponto [i][j]
    if (!checkSubMatrizForcaBruta(mat, i, j, range)){
      return maior;
    }

    maior = range;
    range++;
  }
  return maior;
}


int checkSubMatrizForcaBruta(int **mat, int i, int j, int range){

  for (int lin = i; lin < i + range; lin++){      //percorre a matriz, a partir do ponto (i,j)
    for (int col = j; col < j + range; col++){    //até o ponto mais o tamanho da submatriz (range)
      if (mat[lin][col] == 0){                    //se achar um valor 0 na submatriz, retorna 0
        return 0;
      }
    }
  }                                               //se todos os elementos da submatriz testada forem 1,
  return range;                                   //a função teve êxito e retorna o tamanho
}


int guloso(int **mat, int tamanhoDiagonal, Ponto elemento, Ponto* inicial){

  for (int maior = tamanhoDiagonal; maior >= 0; maior--){       //verifica todas as submatrizes possíveis
    int range = tamanhoDiagonal - maior + 1;                    //a partir do maior tamanho possivel
    for (int i = elemento.x; i < elemento.x + range; i++){      //achado atraves da maior sequencia de 1's
      for (int j = elemento.y; j < elemento.y + range; j++){    //vai diminuindo e verificando até achar uma submatriz válida
        if (checkSubMatrizGuloso(mat, i, j, maior)){
          inicial->x = i;
          inicial->y = j;
          if (maior == 0){                                      //se não houver 1 na matriz, retorna o ponto (-1,-1)
            inicial->x = -1;
            inicial->y = -1;
          }
          return maior;
        }
      }
    }
  }
}


int checkSubMatrizGuloso(int **mat, int x, int y, int maior){
  for (int i = 0; i < maior; i++) {                  //verica a submatriz passada
    for (int j = 0; j < maior; j++){                 //se for composta apenas de 1, retorna 1
        if (mat[i+x][j+y] == 0)                      //caso contrário retorna 0
          return 0;
    }
  }
  return 1;
}



int maiorDiagonal(int **mat, int tamanhoMatriz, Ponto* elemento){
  int maior = 0, diagonal;
  for (int i=0; i<tamanhoMatriz; i++){                //checa todas as diagonais, acha a com a maior sequencia de 1's
    for (int j=0; j<tamanhoMatriz; j++){
      if ((diagonal = tamanhoDiagonal(i, j, mat, tamanhoMatriz)) >= maior){
        maior = diagonal;                             //salva o ponto que começa a sequência
        elemento->x = i;
        elemento->y = j;
      }
    }
  }
  return maior;                                       //retorna a maior sequência
}

int tamanhoDiagonal(int i, int j, int **mat, int tamanhoMatriz){
  int maior = 0;
  while (i < tamanhoMatriz && j < tamanhoMatriz){
    if (mat[i][j] == 1)                             //verifica a diagonal
      maior++;                                      //acha e retorna a maior sequencia de 1's nela
    else
      break;
    i++;
    j++;

  }
  return maior;
}

int dinamica(int **matriz, int tamanhoMatriz, Ponto* inicial){
  int i,j,maior = 0;
  int matAux[tamanhoMatriz+1][tamanhoMatriz+1];         //criação da matriz de soluções
  for(i=0;i<tamanhoMatriz+1;i++){
    matAux[0][i] = 0;                                   //atribui o valor 0 para a primeira linha
    matAux[i][0] = 0;                                   //e para a primeira coluna
  }

  for(i=1;i<tamanhoMatriz+1;i++){                       //percorre a matriz de soluções atribuindo os valores
    for(j=1;j<tamanhoMatriz+1;j++){
      if(!matriz[i-1][j-1])                             //se o ponto correspondente for 0, atribui 0
          matAux[i][j] = 0;                             //se for 1, atribui o minimo entre os pontos indicados + 1
      else{
        matAux[i][j] = 1 + minimo(matAux[i-1][j], minimo(matAux[i][j-1],matAux[i-1][j-1]));
        if(matAux[i][j] > maior){                       //verifica o número salvo, que representa o tamanho da submatriz com apenas 1's
          maior = matAux[i][j];                         //se for maior que o antigo maior, atualiza o maior
          inicial->x = i-maior;                         //salva o ponto mais a esquerda e acima da submatriz na estrutra Ponto inicial
          inicial->y = j-maior;
        }
      }
    }
  }
  if (maior == 0){                                      //se não houver 1 na matriz, retorna o ponto (-1,-1)
    inicial->x = -1;
    inicial->y = -1;
  }
  return maior;
}


int minimo(int x, int y){         // simplesmente retorna o menor entre dois valores
  if(x < y)
    return x;
  else
  return y;
}
