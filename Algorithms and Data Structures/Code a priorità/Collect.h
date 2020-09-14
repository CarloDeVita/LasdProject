//DE VITA CARLO N86001634

//LIBRERIA PER LA GESTIONE DI UNA LISTA 


//DEFINIZIONE DELLA STRUTTURA 
struct collect {
	int id;
	void* x;
	struct collect* next;
};

typedef struct collect Collect;

//Inserisce un elemento non presente all'interno della lista
Collect* InsertLista(Collect *L,void* z);

Collect* CancLista(Collect *L,int n);

Collect* CercaElem(Collect* L, int n);

//Cancella la testa
Collect* CancTestaLista(Collect *L);

//Dealloca tutto
void DeallocaLista(Collect *L);
