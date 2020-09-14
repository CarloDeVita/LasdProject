struct HashElem{
	void *ind;//chiave per trovare l'indirizzo
	void *k;//indirizzo suo reale
};
typedef struct HashElem helem;

struct List{
   	helem *data;
	struct List* next;
};
typedef struct List hlist;

struct Table{
	hlist **table;
	int n; //per rispettare regola euristica --> tot inseriti/n = 1;
	int totInseriti;
};
typedef struct Table htable;

htable *CreaHash();
void InserimentoHash(htable *tab, void *i,void *x);
void CancellazioneHash(htable *tab, void *i);
void cambiaVal(htable *tab, void* i, void*x);
helem* HashSearch( htable* tab, void *i); 
void scambiaValoriHash(htable *tab , void* x , void* y);
void setValoreHash(htable *tab, void *x, void* key);
