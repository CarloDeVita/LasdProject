#include"Lista.h"

struct ListaAdiacenza{
	ADJ** E;
	int dim;
};
typedef struct ListaAdiacenza adjList;

void* traspostoL(void* adjlist);
adjList* allocaAdjList(int dim);
int getDimL(void* E);
void* inserisciVerticeL(void *,int);
void inserisciArcoL(void* ,int  ,int ,float);
void eliminaArcoL (void*,int ,int );
void* eliminaVerticeL(void*,int);
ADJ* ControlloArchi(ADJ* adj,int v);
ADJ* adiacentiL(void*A,int v);
void freeAdjL(ADJ*); 
void deallocaStrutturaL(void* S);
void* parserL(char*);
void stampaArchiL(void*S,int);
float hL(void*,int,int);
