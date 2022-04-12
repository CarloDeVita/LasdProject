#include "codeAlberi.h"
#include "codeArray.h"
#include "codeHash.h"
//#include "fun.h"
#include "mystring.h"
#include "Collect.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>



coda* init();
dfun* assegnaFunzioniDati();
fun* getFunctions();
void stampaLista(Collect* l, dfun *df);

main() {
	srand(time(NULL));
    coda *Q = init();
    void *start=NULL, *x;
    int i,p,scelta;
    elem *tmp;
    Collect* l = NULL, *l2 = NULL;
    do{
    	printf("\n\n1) Inserisci un elemento nella coda.\n");
    	printf("2) Estrai e visualizza il massimo, secondo l'ordinamento, dalla coda.\n");
		printf("3) Visualizza il massimo, secondo l'ordinamento, dalla coda.\n");
		printf("4) Aumenta priorità, secondo l'ordinamento, di un elemento\n");    
		printf("5) Diminuisci priorità, secondo l'ordinamento, di un elemento\n");
		printf("6) Elimina elemento\n");
		printf("7) Estrai tutta la coda in ordine\n");
		printf("8) Cancella tutti gli elementi\n");
		printf("9) Esci\n");
		
		printf("Scelta: ");
		scelta = intControlInterval(1,11);
		
		switch(scelta){
			case 1:
				printf("Inserisci il nome dell'elemento: ");
				x = Q->df->insert();
				printf("Inserisci la priorità dell'elemento: ");
				p = intControl();
				if (Insert(Q,x,p) == 1)
					l = InsertLista(l,x);
				break;
			
			case 2:
				tmp = EstraiMax(Q);	
				printf("Il massimo estratto è: ");//mettere un if tmp != null
				Q->df->stamp(tmp->nome);
				printf(" con priorità %d\n",tmp->p);
				l = CancListaPerNome(l,tmp->nome,Q->df);
				Q->df->tfree(tmp->nome);
				free(tmp);
				break;
				
			case 3:
				tmp = Max(Q);
				printf("Il massimo è: ");
				Q->df->stamp(tmp->nome);
				printf(" con priorità %d\n",tmp->p);
				break;
				
			case 4:
				printf("Gli elementi della lista sono i seguenti:\n");
				stampaLista(l, Q->df);
				printf("Scegliere ID elemento su cui operare: ");
				i = intControl();
				l2 = CercaElem(l,i);
				printf("Scegliere nuova priorità: ");
				p = intControl();
				IncreaseKey(Q,x,p);
				break;
			
			case 5:
				printf("Gli elementi della lista sono i seguenti:\n");
				stampaLista(l, Q->df);
				printf("Scegliere ID elemento su cui operare: ");
				i = intControl();
				l2 = CercaElem(l,i);
				printf("Scegliere nuova priorità: ");
				p = intControl();
				DecreaseKey(Q,x,p);
				break;	  
				
			case 6:
				printf("Gli elementi della lista sono i seguenti:\n");
				stampaLista(l,Q->df);
				printf("Scegliere ID elemento su cui operare: ");
				i = intControl();
				l2 = CercaElem(l,i);
				if(l2 != NULL){
					DeleteNode(Q,l2->x);
					l = CancLista(l,i);
				}
				break;
			
			case 7:
				l2 = l;
				while(l2 != NULL){
					tmp = EstraiMax(Q);
					printf("nome: ");
					Q->df->stamp(tmp->nome);
					printf(" priorita: %d\n",tmp->p);
					Q->df->tfree(tmp->nome);
					free(tmp);
					//l=CancTestaLista(l);
					l2 = l2->next;
				}
				
				DeallocaLista(l);
				l=NULL;
				break;
			
			case 8:
				cancellaTutto(Q);
				DeallocaLista(l);
				l = NULL;
				break;
		
		
			
			case 11:
				for(i = 0; i<150; i++){
					printf("Aggiungo\n");
					void* sup = malloc(sizeof(int));
					*(int*)sup = i;
					Insert(Q,sup,rand()%200);
					free(sup);
				 }
				
				while(Q->heapsize > 0){
						printf("Priorita %f\n",EstraiMax(Q)->p); 
				}
			
				break;			
    	}
    	
    }while(scelta != 9);
	dealloca(Q);
	DeallocaLista(l);
	l=NULL;
		
}


        
   
        





coda* init(){
	int scelta;
	coda *Q = NULL;
	fun* f = NULL;
	dfun *df = NULL;
	int (*comp)(int,int);
	printf("Scegli il tipo di ordinamento della coda\n1: Decrescente\n2: Crescente\n");
	scelta = intControlInterval(1,2);
	if(scelta==1) comp = MajorCompare;
	else comp = MinusCompare;
	
	printf("Scegli quale struttura dati utilizzare:\n1: Alberi\n2: Array\n");
	f = getFunctions();
	
	printf("Scegli quale tipo di dato associare al nome degli elementi della coda:\n1: Interi\n2: Float\n3: Stringhe\n");
	df = assegnaFunzioniDati();
	Q = AllocaCoda(f,comp,df);
	free(f);
	free(df);
	return Q;	
}

dfun* assegnaFunzioniDati(){
	dfun *df = malloc(sizeof(dfun));
	int scelta = intControlInterval(1,3);
	if(scelta==1){   
   		df->crea=creaint;   
   		df->comp=&compint;
   		df->tfree=&free;
   		df->stamp=&stampaint;
   		df->insert=&insintero;
   		df->pari=&pariint;
		df->random=&random_int;
	}
	else if(scelta==2){
   		df->crea=&creafloat;
   		df->comp=&compfloat;
   		df->tfree=&free;
   		df->stamp=&stampafloat;
   		df->insert=&insfloat;
   		df->pari= &parifloat;
   		df->random=&random_float;
	}
	else if(scelta==3){
   		df->crea=&creastr;
		df->comp=&compstr;
   		df->tfree=&free;
   		df->stamp=&stampastr;
   		df->insert=&insertstr;
		df->pari=&paristring;
		df->random=&random_string;
	}
	return df;
}

fun* getFunctions(){
	int scelta = intControlInterval(1,2);
	fun *f = malloc(sizeof(fun));
	if(scelta == 1){ //Heap
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
    }else if (scelta == 2){
    	f->AllocaStruttura = AllocaStrutturaA;
        f->deallocaStruttura = deallocaStrutturaA;
        f->left = leftA;
        f->right = rightA;
        f->father = fatherA;
        f->isNode = isNodeA;
        f->getDato = getDatoA;
        f->scambia = scambiaA;
        f->getMassimo = getMassimoA;
        f->getUltimo = getUltimoA;
        f->getPun = getPunA;
        f->addElem = addElemA;
        f->freeNode = freeNodeA;
        f->dealloca = deallocaA;
    }
}
    	


		

