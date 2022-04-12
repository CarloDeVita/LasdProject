#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ABR.h"
#include"mystring.h"
#include"fun.h"
#include"stack.h"


//allocazione nodo
ABR* AllocaNodo (ABR*T){
	T=(ABR*)malloc(sizeof(ABR));
	return T;
}

//deallocazione nodo
void DeallocaNodo (ABR*T,FUNZIONI *fun){
	if(T!=NULL){
		fun->tfree(T->key);
		free(T);
	}
}

//inserimento di un nodo in ABR
ABR* InserimentoABR(ABR*T,void *k,FUNZIONI *fun){
 ABR* X;
 ABR* C=T;
 ABR* P=NULL;
 int m;
 while (C!=NULL && (m=fun->comp(C->key,k))!=0 ) {
 	P=C;
     if( m>0 )	C=C->sx;          
     else C=C->dx;
 }
 if(C==NULL){
 	X=creanode(k,fun); 
     if (P==NULL) T=X;   
     else{        
     	if(m<0) P->dx=X;
        	else P->sx=X;
     }
 }      
 return T;
}

//crea nodo   
ABR* creanode(void*k,FUNZIONI *fun){
   ABR*node=AllocaNodo(node);
   node->key=fun->crea(k);
   node->sx=NULL;
   node->dx=NULL;
   return node;
 
}

//VISITE PREORDER/INORDER/POSTORDER
void preorder (ABR*T,FUNZIONI *fun){     
     ABR*curr=T;
     STACK*st=NULL;
     while(curr!=NULL || st!=NULL ){          
           if (curr!=NULL){
              fun->stamp(curr->key);
              st=push(st,curr);
              curr=curr->sx;     
              }
           else{
              curr=top(st);
              st=pop(st);
              curr=curr->dx;
              }
     }
}


void inorder (ABR*T,FUNZIONI *fun){     
     ABR*curr=T;
     STACK*st=NULL;
     while(curr!=NULL || st!=NULL ){          
           if (curr!=NULL){              
              st=push(st,curr);
              curr=curr->sx;     
              }
           else{
              curr=top(st);
              fun->stamp(curr->key);
	         st=pop(st);
              curr=curr->dx;
              }
     }
}


void postorder (ABR*T,FUNZIONI *fun){
    ABR*curr=T;
    STACK*st=NULL;
    ABR*LAST=NULL;
    while(curr!=NULL || st!=NULL){
         if(curr!=NULL){
           st=push(st,curr);
           curr=curr->sx;
           }
          else{
             curr=top(st);
             if (curr->dx!=LAST && curr->dx!=NULL){
                curr=curr->dx;
               }
             else{
                fun->stamp(curr->key);
                LAST=curr;
                st=pop(st);
                curr=NULL;
               }
           }
   }
}




//cancella tutto l'albero
ABR*  CancAlbero(ABR* T,FUNZIONI *fun){
    ABR*curr=T;
    STACK*st=NULL;
    ABR*LAST=NULL;
    ABR*tmp=NULL;
    ABR*p=NULL;
    while(curr!=NULL || st!=NULL){
         if(curr!=NULL){
           st=push(st,curr);
           curr=curr->sx;
           }
          else{
             curr=top(st);
             if (curr->dx!=NULL && curr->dx!=LAST){
                curr=curr->dx;
               }
             else{
			st=pop(st);                
			p=top(st);		
			LAST=curr;	
			if(p!=NULL){
				if(p->sx==curr){
					p->sx=cancellaroot(curr,fun);
					LAST=p->sx;
				}else{
					p->dx=cancellaroot(curr,fun);
					LAST=p->dx;
				}
			}else T=cancellaroot(T,fun);  
			curr=NULL;               
           }
      }
 }
 return NULL;
}

