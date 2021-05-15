#ifndef arvore_h
#define arvore_h

typedef struct arv Arvore;

Arvore* leArvore();

Arvore* arvore_CriaVazia();

Arvore* arvore_Cria(Arvore* e, Arvore* d);

Arvore* arvore_Libera(Arvore* a);

int arvore_Vazia(Arvore* a);

void arvore_Imprime(Arvore* a);

int tokenAbreParenteses(char* token);

int tokenOperador(char* token);

int tokenFechaParenteses(char* token);

float soma(float a,float b);

float sub(float a,float b);

float divisao(float a,float b);

float mult(float a,float b);

void preencheId(Arvore* arv,int* i);

float calculaArvore(Arvore* arv, float result);

void imprimeArvore(Arvore* arv,FILE* graphviz);

Arvore* executaAbreParenteses(char* tokenAtual,char* tokenAntigo,Arvore* nodeAtual,Arvore* nodePrimario);

void executaOperador(char* tokenAtual,Arvore* nodeAtual);

void executaNumero(char* tokenAtual,Arvore* nodeAtual);

Arvore* executaFechaParenteses(Arvore* nodeAtual,Arvore* nodePrimario);

Arvore* arvore_pai(Arvore* a,char* c);


#endif