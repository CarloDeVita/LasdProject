#include"Hash.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


htable *CreaHash( dfun* dfunzioni ){
	int i;
	htable *newH = malloc(sizeof(htable));
	newH->n = 13;//numero di posizioni nella hash
	newH->table= malloc(newH->n * sizeof(hlist*));
	newH->totInseriti = 0;
	newH->df = malloc(sizeof(dfun));
	memcpy(newH->df,dfunzioni,sizeof(dfun));
	for (i=0;i<newH->n;i++)
		newH->table[i] = NULL;	
	return newH;
}

void DistruggiHash(htable* tab){
	int i;
	hlist** tmp = tab->table;
	hlist* sup;
	for(i=0;i<tab->n;i++){
		while(tmp[i] != NULL){
			sup = tmp[i];
			tmp[i] = tmp[i]->next;
			free(sup->data);
			free(sup);
		}
	}
	free(tab->df);
	free(tab->table);
	free(tab);
}

void AumentaDimensioneHash(htable *tab){
	int i,pos;
	tab->n = tab->n * 2;
	hlist** tmp = tab->table;
	hlist* insert;	
	hlist** sup=tmp;
	tab->table = malloc(tab->n * sizeof(hlist*));
	for (i = 0 ; i< tab->n; i++)
		tab->table[i] = NULL;
		
		
	for (i = 0 ; i< (tab->n)/2; i++){
		//pos = i % tab->n;
		
		while (tmp[i] != NULL){
			pos = tab->df->hashCode(tmp[i]->data->ind) % tab->n;
			insert = tmp[i];
			tmp[i] = tmp[i]->next;
			insert->next = tab->table[pos];
			tab->table[pos] = insert;
			
		}
		
	}
	free(tmp);
}

void DiminuisciDimensioneHash(htable *tab){
	int i,pos;
	tab->n = tab->n / 2;
	hlist** sup = tab->table;	
	hlist *insert;
	hlist** tmp = sup;
	tab->table = malloc(tab->n * sizeof(hlist*));
	
	for (i = 0 ; i< tab->n; i++)
		tab->table[i] = NULL;
	
	for (i = 0 ; i< (tab->n)*2; i++){
		//pos = i % tab->n;
		while (tmp[i] != NULL){
			pos = tab->df->hashCode(tmp[i]->data->ind) % tab->n;
			insert = tmp[i];
			tmp[i] = tmp[i]->next;
			insert->next = tab->table[pos];
			tab->table[pos] = insert;
			
		}	
		
	}
	free(tmp);
	
}




void InserimentoHash(htable *tab, void* i , void* x){
	if(HashSearch(tab,i) == NULL){
		int pos =  tab->df->hashCode(i);
		//printf("sto mettendo nell hash %d\n",pos);
		pos = pos%tab->n;
		hlist *newList = malloc(sizeof(hlist));
		helem* newDato = malloc(sizeof(helem));
		newDato->ind = i;
		newDato->k = x;
		newList->data = newDato;
		newList->next = tab->table[pos];
		tab->table[pos] = newList;
		tab->totInseriti++;
		if ( tab->totInseriti/tab->n >= 0.9 )
			AumentaDimensioneHash(tab);
	}
	else
		printf("Gia esiste un elemento con questo nome\n");
}

void CancellazioneHash(htable *tab, void* i){
	int pos = tab->df->hashCode(i);
	pos = pos%tab->n;
	hlist *p = NULL,*l,*tmp;
	l = tab->table[pos];
	while (l != NULL && tab->df->comp(l->data->ind,i)!=0 ){
		p = l;
		l = l->next;
	}
	if ( l != NULL ){
		tmp = l;
		l = l->next;
		if (p != NULL) 
			p->next = l;
		else
			tab->table[pos] = l;	
		free(tmp->data);
		free(tmp);
		tab->totInseriti--;
		if ( tab->totInseriti/tab->n < 0.2 && tab->n > 13 )
			DiminuisciDimensioneHash(tab);
	}
}

helem* HashSearch(htable *tab, void* i){ 
//cerco in base al nome dell'elemento (dalla struttura elem) per trovare indirizzo reale(passo coppia indirizzo|nome)
	int pos = tab->df->hashCode(i);
	hlist *p = NULL,*l,*tmp;
	helem* ret = NULL;
	pos = pos%tab->n;
	l = tab->table[pos];
	while (l != NULL && tab->df->comp(l->data->ind,i) != 0){
		p = l;
		l = l->next;
	}
	if (l != NULL) ret = l->data;
	return ret;
}

void scambiaValoriHash(htable *tab , void* x , void* y){
	helem *a,*b;
	void *tmp;
	a = HashSearch(tab,x);
	b = HashSearch(tab,y);
	tmp = a->k; 
	a->k = b->k;
	b->k = tmp;
}

void setValoreHash(htable *tab, void *x, void* k){
	helem *a = HashSearch(tab,x);
	a->k = k;
}