//cancella un nodo dall'abr
ABR* CancNodo(ABR* T,void*k,FUNZIONI *fun){
     ABR*curr=T;
     ABR*P=NULL;
     while(curr!=NULL && fun->comp(curr->key,k)!=0){
           P=curr;
           if( fun->comp(curr->key,k)<0 )  curr=curr->dx;
           else if( fun->comp(curr->key,k)>0 ) curr=curr->sx;
     }         
     if(curr!=NULL){
     	if (P==NULL) T=cancellaroot(T,fun); 
          else{
          	if(P->sx==curr) P->sx=cancellaroot(P->sx,fun);
               else P->dx=cancellaroot(P->dx,fun);       
           }
      }         
return T;
}


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

ABR* staccamin(ABR* P,ABR* T){
if(T!=NULL){
   while(T->sx!=NULL){
     P=T;
     T=T->sx;
    }   
       if(P->sx==T)
          P->sx=T->dx; 
       else
          P->dx=T->dx;            
 }  
return T;
}

//Cancella nodo le cui chiavi sono in un dato intervallo ed hanno una certa parità
ABR* CancIntervallo(ABR* T,int tipo,void *k1, void *k2,FUNZIONI *fun){
	ABR*curr=T;
     STACK* st=NULL;
	ABR*P=NULL;
	ABR*last=NULL;
	int m;
	if(fun->comp(k1,k2)>0) printf("Errore dati inseriti\n");
	else{
		while(st!=NULL || curr!=NULL){		        	
			if(curr!=NULL){
          	     st=push(st,curr);			
				if( fun->comp(curr->key,k1)>0){
          	              	curr=curr->sx;
				}
				else{
					last=curr->sx; //simulazione discesa a sinistra
					curr=NULL; //per risalire
				}
			}
			else{
				curr=top(st);
				if(curr->dx!=last && curr->dx!=NULL){
					if(fun->comp(curr->key,k2)<0){
						curr=curr->dx;
					}
					else{
						last=curr->dx;
						curr=NULL;
					}
				}else{
				   st=pop(st);
				   P=top(st);									
				   last=curr;					
				   if(fun->comp(curr->key,k1)>=0 && fun->comp(curr->key,k2)<=0 && fun->pari(curr->key)==tipo){							
						if (P==NULL){						
							T=cancellaroot(T,fun);
						}else{
							if(P->sx==curr){
								P->sx=cancellaroot(curr,fun);
								last=P->sx;
							}else{
								P->dx=cancellaroot(curr,fun);
								last=P->dx;
							}
						}
					}
					curr=NULL;
				}
		}
	}
 }	
 return T;
}

//abr casuale
ABR* ABRcasual(int n,FUNZIONI *fun){
	void*k;
	int i;
	ABR*T=NULL;
	for(i=0;i<n;i++){
		k=fun->random();				
		T=InserimentoABR(T,k,fun);
	}	
	return T;
}

//Chiavi di abr in array ordinato
int ArrayOrd(ABR* T,void **A, int i,FUNZIONI *fun){
     ABR*curr=T;
     STACK*st=NULL;
     while(curr!=NULL || st!=NULL ){
     	 if (curr!=NULL){             
              st=push(st,curr);
              curr=curr->sx;     
		}
		else{
			curr=top(st);
			A[i]=fun->crea(curr->key);
			i=i+1;
			st=pop(st);
			curr=curr->dx;
      	}
	}
	return i;
}

//numero nodi
int NumeroNodi(ABR* T){
     int n=0;
     ABR*curr=T;
     STACK*st=NULL;
     while(curr!=NULL || st!=NULL ){          
		if (curr!=NULL){              
      		st=push(st,curr);
			curr=curr->sx;     
    	  }
		else{
			curr=top(st);
			n=n+1;
			st=pop(st);
			curr=curr->dx;
		}
	}
	return n;
}
	                      

//duplicazione abr
ABR* duplicatoabr(ABR* T,FUNZIONI *fun){
	ABR*duplicate=NULL;
	ABR*curr=T;
   	ABR*node=NULL;    	
	STACK*st=NULL;    
	STACK*std=NULL;	
	ABR*LAST=NULL;
	ABR*padre=NULL;
	ABR*padre1=NULL;
		while(curr!=NULL || st!=NULL ){
    		if(curr!=NULL){
	    		st=push(st,curr);
				node=creanode(curr->key,fun);        	        
				std=push(std,node);
				curr=curr->sx;
        	}
        	else{
       		 	curr=top(st);
            	if (curr->dx!=LAST && curr->dx!=NULL){
	        		curr=curr->dx;
            	}
 				else{
	    		        		
	 				st=pop(st);
					padre=top(st); 						
					node=top(std);					
					std=pop(std);     
					padre1=top(std);  
					LAST=curr;						        
					if(padre!=NULL){
						if(padre->sx==curr)	padre1->sx=node;
						else padre1->dx=node;				               			
					}else duplicate=node;						
				
					curr=NULL;
	 			}
		}
 	}	
  	return duplicate;	
}



