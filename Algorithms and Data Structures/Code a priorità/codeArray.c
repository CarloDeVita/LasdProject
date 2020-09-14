#include"codeArray.h"
#include<stdlib.h>
#include<stdio.h>


void* AllocaStrutturaA(){
	heapA *h = malloc(sizeof(heapA));
	h->dim = 20;
	h->A = malloc(20*sizeof(void*));
	h->hsize=0;
	return h;
}

void deallocaStrutturaA(void*S){
	heapA *h = S;
	free(h->A);
	free(h);
		
}


void* leftA(void* S,void* i){
	heapA *Z = S;
	int pos = (int) ( (void**)i - (Z->A ) );
	if (2*pos +1 < Z->hsize )
		return ( Z->A + (2*pos + 1) );
	else
		return NULL;
}

void* rightA(void* S,void* i){
	heapA *Z = S;
	int pos = (int) ( (void**)i - (Z->A ) );
	if (2*pos +2 < Z->hsize )
		return ( Z->A + (2*pos + 2) );
	else
		return NULL;
}

void* fatherA(void* S,void* i){
	int pos = (int) ( (void**)i - ((heapA*)S)->A);
	if ( pos == 0) 
		return NULL;
	else if (pos%2 == 0)
		return ( ((heapA*)S)->A + (pos/2 -1) );
	else 
		return ( ((heapA*)S)->A + (pos/2) );
}

int isNodeA(void *S, void *i){
	int v = 0;
	if (i != NULL ) v = 1; //left right e father tornano gia null se il nodo non esiste.
	return v;
} 

void* getDatoA(void* i){
	return ( *((void**)i) );	
}

void scambiaA(void *x,void *y){
	void *tmp, **a = x , **b = y;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void* getMassimoA(void* S){
	return ( ((heapA*)S)->A ); //puntatore al primo voidento dell'array
}

void* getUltimoA(void *S){
	heapA* Z = S;
	int k = Z->hsize;
	return ( Z->A + k - 1 );
}

void* getPunA(void* S,int i){
	return ( ((heapA*)S)->A + i -1 );
}

void addElemA(void* S,void* x){
	heapA* Z = S;
	int i,dim2;
	void **supp;
	Z->hsize++;
	Z->A[Z->hsize-1] = x;
	if ( Z->hsize == Z->dim ){
		dim2 = Z->dim * 2;
		supp = malloc(dim2 * sizeof(void*));
		for (i = 0; i < Z->dim ; i++)
 			supp[i] = Z->A[i];
		for ( i = Z->dim; i < dim2 ; i++)
			supp[i] = NULL;	
		free(Z->A);
		Z->A = supp;
		Z->dim = dim2;
	}
}

void freeNodeA(void* x){

}

void* deallocaA(void* S){
	heapA *Z = S;
	Z->hsize--;
	return (Z->A + Z->hsize);
	
}	

	



