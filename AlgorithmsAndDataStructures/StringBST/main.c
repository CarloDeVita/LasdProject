//DE VITA CARLO N86001634
//GESTIONE ABR CON CHIAVI DI TIPO STRINGA
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ABR.h"
#include"mystring.h"
#include"Collect.h"

main(){

abrCollect *L=NULL,*nodo,*nodo2;
char* x,*s;
char *str1,*str2,**arr;
int scelta, tipo;
int n,verifica,i,id,len,h1,h2;


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
          	    x=insertString(10);
          	    nodo->root=inserimentoABR(nodo->root,x);
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
				nodo->root=CancAlbero(nodo->root);
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
           		x=insertString(10);
		   		nodo->root =CancNodo(nodo->root,x);
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
				stampaAbr(nodo->root);
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
            	printf("\nInserimento Stringa 1: \n");
            	str1=insertString(10);
            	printf("\nInserimento Stringa 2: \n");
            	str2=insertString(10);
            	printf("\nInserimento Altezza 1: \n");
            	h1 = intControl();
            	printf("\nInserimento Altezza 2: \n");
            	h2 = intControl();
            	nodo->root=cancInterv(nodo->root,str1,str2,h1,h2);
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
		printf("Scegliere il numero di stringhe da inserire: ");
		n=intControl();
		printf("Scegliere lunghezza massima delle stringhe: ");
		len=intControl();
		L->root=ABRcasual(n,len);
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
             	L->root=duplicatoabr(nodo->root);
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
	                verifica=VerifyEqual(nodo->root,nodo2->root);
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
				arr=(char**)malloc(n*sizeof(char*));
    			i=0;
     			i=ArrayOrd(nodo->root,arr,i); 
     			printf("L'array ordinato è il seguente: ");
     			stampArray(arr,i);
     			deallocArrayStr(arr,i);
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
               	L->root=Pbil(nodo->root);
				PbilControl(L->root)==1 ? printf("ALBERO PERFETTAMENTE BILANCIATO\n") : printf("ALBERO NON PERFETTAMENTE BILANCIATO\n");                                                      
			}else printf("ALBERO NON ESISTENTE\n");
		}
		printf("\n");
		break;
 
	case 13: //DEALLOCA TUTTO MA NON ESCE
		while(L!=NULL) {
        	L->root=CancAlbero(L->root);
            L=CancLista(L,L->id);
      	}
		printf("\n");
      	break;

  
	case 14://DEALLOCA TUTTO ED ESCE 
		while(L!=NULL) {
			L->root=CancAlbero(L->root);
            L=CancLista(L,L->id);
		}
      	break;
   
  	default: printf("NON E' STATO INSERITO UN VALORE CORRETTO. REINSERIRE!\n ");
		break;
} 
}while (scelta!=14);

} 