//verifica iterativa
int VerifyEqual(ABR*T,ABR*T2,FUNZIONI *fun){
	ABR*curr=T;
	ABR*curr2=T2;
	STACK* st=NULL;
	STACK*st2=NULL;
	int verifica=1;
	while( verifica==1 && ( (st!=NULL && st2!=NULL) || (curr!=NULL && curr2!=NULL) ) ){
		if (curr!=NULL && curr2!=NULL) {
			if(fun->comp(curr->key,curr2->key)==0){
				st=push(st,curr);
				st2=push(st2,curr2);
				curr=curr->sx;
				curr2=curr2->sx;
			}else
				verifica=0;
		}else if(curr==NULL && curr2==NULL){
			curr=top(st);
			curr2=top(st2);
			st=pop(st);
			st2=pop(st2);
			curr=curr->dx;
			curr2=curr2->dx;
		}else 
			verifica=0;
	}
return verifica;
}	
			

//struttura per gli indici dell'array		
struct indici{
	int a;
	int b;
};

typedef struct indici intervallo;

//funzione che restituisce un puntatore a una struttura intervallo dati gli indici come input 
intervallo *CreaIntervallo(int x, int y){
	intervallo *interv = malloc(sizeof(intervallo));
	interv->a=x;
	interv->b=y;
	return interv;
}

//funzione che crea un abr perfettamento bilanciato a partire da un altro abr
ABR *Pbil(ABR *ROOT,FUNZIONI *fun){
	int mid;
	intervallo *curr = malloc(sizeof(intervallo));
	intervallo *last = malloc(sizeof(intervallo));
	intervallo *PI;
	ABR *PN=NULL;
	ABR* node=NULL;
	ABR* bilanciato=NULL;
	STACK *stI = NULL;//stack con gli intervalli
	STACK *stN = NULL;//stack con i nodi
	void **A;
	int n,m;
	
	m=NumeroNodi(ROOT);
	A=malloc(m*sizeof(void*));//alloco array 
	n=ArrayOrd(ROOT,A,0,fun);//riempio l'array ordinato contenente le chiavi dell'albero
	curr->a=0;
	curr->b=n-1;  
	while ( curr->a<=curr->b  || stI!=NULL ){
		if(curr->a<=curr->b){
			mid=(curr->a+curr->b)/2;
			node=creanode(A[mid],fun);
			stN=push(stN,node);
			stI=push(stI,curr);
			curr=CreaIntervallo(curr->a, mid-1);
		}else{
			free(curr);
			curr=top(stI);
			mid=(curr->a + curr->b)/2;
			if(mid+1<=curr->b  && mid+1!=last->a && curr->b!=last->b)
				curr = CreaIntervallo(mid+1, curr->b);			
			else{
				node=top(stN);
				stN=pop(stN);
				stI=pop(stI);
				PN=top(stN);
				PI=top(stI);
          		if(PN!=NULL){				
					if (PI->a==curr->a && PI->b>curr->b) PN->sx=node;
					else	PN->dx=node;
				}else bilanciato=node;
				last->a=curr->a;
				last->b=curr->b;
				curr->a=0; //assegno intervallo [0,-1] per effettuare la risalita
				curr->b=-1;
			}
		}
	}
	free(curr);
	free(last);
	DeallocArr(A,n,fun);	
	return bilanciato;
}

	


//deallocazione array
void DeallocArr(void ** A,int n,FUNZIONI *fun){
    int j;
    for(j=0;j<n;j++) fun->tfree(A[j]);
    free(A);
}
