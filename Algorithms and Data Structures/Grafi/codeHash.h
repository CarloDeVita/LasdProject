#include"Hash.h"


struct Elem{
	void* nome;
	float p;
};

typedef struct Elem elem;

struct Funzioni{
	void* (*AllocaStruttura)();
	void* (*left)(void*,void*);
	void* (*right)(void*,void*);
	void* (*father)(void*,void*);
	int (*isNode)(void *, void *);
	void* (*getDato)(void*);
	void (*scambia)(void*,void*);
	void* (*getMassimo)(void*);//primo
	void* (*getUltimo)(void*);//ultimo nodo
	void* (*getPun)(void*,int);
	void (*addElem)(void*,void*);
	void* (*dealloca)(void*);//dealloca l'ultimo elemento
};

typedef struct Funzioni fun;

//funzioni per i dati
struct DFunzioni{
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
typedef struct DFunzioni dfun;




struct Coda{
	void *S;
	int heapsize;
	int (*comparison) (int x, int y);
	fun *f;
	dfun *df;
	htable *HashTab;
};
typedef struct Coda coda;

int MajorCompare(float a, float b);	
int MinusCompare(float a, float b);

int codaVuota(Q); 
coda* AllocaCoda(fun* f,int (*compare) (int,int), dfun* dfunzioni );
int Insert(coda *Q, void *x, float k);
elem* Max(coda *Q);
elem* EstraiMax(coda *Q);
void DecreaseKey(coda *Q, void* indirizzo, float k);
void IncreaseKey(coda *Q, void* indirizzo, float k);
void DeleteNode(coda *Q, void* x);
void AggiornaValoriInHash(coda* Q);
void cancellaTutto(coda *Q);
void deallocaTutto(coda* Q);
