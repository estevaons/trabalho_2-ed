#ifndef arvore_h
#define arvore_h

typedef struct arv Arvore;

Arvore* leArvore();

Arvore* arvore_CriaVazia();

Arvore* arvore_Cria(char c, Arvore* e, Arvore* d);

Arvore* arvore_Libera(Arvore* a);

int arvore_Vazia(Arvore* a);

void arvore_Imprime(Arvore* a);

int arvore_QtdFolhas(Arvore* a);

int arvore_altura(Arvore* a);

int tokenAbreParenteses(char token);

int tokenOperador(char token);

int tokenFechaParenteses(char token);

void executaAbreParenteses(char tokenAtual,char tokenAntigo,Arvore* nodeAtual,Arvore* nodePrimario);

void executaOperador(char tokenAtual,Arvore* nodeAtual);

void executaNumero(char tokenAtual,Arvore* nodeAtual);

void executaFechaParenteses(Arvore* nodeAtual,Arvore* nodePrimario);

Arvore* arvore_pai(Arvore* a,char c);


#endif