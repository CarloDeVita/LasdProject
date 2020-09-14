//DE VITA CARLO N86001634

//IMPLEMENTAZIONE DELLE FUNZIONI DELLA LIBRERIA ABR
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ABR.h"
#include"mystring.h"

//allocazione nodo
ABR* AllocaNodo (ABR*T){
	T=(ABR*)malloc(sizeof(ABR));
	return T;
}

//dellazione nodo
void DeallocaNodo (ABR*T,FUNZIONI *fun){
	fun->tfree(T->key);
	free(T);
}
//crea nodo
ABR* creanode(void*k,FUNZIONI *fun){
   ABR*node=AllocaNodo(node);
   node->key=fun->crea(k);
   node->sx=NULL;
   node->dx=NULL;
   return node;
 
}


//Inserimento nodo in Abr
ABR* inserimentoABR(ABR*T, void *k,FUNZIONI *fun){
	if(T==NULL) T=creanode(k,fun);       
	else if(fun->comp(T->key,k)>0) T->sx=inserimentoABR(T->sx,k,fun);        
	else if (fun->comp(T->key,k)<0) T->dx=inserimentoABR(T->dx,k,fun);        
   	return T;
 }

//Stampa ABR
void stampaAbr (ABR* T,FUNZIONI *fun){
	int tipo;
	if (T == NULL) 
		printf("Albero vuoto\n");
	else{
		printf("Scegliere tipo di visita: \n1-PREORDER\n2-INORDER\n3-POSTORDER");
		printf("\nScelta: ");
		tipo=intControlInterval(1,3);
		switch(tipo){
			case 1:
				preorder(T,fun);
				break;
			case 2: 
				inorder(T,fun);
				break;
			case 3:
				postorder(T,fun);
				break; 
		}
	}
}

//PREORDER 
void preorder(ABR*T,FUNZIONI *fun){
	if(T!=NULL){
		fun->stamp(T->key);
        preorder(T->sx,fun);       
        preorder(T->dx,fun);
   }
}

//INORDER
void inorder(ABR*T,FUNZIONI *fun){
	if(T!=NULL){
		inorder(T->sx,fun);       
        fun->stamp(T->key);
        inorder(T->dx,fun);
   }
}

//POSTORDER
void postorder(ABR*T,FUNZIONI *fun){
	if(T!=NULL){
		postorder(T->sx,fun);
		postorder(T->dx,fun);
		fun->stamp(T->key);
	}
}


//Cancellazione di tutti i nodi
ABR*  CancAlbero(ABR* T,FUNZIONI *fun){
    if (T!=NULL) {
        T->sx=CancAlbero(T->sx,fun);
        T->dx=CancAlbero(T->dx,fun);
        T=cancellaroot(T,fun);         
    }
    return T ;
}


//Cancella nodo data una stringa
ABR* CancNodo(ABR* T,void*k,FUNZIONI *fun){
	if(T!=NULL){
   		if(fun->comp(T->key,k)>0){
       	   	T->sx=CancNodo(T->sx,k,fun);
      	}
       	else if(fun->comp(T->key,k)<0){
			T->dx=CancNodo(T->dx,k,fun);
		}
       	else if(fun->comp(T->key,k)==0){
			T=cancellaroot(T,fun); 
		}
	}
	return T;
}


//Cancella Nodo
ABR* cancellaroot(ABR* T,FUNZIONI *fun){
	if(T!=NULL){
		ABR*tmp=NULL;
		void* scambio=NULL;
		if(T->sx==NULL){
        	tmp=T;
            T=T->dx;                    
        }
      	else if(T->dx==NULL){
        	tmp=T;
            T=T->sx;
       	}
      	else{
            tmp=staccamin(T,T->dx);
            scambio=tmp->key;
            tmp->key=T->key;
            T->key=scambio;            
		}
     	DeallocaNodo(tmp,fun); 
	}  
 	return T;
}


//Trova il minimo del sottoalbero destro
ABR* staccamin(ABR* P,ABR* T){
if(T!=NULL){
	if(T->sx!=NULL) return staccamin(T,T->sx);   
   	else{ 
       if(P->sx==T) P->sx=T->dx;        	
       else  P->dx=T->dx;          
     }
  }
  return T;
}

/*INTERFACCIA: Cancella da un albero le stringhe che hanno lunghezza
  pari o dispari, in funzione di un paramentro, e hanno
  valore compreso tra altre due stringhe in ingresso */
ABR* cancInterv(ABR* T,void* k1,void *k2,int h1,int h2,FUNZIONI *fun){
	if (fun->comp(k1,k2)<=0 && h1<=h2) 
		T= cancInterv1(T,k1,k2,h1,h2,fun);//controllo che k1 sia minore uguale di k2
	else 
		printf("Errore dati inseriti.\n");
	return T;
}

