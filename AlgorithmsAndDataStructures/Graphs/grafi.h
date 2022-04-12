#include"Lista.h"

struct FunzioniG{
	void* (*allocaGrafo)(int dim);
	void* (*inserisciVertice)(void* E,int dim);
	void (*inserisciArco)(void* E,int a,int b,float p); 
	void* (*eliminaVertice)(void* E,int dim,int v);
	void (*eliminaArco)(void* E,int a,int b);
	ADJ* (*adiacenti)(void* E, int dim, int v);	
	void (*deallocaStruttura) (void* E,int dim);
	void (*freeAdj)(ADJ* l);
	
};
typedef struct FunzioniG fung;



struct Grafo{
	void* S;
	fung *f;
	int size;
};	
typedef struct Grafo grafo;


grafo* CreaGrafo(fung* functions,int dim );
void DeallocaGrafo(grafo* G);
void InserimentoVertice(grafo* G);
void InserimentoArco(grafo* G,int a,int b, float p);
void EliminazioneVertice(grafo* G,int v);
void EliminazioneArco(grafo* G,int a,int b);
grafo* CreazioneTrasposto(grafo* G);
void StampaArchi(grafo* G);
void BFS(grafo *G,int s);
void PercorsoMinimo(grafo *G,int a , int b);
void PercorsoCasuale(grafo *G,int a,int b);
grafo* GrafoCasuale(int k,fung* f,float prob);
void ConversioneAdiacenza(grafo *G,fung *F);
void DFS(grafo *G);
int DFS_cicli(grafo *G);

grafo* GrafoParser(char* namef, fung* f);
void StampaArchiFile(grafo* G,char* path);
