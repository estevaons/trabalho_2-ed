#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

struct arv{
    char caracter;
    struct arv* esq;
    struct arv* dir;
};

void leArvore(){
    FILE* entrada;
    char c;

    entrada = fopen("entrada.txt","r");

    while(!feof(entrada)){

        fscanf("%c",&c);

        if(c=='('){
            arvore_Cria(c,arvore_CriaVazia(),arvore_CriaVazia());
        }
    }


    fclose(entrada);
}

Arvore* arvore_CriaVazia(){
    return NULL;
}

Arvore* arvore_Cria(char c,Arvore* e,Arvore* d){
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));
    a->caracter = c;
    a->esq = e;
    a->dir = d;
    return a;
}

Arvore* arvore_Libera(Arvore* a){
    if(!arvore_Vazia(a)){
        arvore_Libera(a->esq);
        arvore_Libera(a->dir);
        free(a);
    }
    return NULL;
}

int arvore_Vazia(Arvore* a){
    if(a == NULL){
        return 1;
    }
    return 0;
}

void arvore_Imprime(Arvore* a){
    printf("(");
    if(!arvore_Vazia(a)){
        imprimeAluno(a->caracter);
        arvore_Imprime(a->esq);
        arvore_Imprime(a->dir);
    }
    printf(")");
}


int arvore_QtdFolhas(Arvore* a){
    if(arvore_Vazia(a->esq) && arvore_Vazia(a->dir)){
        return 1;
    }else if(!arvore_Vazia(a->esq) && arvore_Vazia(a->dir)){
        return arvore_QtdFolhas(a->esq);
    }else if(arvore_Vazia(a->esq) && !arvore_Vazia(a->dir)){
        return arvore_QtdFolhas(a->dir);
    }
    return arvore_QtdFolhas(a->esq) + arvore_QtdFolhas(a->dir);
}


static int maiorEntreOsDois (int a, int b){
    return (a>b) ? a : b; // retorna a se a>b ou b se a<b
}

int arvore_altura(Arvore* a){
    if(arvore_Vazia(a)){
        return -1;
    }else{
        return 1 + maiorEntreOsDois (arvore_altura(a->esq), arvore_altura(a->dir));
    }
}