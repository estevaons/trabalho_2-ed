#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"


struct arv{
    char caracter;
    int id;
    Arvore* esq;
    Arvore* dir;
};

int tokenAbreParenteses(char token){
    if(token=='('){
        return 1;
    }else{
        return 0;
    }
}

int tokenOperador(char token){
    if(token=='+' || token=='-' || token=='*' || token=='/'){
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
// ((((5)-(3))*((4)/(1)))+(10))
void executaAbreParenteses(char tokenAtual,char tokenAntigo,Arvore* nodeAtual,Arvore* nodePrimario){
    if(tokenAntigo=='h'){ // se for o primeiro nó da arvore
        nodeAtual = arvore_Cria('0',NULL,NULL); // cria um nó vazio
        nodePrimario = nodeAtual;
                
    }else{ 
        if(tokenOperador(tokenAntigo)){ // se o token antigo for um operador
            
            nodeAtual->dir = arvore_Cria('0',NULL,NULL); // cria um nó vazio na direita do nó atual
            nodeAtual = nodeAtual->dir;
            
        }else{   
            
            nodeAtual->esq = arvore_Cria('0',NULL,NULL); // cria um nó vazio na esquerda do nó atual
            printf("2\n");
            nodeAtual = nodeAtual->esq; 
            
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


Arvore* leArvore(){
    FILE* entrada;

    entrada = fopen("entrada.txt","r");

    char tokenAtual,tokenAntigo = 'h';
    Arvore* nodeAtual;
    Arvore* nodePrimario;

    while(!feof(entrada)){
  
        fscanf(entrada,"%c",&tokenAtual);

        if(tokenAbreParenteses(tokenAtual)){ // se o token for '('
            
            executaAbreParenteses(tokenAtual,tokenAntigo,nodeAtual,nodePrimario);  

        }else if(tokenOperador(tokenAtual)){

            executaOperador(tokenAtual,nodeAtual);

        }else if(tokenFechaParenteses(tokenAtual)){
            if(nodeAtual!=nodePrimario){
                executaFechaParenteses(nodeAtual,nodePrimario);
            }

        }else{

            executaNumero(tokenAtual,nodeAtual);

        }

        tokenAntigo = tokenAtual;

    }
    fclose(entrada);
    
    return nodePrimario;
}

int soma(int a, int b){
    return a+b;
}

int sub(int a,int b){
    return a-b;
}

int mult(int a,int b){
    return a*b;
}

int divisao(int a,int b){
    return a/b;
}

char calculaArvore(Arvore* arv){
    if(!arvore_Vazia(arv->dir) && !arvore_Vazia(arv->esq)){
        if(arv->caracter=='+'){
            return (char)soma((int)calculaArvore(arv->dir),(int)calculaArvore(arv->esq));
        }
        if(arv->caracter=='-'){
            return (char)sub((int)calculaArvore(arv->dir),(int)calculaArvore(arv->esq));
        }
        if(arv->caracter=='/'){
            return (char)divisao((int)calculaArvore(arv->dir),(int)calculaArvore(arv->esq));
        }
        if(arv->caracter=='*'){
            return (char)mult((int)calculaArvore(arv->dir),(int)calculaArvore(arv->esq));
        }
    }

    return arv->caracter;
    
}

void preencheId(Arvore* arv,int* i){
    arv->id = *i;
    *i = *i+1;
    if(!arvore_Vazia(arv->esq) && !arvore_Vazia(arv->dir)){
        preencheId(arv->esq,i);
        preencheId(arv->dir,i);
    }
    
}

void imprimeArvore(Arvore* arv){
    printf("strict graph {\n\n");
    
    printf("no%d[label=\"%c\"];\n",arv->id,arv->caracter);

    if(!arvore_Vazia(arv->esq) && !arvore_Vazia(arv->dir)){
        printf("no%d--no%d;\n",arv->id,arv->esq->id);
        imprimeArvore(arv->esq);
        printf("no%d--no%d;\n",arv->id,arv->dir->id);
        imprimeArvore(arv->dir);      
    }
    printf("}\n");

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