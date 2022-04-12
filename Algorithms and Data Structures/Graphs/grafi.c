#include"grafi.h"
#include"Lista.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"codeHash.h"
#include"codeAlberi.h"
#include"fun.h"
#include"Collect.h"
#include<limits.h>

//Funzione di allocazione del grafo
grafo* CreaGrafo(fung* functions,int dim){
	grafo* newGrafo = malloc(sizeof(grafo));
	newGrafo->f = malloc(sizeof(fung));
	memcpy(newGrafo->f,functions,sizeof(fung));
	newGrafo->S = functions->allocaGrafo(dim);
	newGrafo->size = dim;
	return newGrafo;
}

//Funzione di deallocazione del grafo
void DeallocaGrafo(grafo* G){
	if(G != NULL){
		G->f->deallocaStruttura(G->S,G->size);
		free(G->f);
 	}
}


//Funzione che stampa il grafo
void StampaArchi(grafo* G){
	int i;
	ADJ *adj,*l;
	if(G != NULL){
		for(i=0;i<G->size;i++){
			adj = G->f->adiacenti(G->S,G->size,i);
			l = adj;
			printf("\n%d) ",i);
			while(l != NULL){
				printf("->[ %d, %.2f ]",l->key,l->p);
				l = l->next;
			}
			G->f->freeAdj(adj);
		}	
	}
	else
		printf("Il grafo inserito è vuoto\n");
}

//Funzione che stampa il grafo su file
void StampaArchiFile(grafo* G,char* path){
	int i;
	ADJ *adj,*l;
	FILE* fd = fopen(path,"w+");
	if(fd != NULL){
		if(G != NULL){
			fprintf(fd,"(%d) ",G->size);
			for(i=0; i<G->size; i++){
				adj = G->f->adiacenti(G->S,G->size,i);
				l = adj;
				fprintf(fd,"\n%d ",i);
				if( l!= NULL)
					fprintf(fd,"->");
				while(l != NULL){
					fprintf(fd,"( %d, %.2f )",l->key,l->p);
					l = l->next;
					if(l != NULL) fprintf(fd,",");
				}
				fprintf(fd,";");
				G->f->freeAdj(adj);
			}	
			fprintf(fd,".");
			fclose(fd);
		}
		else
			fprintf(fd,"Il grafo inserito è vuoto\n");
	}
}


//Funzione di inserimento di un vertice
void InserimentoVertice(grafo* G){
	G->S = G->f->inserisciVertice(G->S, G->size);
	G->size++;
}

//Funzione di inserimento di un arco
void InserimentoArco(grafo* G, int a, int b,float p){
	//controllo che a e b siano compresi tra 0 e dimensione(se esistono!)
	if ( a<0 || a>=G->size || b<0 || b>=G->size )
		printf("Errore creazione arco: uno dei vertici non esistente\n");
	else
		G->f->inserisciArco(G->S, a, b, p);
}

//Funzione di eliminazione di un vertice
void EliminazioneVertice(grafo* G, int v){
	if (v<0 || v>=G->size)
		printf("Errore eliminazione vertice: vertice non esistente.\n");
	else{
		G->S = G->f->eliminaVertice(G->S,G->size,v);	
		G->size--;
	}
}

//Funzione di eliminazione di un arco
void EliminazioneArco(grafo* G, int a, int b){
	if ( a<0 || a>=G->size || b<0 || b>=G->size )
		printf("Errore eliminazione arco: uno dei vertici non esistente\n");
	else
		G->f->eliminaArco(G->S,a,b);
}

//Funzione che crea il grafo trasposto
grafo *CreazioneTrasposto(grafo* G){
	fung* f2 = malloc(sizeof(fung));
	memcpy(f2,G->f,sizeof(fung));
	grafo* newG = CreaGrafo(f2, G->size);
	int i;
	ADJ* L,*tmp;
	for(i=0; i<G->size; i++){
		L = G->f->adiacenti(G->S,G->size,i);
		tmp = L;
		while(tmp != NULL){
			G->f->inserisciArco(newG->S,tmp->key,i,tmp->p);
			tmp = tmp->next;
		}
		G->f->freeAdj(L);
	}
	return newG;
}

