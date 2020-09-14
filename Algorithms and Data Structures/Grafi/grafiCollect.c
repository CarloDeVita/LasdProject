//DE VITA CARLO N86001634

//IMPLEMENTAZIONE LIBRERIA PER LA GESTIONE DI UNA LISTA DI ALBERI

#include<stdio.h>
#include<stdlib.h>
#include"grafiCollect.h"

//Ricerca nella lista di alberi e ritorna il puntatore alla radice dell'albero che cerchiamo
GCOLLECT* CercaGrafo(GCOLLECT* L,int x){
	if (L!=NULL){
		if(L->id != x)
            return CercaGrafo(L->next,x);
	}
	return L;
}


//Inserimento in lista
GCOLLECT* InserisciLista(GCOLLECT* L,int x){
	GCOLLECT* nuovo;
	nuovo=(GCOLLECT*)malloc(sizeof(GCOLLECT));
	nuovo->id=x;
   	nuovo->next=L;
	nuovo->G=NULL;//radice settata a NULL
   	L=nuovo;
	return L;
}

//Inserimento controllato di un elemento. Reinserisco se il nodo è gia presente nell'albero
GCOLLECT* InsGrafiCollect(GCOLLECT *L){
    
	int n;
    
	printf("Scegliere identificativo grafo: ");
	while ( CercaGrafo(L, (n=Intcontrol() )) ) printf("ID GIA' PRESENTE.REINSERIRE ID: ");
 	L = InserisciLista(L,n);  	
   	return L; 
}  

//Stampa la lista
void Stampalist(GCOLLECT* L){
     if(L!=NULL){
         printf("%d  ",L->id);
         Stampalist(L->next); 
     }
}


//Cancella dalla lista
GCOLLECT* CancLista(GCOLLECT *L,int x){
	if(L!=NULL){
		if(L->id!=x)
			L->next=CancLista(L->next,x);
 		else{
            GCOLLECT *tmp = L;
            L=L->next;
            free(tmp);
        }
     }
     return L;
} 
                
//Cancellazione in testa
GCOLLECT* CancTestaLista(GCOLLECT *L){
	GCOLLECT* tmp = NULL;
	if (L != NULL){
		tmp = L;
		L = L->next;
		free(tmp);
	}
	return L;
}	



//dealloca tutto
void DeallocaLista(GCOLLECT *L){
	if(L != NULL){
		DeallocaLista(L->next);	
		free(L);	
	}
}
