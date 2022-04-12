
#include"Lista.h"
void* allocaGrafoM(int k);
void* inserisciVerticeM(void*,int);
void inserisciArcoM(void*,int a,int b,float peso); //ricorda cotrollo a,b g->size
void* eliminaVerticeM(void*,int,int v);
void eliminaArcoM(void*,int a,int b);
ADJ* adiacentiM(void*A,int k,int v);
void freeAdjM(ADJ*);
void deallocaStrutturaM(void *A,int );
void stampaArchiM(void *A,int k);