//Funzione che converte la struttura di adiacenza di un grafo
void ConversioneAdiacenza(grafo *G,fung *F){
	void *A,*X;
	int i;
	ADJ *adj,*l;
	fung *tmp;
	A = F->allocaGrafo(G->size);
	for(i=0;i<G->size;i++){
		adj=G->f->adiacenti(G->S,G->size,i);//uso la vecchia funzione per trovare gli adiacenti
		l = adj;
		while( l != NULL ){
			F->inserisciArco(A, i, l->key, l->p);//uso la nuova funzione per inserire
			l = l->next;
		}
		G->f->freeAdj(adj);
	}
	/*Assegno nuova struttura di adiacenza e libero area occupata dalla vecchia*/
	G->f->deallocaStruttura( G->S,G->size );
	G->S = A;
	/* Assegno nuova struttura delle funzioni e libero area occupata dalla vecchia */
	tmp=G->f; 
	G->f=F;
	free(tmp);
}


//Funzione che crea un grafo casuale, data una probabilità di generazione arco
grafo* GrafoCasuale(int k,fung* f,float prob){
	srand(time(NULL));
	grafo *G= CreaGrafo(f,k);
	int i,j;
	float peso;
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			if( (float)rand()/(float)RAND_MAX <= prob ){
				peso = ( (float)rand()/(float)RAND_MAX ) * 10; //peso casuale tra 0 e 10
				InserimentoArco(G,i,j,peso);
			}
		}	
	}
	return G;
}	




//VISITE

//Inizializzo array dei colori
void Init(grafo *G,int *col){
	int i,k;
	k=G->size;
	for( i=0;i<k;i++)
		col[i]=0;
}

//Visita in ampiezza
void BFS(grafo *G,int s){
	int *Q,*col,testa,coda,m,v;
	ADJ *adj,*l;
	if(s >= G->size || s<0)
		printf("Errore inserimento sorgente.\n");
	else{
		m=G->size;
		Q=malloc(m*sizeof(int));
		col=malloc(m*sizeof(int));
		Init(G,col);
		col[s]=1; //grigio
		testa=0;
		coda=0;
		Q[coda++]=s;
		while(testa < coda){
			v=Q[testa];
			printf("%d ",v);			
			adj=G->f->adiacenti(G->S,G->size,v);
			l = adj;
			while(l != NULL){
				if( col[l->key] == 0 ){
					Q[coda++]=l->key;
					col[l->key] = 1;
				}
				l=l->next;
			}	
			testa++;
			col[v]=2;
			G->f->freeAdj(adj);		
		}
		free(Q);
		free(col);
	}		
}

//Visita in profondità

void DFS_visit(grafo *G,int v,int *col){
	ADJ *adj,*tmp;
	col[v]=1;
	printf("%d ",v);//STAMPA VERTICE
	adj=G->f->adiacenti(G->S,G->size,v);
	tmp = adj;
	while(tmp != NULL){
		if( col[tmp->key] == 0 )
			DFS_visit(G,tmp->key,col);
		tmp=tmp->next;
	}
	col[v]=2;
	G->f->freeAdj(adj);
}


void DFS(grafo *G){
	int i,k,*col;
	k=G->size;
	col=malloc(k*sizeof(int));
	Init(G,col);
	for(i=0;i<k;i++)
		if(col[i]==0)
			DFS_visit(G,i,col);
	free(col);
}	

//PERCORSI MINIMI E CASUALI

//Stampa del percorso tra due vertici
void StampaPercorso(grafo* G,int a,int b,int *pred){
	if (a==b)
		printf("%d ",a);
	else if (pred[b]== -1)
		printf("Non c'è percorso.\n");
	else{
		StampaPercorso(G,a,pred[b],pred);
		printf("%d ",b);
	}
}



//PERCORSO MINIMO

//Inizializzo array di colori, distanze e predecessori
void Init_Pminimo(grafo *G,int *col,int *pred,int *dist){
	int i,k;
	k=G->size;
	for( i=0;i<k;i++){
		col[i]=0;
		dist[i]= -1;
		pred[i]= -1;	
	}
}

