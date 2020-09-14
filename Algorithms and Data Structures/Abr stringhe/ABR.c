//DE VITA CARLO N86001634

//IMPLEMENTAZIONE DELLE FUNZIONI DELLA LIBRERIA ABR CON CHIAVI DI TIPO STRINGA
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


//deallocazione nodo
void DeallocaNodo (ABR*T){
	free(T->parola);
	free(T);
}


//Inserimento nodo in Abr
ABR* inserimentoABR(ABR*T, char* str){
	if(T==NULL){
		T=AllocaNodo(T);
       	T->parola=allocaString(strlen(str));
       	strcpy(T->parola,str);
       	T->dx=NULL;
       	T->sx=NULL;
  	}
   	else if(strcmp(T->parola,str)>0){
        T->sx=inserimentoABR(T->sx,str);
    }
   	else if (strcmp(T->parola,str)<0){
        T->dx=inserimentoABR(T->dx,str);
 	}   
   	return T;
 }
   


//Stampa abr

void stampaAbr (ABR* T){
	int tipo;
	if (T == NULL) 
		printf("Albero vuoto\n");
	else{
		printf("Scegliere tipo di visita: \n1-PREORDER\n2-INORDER\n3-POSTORDER");
		printf("\nScelta: ");
		tipo=intControlInterval(1,3);
		switch(tipo){
			case 1:
				preorder(T);
				break;
			case 2: 
				inorder(T);
				break;
			case 3:
				postorder(T);
				break; 
		}
	}
}
//PREORDER 
void preorder(ABR*T){
	if(T!=NULL){
    	printf("%s  ",T->parola);
        preorder(T->sx);       
        preorder(T->dx);
   }
}

//INORDER
void inorder(ABR*T){
	if(T!=NULL){
	    inorder(T->sx);       
        printf("%s  ",T->parola);
        inorder(T->dx);
   }
}

//POSTORDER
void postorder(ABR*T){
	if(T!=NULL){
      postorder(T->sx);
      postorder(T->dx);
      printf("%s  ",T->parola);
	}
}




//Cancellazione di tutti i nodi
ABR*  CancAlbero(ABR* T){
    if (T!=NULL) {
		T->sx=CancAlbero(T->sx);
        T->dx=CancAlbero(T->dx);
        T=cancellaroot(T);
    }
    return T ;
}


//Cancella nodo data una stringa
ABR* CancNodo(ABR* T,char* str){
	if(T!=NULL){
		if(strcmp(T->parola,str)>0)
			T->sx=CancNodo(T->sx,str);
   		else if(strcmp(T->parola,str)<0)
          	T->dx=CancNodo(T->dx,str);
       else if(strcmp(T->parola,str)==0)
            T=cancellaroot(T); 
}
 return T;
}


//Cancella Nodo
ABR* cancellaroot(ABR* T){
	if(T!=NULL){
		ABR*tmp=NULL;
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
            char*scambio=tmp->parola;
            tmp->parola=T->parola;
            T->parola=scambio;		
	    }
		DeallocaNodo(tmp);        
	}  
    return T;
}


//Trova il minimo del sottoalbero destro
ABR* staccamin(ABR* P,ABR* T){
	if(T!=NULL){
		if(T->sx!=NULL)
			return staccamin(T,T->sx);
	   	else{ 
	       	if(P->sx==T)
				P->sx=T->dx; 
	       else           
	          	P->dx=T->dx;         
	     }
	}
  	return T;
}



/*Cancella da un albero le stringhe che hanno
  valore compreso tra altre due stringhe in ingresso
  e profondità compresa tra due interi in ingresso */
  
ABR* cancInterv(ABR* T,char*str1,char*str2,int h1,int h2){
	if (strcmp(str1,str2)<=0 && h1<=h2 ) 
		T=cancInterv1(T,str1,str2,h1,h2);
	else 
		printf("Errore dati inseriti.\n");
	return T;
}