/*Algoritmo effettivo che cancella un valore in intervallo */
ABR* cancInterv1(ABR* T,void* k1,void *k2,int h1,int h2,FUNZIONI *fun){      
	if (T!=NULL){
		if (h2 >= 0){
			if(fun->comp(T->key,k1)<0) 
				T->dx=cancInterv1(T->dx,k1,k2,h1-1,h2-1,fun);                        
    		else if (fun->comp(T->key,k2)>0)
				T->sx=cancInterv1(T->sx,k1,k2,h1-1,h2-1,fun);              
            else {
				T->sx=cancInterv1(T->sx,k1,k2,h1-1,h2-1,fun);
               	T->dx=cancInterv1(T->dx,k1,k2,h1-1,h1-1,fun);
               	if (h1 <= 0)
               		T=cancellaroot(T,fun);                  
			}
		}  
	}
	return T;
}

//Interfaccia ABR fatto da stringhe casuali 
ABR* ABRcasual(int n,FUNZIONI *fun){	  
	ABR* T=NULL;
	T=ABRcasual1(T,n,fun);
	return T;
}

//Algoritmo effettivo che crea un ABR fatto da stringhe casuali
ABR* ABRcasual1(ABR*T,int n,FUNZIONI *fun){
	void*k;  
	if(n>0){
		k=fun->random();
		T=inserimentoABR(T,k,fun);
		T=ABRcasual1(T,n-1,fun);
	}
	return T;
}

//Verifica che due abr sono identici
int VerifyEqual(ABR* T, ABR*T2,FUNZIONI *fun){
	if(T && T2) return ( fun->comp(T->key,T2->key)==0 && VerifyEqual(T->sx,T2->sx,fun) && VerifyEqual(T->dx,T2->dx,fun) );
	else return (!T && !T2);
}



//Funzione che crea duplicato
ABR* duplicatoabr(ABR*T,FUNZIONI *fun){
	ABR*Tn=NULL;
    if(T!=NULL){		
        Tn=AllocaNodo(Tn);
        Tn->key=fun->crea(T->key);
        Tn->sx=duplicatoabr(T->sx,fun);
        Tn->dx=duplicatoabr(T->dx,fun);
    }
	return Tn;
} 


//Riversa in un array le chiavi dell'abr in ordine crescente
int ArrayOrd(ABR* T,void **A, int i,FUNZIONI *fun){
	if (T!=NULL){
		i=ArrayOrd(T->sx,A,i,fun);
		A[i]=fun->crea(T->key);
      	i=i+1;
      	i=ArrayOrd(T->dx,A,i,fun);
  }
  return i;         
}


//Conta il numero dei nodi in un albero
int NumeroNodi(ABR*T){
	if(T!=NULL) return NumeroNodi(T->sx)+NumeroNodi(T->dx)+1;
	else return 0;
}


//Funzione che crea un albero perfettamente bilanciato partendo
ABR* Pbil(ABR*T,FUNZIONI *fun){
	int i=0,n,j;
	void **A;
	ABR*Tn=NULL;
	if(T!=NULL){	
		n=NumeroNodi(T);
		A=(void**)malloc(n*sizeof(void*));
		i=ArrayOrd(T,A,i,fun);
		Tn=Pbileff(A,0,i-1,fun);  		 
		DeallocArr(A,i,fun);
    }
	return Tn;
}


//Funzione effettiva che crea l'albero bilanciato
ABR* Pbileff(void** A,int a,int b,FUNZIONI *fun){
	ABR* Tn=NULL;  
	if(a<=b){
		int mid=(a+b)/2;
		Tn=AllocaNodo(Tn);
		Tn->key=fun->crea(A[mid]);
		Tn->sx=Pbileff(A,a,mid-1,fun);
		Tn->dx=Pbileff(A,mid+1,b,fun);
	}
	return Tn;
}

//Funzione che controlla se un albero è perfettamente bilanciato
int PbilControl(ABR *T){
	int a,b,diff;
	if(T!=NULL){
		a=NumeroNodi(T->sx);
		b=NumeroNodi(T->dx);
		diff=a-b;
		return ( (diff<=1 && diff>=-1) && PbilControl(T->sx) && PbilControl(T->dx) );
	}
	else 
		return 1;
}

//Deallocazione array
void DeallocArr(void ** A,int n,FUNZIONI *fun){
    int j;
    for(j=0;j<n;j++) fun->tfree(A[j]);
    free(A);
}
