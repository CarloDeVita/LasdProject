#include"Lista.h"

void* allocaGrafoL(int k);
void* inserisciVerticeL(void *,int);
void inserisciArcoL(void* ,int  ,int ,float);
void eliminaArcoL (void*,int ,int );
void* eliminaVerticeL(void*,int,int );
ADJ* ControlloArchi(ADJ* adj,int v);
ADJ* adiacentiL(void*A,int k,int v);
void freeAdjL(ADJ*); 
void deallocaStrutturaL(void* S,int );
void stampaArchiL(void*S,int);