ABR* cancInterv1(ABR* T,char*str1,char*str2,int h1,int h2){
	if (T!=NULL){
    	if (h2 >= 0){
    		if(strcmp(T->parola,str1)<0)
				T->dx=cancInterv1(T->dx,str1,str2,h1-1,h2-1);                        
        	else if (strcmp(T->parola,str2)>0) 
        		T->sx=cancInterv1(T->sx,str1,str2,h1-1,h2-1);              
        	else {
           		T->sx=cancInterv1(T->sx,str1,str2,h1-1,h2-1);
           		T->dx=cancInterv1(T->dx,str1,str2,h1-1,h2-1);
           		if (h1 <= 0)
           	 		T=cancellaroot(T);                   
        	}
   		}
   }
   return T;
}

//ABR fatto da stringhe casuali interfaccia
ABR* ABRcasual(int n,int len){
	ABR* T=NULL;
	T=ABRcasual1(T,n,len);
	return T;
}

//Algoritmo effettivo che crea un ABR fatto da stringhe casuali
ABR* ABRcasual1(ABR*T,int n,int len){
	char *s;  
	if(n>0){
		s=casualString(len);
		T=inserimentoABR(T,s);
		T=ABRcasual1(T,n-1,len);
      }
	return T;
}


//verifica che due abr sono identici
int VerifyEqual(ABR* T, ABR*T2){
	if(T && T2) return ( strcmp(T->parola,T2->parola)==0 && VerifyEqual(T->sx,T2->sx) && VerifyEqual(T->dx,T2->dx) );
	else return (!T && !T2);
}

//Riversa in un array le chiavi dell'abr in ordine crescente
int ArrayOrd(ABR* T,char **A, int i){
	if (T!=NULL){
		i=ArrayOrd(T->sx,A,i);
        A[i]=allocaString(strlen(T->parola));
		strcpy(A[i],T->parola);
		i=i+1;
		i=ArrayOrd(T->dx,A,i);
	}
	return i;         
}


//Conta il numero dei nodi in un albero
int NumeroNodi(ABR*T){
	if(T!=NULL)
		return NumeroNodi(T->sx)+NumeroNodi(T->dx)+1;
	else
		return 0;
}


//Funzione che crea duplicato
ABR* duplicatoabr(ABR*T){
	ABR*Tn=NULL;
    if(T!=NULL){		
		Tn=AllocaNodo(T);
		Tn->parola=allocaString(strlen(T->parola));                
		strcpy(Tn->parola,T->parola);
       	Tn->sx=duplicatoabr(T->sx);
       	Tn->dx=duplicatoabr(T->dx);
	}
	return Tn;
} 

//Funzione che crea un albero perfettamente bilanciato partendo
ABR* Pbil(ABR*T){
	int i=0,n,j;
	char **A;
	ABR*Tn=NULL;
	if(T!=NULL){
		n=NumeroNodi(T);
		A=(char**)malloc(n*sizeof(char*));
		i=ArrayOrd(T,A,i);
		Tn=Pbileff(A,0,i-1); 		 
		deallocArrayStr(A,i);
    }
	return Tn;
}


//Funzione effettiva che crea l'albero bilanciato
ABR* Pbileff(char** A,int a,int b){
	ABR* Tn=NULL;  
	if(a<=b){
		int mid=(a+b)/2;
		Tn=AllocaNodo(Tn);
		Tn->parola=allocaString(strlen(A[mid]));
		strcpy(Tn->parola,A[mid]);
		Tn->sx=Pbileff(A,a,mid-1);
		Tn->dx=Pbileff(A,mid+1,b);
	}
	return Tn;
}


//Controlla se un abr è perfettamente bilanciato
int PbilControl(ABR *T){
	int a,b,diff;
	if(T!=NULL){
		a=NumeroNodi(T->sx);
		b=NumeroNodi(T->dx);
		diff=a-b;
		return ( (diff<=1 && diff>=-1) && PbilControl(T->sx) && PbilControl(T->dx) );
	}else return 1;
}