//BFS che trova i percorsi minimi tramite array dei predecessori
void BFS_PercorsiMinimi(grafo *G,int *pred, int* dist ,int s){
	int *Q,testa,coda,m,v;
	ADJ *adj, *l;
	if(s >= G->size)
		printf("Errore.\n");
	else{
		int*col;
		m=G->size;
		Q=malloc(m*sizeof(int));
		col=malloc(m*sizeof(int));
		Init_Pminimo(G,col,pred,dist);
		col[s]=1; //grigio
		dist[s]=0;
		testa=0;
		coda=0;
		Q[coda++]=s;		
		
		while(testa < coda){
			v=Q[testa];
			adj=G->f->adiacenti(G->S,G->size,v);
			l = adj;
			while(l != NULL){
				if( col[l->key] == 0 ){ 
					Q[coda++]=l->key;
					col[ l->key ] = 1;
					dist[ l->key ]= dist[v]+1;
					pred[ l->key]= v;
				}
				l = l->next;
			}	
			testa++;
			col[v]=2;
			G->f->freeAdj(adj);		
		}
		free(Q);
		free(col);
	}		
}

//Trova percorso minimo e lo stampa
void PercorsoMinimo(grafo *G,int a , int b){
	int k,*pred,*dist;
	k=G->size;
	if ( a<0 || a>=k || b<0 || b>=k ) printf("Errore inserimento vertici\n");
	else{
		pred=malloc(k*sizeof(int));
		dist=malloc(k*sizeof(int));	
		BFS_PercorsiMinimi(G,pred,dist,a);	
		StampaPercorso(G,a,b,pred);
		free(pred);
		free(dist);
	}
}	


//PERCORSO CASUALE
//Inizializzo array di colori e predecessori
void Init_Pcasuale(grafo *G,int *col,int *pred){
	int i,k;
	k=G->size;
	for( i=0;i<k;i++){
		col[i]=0;
		pred[i]= -1;	
	}
}

//DFS VISIT per trovare percorsi tramite array dei predecessori
void DFS_visit_Percorso(grafo *G,int v,int *col,int* pred){
	ADJ *adj,*l;
	col[v]=1;
	adj=G->f->adiacenti(G->S,G->size,v);	
	l = adj;
	while( l != NULL ){
		if( col[l->key]== 0 ){
			pred[l->key]= v;
			DFS_visit_Percorso(G,l->key,col,pred);
		}			
		l = l->next;
	}
	col[v]=2;
	G->f->freeAdj(adj);
}	

//Trova percorso casuale tra due vertici e lo stampa
void PercorsoCasuale(grafo *G,int a, int b){
	int i,k,*col,*pred;
	k=G->size;
	if ( a<0 || a>=k || b<0 || b>=k ) printf("Errore inserimento vertici\n");
	else{
		col=malloc(k*sizeof(int));
		pred=malloc(k*sizeof(int));
		Init_Pcasuale(G,col,pred);
		DFS_visit_Percorso(G,a,col,pred);
		StampaPercorso(G,a,b,pred);
		free(pred);
		free(col);
	}
}

//DFS che controlla se il grafo è ciclico
int DFS_visit_cicli(grafo *G,int v,int *col){
	int ciclo = 0;
	ADJ *adj,*l;
	col[v]=1;
	adj=G->f->adiacenti(G->S,G->size,v);
	l = adj;
	while( (ciclo == 0) && (l != NULL) ){
		if( col[l->key] == 0 )
			ciclo = DFS_visit_cicli(G,l->key,col);
		else if ( col[l->key] == 1 )
			ciclo = 1;
		l=l->next;
	}
	col[v]=2;
	G->f->freeAdj(adj);
	return ciclo;
}

int DFS_cicli(grafo *G){
	int i,k,*col,ciclo;
	k=G->size;
	col=malloc(k*sizeof(int));
	Init(G,col);
	ciclo=0;
	i=0;
	while(i< k && ciclo==0){
		if (col[i]==0)
			ciclo=DFS_visit_cicli(G,i,col);
		i++;
	}
	return ciclo;
}

		 

