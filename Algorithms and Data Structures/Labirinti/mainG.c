#include<stdio.h>
#include<stdlib.h>
#include"grafi.h"
#include"grafiMatrice.h"
#include"grafiLista.h"
#include"grafiChar.h"
#include"Lista.h"
#include"mystring.h"
#include"Collect.h"



fung* assegnaFunLista();
fung* assegnaFunMatrice();
fung* assegnaFunChar();

main() {
	adjList* adjL;
	matAdj* adjM;
	cMap* cmap;
	
	char *file;
	int scelta,x,dim,src,dest,s,cicli;
	int f,v,tipo;
	int size,r,c;
	float peso,prob;
	pos* dimC; //righe e colonne mappa di char
	grafo* A = NULL;
	Collect *L= NULL,*tmp = NULL;
	fung* funzioniM = assegnaFunMatrice();
	fung* funzioniL = assegnaFunLista();
	fung* funzioniC = assegnaFunChar();
	fung* funzioni = NULL;
	system("clear");
	printf("\n\n\t\t-----LIBRERIA GESTIONE GRAFI-----\n");
	
	
	do{
		printf("\n\n1) STAMPA LISTA DEI GRAFI\n");
		printf("2) CREAZIONE GRAFO\n");
		printf("3) STAMPA GRAFO\n");
		printf("4) VISITA GRAFO IN AMPIEZZA\n"); 
		printf("5) VISITA GRAFO IN PROFONDITA'\n");
		printf("6) INSERIMENTO VERTICE\n");
		printf("7) INSERIMENTO ARCO\n");
		printf("8) ELIMINAZIONE VERTICE\n");
		printf("9) ELIMINAZIONE ARCO\n");
		printf("10) CREAZIONE GRAFO TRASPOSTO\n");
		printf("11) CREAZIONE GRAFO CASUALE\n");
		printf("12) CONVERSAZIONE ADIACENZA\n");
		printf("13) PERCORSO MINIMO TRA DUE VERTICI\n");
		printf("14) PERCORSO CASUALE TRA DUE VERTICI\n");
		printf("15) CONTROLLARE SE UN GRAFO E' CICLICO\n");
		printf("16) COSTRUISCI GRAFO DA FILE\n");
		printf("17) STAMPA GRAFO SU FILE\n");
		printf("18) ELIMINA UN GRAFO\n");
		printf("19) DIJKSTRA\n");
		printf("20) ASTAR\n");
		printf("21) ELIMINA TUTTI I GRAFI\n");
		printf("22) ESCI\n");
	
		printf("Inserisci scelta: ");
		scelta = intControl();
		system("clear");
		switch(scelta){
			
			case 1:
				printf("LISTA DEI GRAFI: ");
				(L == NULL) ? printf("Non ci sono grafi") : Stampalist(L); 
				printf("\n");
				break;
			
			case 2: 
				printf("LISTA DEI GRAFI: ");
				(L == NULL) ? printf("Non ci sono grafi") : Stampalist(L); 
				
				printf("\nScegliere tipo di rappresentazione:\n1)Liste di adiacenza\n2)Matrice\n3)Mappa di char\nScelta: ");
				f = intControlInterval(1,3);
				funzioni = (f == 1) ? funzioniL : ((f == 2) ? funzioniM : funzioniC) ;
				L = InsertLista(L,NULL);
				if ( funzioni->tipo == 1){
					printf("\nInserisci la dimensione del grafo: ");
					size = intControl();
					adjL = allocaAdjList(size);
					L->x = CreaGrafo(funzioni,adjL);
				}
				else if(funzioni->tipo == 2){
					printf("\nInserisci la dimensione del grafo: ");
					size = intControl();
					adjM = allocaMatAdj(size);
					L->x = CreaGrafo(funzioni,adjM);
				}
				else {
					printf("\nInserisci righe: ");
					r = intControl();
					printf("\nInserisci colonne: ");
					c = intControl();
					cmap = allocaCharMap(r,c);
					L->x = CreaGrafo(funzioni,cmap);
					
				}
				system("clear");
				break;
			
			case 3:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("Scegliere quale grafo stampare: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL) 
						StampaArchi(tmp->x);
					else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 4:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere su quale grafo effettuare la visita in ampiezza: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){ 
						printf("Scegliere da quale vertice inizia la visita: ");
						src = intControl();
						BFS(tmp->x, src);
					}	
					else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;			
					
			case 5:	
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere su quale grafo effettuare la visita in profondità: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL) 
						DFS(tmp->x);
					else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 6:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui inserire un nuovo vertice: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
				 		if( ((grafo*) tmp->x)->f->tipo <= 2) InserimentoVertice(tmp->x,0); //per convenzione metto 0
						else{
							printf("Scegli quale vertice aggiungere nella mappa :");
							x = intControl();
							InserimentoVertice(tmp->x,x);
						}
						system("clear");
					}
					else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
		
			case 7:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui inserire un nuovo arco: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere sorgente, destinazione e peso dell'arco da aggiungere\nSorgente: ");
						src = intControl();
						printf("Destinazione: ");
						dest = intControl();
						printf("Peso: ");
						peso = floatControl();
						InserimentoArco(tmp->x,src,dest,peso);
						system("clear");
					}
					else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 8:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui eliminare un vertice: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if(tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegli quale vertice eliminare :");
						x = intControl();
						EliminazioneVertice(tmp->x,x);
						system("clear");
					}
					else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
				
			case 9:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui eliminare un arco: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if(tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere sorgente e destinazione dell'arco da eliminare\nSorgente: ");
						src = intControl();
						printf("Destinazione: ");
						dest = intControl();
						EliminazioneArco(tmp->x, src, dest);
						system("clear");
					}else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 10:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo di cui costruire il trasposto: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if(tmp != NULL){
						L = InsertLista(L,NULL);
						L->x = CreazioneTrasposto(tmp->x);
						system("clear");
					}else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}		
				break;
					
			case 11:
				printf("LISTA DEI GRAFI: ");
				(L == NULL)? printf("Non ci sono grafi") : Stampalist(L);
				
				printf("\nScegliere tipo di rappresentazione:\n1)Liste di adiacenza\n2)Matrice\n3)Mappa di char\nScelta: ");
				f = intControlInterval(1,3);
				funzioni = (f == 1) ? funzioniL : ((f == 2) ? funzioniM : funzioniC) ;
				L = InsertLista(L,NULL);
				if ( funzioni->tipo == 1){
					printf("\nScegliere dimensione del grafo: ");
					size = intControl();
					printf("Scegliere la probabilità di creazione arco: ");
					prob = floatControlInterval(0,1);
					
					adjL = allocaAdjList(size);
					L->x = GrafoCasuale(adjL, funzioni, prob);
				}
				else if(funzioni->tipo == 2){
					printf("\nScegliere dimensione del grafo: ");
					size = intControl();
					printf("Scegliere la probabilità di creazione arco: ");
					prob = floatControlInterval(0,1);
					
					adjM = allocaMatAdj(size);
					L->x = GrafoCasuale(adjM, funzioni, prob);
				}
				else {
					//
					printf("per ora niente\n");
					
				}
				
				system("clear");
				break;					  
				  	
			case 12:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo su cui effettuare una conversione della struttura di adiacenza: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Scegliere quale struttura associare al grafo:\nLista di adiacenza: 1\nMatrice: 2\nScelta: ");
						tipo = intControlInterval(1,2);
						if(tipo == 1){
							adjList* A = allocaAdjList ( ((grafo*)tmp->x)->size );
							ConversioneAdiacenza(tmp->x,funzioniL,A);				
						}
						else {
							matAdj* A = allocaMatAdj( ((grafo*)tmp->x)->size );
							ConversioneAdiacenza(tmp->x,funzioniM,A); 
							system("clear");
						}
					}else
						printf("Non è stato trovato il grafo con id %d\n",x); 
				}
				break;
			
			case 13:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui cercare il percorso minimo tra due vertici: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere vertice iniziale: ");
						src = intControl();
						printf("Scegliere vertice finale: ");
						dest = intControl();
						PercorsoMinimo(tmp->x,src,dest);
					}else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;		
			
			case 14:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere grafo in cui cercare un percorso casuale tra due vertici: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere vertice iniziale: ");
						src = intControl();
						printf("Scegliere vertice finale: ");
						dest = intControl();
						PercorsoCasuale(tmp->x,src,dest);
					}else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;		
			
			case 15:	
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere su quale grafo effettuare il controllo di cicli: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL)
						( DFS_cicli(tmp->x) ) ? printf("Il grafo è ciclico\n") : printf("Il grafo non è ciclico\n");
					else 
						printf("Non è stato trovato il grafo con id %d\n",x); 	
				}
				break;
				
			case 16:
				printf("LISTA DEI GRAFI: ");
				(L == NULL) ? printf("Non ci sono grafi") : Stampalist(L);
				printf("\nScegliere tipo di rappresentazione:\n1)Liste di adiacenza\n2)Matrice\n3)Mappa di char\nScelta: ");
				f = intControlInterval(1,3);
				funzioni = (f == 1) ? funzioniL : ((f == 2) ? funzioniM : funzioniC) ;
				L = InsertLista(L,NULL);
				printf("Nome file da aprire: ");
				file = insertString(100);
				L->x = GrafoParser(file,funzioni);
				free(file);
				if (L->x == NULL) 
					L = CancTestaLista(L);	
				else
					system("clear");
				break;
		
			case 17:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("Scegliere quale grafo stampare su file: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL)
					 	StampaArchiFile(tmp->x,"stampa.txt");
					else 
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 18:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere quale grafo eliminare: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						DeallocaGrafo(tmp->x);
						L = CancLista(L,x);
					}
					else
						printf("Non è stato trovato il grafo con id %d\n",x);	
				}	
				break;
		
			case 19:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere su quale grafo effettuare Dijkstra: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere vertice iniziale: ");
						src = intControl();
						printf("Scegliere vertice finale: ");
						dest = intControl();
						P_Dijkstra(tmp->x,src,dest);
					}else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;
			
			case 20:
				printf("LISTA DEI GRAFI: ");
				if (L == NULL) printf("Non ci sono grafi\n");
				else{
					Stampalist(L);
					printf("\nScegliere su quale grafo effettuare ASTAR: ");
					x = intControl();
					tmp = CercaElem(L,x);
					if (tmp != NULL){
						printf("Nodi presenti da 0 a %d\n",((grafo*)tmp->x)->size-1);
						printf("Scegliere vertice iniziale: ");
						src = intControl();
						printf("Scegliere vertice finale: ");
						dest = intControl();
						P_Astar(tmp->x,src,dest);
					}else
						printf("Non è stato trovato il grafo con id %d\n",x);
				}
				break;	
			
			case 21:
				while(L != NULL){
					DeallocaGrafo(L->x);
					tmp = L;
					L = L->next;
					free(tmp);
				}
				tmp = NULL;			
				break;
					
			case 22: //dealloca ed esce
				while(L != NULL){
					DeallocaGrafo(L->x);
					tmp = L;
					L = L->next;
					free(tmp);
				}
				break;
			
				
			
		}			
	}while(scelta != 22);
	free(funzioniM);
	free(funzioniL);
	free(funzioniC);
}


