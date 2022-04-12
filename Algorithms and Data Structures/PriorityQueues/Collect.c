//DE VITA CARLO N86001634

//IMPLEMENTAZIONE LIBRERIA PER LA GESTIONE DI UNA LISTA DI ALBERI

#include<stdio.h>
#include<stdlib.h>
#include"Collect.h"
#include"fun.h"


//Inserimento in lista
Collect* InserisciLista(Collect* L, int n, void* z){
	Collect* nuovo;
	nuovo=malloc(sizeof(Collect));
   	nuovo->next=L;
	nuovo->x = z;
	nuovo->id = n;
   	L=nuovo;
	return L;
}

Collect* InsertLista(Collect *L, void* z){
	int n;
	printf("Scegliere identificativo numerico per l'elemento: ");
	while ( CercaElem(L, (n=intControl() )) ) printf("ID GIA' PRESENTE.REINSERIRE ID: ");
 	L = InserisciLista(L,n,z);  	
   	return L; 
}

//Cancella dalla lista
Collect* CancLista(Collect *L,int n){
	if(L!=NULL){
		if(L->id != n)
			L->next=CancLista(L->next,n);
 		else{
            Collect *tmp = L;
            L = L->next;
            free(tmp);
        }
     }
     return L;
} 


Collect* CancListaPerNome(Collect* L,void*x,dfun* df){
	if(L!=NULL){
		if( df->comp(x,L->x) != 0)
			L->next=CancListaPerNome(L->next,x,df);
 		else{
            Collect *tmp = L;
            L = L->next;
            free(tmp);
        }
     }
     return L;
} 


Collect* CercaElem(Collect* L, int i){
	if(L != NULL){
		if(L->id != i)
			return CercaElem(L->next,i);
		else
			return L;
	}
	return NULL;	
}
         
//Cancellazione in testa
Collect* CancTestaLista(Collect *L){
	Collect* tmp = NULL;
	if (L != NULL){
		tmp = L;
		L = L->next;
		free(tmp);
	}
	return L;
}	



//dealloca tutto
void DeallocaLista(Collect *L){
	if(L != NULL){
		DeallocaLista(L->next);	
		free(L);	
	}
}



void stampaLista(Collect* l, dfun *df){
	Collect *tmp = l;
	while(tmp != NULL){
		printf("ID: %d - ",tmp->id);
		printf("Nome Elemento: ");
		df->stamp(tmp->x);
		tmp = tmp->next;
		printf("\n");
	}
	printf("\n");
}	
