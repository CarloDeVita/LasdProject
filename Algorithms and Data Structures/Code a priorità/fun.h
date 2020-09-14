//funzioni per la gestione dei vari tipi di dato


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



struct struttura {
    int intero;
    char *stringa;
};

typedef struct struttura RECORD;


//creazione
void* creaint(void* k);

void* creafloat(void* k);

void* creastr(void *str);

void* crearecord(void* rec);
//confronto
int compint(void* a,void* b);

int compfloat(void* a,void* b);

int compstr(void* s1,void* s2);

int comprecord(void* rec1, void *rec2);

//stampa
void stampaint(void* k);

void stampafloat(void* k);

void stampastr(void *s);

void stamprecord(void* rec);
//inserimento
void* insintero(void);

void*insertstr(void);

void* insfloat(void);

void* insertrecord(void);
//parità
int pariint(void *k);

int parifloat(void *k);

int paristring(void *k);

int parirecord(void *rec);
//valori casuali
void* random_int(void);

void* random_float(void);

void* random_string(void);

void* random_record(void);

//gestione array
void StmArr(void **A,int n,dfun *fun);
//free record
void free_rec(void*rec);