fung* assegnaFunMatrice(){
	fung* f = malloc(sizeof(fung));	
	f->trasposto = traspostoM;								
	f->getDim = getDimM;
	f->inserisciVertice = inserisciVerticeM;
	f->inserisciArco = inserisciArcoM;
	f->eliminaVertice = eliminaVerticeM;
	f->eliminaArco = eliminaArcoM;
	f->adiacenti = adiacentiM;	
	f->deallocaStruttura = deallocaStrutturaM;
	f->freeAdj = freeAdjM;
	f->h = hM;
	f->parser = parserM;
	f->tipo = 2;
	return f;
}
	
fung* assegnaFunLista(){
	fung* f = malloc(sizeof(fung));
	f->trasposto = traspostoL;
	f->getDim = getDimL;
	f->inserisciVertice = inserisciVerticeL;
	f->inserisciArco = inserisciArcoL;
	f->eliminaVertice = eliminaVerticeL;
	f->eliminaArco = eliminaArcoL;
	f->adiacenti = adiacentiL;	
	f->deallocaStruttura = deallocaStrutturaL;
	f->freeAdj = freeAdjL;
	f->h = hL;
	f->parser = parserL;
	f->tipo = 1;
	return f;
}

fung* assegnaFunChar(){
	
	fung* f = malloc(sizeof(fung));
	f->getDim = getDimC; //Viene usata un'altra funzione
	f->inserisciVertice = inserisciVerticeC;
	f->inserisciArco = inserisciArcoC; //Non c'è bisogno di inserire archi
	f->eliminaVertice = eliminaVerticeC;
	f->eliminaArco = NULL; //Non si eliminano nemmeno
	f->adiacenti = adiacentiC;	
	f->deallocaStruttura = deallocaStrutturaC;
	f->freeAdj = freeAdjC;
	f->h = hM;
	f->parser = parserC;
	f->tipo = 3;
	return f;
}

