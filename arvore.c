#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"


struct arv{
    char* caracter;
    int id;
    Arvore* esq;
    Arvore* dir;
};

int tokenAbreParenteses(char* token){
    if(token[0]=='('){
        return 1;
    }else{
        return 0;
    }
}

int tokenOperador(char* token){
    if(token[0]=='+' || token[0]=='-' || token[0]=='*' || token[0]=='/'){
        return 1;
    }else{
        return 0;
    }
}

int tokenFechaParenteses(char* token){
    if(token[0]==')'){
        return 1;
    }else{
        return 0;
    }
}

Arvore* executaAbreParenteses(char* tokenAtual,char* tokenAntigo,Arvore* nodeAtual,Arvore* nodePrimario){

    if(tokenOperador(tokenAntigo)){ // se o token antigo for um operador
        nodeAtual->dir = arvore_Cria(NULL,NULL); // cria um nó vazio na direita do nó atual
        nodeAtual = nodeAtual->dir;

    }else{
        nodeAtual->esq = arvore_Cria(NULL,NULL); // cria um nó vazio na esquerda do nó atual
        nodeAtual = nodeAtual->esq;
    }

    return nodeAtual;

}

void executaOperador(char* tokenAtual,Arvore* nodeAtual){

    nodeAtual->caracter = strdup(tokenAtual);

}

void executaNumero(char* tokenAtual,Arvore* nodeAtual){
    nodeAtual->caracter = strdup(tokenAtual);

}

Arvore* executaFechaParenteses(Arvore* nodeAtual,Arvore* nodePrimario){
    Arvore* nodePai = arvore_pai(nodePrimario,nodeAtual->caracter); // procura o pai do nó atual


    nodeAtual = nodePai; // torna o pai do nó atual como nó atual

    return nodeAtual;
}


Arvore* leArvore(){
    FILE* entrada;

    entrada = fopen("entrada.txt","r");

    char caracterEntrada,caracterInicial='h';

    char* tokenAtual, *tokenAntigo;
    Arvore* nodeAtual;
    Arvore* nodePrimario;

    tokenAntigo = &caracterInicial;

    while(!feof(entrada)){

//  ((((10)*(3))+(5))/((10)-(5)))
        fscanf(entrada,"%c",&caracterEntrada);

        tokenAtual = &caracterEntrada;



        if(tokenAbreParenteses(tokenAtual)){ // se o token for '('
            if(*tokenAntigo=='h') { // se for o primeiro nó da arvore
                nodeAtual = arvore_Cria(NULL, NULL); // cria um nó vazio
                nodePrimario = nodeAtual;
            }else
                nodeAtual = executaAbreParenteses(tokenAtual,tokenAntigo,nodeAtual,nodePrimario);

        }else if(tokenOperador(tokenAtual)){
            executaOperador(tokenAtual,nodeAtual);

        }else if(tokenFechaParenteses(tokenAtual)){
            if(nodeAtual!=nodePrimario){
                nodeAtual = executaFechaParenteses(nodeAtual,nodePrimario);
            }

        }else{ // Eh numero
            int i = 0;


            char numero[5];
            char* aux =(char*)malloc(5*sizeof(char));
            *aux = *tokenAtual;

            while(!tokenAbreParenteses(tokenAtual) && !tokenFechaParenteses(tokenAtual) && !tokenOperador(tokenAtual)){
                fscanf(entrada,"%c",&numero[i]);

                if(numero[i]==')'){
                    break;
                }

                *tokenAtual = numero[i];
                i++;

            }
            numero[i]='\0';

            aux[1] = '\0';
            strcat(aux,numero);

            strcpy(tokenAtual,aux);

            executaNumero(tokenAtual,nodeAtual);


            if(nodeAtual!=nodePrimario){
                nodeAtual = executaFechaParenteses(nodeAtual,nodePrimario);
            }
            tokenAtual[1] = '\0';

        }

        tokenAntigo = strdup(tokenAtual);

    }
    free(tokenAntigo);
    fclose(entrada);

    return nodePrimario;
}

float soma(float a, float b){
    return a+b;
}

float sub(float a,float b){
    return a-b;
}

float mult(float a,float b){
    return a*b;
}

float divisao(float a,float b){
    return a/b;
}

float calculaArvore(Arvore* arv,float result){
    if(!arvore_Vazia(arv->dir) && !arvore_Vazia(arv->esq)){
        if(*arv->caracter=='+'){
            result = soma(calculaArvore(arv->esq,result),calculaArvore(arv->dir,result));
            return result;
        }
        if(*arv->caracter=='-'){
            result = sub(calculaArvore(arv->esq,result),calculaArvore(arv->dir,result));
            return result;
        }
        if(*arv->caracter=='/'){
            result = divisao(calculaArvore(arv->esq,result),calculaArvore(arv->dir,result));
            return result;
        }
        if(*arv->caracter=='*'){
            result = mult(calculaArvore(arv->esq,result),calculaArvore(arv->dir,result));
            return result;
        }
    }else{
        return atof(arv->caracter); // transforma o char* em float
    }

    return result;

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

    printf("no%d[label=\"%s\"];\n",arv->id,arv->caracter);

    if(!arvore_Vazia(arv->esq) && !arvore_Vazia(arv->dir)){
        printf("no%d--no%d;\n",arv->id,arv->esq->id);
        imprimeArvore(arv->esq);
        printf("no%d--no%d;\n",arv->id,arv->dir->id);
        imprimeArvore(arv->dir);
    }


}

Arvore* arvore_pai(Arvore* a,char* c){
    if(arvore_Vazia(a)){
        return NULL;
    }

    if(!arvore_Vazia(a->esq)){
        if(a->esq->caracter==c){
            return a;
        }
    }
    if(!arvore_Vazia(a->dir)){
        if(a->dir->caracter==c){
            return a;
        }
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

Arvore* arvore_Cria(Arvore* e,Arvore* d){
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));
    a->caracter = NULL;
    a->esq = e;
    a->dir = d;
    return a;
}

Arvore* arvore_Libera(Arvore* a){
    if(!arvore_Vazia(a)){
        arvore_Libera(a->esq);
        arvore_Libera(a->dir);
        free(a->caracter);
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

