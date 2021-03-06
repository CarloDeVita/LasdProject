//DE VITA CARLO N86001634
//GESTIONE ABR CON CHIAVI DI TIPO STRINGA
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ABR.h"
#include"mystring.h"
#include"Collect.h"
#include"fun.h"
main(){

abrCollect *L=NULL,*nodo,*nodo2;
void *x,*s,*k1,*k2;
void **arr;
int scelta,h1,h2;
int n,verifica,i,id,len;
FUNZIONI *fun=malloc(sizeof(FUNZIONI));
srand(time(NULL));
printf("\n|||GESTIONE LIBRERIA ALBERI BINARI DI RICERCA|||\n");
printf("Scegliere se lavorare con:\n1-interi\n2-float\n3-stringhe\n4-record (intero;stringa)\n\nLa scelta è: ");
id=intControlInterval(1,4);
printf("\n");

if(id==1){   
   fun->crea=creaint;   
   fun->comp=&compint;
   fun->tfree=&free;
   fun->stamp=&stampaint;
   fun->insert=&insintero;
   fun->pari=&pariint;
   fun->random=&random_int;
}
else if(id==2){
   fun->crea=&creafloat;
   fun->comp=&compfloat;
   fun->tfree=&free;
   fun->stamp=&stampafloat;
   fun->insert=&insfloat;
   fun->pari= &parifloat;
   fun->random=&random_float;
}
else if(id==3){
   fun->crea=&creastr;
   fun->comp=&compstr;
   fun->tfree=&free;
   fun->stamp=&stampastr;
   fun->insert=&insertstr;
   fun->pari=&paristring;
   fun->random=&random_string;
}

else {
   fun->crea=&crearecord;
   fun->comp=&comprecord;
   fun->tfree=&free_rec;
   fun->stamp=&stamprecord;
   fun->insert=&insertrecord;
   fun->pari=&parirecord;
   fun->random=&random_record;
}
srand(time(NULL));
do{
 printf("\n|||GESTIONE LIBRERIA ALBERI BINARI DI RICERCA|||\n");
 printf("1- Creazione di un albero su cui lavorare \n"); 
 printf("2- Stampa della lista di alberi su cui sto lavorando\n");
 printf("3- Inserimento in ABR\n");
 printf("4- Cancella tutto l'ABR\n");
 printf("5- Cancella stringa data dall'ABR\n"); 
 printf("6- Stampa ABR \n");
 printf("7- Cancella stringhe pari o dispari e con valore compreso tra altre due stringhe in ingresso\n");
 printf("8- Costruzione di un ABR con n stringhe casualmente generate\n");
 printf("9- Duplicazione di un ABR\n");
 printf("10- Verifica se due ABR sono identici\n");
 printf("11- Inserisci chiavi dei nodi in un array ordinato\n");
 printf("12- Costruzione di un ABR perfettamente bilanciato a partire da un ABR dato\n");
 printf("13- CANCELLA TUTTI GLI ALBERI\n");
 printf("14- ESCI\n");
 printf("\nINSERIRE SCELTA: ");
 scelta=0;
 scanf("%d",&scelta);
 printf("\n");
 
	SvuotaBuffer();
	switch(scelta){
	case 1: 
		printf("LISTA DEGLI ALBIERI: ");
	  	(L==NULL? printf("NON CI SONO ALBERI") : Stampalist(L));
		printf("\nScegliere ID dell'albero che deve essere creato (DEVE ESSERE UN NUMERO INTERO): ");
		L=InsertCollect(L);
		printf("\n");
		break;
           
    case 2: 
          printf("LISTA DEGLI ALBERI: ");
          (L==NULL? printf("NON CI SONO ALBERI\n") : Stampalist(L));
          printf("\n");
          break;
               
    case 3:          
		printf("LISTA DEGLI ALBERI: ");
		if (L==NULL) printf("NON CI SONO ALBERI\n");
		else{ 
			Stampalist(L);
			printf("\nScegliere su quale albero effettuare l'inserimento: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
          	    printf("Inserisci stringa: ");
          	    x=fun->insert();
          	    nodo->root=inserimentoABR(nodo->root,x,fun);
          	}
          	else printf("ALBERO NON ESISTENTE\n"); 
     	}
      	break;
        
    case 4:
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {	         
			Stampalist(L);
			printf("\nScegliere quale albero cancellare: ");
		  	id=intControl();
     	  	nodo=CercaRoot(L,id);
			if (nodo!=NULL){
				nodo->root=CancAlbero(nodo->root,fun);
				L=CancLista(L,id);//cancelliamo l'albero dalla lista
			}
			else printf("ALBERO NON ESISTENTE\n");
		}
		printf("\n");
		break;
    
    case 5:
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {
			Stampalist(L);
          	printf("\nScegliere su quale albero effettuare questa cancellazione: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
           		printf("Inserisci la stringa da cancellare: ");
           		x=fun->insert();
		   		nodo->root =CancNodo(nodo->root,x,fun);
	       		if(nodo->root==NULL) L=CancLista(L,id);      //
      		}
      		else printf("ALBERO NON ESISTENTE\n");
        }
		printf("\n");
		break;  
    
    case 6:
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {
			Stampalist(L);
          	printf("\nScegliere quale albero stampare: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL)
				stampaAbr(nodo->root,fun);
          	else printf("ALBERO NON ESISTENTE\n");              
		} 
		printf("\n");
		break;
    
    case 7:
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {
			Stampalist(L);
 			printf("\nScegliere da quale albero effettuare questa cancellazione: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
            	printf("\nInserimento Dato 1: \n");
            	k1 = fun->insert();
            	printf("\nInserimento Dato 2: \n");
            	k2 = fun->insert();
            	printf("\nInserimento Altezza 1: \n");
            	h1 = intControl();
            	printf("\nInserimento Altezza 2: \n");
            	h2 = intControl();
            	nodo->root=cancInterv(nodo->root,k1,k2,h1,h2,fun);
            	if(nodo->root==NULL) L=CancLista(L,id);
			}
            else printf("ALBERO NON ESISTENTE\n");
          }
          printf("\n");     
          break;
    
    case 8:
		printf("LISTA DEGLI ALBERI: ");
		if (L==NULL) printf("NON CI SONO ALBERI\n");
		else{  
			Stampalist(L); 
			printf("\n");
		}
		printf("Scegliere ID del nuovo albero(Deve essere un numero intero): ");
		L=InsertCollect(L);
		printf("Scegliere il numero di dati da inserire: ");
		n=intControl();
		L->root=ABRcasual(n,fun);
		printf("\n");
		break;
     
    case 9:
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {
      		Stampalist(L);
          	printf("\nScegliere quale albero deve essere duplicato: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
          		printf("Scegliere ID del nuovo albero: ");
          		L=InsertCollect(L);
             	L->root=duplicatoabr(nodo->root,fun);
          	}             
          	else printf("ALBERO NON ESISTENTE\n");
      	}
		printf("\n");
		break;
     
    case 10:
		if(L!=NULL && L->next!=NULL){   
			printf("LISTA DEGLI ALBERI: ");
            Stampalist(L);
			printf("\nInserisci ID del primo albero: ");
			id=intControl();
			nodo=CercaRoot(L,id);
			if(nodo!=NULL){
				printf("Inserisci ID del secondo albero: ");
				id=intControl();
             	nodo2=CercaRoot(L,id);
             	if(nodo2!=NULL){
	                verifica=VerifyEqual(nodo->root,nodo2->root,fun);
                    if(verifica==1) printf("Gli alberi sono identici");
            		else printf("Gli alberi NON sono identici");
             	}
             	else printf("ALBERO NON ESISTENTE\n");
              	}
              	else printf("ALBERO NON ESISTENTE\n");
          }
          else printf("ERRORE: NON ESISTONO ALMENO DUE ALBERI");
          printf("\n");
          break; 
    
    case 11:
		printf("LISTA DEGLI ALBERI: "); 
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else {
			Stampalist(L);
         	printf("\nScegliere da quale albero creare l'array ordinato: ");
     		id=intControl();
			nodo=CercaRoot(L,id);
     		if(nodo!=NULL){
				n=NumeroNodi(nodo->root);
				arr=(void**)malloc(n*sizeof(void*));
    			i=0;
     			i=ArrayOrd(nodo->root,arr,i,fun); 
     			printf("L'array ordinato è il seguente: ");
     			StmArr(arr,i,fun);
          		DeallocArr(arr,i,fun);
     		}
     		else printf("ALBERO NON ESISTENTE");
		}
		printf("\n");
		break;
 
	case 12: 
		printf("LISTA DEGLI ALBERI: ");
		if(L==NULL) printf("NON CI SONO ALBERI\n");
		else{
      		Stampalist(L);
          	printf("\nScegliere da quale albero costruire un ABR Perfettamente Bilanciato: ");
          	id=intControl();
          	nodo=CercaRoot(L,id);
          	if(nodo!=NULL){
    	    	printf("Scegliere ID del nuovo albero: ");
    	    	L=InsertCollect(L);
               	L->root=Pbil(nodo->root, fun);
				PbilControl(L->root)==1 ? printf("ALBERO PERFETTAMENTE BILANCIATO\n") : printf("ALBERO NON PERFETTAMENTE BILANCIATO\n");                                                      
			}else printf("ALBERO NON ESISTENTE\n");
		}
		printf("\n");
		break;
 
	case 13: //DEALLOCA TUTTO MA NON ESCE
		while(L!=NULL) {
        	L->root=CancAlbero(L->root, fun);
            L=CancLista(L,L->id);
      	}
		printf("\n");
      	break;

  
	case 14://DEALLOCA TUTTO ED ESCE 
		while(L!=NULL) {
			L->root=CancAlbero(L->root, fun);
            L=CancLista(L,L->id);
		}
      	break;
   
  	default: printf("NON E' STATO INSERITO UN VALORE CORRETTO. REINSERIRE!\n ");
		break;
} 
}while (scelta!=14);

} 


