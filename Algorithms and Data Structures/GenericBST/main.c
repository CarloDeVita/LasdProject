//DE VITA CARLO N86001634
//GESTIONE ABR CON CHIAVI DI TIPO STRINGA
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ABR.h"
#include"mystring.h"
#include"ListRoot.h"
#include"fun.h"
main(){

ABRLIST *L=NULL,*nodo,*nodo2;
void *x,*s,*k1,*k2;
void **arr;
int scelta,tipo;
int n,verifica,i,id,len;
FUNZIONI *fun=malloc(sizeof(FUNZIONI));
srand(time(NULL));
printf("\n|||GESTIONE LIBRERIA ALBERI BINARI DI RICERCA|||\n");
printf("Scegliere se lavorare con:\n1-interi\n2-float\n3-stringhe\n4-record (intero;stringa)\n\nLa scelta è: ");
id=abcontrol(1,4);
printf("\n");

if(id==1){   
   fun->crea=creaint;   
   fun->comp=&compint;
   fun->tfree=&free;
   fun->stamp=&stampaint;
   fun->insert=&insintero;
   fun->pari=&pariint;
   fun->random=&random_int;
   printf("ok\n");
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
do{

 printf("1- Creazione di un albero su cui lavorare \n"); 
 printf("2- Stampa della lista di alberi su cui sto lavorando\n");
 printf("3- Inserimento in ABR\n");
 printf("4- Cancella tutto l'ABR\n");
 printf("5- Cancella valore dato dall'ABR\n"); 
 printf("6- Stampa ABR \n");
 printf("7- Cancella valori pari o dispari e con valore compreso tra altre due valori in ingresso\n");
 printf("8- Costruzione di un ABR con n valori casuali\n");
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
          id=Insid(L);
          L=InserisciLista(L,id);
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
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
          	    printf("Inserisci chiave: ");
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
			id=Intcontrol();
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
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
               		printf("Inserisci chiave da cancellare: ");
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
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
	          	printf("Scegliere tipo di visita: \n1-PREORDER\n2-INORDER\n3-POSTORDER");
   				printf("\nScelta: ");
        			tipo=abcontrol(1,3);
        			if(tipo==1) preorder(nodo->root,fun);
        			else if(tipo==2) inorder(nodo->root,fun);
        			else postorder(nodo->root,fun);
         	  	}
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
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
                	printf("Scegliere il valore del nodo da cancellare deve essere pari o dispari \n");
                	printf("0- Dispari\n1- Pari\nScelta: ");
                	tipo=abcontrol(0,1);
                	printf("\nInserimento Chiave 1: \n");
                	k1=fun->insert();
                	printf("\nInserimento Chiave 2: \n");
                	k2=fun->insert();
                	nodo->root=cancInterv(nodo->root,tipo,k1,k2,fun);
                	if(nodo->root==NULL) L=CancLista(L,id);
          	}
                else printf("ALBERO NON ESISTENTE\n");
          }
          printf("\n");     
          break;
    
    case 8:
          printf("LISTA DEGLI ALBERI: ");
          if (L==NULL) printf("NON CI SONO ALBERI\n");
          else{  Stampalist(L); printf("\n");}
          printf("Scegliere ID del nuovo albero(Deve essere un numero intero): ");
          id=Insid(L);
          L=InserisciLista(L,id);
          printf("Scegliere il numero di nodi da inserire: ");
          n=Intcontrol();
          L->root=ABRcasual(n,fun);
          printf("\n");
          break;
     
    case 9:
          printf("LISTA DEGLI ALBERI: ");
          if(L==NULL) printf("NON CI SONO ALBERI\n");
          else {
          	Stampalist(L);
          	printf("\nScegliere quale albero deve essere duplicato: ");
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if (nodo!=NULL){
              		printf("Scegliere ID del nuovo albero: ");
              		id=Insid(L);
                    L=InserisciLista(L,id);
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
             	 id=Intcontrol();
             	 nodo=CercaRoot(L,id);
             	 if(nodo!=NULL){
                    printf("Inserisci ID del secondo albero: ");
                 	id=Intcontrol();
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
     		id=Intcontrol();
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
          printf("\n\n");
          break;
 
   case 12: 
          printf("LISTA DEGLI ALBERI: ");
          if(L==NULL) printf("NON CI SONO ALBERI\n");
          else{
          	Stampalist(L);
          	printf("\nScegliere da quale albero costruire un ABR Perfettamente Bilanciato: ");
          	id=Intcontrol();
          	nodo=CercaRoot(L,id);
          	if(nodo!=NULL){
                	printf("Scegliere ID del nuovo albero: ");
                	id=Insid(L);
                	L=InserisciLista(L,id); 
                   	L->root=Pbil(nodo->root,fun);
				PbilControl(L->root)==1 ? printf("ALBERO PERFETTAMENTE BILANCIATO\n") : printf("ALBERO NON PERFETTAMENTE BILANCIATO\n");                                       
			}else printf("ALBERO NON ESISTENTE\n");
          }
 	  	printf("\n");
         	break;
 
  case 13: //DEALLOCA TUTTO MA NON ESCE
          while(L!=NULL) {
            L->root=CancAlbero(L->root,fun);
            L=CancLista(L,L->id);
          }
          printf("\n");
          break;
 
  
  case 14://DEALLOCA TUTTO ED ESCE 
          while(L!=NULL) {
            L->root=CancAlbero(L->root,fun);
            L=CancLista(L,L->id);
          }
          break;
   
  default: printf("NON E' STATO INSERITO UN VALORE CORRETTO. REINSERIRE!\n ");
           break;
} 
}while (scelta!=14);
free(fun);		
} 


