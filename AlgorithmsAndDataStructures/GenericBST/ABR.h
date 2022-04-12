//DE VITA CARLO N86001634

//LIBRERIA ABR CON CHIAVI DI TIPO STRINGA
//DEFINIZIONE STRUTTURA ABR
struct abr {
     void *key;
     struct abr* dx;
     struct abr* sx;
};
typedef struct abr ABR;


struct funzioni{
	void (*tfree) (void*);
	int (*comp) (void*,void*);
	void* (*crea) (void*);
	void (*stamp) (void*);
	void* (*insert) (void);
	int (*pari) (void*);
	void* (*random) (void);
	/*FREEFUN tfree;
	CREAFUN crea;
	STAMPAFUN stamp;
	COMPFUN comp;
	INSFUN insert;
	PARIFUN pari;
	RANDFUN random;*/
};
typedef struct funzioni FUNZIONI;

//alloca nodo
ABR* AllocaNodo (ABR*T);

//creazione nodo
ABR* creanode(void*k,FUNZIONI *fun);

//Inserimento in un Abr
ABR* inserimentoABR(ABR *T, void*k,FUNZIONI *fun);

//Stampa (visita) di un Abr
void Stampabr(ABR* T,FUNZIONI *fun);

//Cancellazione di tutti i nodi da un Abr
ABR*  CancAlbero(ABR* T,FUNZIONI *fun);

//Cancella un nodo data una stringa da un Abr
ABR* CancNodo(ABR* T,void*k,FUNZIONI *fun);

//Cancella Nodo
ABR* cancellaroot(ABR* T,FUNZIONI *fun);

//Trova il minimo del sottoalbero destro 
ABR* staccamin(ABR* P,ABR* T);

/*Cancella da un albero le stringhe che hanno lunghezza
  pari o dispari, in funzione di un paramentro, e hanno
  valore compreso tra altre due stringhe in ingresso */
ABR* cancInterv(ABR* T,void*k1,void*k2,int h1,int h2,FUNZIONI *fun);

ABR* cancInterv1(ABR* T,void* k1,void *k2,int h1, int h2, FUNZIONI *fun);

//Riversa in un array ordinato le chiavi dell'albero
int ArrayOrd(ABR* T,void** A,int i,FUNZIONI *fun);

//Conta il numero di nodi dell'albero
int NumeroNodi(ABR* A);

//Crea un Abr identico,nelle chiavi e nella forma, ad un altro Abr.
ABR* duplicatoabr(ABR*T,FUNZIONI *fun);

//Interfaccia per la creazione di un Abr bilanciato a partire da un altro Abr
ABR* Pbil(ABR*T,FUNZIONI *fun);

//Algoritmo effettivo che crea l'Abr bilanciato
ABR* Pbileff(void** A,int a,int b,FUNZIONI *fun);

//Controlla se un ABR è perfettamente bilanciato
int PbilControl(ABR *T);

//stampa
void stampaAbr (ABR* T,FUNZIONI *fun);

//Visita preorder
void preorder(ABR*T,FUNZIONI *fun);

//Visita inorder
void inorder(ABR*T,FUNZIONI *fun);

//Visita postorder
void postorder(ABR*T,FUNZIONI *fun);

//Interfaccia algoritmo di costruzione ABR con n stringhe casuali
ABR* ABRcasual(int n,FUNZIONI *fun);

//Algoritmo effettivo che costruisce un ABR con n stringhe casuali
ABR* ABRcasual1(ABR*T,int n,FUNZIONI *fun);

//Verifica che due ABR sono identici nella forma e nelle chiavi
int VerifyEqual(ABR*T,ABR*T2,FUNZIONI *fun);

//deallocazione array 
void DeallocArr(void ** A,int n,FUNZIONI *fun);


/*------------------------------------------------------------------*/


 
