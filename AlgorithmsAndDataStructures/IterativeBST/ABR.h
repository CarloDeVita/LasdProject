struct abr {
  
     void *key;
     struct abr* dx;
     struct abr* sx;
};
typedef struct abr ABR;

typedef void (*FREEFUN) (void*);
typedef int (*COMPFUN) (void*,void*);
typedef void* (*CREAFUN) (void*);
typedef void (*STAMPAFUN) (void*);
typedef void* (*INSFUN) (void);
typedef int (*PARIFUN) (void*);
typedef void* (*RANDFUN) (void);

struct funzioni{
	FREEFUN tfree;
	CREAFUN crea;
	STAMPAFUN stamp;
	COMPFUN comp;
	INSFUN insert;
	PARIFUN pari;
	RANDFUN random;
};
typedef struct funzioni FUNZIONI;

//Inserimento in un Abr
ABR *InserimentoABR(ABR *T, void*k,FUNZIONI *fun);

//creazione nodo
ABR* creanode(void*k,FUNZIONI *fun);

//Stampa abr
void Stampabr(ABR* T,FUNZIONI *fun);

//preorder
void preorder (ABR*T,FUNZIONI *fun);

//inorder
void inorder (ABR*T,FUNZIONI *fun);

//postorder
void postorder (ABR*T, FUNZIONI *fun);

//cancella albero
ABR*  CancAlbero(ABR* T,FUNZIONI *fun);

//cancella nodo
ABR* CancNodo(ABR* T,void*k,FUNZIONI *fun);

//cancella radice
ABR* cancellaroot(ABR* T,FUNZIONI *fun);

//torna il minimo del sottoalbero destro
ABR* staccamin(ABR* P,ABR* T);

//cancella valori pari o dispari compresi tra altri due valori
ABR* CancIntervallo(ABR* T,int tipo,void *k1, void *k2, FUNZIONI *fun);

//valori in array ordinato
int ArrayOrd(ABR* T,void **A, int i,FUNZIONI *fun);

//numero nodi
int NumeroNodi(ABR* T);

//costruzione abr casuale
ABR* ABRcasual(int n,FUNZIONI *fun);

//duplicato ABR
ABR* duplicatoabr(ABR* T,FUNZIONI *fun);

//verifica se due ABR sono identici
int VerifyEqual(ABR* T,ABR* T2,FUNZIONI *fun);

//Costruzione di un abr perfettamente bilanciato a partire da un altro abr
ABR* Pbil(ABR*T,FUNZIONI *fun);

//deallocazione array
void DeallocArr(void ** A,int n,FUNZIONI *fun);


