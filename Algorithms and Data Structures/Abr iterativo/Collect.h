//DE VITA CARLO N86001634

//LIBRERIA PER LA GESTIONE DI UNA LISTA DI ALBERI

//DEFINIZIONE DELLA STRUTTURA 'LISTA DI ALBERI'
struct collect {
	int id; //identificativo dell'albero 
	void* root;
	struct collect* next;
};

typedef struct collect abrCollect;
//Ricerca nodo nella lista e lo restituisce
abrCollect* CercaRoot(abrCollect* L,int x);

//Inserisce un ID non presente all'interno della lista
abrCollect* InsertCollect(abrCollect *L);

//stampa lista
void Stampalist(abrCollect* L); 

//cancella da lista
abrCollect* CancLista(abrCollect *L,int x);

//cancella
abrCollect* CancTestaLista(abrCollect *L);

//Dealloca tutto
void DeallocaLista(abrCollect *L);
