//DE VITA CARLO N86001634

//LIBRERIA PER LA GESTIONE DI UNA LISTA DI ALBERI

//DEFINIZIONE DELLA STRUTTURA 'LISTA DI ALBERI'
struct grafiCollect {
	int id; //identificativo dell'albero 
	void* G;
	struct grafiCollect* next;
};

typedef struct grafiCollect GCOLLECT;
//Ricerca nodo nella lista e lo restituisce
GCOLLECT* CercaGrafo(GCOLLECT* L,int x);

//Inserisce un ID non presente all'interno della lista
GCOLLECT* InsGrafiCollect(GCOLLECT *L);

//stampa lista
void Stampalist(GCOLLECT* L); 

//cancella da lista
GCOLLECT* CancLista(GCOLLECT *L,int x);

//cancella
GCOLLECT* CancTestaLista(GCOLLECT *L);

//Dealloca tutto
void DeallocaLista(GCOLLECT *L);
