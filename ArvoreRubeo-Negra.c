#include <stdio.h>
#include <stdlib.h>

struct No{
    int num;
    char cor;
    struct No* esq;
    struct No* dir;
}No;

struct No* rotdir(struct No* pt){
    struct No* temp = pt->esq;
    struct No* T2 = temp->dir;
    
    temp->dir = pt;
    pt->esq = T2;
    
    return temp;
    
}

struct No* rotesq(struct No* pt){
    struct No* temp = pt->dir;
    struct No* T2 = temp->esq;
    
    temp->esq = pt;
    pt->dir = T2;
    
    return temp;
}

void imprimeArv(struct No* pt){
    struct No* temp = pt;
    if(pt){
        printf("%d %c\n", temp->num, temp->cor);
        imprimeArv(temp->esq);
        imprimeArv(temp->dir);
    }
}

struct No* criarNo(int novo_num){
    struct No* temp = malloc(sizeof(struct No));
    temp->num = novo_num;
    temp->esq = temp->dir = NULL;
    temp->cor = *"R";
    return temp;
}

struct No* ptraiz;

void insereNo(int novo_num) {
    struct No *pilha[98],*novo, *xpt, *ypt;
    int dir[98], track = 0, index;
    struct No* pt = ptraiz;
    
    if(!ptraiz){
        ptraiz = criarNo(novo_num);
    return;
    }
    
    pilha[track] = ptraiz;
    dir[track++] = 0;

    while(pt){
        index = (novo_num - pt->num) > 0 ? 1 : 0;
        pilha[track] = pt;
        if(index == 1){pt = pt->dir;}
        else{pt = pt->esq;}
        dir[track++] = index;
    }

    if(index == 0){pilha[track - 1]->esq = novo = criarNo(novo_num);}
    else{pilha[track - 1]->dir = novo = criarNo(novo_num);}

    while ((track >= 3) && (pilha[track - 1]->cor == *"R")) {
        if (dir[track - 2] == 0) {
        ypt = pilha[track - 2]->dir;
        if (ypt != NULL && ypt->cor == *"R") {
            pilha[track - 2]->cor = *"R";
            pilha[track - 1]->cor = ypt->cor = *"N";
            track -= 2;
        } else {

            if (dir[track - 1] == 0) {
            ypt = pilha[track - 1];
            } else {
            xpt = pilha[track - 1];
            ypt = xpt->dir;
            xpt->dir = ypt->esq;
            ypt->esq = xpt;
            pilha[track - 2]->esq = ypt;////////////////////
            }

            xpt = pilha[track - 2];
            xpt->cor = *"R";
            ypt->cor = *"N";
            xpt->esq = ypt->dir;
            ypt->dir = xpt;////////////////

            if (xpt == ptraiz) {
                ptraiz = ypt;
            } else {
                if(dir[track - 3] == 0){pilha[track - 3]->esq = ypt;}
                else{pilha[track - 3]->dir = ypt;}
            }

            break;
        }
        } else {

        ypt = pilha[track - 2]->esq;

        if ((ypt != NULL) && (ypt->cor == *"R")) {
            pilha[track - 2]->cor = *"R";
            pilha[track - 1]->cor = ypt->cor = *"N";
            track -= 2;

        } else {

            if (dir[track - 1] == 1) {
            ypt = pilha[track - 1];
            } else {
            xpt = pilha[track - 1];
            ypt = xpt->esq;
            xpt->esq = ypt->dir;
            ypt->dir = xpt;
            pilha[track - 2]->dir = ypt;/////////////////
            }

            xpt = pilha[track - 2];
            ypt->cor = *"N";
            xpt->cor = *"R";
            xpt->dir = ypt->esq;
            ypt->esq = xpt;//////////////////

            if (xpt == ptraiz) {
            ptraiz = ypt;
            } else {
                if(dir[track - 3] == 0){pilha[track - 3]->esq = ypt;}
                else{pilha[track - 3]->dir = ypt;}
            }

            break;
        }

        }
    }
}

int main(){

    int a;
    while(scanf("%d", &a) != EOF){
        insereNo(a);
    }
    
    imprimeArv(ptraiz);
    return 0;
}

