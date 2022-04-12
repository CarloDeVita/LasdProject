#include"grafi.h"
#include"Lista.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"codeHash.h"
#include"codeAlberi.h"
//#include"fun.h"
#include"Collect.h"
#include<limits.h>
#include"posizione.h"

void freeVisita(visita* vis){
	free(vis->pred);
	free(vis->col);
	free(vis);
}

//Funzione di allocazione del grafo (passare la struttura)
grafo* CreaGrafo(fung* functions,void* E){
	grafo* newGrafo = malloc(sizeof(grafo));
	newGrafo->f = malloc(sizeof(fung));
	memcpy(newGrafo->f,functions,sizeof(fung));
	newGrafo->S = E;
	newGrafo->size = functions->getDim(E);
	return newGrafo;
}

//Funzione di deallocazione del grafo
void DeallocaGrafo(grafo* G){
	if(G != NULL){
		G->f->deallocaStruttura(G->S);
		free(G->f);
		free(G);
 	}
}


//Funzione che stampa il grafo
void StampaArchi(grafo* G){
	int i;
	ADJ *adj,*l;
	if(G != NULL){
		for(i=0;i<G->size;i++){
			adj = G->f->adiacenti(G->S,i);
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
				adj = G->f->adiacenti(G->S,i);
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
void InserimentoVertice(grafo* G,int v){
	G->S = G->f->inserisciVertice(G->S,v);
	if (G->f->tipo <=2) G->size++;
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
		G->S = G->f->eliminaVertice(G->S,v);
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

grafo *CreazioneTrasposto(grafo *G){
	void *S = G->f->trasposto(G->S);
	grafo *newG = CreaGrafo(G->f,S);
	return newG;
}

/*grafo *CreazioneTrasposto(grafo* G){
	if(G->f->tipo == 3) return G; //se è un grafo implicito, il trasposto sarà il grafo stesso

	fung* f2 = malloc(sizeof(fung));
	memcpy(f2,G->f,sizeof(fung));
	void* E
	grafo* newG = CreaGrafo(f2, dim);//mi devo trovare le righe e colonne e poi invocare creaGrafo per le mappe di char
	int i;
	ADJ* L,*tmp;
	for(i=0; i<G->size; i++){
		L = G->f->adiacenti(G->S,i);
		tmp = L;
		while(tmp != NULL){
			G->f->inserisciArco(newG->S,tmp->key,i,tmp->p);
			tmp = tmp->next;
		}
		G->f->freeAdj(L);
	}
	return newG;
}
*/
//Funzione che converte la struttura di adiacenza di un grafo

void ConversioneAdiacenza(grafo *G,fung *F,void* S){
	if(F->tipo == 3){
	 	printf("Non è possibile convertire in mappa di char\n");
 		return; //Se quello di destinazione è mappa di char non si puo fare
	}
	if(F->tipo == G->f->tipo){
		printf("Inutile\n");
		G->f->deallocaStruttura(S);
		return; //se la struttura di destinazione è la stessa è inutile andare avanti, ma bisogna deallocare la struttura creata.
	}
	void *A,*X;
	int i,dim;
	ADJ *adj,*l;
	fung *tmp;

	for(i=0;i<G->size;i++){
		adj=G->f->adiacenti(G->S,i);//uso la vecchia funzione per trovare gli adiacenti della struttura vecchia
		l = adj;
		while( l != NULL ){
			F->inserisciArco(S, i, l->key, l->p);//uso la nuova funzione per inserire
			l = l->next;
		}
		G->f->freeAdj(adj);
	}
	//Assegno nuova struttura di adiacenza e libero area occupata dalla vecchia
	G->f->deallocaStruttura( G->S );
	G->S = S;
	// Assegno nuova struttura delle funzioni e libero area occupata dalla vecchia
	free(G->f);
	G->f= malloc(sizeof(fung));
	memcpy(G->f,F,sizeof(fung));
	G->size = G->f->getDim(G->S);
}


//Funzione che crea un grafo casuale, data una probabilità di generazione arco
grafo* GrafoCasuale(void*E,fung* f,float prob){
	srand(time(NULL));
	grafo *G= CreaGrafo(f,E);
	int k = G->size;
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
			adj=G->f->adiacenti(G->S,v);
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
	adj=G->f->adiacenti(G->S,v);
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
		printf("\n%d ",a);
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
void BFS_PercorsoMinimo(grafo *G,int *pred, int* dist ,int* col,int s,int d){
	int *Q,testa,coda,m,v;
	ADJ *adj, *l;
	if(s >= G->size || d>= G->size)
		printf("Errore.\n");
	else{
		Init_Pminimo(G,col,pred,dist);
		col[s]=1; //grigio
		dist[s]=0;
		if(s != d){ 
			int trovato = 0;
			m=G->size;
			Q=malloc(m*sizeof(int));
			testa=0;
			coda=0;
			Q[coda++]=s;
		
			while(testa < coda && !trovato){
				v=Q[testa];
				adj=G->f->adiacenti(G->S,v);
				l = adj;
				while(l != NULL && !trovato){
					if( col[l->key] == 0 ){
						Q[coda++]=l->key;
						col[ l->key ] = 1;
						dist[ l->key ]= dist[v]+1;
						pred[ l->key]= v;
						if(l->key == d) trovato = 1;
					}
					l = l->next;
				}
				testa++;
				col[v]=2;
				G->f->freeAdj(adj);
			}
			free(Q);
		}
	}
}

//Trova percorso minimo e lo stampa
visita* PercorsoMinimo(grafo *G,int a , int b){
	visita* vis = NULL;
	int k,*pred,*dist,*col;
	k=G->size;
	if ( a<0 || a>=k || b<0 || b>=k ) printf("Errore inserimento vertici\n");
	else{
		pred=malloc(k*sizeof(int));
		dist=malloc(k*sizeof(int));
		col = malloc(k*sizeof(int));
		BFS_PercorsoMinimo(G,pred,dist,col,a,b);
		//StampaPercorso(G,a,b,pred);
		//free(pred);
		free(dist);
        vis = malloc(sizeof(visita));
        vis->pred = pred;
        vis->col = col;
	}
	return vis;
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
void DFS_visit_Percorso(grafo *G,int v,int *col,int* pred,int d){
	ADJ *adj,*l;
	col[v]=1;
	adj=G->f->adiacenti(G->S,v);
	l = adj;
	int trovato = 0;
	while( l != NULL && !trovato ){
		if( col[l->key]== 0 ){
			pred[l->key]= v;
			if(l->key != d) DFS_visit_Percorso(G,l->key,col,pred,d);
			else trovato = 1;
		}
		l = l->next;
	}
	col[v]=2;
	G->f->freeAdj(adj);
}

//Trova percorso casuale tra due vertici e lo stampa
visita* PercorsoCasuale(grafo *G,int a, int b){
	int i,k,*col,*pred;
	visita* vis = NULL;
	k=G->size;
	if ( a<0 || a>=k || b<0 || b>=k )
        printf("Errore inserimento vertici\n");

	else{
		col=malloc(k*sizeof(int));
		pred=malloc(k*sizeof(int));
		Init_Pcasuale(G,col,pred);
		DFS_visit_Percorso(G,a,col,pred,b);
		//StampaPercorso(G,a,b,pred);
		vis = malloc(sizeof(visita));
		vis->col = col;
		vis->pred = pred;
		/*free(pred);
		free(col);*/

	}
	return vis;
}



void init_Dijkstra(grafo* G, float* dist, int *pred,int* col,fun* f, dfun *df){
	//Funzioni per dati e coda (Interi, alberi)
	df->hashCode = &hashCodeInt;
	df->crea=&creaint;
	df->comp=&compint;
	df->tfree=&free;
	df->stamp=&stampaint;
	df->insert=&insintero;

	f->AllocaStruttura = AllocaStrutturaH;
    f->deallocaStruttura = deallocaStrutturaH;
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
    f->freeNode = freeNodeH;
    f->dealloca = deallocaH;

    int i;
    for(i=0;i<G->size;i++){
    	pred[i] = -1;
    	dist[i] = 1000;
    	col[i] = 0;
    }

}

void relax(coda *Q,int src, int dest, float p, int* pred, float* dist){
	if(dist[dest] > dist[src] + p){
		dist[dest] = dist[src] + p;
		pred[dest] = src;
		void * sup = malloc(sizeof(int));
		*(int*)sup = dest;
		IncreaseKey(Q, sup, dist[dest]);
		free(sup);
	}
}

//Dijkstra
void Dijkstra(grafo *G,coda *Q,int s,int* pred, float* dist,int* col,int d){
	if(s < 0 || s >= G->size ) printf("Errore sorgente\n");
	else{
		int i,j=0;
		elem* nodo;
		void* sup;
		int v, trovato =0;
        col[s] = 1;
		dist[s] = 0;

		for(i=0;i< G->size; i++){
			sup = malloc(sizeof(int));
			*(int*)sup = i;
			Insert(Q,sup,dist[i]);
		}
		while(!codaVuota(Q) && !trovato){
			nodo = EstraiMax(Q);
			//printf("Sto analizzando il NODO ");
			//Q->df->stamp(nodo->nome);
			//printf("con distanza %f\n",nodo->p);
			v = *(int*)nodo->nome;
			col[v] = 2;
			if( v == d)
				trovato = 1;
			else{
				ADJ *l=NULL, *adj = G->f->adiacenti( G->S,v);
				l = adj;
				while(l != NULL){
					relax(Q,v,l->key,l->p,pred,dist);
					col[l->key] = 1;
					l = l->next;

				}
				G->f->freeAdj(adj);
			}
			free(nodo->nome);
			free(nodo);
		}
	}
}

visita* P_Dijkstra(grafo *G,int s,int d){
	visita* vis = NULL;
	if(s < 0 || s >= G->size || d<0 || d>= G->size ) printf("Errore sorgente o destinazione\n");
	else{
		int i;
		int *pred = malloc(G->size * sizeof(int));
		float *dist = malloc(G->size * sizeof(float));
		int* col = malloc(G->size * sizeof(int));
		dfun *df = malloc(sizeof(dfun));// dato di tipo intero
		fun *f = malloc(sizeof(fun)); //funzioni per code heap
		init_Dijkstra(G,dist,pred,col,f,df);
		coda *Q = AllocaCoda(f, &MinusCompare, df);
		Dijkstra(G,Q,s,pred,dist,col,d);
		/*for(i = 0; i<G->size;i++)
			printf("Nodo %d distanza %f\n",i,dist[i]);*/

		//StampaPercorso(G,s,d,pred);
		vis = malloc(sizeof(visita));
		vis->col = col;
		vis->pred = pred;
		free(dist);
		//free(pred);
		dealloca(Q);
		free(df);
		free(f);
	}
	return vis;
}




//Algoritmo ASTAR

void init_Astar(grafo* G, float* dist, int *pred,int* col,fun* f, dfun *df){
	//Funzioni per dati e coda (Interi, alberi)
	df->hashCode = &hashCodeInt;
	df->crea=&creaint;
	df->comp=&compint;
	df->tfree=&free;
	df->stamp=&stampaint;
	df->insert=&insintero;

	f->AllocaStruttura = AllocaStrutturaH;
    f->deallocaStruttura = deallocaStrutturaH;
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
    f->freeNode = freeNodeH;
    f->dealloca = deallocaH;


    int i;
    for(i=0;i<G->size;i++){
    	pred[i] = -1;
    	dist[i] = 1000;
    	col[i] = 0;
    }

}

void Astar(grafo *G, coda *closed, coda *open, int s,float* dist, int* pred,int*col, int d){
	 float *f = malloc(G->size * sizeof(float)); //f = dist + h
	 elem* nodo;
	 float cost;
	 int v;
	 int trovato = 0;
	 void *sup;

	 dist[s] = 0;
	 col[s] = 1;
	 f[s] = dist[s] + G->f->h(G->S,s,d); //0 + h
	 sup = malloc(sizeof(int));
	 *((int*)sup) = s;
	 Insert(open,sup,f[s]);

	 while( !codaVuota(open) && !trovato){
	 	nodo = EstraiMax(open);
	 	//printf("Sto analizzando il NODO ");
		//open->df->stamp(nodo->nome);
		//printf("con distanza %f\n",nodo->p);
		v = *(int*)nodo->nome;
		if( v == d){
			trovato = 1;
			free(nodo->nome);
		}else{
	 		ADJ *l = NULL, *adj = G->f->adiacenti(G->S,v);
	 		l = adj;
	 		while(l != NULL && !trovato){
	 			if(dist[v] + l->p < dist[l->key] )
	 				dist[l->key] = dist[v] + l->p;

	 			cost = dist[l->key] + G->f->h(G->S,l->key,d);
	 			sup = malloc(sizeof(int));
	 			*((int*)sup) = l->key;
	 			col[l->key] = 1;
	 			if(searchCoda(open, sup) && cost<f[l->key]){
	 				f[l->key] = cost;
	 				pred[l->key] = v;
	 				IncreaseKey(open,sup,cost);
	 				free(sup);
	 				//printf("Incremento chiave\n");
	 			}
	 			else if(searchCoda(closed,sup) && cost<f[l->key]){
	 				f[l->key] = cost;
	 				pred[l->key] = v;
	 				DeleteNode(closed,sup);//da rivedere (anche se è inutile perche usiamo h consistente, quindi nn ci andra mai).
	 				Insert(open,sup,cost);
	 				//printf("Sto qui\n");
 				}
 				else if(!searchCoda(open,sup) && !searchCoda(closed,sup) && l->key != v){
 					f[l->key] = cost;
 					pred[l->key] = v;
 					Insert(open,sup,cost);
 					//printf("Inserisco in open\n");
 				}else{
 					free(sup);
 					//printf("Uguali e free %d\n",l->key);
	 			}
	 			l = l->next;
 			}
 			Insert(closed,nodo->nome,nodo->p);
			G->f->freeAdj(adj);
		}

		free(nodo);
	}
	free(f);
}

visita* P_Astar(grafo *G,int s, int d){
	visita* vis = NULL;
	if(s<0 || s>=G->size || d<0 || d>= G->size) printf("Errore sorgente o destinazione\n");
	else{
		int i;
		int *pred = malloc(G->size * sizeof(int));
		float *dist = malloc(G->size * sizeof(float));
		int* col = malloc(G->size*sizeof(int));//lo uso per capire se ho visto quel vertice.

		dfun *df = malloc(sizeof(dfun));// dato di tipo intero
		fun *f = malloc(sizeof(fun)); //funzioni per code heap
		init_Astar(G,dist,pred,col,f,df);
		coda *closed = AllocaCoda(f, &MinusCompare, df);
		coda *open = AllocaCoda(f, &MinusCompare, df);
		Astar(G,closed,open,s,dist,pred,col,d);
		//StampaPercorso(G,s,d,pred);
        vis = malloc(sizeof(visita));
        vis->col = col;
        vis->pred = pred;
		free(dist);
		//free(pred);
		dealloca(open);
		dealloca(closed);
		free(df);
		free(f);

	}
	return vis;
}











//DFS che controlla se il grafo è ciclico
int DFS_visit_cicli(grafo *G,int v,int *col){
	int ciclo = 0;
	ADJ *adj,*l;
	col[v]=1;
	adj=G->f->adiacenti(G->S,v);
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


grafo* GrafoParser(char* nomef,fung* f){
	void* E = f->parser(nomef);
	grafo* G = NULL;
	if(E != NULL)
		G = CreaGrafo(f,E);
	return G;
}

