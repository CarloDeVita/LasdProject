#include"codeAlberi.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

void* AllocaStrutturaH(){
	heapS* newT = malloc(sizeof(heapS));
	newT->T = NULL;
	newT->last = NULL;
	newT->hsize = 0;
	return newT;
}

void deallocaStrutturaH(void*S){
	free(S);

}

void* leftH(void *S , void *i){
	return ( ((heap*)i)->sx );
}

void* rightH(void *S , void *i){
	return ( ((heap*)i)->dx );
}

void* fatherH(void *S , void *i){
	return ( ((heap*)i)->f );
}


int isNodeH(void *S, void *i){
	int v = 0;
	if (i != NULL)
		v = 1;
 	return v; 
}


void* getDatoH(void *i){
	return ((heap*)i)->dato;
}

void scambiaH(void *x,void *y){
	void* tmp;
	heap *a = x , *b = y;		
	tmp = a->dato;
	a->dato = b -> dato;
	b->dato = tmp;
}

void* getMassimoH(void *S){
	return ((heapS*)S)->T;
}


void* getUltimoH(void *S){
	return ((heapS*)S)->last;
}

void* getPunH(void *S, int i){
	heap* H;
	int k = (sizeof(int)*8) -2; //tolgo bit segno
	int maschera = (int) pow(2, k);
	if (i == 0 ) 
		H = NULL;
	else{
		H = ((heapS*)S)->T;
		while ( (maschera & i) == 0) maschera /= 2;
		maschera /= 2;
		while (maschera != 0){
			if (( i & maschera) == 0)
				H = H->sx;
			else 
				H = H->dx;
			maschera /= 2;
		}
	}
	return H;
}
			


void addElemH(void *S,void* x){
	heapS *H = S;
	H->hsize++;
	
	int pfather = H->hsize/2;
	heap* padre = getPunH(H, pfather);
	heap* nuovo = malloc(sizeof(heap));
	nuovo->sx = nuovo->dx = NULL;
	nuovo->f = padre;
	nuovo->dato = x;
	if (padre != NULL){
		if ( H->hsize%2 == 0)
			padre->sx = nuovo;
		else
			padre->dx = nuovo;
	}else
		H->T = nuovo;
	H->last = nuovo;
}	


void freeNodeH(void* x){
	free(x);
}

void* deallocaH(void*S){//dealloca e torna il dato
	heapS* H = S;
	heap *padre, *tmp;
	void* ret = H->last->dato;
	H->hsize--;
	if(H->hsize == 0){
		H->T = NULL;
		free(H->last);
		H->last = NULL;
	}else{
		padre = H->last->f;
		if (padre->sx == H->last) 
			padre->sx = NULL;
		else
			padre->dx = NULL;
		free(H->last);	
		H->last = getPunH(H,H->hsize);
	}
	
	return ret;
}



