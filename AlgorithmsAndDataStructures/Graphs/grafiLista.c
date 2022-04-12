#include<stdio.h>
#include<stdlib.h>
//#include"Grafi.h"
#include"grafiLista.h"


void* allocaGrafoL(int k){
	ADJ** A=NULL;
	if(k>0) 
		A=calloc(k,sizeof(ADJ*));
	return A;
}

void* inserisciVerticeL(void *A,int k){
	A=realloc(A,(k+1)*sizeof(ADJ*));
	((ADJ**)A)[k]=NULL;//lista di adiacenza a NULL
	return A;
}	 

void inserisciArcoL(void *A,int a, int b,float peso){
	((ADJ**)A)[a]=InsertL( ((ADJ**)A)[a], b,peso);
}		

void* eliminaVerticeL(void*A,int k,int v){
	int i,a;
	ADJ** tmp=A;
	A=(ADJ**)malloc((k-1) * sizeof(ADJ*));
	
	a=0;
	for(i=0;i<k;i++){
		if(i != v){
			((ADJ**)A)[a]=ControlloArchi(tmp[i],v);
			a++;		
		}	 
	}
	FreeLista(tmp[v]);		
	free(tmp);	
	return A;
}


ADJ* ControlloArchi(ADJ* adj,int v){
	if(adj != NULL ){
		adj->next=ControlloArchi(adj->next,v);
			if (adj->key == v ){
				ADJ*tmp=adj;
				adj=adj->next;
				free(tmp);
			}
			else if (adj->key > v)
				adj->key--;	 	
	}
	return adj;
}

void eliminaArcoL (void *A,int a ,int b){
	((ADJ**)A)[a]=DeleteL( ((ADJ**)A)[a], b );
}

ADJ* adiacentiL(void*A,int k,int v){
	return ((ADJ**)A)[v] ;		
}

void freeAdjL(ADJ* list){
	//non fa nulla
}

void deallocaStrutturaL(void* S,int k){
	ADJ** A = S;
	int i;
	ADJ* l;
	for (i=0; i<k; i++)
		FreeLista( A[i] );
	free(A);
}
						
/*void stampaArchiL(void *A,int k){
	ADJ *l = NULL;
	int i;
	for(i=0;i<k;i++){
		l = ((ADJ**)A)[i];
		while(l != NULL){
			printf("%d, %d\n",i,l->key);
			l = l->next;
		}
	}
}*/
					


