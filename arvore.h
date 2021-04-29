#ifndef arvore_h
#define arvore_h

typedef struct arv Arvore;

void leArvore();

Arvore* arvore_CriaVazia();

Arvore* arvore_Cria(char c, Arvore* e, Arvore* d);

Arvore* arvore_Libera(Arvore* a);

int arvore_Vazia(Arvore* a);

void arvore_Imprime(Arvore* a);

int arvore_QtdFolhas(Arvore* a);

int arvore_altura(Arvore* a);


#endif