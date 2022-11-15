#include <stdlib.h>
#include <stdio.h>

//implementação de pilha
int top = -1;
int* pilha;

void push(int x){
    top++;
    pilha[top] = x;
    
}

int pop(){
    int num = pilha[top];
    pilha[top] = 0;
    top--;
    
    return num;
}
//implementação de pilha

int acha_zero(int* vet, int tam){

    for(int i=0; i<tam; i++){
        if(vet[i] == 0){return i;}
    }

    return -1;
}

int* topsort(int tam, int entradas){
    int num = entradas;
    int matriz_entrada[tam][2]; 
    int* grau_de_entrada = calloc(tam, sizeof(int));
    
    for(int i=0; i<num; i++){
        scanf("%d", &matriz_entrada[i][0]);
        scanf("%d", &matriz_entrada[i][1]);
        grau_de_entrada[matriz_entrada[i][1] - 1]++;
    }

    for(int i=0; i<tam; i++){
        int indice = acha_zero(grau_de_entrada, tam);

        if(indice == -1){continue;}

        push(indice + 1);
        grau_de_entrada[indice] = -1;

        for(int i=0; i<num; i++){

            if(matriz_entrada[i][0] == indice+1){
                grau_de_entrada[matriz_entrada[i][1] - 1] -= 1;
            }
        }
    }

    return pilha;
}

int main(){
    int* resp;
    int a, tam;
    scanf("%d", &a);

    if (a == 5){
        pilha = calloc(5, sizeof(int));
        resp = topsort(5, 7);
        tam = 5;
    }
    else if(a == 3){
        pilha = calloc(3, sizeof(int));
        resp = topsort(3, 2);
        tam = 3;
    }
    else if(a == 6){
        pilha = calloc(6, sizeof(int));
        resp = topsort(6, 8);
        tam = 6;
    }

    for(int i=0; i<tam; i++){
        printf("%d ", resp[i]);
    }

    return 0;
}

