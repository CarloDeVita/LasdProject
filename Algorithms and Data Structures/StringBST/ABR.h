//DE VITA CARLO N86001634

//LIBRERIA ABR CON CHIAVI DI TIPO STRINGA
//DEFINIZIONE STRUTTURA ABR
struct abr {
  
     char * parola;
     struct abr* dx;
     struct abr* sx;
};
typedef struct abr ABR;


//Inserimento in un Abr
ABR* inserimentoABR(ABR *T, char* str);

//Cancellazione di tutti i nodi da un Abr
ABR*  CancAlbero(ABR* T);

//Cancella un nodo data una stringa da un Abr
ABR* CancNodo(ABR* T,char* str);

//Cancella Nodo
ABR* cancellaroot(ABR* T);

//Trova il minimo del sottoalbero destro 
ABR* staccamin(ABR* P,ABR* T);

/*Cancella da un albero le stringhe che hanno
  valore compreso tra altre due stringhe in ingresso
  e profondità compresa tra due interi in ingresso */
ABR* cancInterv(ABR* T,char* str1,char* str2,int h1,int h2);

ABR* cancInterv1(ABR* T,char* str1,char* str2,int h1,int h2);

//Riversa in un array ordinato le chiavi dell'albero
int ArrayOrd(ABR* T,char** A,int i);

//Conta il numero di nodi dell'albero
int NumeroNodi(ABR* A);

//Crea un Abr identico,nelle chiavi e nella forma, ad un altro Abr.
ABR* duplicatoabr(ABR*T);

//Interfaccia per la creazione di un Abr bilanciato a partire da un altro Abr
ABR* Pbil(ABR*T);

//Algoritmo effettivo che crea l'Abr bilanciato
ABR* Pbileff(char** A,int a,int b);

//Stampa abr
void stampaAbr (ABR* T);

//Visita preorder
void preorder(ABR*T);

//Visita inorder
void inorder(ABR*T);

//Visita postorder
void postorder(ABR*T);

//Interfaccia algoritmo di costruzione ABR con n stringhe casuali
ABR* ABRcasual(int n,int len);

//Algoritmo effettivo che costruisce un ABR con n stringhe casuali
ABR* ABRcasual1(ABR*T,int n,int len);

//Verifica che due ABR sono identici nella forma e nelle chiavi
int VerifyEqual(ABR *T,ABR *T2);

//Controlla se un ABR è perfettamente bilanciato
int PbilControl(ABR *T);



 