void init_Dijkstra(grafo* G, float* dist, int *pred,fun* f, dfun *df){
	//Funzioni per dati e coda (Interi, alberi)
	df->crea=&creaint;   
	df->comp=&compint;
	df->tfree=&free;
	df->stamp=&stampaint;
	df->insert=&insintero;
	
	f->AllocaStruttura = AllocaStrutturaH;
    f->left = leftH;
    f->right = rightH;
    f->father = fatherH;
    f->isNode = isNodeH;
    f->getDato = getDatoH;
    f->scambia = scambiaH;
    f->getMassimo = getMassimoH;
    f->getUltimo = getUltimoH;
    f->getPun = getPunH;
    f->addElem = addElemH;
    f->dealloca = deallocaH;
    
    int i;
    for(i=0;i<G->size;i++){
    	pred[i] = -1;
    	dist[i] = 1000;
    }
    
}	

void relax(coda *Q,int src, int dest, float p, int* pred, float* dist){
	if(dist[dest] > dist[src] + p){
		printf("vecchia %f -> nuova %f\n",dist[dest],dist[src]+p);
		dist[dest] = dist[src] + p;
		pred[dest] = src;
		IncreaseKey(Q, (void*)dest, dist[dest]);
		printf(" il minimo è: %f\n",Max(Q));
	}
}	

//Dijkstra
void Dijkstra(grafo *G,coda *Q,int s,int* pred, float* dist){
	if(s < 0 || s >= G->size ) printf("Errore sorgente\n");
	else{
		int i,j=0;
		elem* nodo;
		void* sup;
		
		dist[s] = 0;
		
		for(i=0;i< G->size; i++){
			//sup = malloc(sizeof(int));
			//*(int*)sup = i;
			Insert(Q,(void*)i,dist[i]);
			//inseriti = InserisciLista(inseriti, i, sup);
		}
		while(!codaVuota(Q)){
			nodo = EstraiMax(Q);
			
			printf("nodo %d\n",(int)(nodo->nome));
			ADJ *l=NULL, *adj = G->f->adiacenti(G->S,G->size,nodo->nome);
			l = adj;
			while(l != NULL){
				relax(Q,nodo->nome,l->key,l->p,pred,dist);
				l = l->next;
			}
		}	
		
		
	}	
	
}

void P_Dijkstra(grafo *G,int s){
	if(s < 0 || s >= G->size ) printf("Errore sorgente\n");
	else{
		int i;
		int *pred = malloc(G->size * sizeof(int));
		float *dist = malloc(G->size * sizeof(float));
		dfun *df = malloc(sizeof(dfun));// dato di tipo intero
		fun *f = malloc(sizeof(fun)); //funzioni per code heap
		init_Dijkstra(G,dist,pred,f,df);
		coda *Q = AllocaCoda(f, &MinusCompare, df);
		Dijkstra(G,Q,s,pred,dist);
		/*for(i = 0; i<G->size;i++)
			printf("nodo %d distanza %f\n",i,dist[i]);*/
	}
}

	





















//PARSER	

//Enumerazione dei simboli
typedef enum {LPAR, RPAR, ARROW, COMMA, SEMICOLON, DOT} symbols;

//Funzione che salta gli spazi,newline e carattere di tabulazione
void avoidSpace (FILE* fd){
	int c;
	while (   ((c=fgetc(fd))==' ') || (c=='\n') || (c=='\t') ); 
	ungetc(c,fd); //rimette il carattere dentro perchè va bene.
}

//Funzione che controlla se il carattere letto è quello che ci si aspetta
int match (FILE *fd, symbols sym){
	char c,c2,r;
	int v = 1;
	avoidSpace(fd);
	r = fgetc(fd);
	switch(sym){
		case LPAR:
			c = '(';
			break;
			
		case RPAR:
			c = ')';
			break;
			
		case COMMA:
			c = ',';
			break;
		
		case SEMICOLON:
			c = ';'; 
			break;
		
		case DOT:
			c = '.';
			break;
		
		case ARROW:
			c = '-';
			c2 = '>';
			break;
	}
	
	if ( c != r ){
		ungetc(r,fd);
		v = 0;
	}
	return ( v && (!(c == '-') || (fgetc(fd)==c2) ) ); //ritorna il confronto e, se è un trattino controlla che quello di dopo e un '>'
}

