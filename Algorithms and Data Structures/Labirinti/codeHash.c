#include"codeHash.h"
#include<stdlib.h>
#include<stdio.h>
#include<float.h>
#include<string.h>


float MajorCompare(float a, float b){
        return a-b;
}

float MinusCompare(float a, float b){
        return (b-a);
}

int codaVuota(coda *Q){
	if(Q->heapsize == 0)
		return 1;
	return 0;
}

int searchCoda(coda* Q, void*x){
	if (HashSearch(Q->HashTab,x) != NULL)
		return 1;
	return 0;
}

//Allocazione della coda
coda* AllocaCoda(fun* funzioni,float (*compare) (float,float), dfun* dfunzioni  ){
	coda* Q = malloc(sizeof(coda));
	Q->f = malloc(sizeof(fun));
	memcpy(Q->f, funzioni, sizeof(fun)); 
	Q->df = malloc(sizeof(dfun));
	memcpy(Q->df,dfunzioni,sizeof(dfun));
	Q->heapsize = 0;
	Q->comparison = compare;
	Q->S = Q->f->AllocaStruttura();
	Q->HashTab = CreaHash(Q->df);
	return Q;
}

void Heapify(coda *Q, void* i){
	void* l = Q->f->left(Q->S, i);
	void* r = Q->f->right(Q->S, i);
	void *max = i;
	elem *e1,*e2, *massimo;
	//sia per alberi che per array ritorno NULL se non fa parte della coda.
	if ( Q->f->isNode(Q->S,l)){
		e1 = Q->f->getDato(i);
		e2 = Q->f->getDato(l);
	  	if (Q->comparison( e1->p,e2->p ) < 0 ){
			max = l;
			massimo = e2;
		}else
			massimo = e1;				
	}	
	if (Q->f->isNode(Q->S,r)){
		e2 = Q->f->getDato(r);
		if (Q->comparison( massimo->p,e2->p ) < 0 ){
			max = r;
			massimo = e2;
		}
	}	
	if (max != i){
		Q->f->scambia(max,i);
		scambiaValoriHash(Q->HashTab, massimo->nome, e1->nome);
		Heapify(Q,max);
	}
}

elem* Max(coda *Q){
	elem* ret;
	if ( Q->heapsize < 1 )
		ret = NULL;
	else 
		ret = Q->f->getDato( Q->f->getMassimo(Q->S)); //prendi il dato dall'elemento che è in prima posizione
	return ret;
}


elem* EstraiMax(coda *Q){
		elem* ret, *datoUlt;
		helem* prova;
		void *first,*last;
	if ( Q->heapsize < 1 )
		ret = NULL;
	else {
		ret = Q->f->getDato(first =  Q->f->getMassimo(Q->S)); //prendi il dato dall'elemento che è in prima posizione
		last = Q->f->getUltimo(Q->S);
		datoUlt = Q->f->getDato(last);
		//prova = HashSearch(Q->HashTab, datoUlt->nome);
		//printf("Indirizzo Cercato %p ; indirizzo reale %p\n", prova->k, last);
		Q->f->scambia(first,last);
		setValoreHash(Q->HashTab, datoUlt->nome,first); //al primo elemento faccio combaciare il nome dell'ultimo dato
		CancellazioneHash(Q->HashTab,ret->nome);
		Q->f->dealloca(Q->S);
		Q->heapsize--;
	
		if( Q->heapsize != 0)
			Heapify(Q,first);	
	}
	return ret;
}	
		



void IncreaseKey2(coda *Q,void* pun,float priorita){	
	void* padre;
	elem *dato = Q->f->getDato(pun) ,*datoPadre;//dato
	if (Q->comparison( dato->p , priorita ) > 0 )
		printf("Errore: Nuova priorità più piccola.\n");	
	else if (Q->comparison( dato->p , priorita ) < 0 ){
	 	dato->p = priorita;
 		//continua while se prior figlio > padre.
 		while( Q->f->isNode(Q->S,pun) && Q->f->isNode(Q->S, padre = Q->f->father(Q->S,pun) ) && Q->comparison( dato ->p , (datoPadre=((elem*)Q->f->getDato(padre)))->p  ) > 0 ){ 
			//confronto la priorità del figlio con quella del padre. Assegno variabile "dato" al padre che sarà il prossimo figlio
			//printf("sto scambiando padre figlio, priorita %f -- %f\n", datoPadre->p, dato->p);
			
			Q->f->scambia(padre,pun);
			scambiaValoriHash(Q->HashTab,dato->nome,datoPadre->nome);
			pun = padre;
			dato = Q->f->getDato(pun);
		}
		/*if( !Q->f->isNode(Q->S,pun)) printf("puntatore sbagliato\n");
		if( !Q->f->isNode(Q->S, padre ) ) printf("puntatore padre sbagliato\n");
		else if ( !Q->comparison( dato ->p , (datoPadre=((elem*)Q->f->getDato(padre)))->p  ) > 0 ) printf("confronto sbagliato %f,%f\n",dato->p,(datoPadre=((elem*)Q->f->getDato(padre)))->p);*/
	}
}



