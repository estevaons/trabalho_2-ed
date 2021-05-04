#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

int main(){
    Arvore* arv = leArvore();
    int x=1;
    int* i = &x;
    float resultFinal;
    float result = 0;



   resultFinal = calculaArvore(arv,result);
   printf("%.2f\n",resultFinal);

    preencheId(arv,i);

    printf("strict graph {\n\n");
    imprimeArvore(arv);
    printf("}\n");


    arvore_Libera(arv);

}
