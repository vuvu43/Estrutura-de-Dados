#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int** faz_matriz(int tam_matriz);
int** multiplica_normal(int tam_matriz, int** matrizA, int** matrizB);
int** multiplica_strassen(int tam_matriz, int** matrizA, int** matrizB);
void display_matriz(int tam_matriz, int** matriz);
void fill_random(int tam_matriz, int** matrizA, int** matrizB);
void fill_input(int tam_matriz, int** matrizA, int** matrizB);


int main(int argc, char *argv[])
{
    //caso em q n passa comando
    int tam_matriz;
    printf("Tamanho: ");
    scanf("%d", &tam_matriz);

    int **matrizA = faz_matriz(tam_matriz);
    int **matrizB = faz_matriz(tam_matriz);
    fill_input(tam_matriz, matrizA, matrizB);
    
    int **matrizF = multiplica_normal(tam_matriz, matrizA, matrizB); 
    
    display_matriz(tam_matriz, matrizA);
    puts("");
    display_matriz(tam_matriz, matrizB);
    puts("");
    display_matriz(tam_matriz, matrizF);
}

int** multiplica_normal(int tam_matriz, int** matrizA, int** matrizB)
{
    int **matriz_final = faz_matriz(tam_matriz);
    
    for (int i = 0; i < tam_matriz; i++) {
      for (int j = 0; j < tam_matriz; j++) {
        matriz_final[i][j] = 0;
        
         for (int k = 0; k < tam_matriz; k++) {
            matriz_final[i][j] += matrizA[i][k] * matrizB[k][j];
         }
      }
   }
   return matriz_final;
}

void fill_input(int tam_matriz, int** matrizA, int** matrizB)
{
    printf("Digite a matriz A: \n");
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++ ){
            scanf("%d", &matrizA[i][j]);
        }
    }
    puts("");
    printf("Digite a matriz B: \n");
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++ ){
            scanf("%d", &matrizB[i][j]);
        }
    }
}

void fill_random(int tam_matriz, int** matrizA, int** matrizB)
{
    srand(time(NULL));
    
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++ ){
            int r = rand()%100 + 1;
            matrizA[i][j] = r;
        }
    }
    
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++ ){
            int r = rand()%100 + 1;
            matrizB[i][j] = r;
        }
    }
}

void display_matriz(int tam_matriz, int** matriz)
{
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++){
            printf("%d ", matriz[i][j]);
        }
        puts("");
    }
}

int** faz_matriz(int tam_matriz){
    int** matriz;
    
    matriz = (int **)malloc(tam_matriz * sizeof(int*));
    for(int i = 0; i < tam_matriz; i++){ 
        matriz[i] = (int *)malloc( tam_matriz * sizeof(int));
    }
    
    return matriz;
}



