#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

struct arv{
    char caracter;
    struct arv* esq;
    struct arv* dir;
};

int tokenAbreParenteses(char token){
    if(token=='('){
        return 1;
    }else{
        return 0;
    }
}

int tokenOperador(char token){
    if(token=='+' || token=='-' || token=="*" || token=="/"){
        return 1; 
    }else{
        return 0;
    }
}

int tokenFechaParenteses(char token){
    if(token==')'){
        return 1;
    }else{
        return 0;
    }
}

void executaAbreParenteses(char tokenAtual,char tokenAntigo,Arvore* nodeAtual,Arvore* nodePrimario){
    if(tokenAntigo=='começo'){ // se for o primeiro nó da arvore
        nodeAtual = arvore_CriaVazia(); // cria um nó vazio
        nodePrimario = nodeAtual;
                
    }else{ 
        if(tokenOperador(tokenAntigo)){ // se o token antigo for um operador
            nodeAtual-> dir = arvore_CriaVazia; // cria um nó vazio na direita do nó atual
        }else{
            nodeAtual->esq = arvore_CriaVazia; // cria um nó vazio na esquerda do nó atual
        }
    }
            
}

void executaOperador(char tokenAtual,Arvore* nodeAtual){

    nodeAtual->caracter = tokenAtual;

}

void executaNumero(char tokenAtual,Arvore* nodeAtual){

    nodeAtual->caracter = tokenAtual;
}

void executaFechaParenteses(Arvore* nodeAtual,Arvore* nodePrimario){
    Arvore* nodePai = arvore_pai(nodePrimario,nodeAtual->caracter); // procura o pai do nó atual

    nodeAtual = nodePai; // torna o pai do nó atual como nó atual
}


void leArvore(){
    FILE* entrada;
    char c;

    entrada = fopen("entrada.txt","r");

//((3)+((4)∗(5)))
    char tokenAtual,tokenAntigo = 'começo';
    Arvore* nodeAtual;
    Arvore* nodePrimario;

    while(!feof(entrada)){
  
        fscanf("%c",&tokenAtual);

        if(tokenAbreParenteses(tokenAtual)){ // se o token for '('

            executaAbreParenteses(tokenAtual,tokenAntigo,nodeAtual,nodePrimario);

        }else if(tokenOperador(tokenAtual)){

            executaOperador(tokenAtual,nodeAtual);

        }else if(tokenFechaParenteses(tokenAtual)){
            if(nodeAtual=!nodePrimario){
                executaFechaParenteses(nodeAtual,nodePrimario);
            }

        }else{

            executaNumero(tokenAtual,nodeAtual);

        }

    }


    fclose(entrada);
}

Arvore* arvore_pai(Arvore* a,char c){
    if(arvore_Vazia(a)){
        return NULL;
    }

    if(((!arvore_Vazia(a->esq)) && (a->esq->caracter ==c)) || ((!arvore_Vazia(a->dir)) && (a->dir->caracter==c))){
        return a;
    }

    Arvore* aux = arvore_pai(a->esq,c);
    if(aux==NULL){
        aux = arvore_pai(a->dir,c);
    }
    return aux;    
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