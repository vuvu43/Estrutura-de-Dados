#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** faz_matriz(int tam_matriz);
int** multiplica_normal(int tam_matriz, int** matrizA, int** matrizB);
int** multiplica_strassen(int tam_matriz, int** matrizA, int** matrizB);
int** soma_matriz(int tam_matriz, int** matrizA, int**matrizB);;
int** subtrai_matriz(int tam_matriz, int** matrizA, int**matrizB);

void free_matriz(int tam_matriz, int** matriz);
void display_matriz(int tam_matriz, int** matriz);
void fill_random(int tam_matriz, int** matrizA, int** matrizB);
void fill_input(int tam_matriz, int** matrizA, int** matrizB);

int main(int argc, char *argv[])
{
    if(argc < 2){
        int tam_matriz;
        printf("Tamanho: ");
        scanf("%d", &tam_matriz);

        int **matrizA = faz_matriz(tam_matriz);
        int **matrizB = faz_matriz(tam_matriz);
        fill_random(tam_matriz, matrizA, matrizB);
    
        double tempo1 = 0.0;
        clock_t begin = clock();
        int **matriz_normal = multiplica_normal(tam_matriz, matrizA, matrizB); 
        clock_t end = clock();
        tempo1 += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTempo da multiplicação normal: %f\n", tempo1);
        //display_matriz(tam_matriz, matriz_normal);
    
        double tempo2 = 0.0;
        clock_t inicio = clock();
        int **matriz_strassen = multiplica_strassen(tam_matriz, matrizA, matrizB); 
        clock_t fim = clock();
        tempo2 += (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\nTempo da multiplicação normal: %f\n", tempo1);
        //display_matriz(tam_matriz, matriz_strassen);
    
    }else{
        int tam_matriz = atoi(argv[argc - 1]);
        
        int **matrizA = faz_matriz(tam_matriz);
        int **matrizB = faz_matriz(tam_matriz);
        fill_random(tam_matriz, matrizA, matrizB);
        
        double tempo1 = 0.0;
        clock_t begin = clock();
        int **matriz_normal = multiplica_normal(tam_matriz, matrizA, matrizB); 
        clock_t end = clock();
        tempo1 += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTempo da multiplicação normal: %f\n", tempo1);
        display_matriz(tam_matriz, matriz_normal);
        
        double tempo2 = 0.0;
        clock_t inicio = clock();
        int **matriz_strassen = multiplica_strassen(tam_matriz, matrizA, matrizB); 
        clock_t fim = clock();
        tempo2 += (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\nTempo da multiplicação Strassen: %f\n", tempo1);
        display_matriz(tam_matriz, matriz_strassen);
    }
    
    return 0;
}

void free_matriz(int tam_matriz, int** ptr){
    for(int i = 0; i < tam_matriz; i++){free(ptr[i]);}
    
    free(ptr);
}

int** multiplica_strassen(int tam_matriz, int** matrizA, int** matrizB)
{
    int** matriz_final = faz_matriz(tam_matriz);
    int k = tam_matriz/2;
    
    if(tam_matriz == 1){
        matriz_final[0][0] = matrizA[0][0]*matrizB[0][0];
        return matriz_final;
    }
    
    int** A = faz_matriz(tam_matriz);
    int** B = faz_matriz(tam_matriz);
    int** C = faz_matriz(tam_matriz);
    int** D = faz_matriz(tam_matriz);
    int** E = faz_matriz(tam_matriz);
    int** F = faz_matriz(tam_matriz);
    int** G = faz_matriz(tam_matriz);
    int** H = faz_matriz(tam_matriz);
	
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            A[i][j] = matrizA[i][j];
		    B[i][j] = matrizA[i][k+j];
		    C[i][j] = matrizA[k+i][j];
		    D[i][j] = matrizA[k+i][k+j];
		    E[i][j] = matrizB[i][j];
		    F[i][j] = matrizB[i][k+j];
		    G[i][j] = matrizB[k+i][j];
		    H[i][j] = matrizB[k+i][k+j];
         }
     }
	
    int** P1 = multiplica_strassen(k, A, subtrai_matriz(k, F, H));
    int** P2 = multiplica_strassen(k, soma_matriz(k, A, B), H);
    int** P3 = multiplica_strassen(k, soma_matriz(k, C, D), E);
    int** P4 = multiplica_strassen(k, D, subtrai_matriz(k, G, E));
    int** P5 = multiplica_strassen(k, soma_matriz(k, A, D), soma_matriz(k, E, H));
    int** P6 = multiplica_strassen(k, subtrai_matriz(k, B, D), soma_matriz(k, G, H));
    int** P7 = multiplica_strassen(k, subtrai_matriz(k, A, C), soma_matriz(k, E, F));
	
    int** R = subtrai_matriz(k, soma_matriz(k, P5, P4), subtrai_matriz(k, P2, P6));
    int** S = soma_matriz(k, P1, P2);
    int** T = soma_matriz(k, P3, P4);
    int** U = subtrai_matriz(k, soma_matriz(k, P5, P1), soma_matriz(k, P3, P7));
	
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            matriz_final[i][j] = R[i][j];
            matriz_final[i][j+k] = S[i][j];
            matriz_final[k+i][j] = T[i][j];
            matriz_final[k+i][k+j] = U[i][j];
	  }
    }
	
	for(int i=9; i<k; i++){
	    free(A[i]);
	    free(B[i]);
	    free(C[i]);
	    free(D[i]);
	    free(E[i]);
	    free(F[i]);
	    free(G[i]);
	    free(H[i]);
	    
	    free(P1[i]);
	    free(P2[i]);
	    free(P3[i]);
	    free(P4[i]);
	    free(P5[i]);
	    free(P6[i]);
	    free(P7[i]);
	    
	    free(R[i]);
	    free(S[i]);
	    free(T[i]);
	    free(U[i]);
	}
	free(A);
	free(B);
	free(C);
	free(D);
    free(E);
    free(F);
	free(G);
    free(H);
	    
	free(P1);
	free(P2);
	free(P3);
	free(P4);
	free(P5);
	free(P6);
	free(P7);
	    
	free(R);
	free(S);
	free(T);
	free(U);
	
    return matriz_final;
}

int** subtrai_matriz(int tam_matriz, int** matrizA, int** matrizB)
{
    int** matriz_final = faz_matriz(tam_matriz);
    
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++){
            matriz_final[i][j] = matrizA[i][j] - matrizB[i][j];
        }
    }
    
    return matriz_final;
}

int** soma_matriz(int tam_matriz, int** matrizA, int** matrizB)
{
    int** matriz_final = faz_matriz(tam_matriz);
    
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++){
            matriz_final[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    
    return matriz_final;
}

int** multiplica_normal(int tam_matriz, int** matrizA, int** matrizB)
{
    int **matriz_final = faz_matriz(tam_matriz);
    
    for (int i=0; i<tam_matriz; i++) {
      for (int j=0; j<tam_matriz; j++) {
        matriz_final[i][j] = 0;
        
        for (int k=0; k<tam_matriz; k++) {
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
            int r = rand()%2 + 1;
            matrizA[i][j] = r;
        }
    }
    
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<tam_matriz; j++ ){
            int r = rand()%2 + 1;
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
    