void IncreaseKey(coda *Q,void* key,float priorita){
	helem* val = HashSearch(Q->HashTab, key);
	void* pun;
	//printf("Sto facendo increaseKey dell'elemento");
	//Q->df->stamp(key);
	if ( val != NULL){
		pun = val->k;
		IncreaseKey2(Q, pun , priorita);
	}else
		printf("Nessun elemento trovato\n");
}
	
	

/*		
void DecreaseKey2(coda *Q,int i,int k){
	void *pun = Q->f->getPun(Q->S,i);//posizione
	elem *dato = Q->f->getDato(pun);//dato
	if (Q->comparison( dato->p , k ) < 0 )
		printf("Errore: Nuova priorità più grande.\n");
	else if (Q->comparison( dato->p , k ) > 0 ){
		dato->p = k;
		Heapify(Q,pun);
	}
}*/

void DecreaseKey2(coda *Q,void* pun,float priorita){
	elem* dato = Q->f->getDato(pun);
	if( Q->comparison(dato->p,priorita) < 0 ) 
		printf("Errore: nuova priorita' più grande");
	else if  ( Q->comparison(dato->p,priorita) > 0 ){
		dato->p = priorita;
		Heapify(Q,pun);
	}
}

void DecreaseKey(coda *Q,void* key,float priorita){
	helem* val = HashSearch(Q->HashTab, key);
	void* pun;
	if (val != NULL){
		pun = val->k;
		DecreaseKey2(Q,pun,priorita);
	}else
		printf("Nessun elemento trovato");
}


			 


void aggiornaValoriHash(coda *Q){
	int i;
	void *pun;
	elem *dato;
	printf("ENTRO QUI\n");
	for(i=1; i<= Q->heapsize;i++){
	 	dato = Q->f->getDato(pun = Q->f->getPun(Q->S,i));
	 	setValoreHash(Q->HashTab, dato->nome,pun);
 	}
}	

//ritorna 1 se inserisci
int Insert(coda *Q, void *x, float k){
	
	void *ultimo,*primo,*newprimo ;
	if(HashSearch(Q->HashTab,x) == NULL){
		/*printf("sto inserendo elemento");
		Q->df->stamp(x);
		printf(" con priorita %f\n",k);*/
		elem* newdato = malloc(sizeof(elem));
		newdato->nome = x;
		newdato->p = (Q->comparison == MajorCompare ? -1 : 99999.99 );
		Q->heapsize++;
		Q->f->addElem(Q->S,newdato);
		//primo = Q->f->getMassimo(Q->S);
		ultimo = Q->f->getUltimo(Q->S);
		InserimentoHash(Q->HashTab, x, ultimo);//
		//newprimo = Q->f->getMassimo(Q->S);
		//confronto il nuovo Primo con il vecchio primo, se è diverso vuol dire che devo aggiornare i valori nella Hash
		//if (primo != newprimo ) aggiornaValoriHash(Q);
	
		IncreaseKey(Q,x,k);
		return 1;
	}else{
		printf("Elemento gia presente nella coda\n");
		return 0;
	}
} 

void DeleteNode(coda *Q, void* x){
	helem* a = HashSearch(Q->HashTab,x);
	elem *old,*new,*tmp;
	int newp,oldp;
	void* last;
	if (a != NULL){
		last = Q->f->getUltimo(Q->S);
		Q->f->scambia(a->k,last);
		new = Q->f->getDato(a->k);//nodo che stava come ultimo e che ora va nel posto occupato da quello da eliminare
		newp = new->p;
		old = (elem*)Q->f->dealloca(Q->S);// nodo da eliminare
		oldp = old->p;
		CancellazioneHash(Q->HashTab, old->nome);
		if( new != old){
			setValoreHash(Q->HashTab,new->nome,a->k);
			Q->df->tfree(old->nome);
			free(old);
		}
		if(Q->comparison(newp,oldp) > 0){
			IncreaseKey(Q, new->nome, new->p);
		}else if(Q->comparison(newp,oldp) < 0){
			DecreaseKey(Q, new->nome, new->p);
		}
		Q->heapsize--;
	}
	else 
		printf("Elemento non esistente nella coda\n");
}

void cancellaTutto2(coda* Q, void* x){
	elem* tmp = NULL;
	if( x != NULL){
		cancellaTutto2(Q,Q->f->left(Q->S,x));
		cancellaTutto2(Q,Q->f->right(Q->S,x));
		tmp = Q->f->getDato(x);
		Q->df->tfree(tmp->nome);//nel main cos
		free(tmp);//
		Q->f->freeNode(x);
	}
	
}

void cancellaTutto(coda* Q){
	void *first = Q->f->getMassimo(Q->S);
	cancellaTutto2(Q,first);
	DistruggiHash(Q->HashTab);
}
		
void dealloca(coda *Q){
	cancellaTutto(Q);
	Q->f->deallocaStruttura(Q->S);
	free(Q->f);
	free(Q->df);
	free(Q);	
}			
