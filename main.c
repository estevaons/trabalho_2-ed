#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

int main(){
    Arvore* arv = leArvore();
    int x;
    int* i = &x;


    preencheId(arv,i);

    imprimeArvore(arv);

}
