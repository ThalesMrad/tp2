#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"
#include "entradaSaida.h"

#define FORCABRUTA 1
#define GULOSO 2
#define DINAMICA 3

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial){
  int maior = 0, clock = 0, sub_matriz;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      // for (int n=1; n<=tamanhoMatriz; n++){
      //   if((sub_matriz = checkSubMatrizForcaBruta(mat, i, j, n)) >= maior){
      //     maior = sub_matriz;
      //     inicial->x = i;
      //     inicial->y = j;
      //   }
      // }
      if ((sub_matriz = submatrizPossivel(i, j, mat, &clock, maior, tamanhoMatriz)) > maior) {
        maior = sub_matriz;
        inicial->x = i;
        inicial->y = j;
      }
    }
  }
  if (maior == 0){
    inicial->x = -1;
    inicial->y = -1;
  }
  return maior;
}

int submatrizPossivel(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz){
  int range = maior + 1;    // esta atribuição poupa tempo ao nao calcular submatrizes menor do que
                                              // a maior submatriz que o algortimo ja possui


  while (1) {
                          // pega a maior submatriz possivel a partir do ponto [i][j]
    if ( range + i > tamanhoMatriz ||  range + j > tamanhoMatriz){
      return maior;
    }

    if (!checkSubMatrizForcaBruta(mat, i, j, range)){
      return maior;
    }

    maior = range;
    range++;
  }
}


int checkSubMatrizForcaBruta(int **mat, int i, int j, int range){

  for (int lin = i; lin < i + range; lin++){
    for (int col = j; col < j + range; col++){
      if (mat[lin][col] == 0){
        return 0;
      }
    }
  }
  return range;
}




int dinamica(int **matriz, int tamanhoMatriz, Ponto* inicial){
  int i,j,maior = 0;
  int matAux[tamanhoMatriz+1][tamanhoMatriz+1];
  for(i=0;i<tamanhoMatriz+1;i++){
    matAux[0][i] = 0;
    matAux[i][0] = 0;
  }

  for(i=1;i<tamanhoMatriz+1;i++){
    for(j=1;j<tamanhoMatriz+1;j++){
      if(!matriz[i-1][j-1])
          matAux[i][j] = 0;
      else{
        matAux[i][j] = 1 + minimo(matAux[i-1][j], minimo(matAux[i][j-1],matAux[i-1][j-1]));
        if(matAux[i][j] > maior){
          maior = matAux[i][j];
          inicial->x = i-maior;
          inicial->y = j-maior;
        }
      }
    }
  }
  if (maior == 0){
    inicial->x = -1;
    inicial->y = -1;
  }
  return maior;
}


int minimo(int x, int y){
  if(x < y)
    return x;
  else
  return y;
}

int guloso(int **mat, int tamanhoDiagonal, Ponto elemento, Ponto* inicial){

  for (int maior = tamanhoDiagonal; maior >= 0; maior--){
    int range = tamanhoDiagonal - maior + 1;
    for (int i = elemento.x; i < elemento.x + range; i++){
      for (int j = elemento.y; j < elemento.y + range; j++){
        if (checkSubMatrizGuloso(mat, i, j, maior)){
          inicial->x = i;
          inicial->y = j;
          if (maior == 0){
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
  for (int i = 0; i < maior; i++) {
    for (int j = 0; j < maior; j++){
        if (!mat[i+x][j+y])
          return 0;
    }
  }
  return 1;
}



int MaiorDiagonal(int **mat, int tamanhoMatriz, Ponto* elemento){
  int maior = 0, diagonal;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if ((diagonal = tamanhoDiagonal(i, j, mat, tamanhoMatriz)) >= maior){
        maior = diagonal;
        elemento->x = i;
        elemento->y = j;
      }
    }
  }
  printf("maior: %d\n", maior);
  printf("ponto: %dx%d\n", elemento->x, elemento->y);
  return maior;
}

int tamanhoDiagonal(int i, int j, int **mat, int tamanhoMatriz){
  int maior_dprincipal= 0, maior_dsecundaria = 0;
  while (i < tamanhoMatriz && j < tamanhoMatriz){
    if (mat[i][j] == 1)
      maior_dprincipal++;
    else
      break;          // diagonal principal
    i++;
    j++;

  }
  // i=0;
  // while (i < tamanhoMatriz && j >= 0){
  //   if (mat[i][j] == 1)
  //     maior_dsecundaria++;
  //   else
  //     break;          // diagonal secundaria
  //   i++;
  //   j--;
  //
  // }
  // if (maior_dprincipal >= maior_dsecundaria){
  //
    return maior_dprincipal;
  // }
  // else{
  //   return maior_dsecundaria;
  // }
}
