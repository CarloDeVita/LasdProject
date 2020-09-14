//DE VITA CARLO N86001634

//IMPLEMENTAZIONE LIBRERIA PER LA GESTIONE DI UNA LISTA DI ALBERI

#include<stdio.h>
#include<stdlib.h>
#include"Collect.h"

//Ricerca nella lista di alberi e ritorna il puntatore alla radice dell'albero che cerchiamo
abrCollect* CercaRoot(abrCollect* L,int x){
	if (L!=NULL){
		if(L->id != x)
            return CercaRoot(L->next,x);
	}
	return L;
}


//Inserimento in lista
abrCollect* InserisciLista(abrCollect* L,int x){
	abrCollect* nuovo;
	nuovo=(abrCollect*)malloc(sizeof(abrCollect));
	nuovo->id=x;
   	nuovo->next=L;
	nuovo->root=NULL;//radice settata a NULL
   	L=nuovo;
	return L;
}

//Inserimento controllato di un elemento. Reinserisco se il nodo è gia presente nell'albero
abrCollect* InsertCollect(abrCollect *L){
    
	int n;
	printf("Scegliere identificativo grafo: ");
	while ( CercaRoot(L, (n=intControl() )) ) printf("ID GIA' PRESENTE.REINSERIRE ID: ");
 	L = InserisciLista(L,n);  	
   	return L; 
}  

//Stampa la lista
void Stampalist(abrCollect* L){
     if(L!=NULL){
         printf("%d  ",L->id);
         Stampalist(L->next); 
     }
}


//Cancella dalla lista
abrCollect* CancLista(abrCollect *L,int x){
	if(L!=NULL){
		if(L->id!=x)
			L->next=CancLista(L->next,x);
 		else{
            abrCollect *tmp = L;
            L=L->next;
            free(tmp);
        }
     }
     return L;
} 
                
//Cancellazione in testa
abrCollect* CancTestaLista(abrCollect *L){
	abrCollect* tmp = NULL;
	if (L != NULL){
		tmp = L;
		L = L->next;
		free(tmp);
	}
	return L;
}	



//dealloca tutto
void DeallocaLista(abrCollect *L){
	if(L != NULL){
		DeallocaLista(L->next);	
		free(L);	
	}
}