//Funzione che descrive l'errore e indica la posizione in cui si presenta all'interno del file
void syntaxErr (symbols sym, int pos) {
	switch(sym){
		case LPAR:
			printf("Error: expected '(' at position %d\n",pos);
			break;
		
		case RPAR:
			printf("Error: expected ')' at position %d\n",pos);
			break;
		
		case COMMA:
			printf("Error: expected ',' at position %d\n",pos);
			break;
			
		case SEMICOLON:
			printf("Error: expected ';' at position %d\n",pos);
			break;
			
		case DOT:
			printf("Error: expected '.' at position %d\n",pos);
			break;
			
		case ARROW:
			printf("Error: expected '->' at position %d\n",pos);
			break;
	}
}


//Funzione che controlla se la stringa letta è un intero
int ParseInt(FILE *fd, int *num){
	int v=0,i=0,c;
	char buf[100];
	avoidSpace(fd);
	while ( (c=fgetc(fd)) >= 48 && (c <= 57) ){
		buf[i] = (char)c;
		i++;
	}
	ungetc(c,fd);
	if(i!=0){
		v=1;
		buf[i]='\0';
		*num = atoi(buf);
	}
	return v;
}

//Funzione che controlla se la stringa letta è un float
int ParseFloat(FILE *fd, float *num){
	int v=0,i=0,c;
	char buf[100];
	avoidSpace(fd);
	while ( (c=fgetc(fd))>= 48 && (c <= 57) ){
		buf[i++] = (char)c;
	}
	if (c == '.'){
		buf[i++] = c;
		while ( (c=fgetc(fd))>= 48 && (c <= 57) )
			buf[i++] = (char)c;
	}
	ungetc(c,fd);
	if(i!=0){
		v=1;
		buf[i]='\0';
		*num = atof(buf);
	}
	return v;
}


//CONTROLLO CHE IL FILE RISPETTA LA DEFINIZIONE DEL GRAFO E LO CREA


int arco(FILE* fd, grafo* G,int x){
	int v, c, y;
	float p;
	if ( match(fd,LPAR)){
		v = ParseInt(fd, &y);
		if (v){
			if(y < G->size){
				if ( match(fd,COMMA) ){
					v = ParseFloat(fd,&p);
					if(v){
						if (match(fd,RPAR) ){
							InserimentoArco(G,x,y,p);
						}
						else{
							v = 0;
							syntaxErr(RPAR,ftell(fd));
						}
					}
					else{
						printf("Errore parser float\n");
					}
				}
				else{
					v = 0;
					syntaxErr(COMMA, ftell(fd));
				}
			}
			else{
				v = 0;
				printf("Il nodo %d non esiste nel grafo\n",y);
			}
		}		
		else{
			v = 0;
			printf("Errore parser intero\n");
		}
	}
	else{
		v = 0;
		syntaxErr(LPAR, ftell(fd));
	}
	return v;
}
	
		
		
		

int lista_archi(grafo *G,FILE *fd,int x){
	int v=0,c;
	v = arco(fd,G,x);
	while (v && match(fd,COMMA) ) 
		v = arco(fd,G,x);
	return v;		
}			


int adiacenze (grafo* G, FILE* fd){
	int v,x,c;
	v = ParseInt(fd,&x);
	if(v){	
		if (x < G->size ){			
			if( match(fd,ARROW) )
				v = lista_archi(G,fd,x); 
			if ( !(match(fd,SEMICOLON)) ){ 
					v = 0;
					syntaxErr(SEMICOLON,ftell(fd));
				}
		}
		else{
			v = 0;
			printf("Il nodo %d non esiste nel grafo\n",x);
		}
	}else{
		printf("Errore parser intero\n");
	}
	return v;
}


grafo* GrafoParser(char* namef, fung* f){
	grafo *G = NULL;
	FILE *fd = fopen(namef,"r+");
	int dim, v;
	int c;
	if(fd != NULL){ 
		if ( match(fd,LPAR)){
			v = ParseInt(fd,&dim);
			if(v){
				if( match(fd,RPAR)){
					G = CreaGrafo(f,dim);
					v = adiacenze(G,fd);
					while ( v && !(match(fd,DOT)) )  
						v = adiacenze(G,fd);
					if (!v){
						DeallocaGrafo(G);
						G = NULL;
					}
				}
				else{
					syntaxErr(RPAR,ftell(fd));	
				}
			}
			else{
				printf("Errore parser intero\n");
			}
		}
		else{
			syntaxErr(LPAR,ftell(fd));
		}
		fclose(fd);
	}	
	return G;
}	



