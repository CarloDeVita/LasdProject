#include<stdio.h>
#include"Hash.h"
#define dim 20
main(){

htable* tabella = CreaHash();
helem* retVal;
int i;

for ( i=0 ; i<dim; i++)	
	InserimentoHash(tabella, NULL+i , NULL+ i + 1);

for ( i=0 ; i<dim; i++){
	printf("Sto cercando indirizzo: %p\n",NULL+i);
	retVal = HashSearch(tabella, NULL+i);
	printf("trovato %p, valore =%p\n\n", retVal->ind, retVal->k);
}

printf("\n\nCANCELLAZIONE\n");
for ( i=dim/3 ; i<dim/2 ; i++ )
	CancellazioneHash(tabella,NULL+i);

for ( i=dim/3 ; i<dim/2 ; i++ ){
	printf("Sto cercando indirizzo: %p\n",NULL+i);
	if ( (retVal = HashSearch(tabella,NULL+i)) != NULL )
		printf("trovato %p, valore =%p\n", retVal->ind, retVal->k);
	else 
		printf("Non ho trovato l'elemento!\n");
	printf("\n");
}

}

