#include<stdio.h>
#include<stdlib.h>
#include"stack.h"


STACK* push(STACK* st,void*T){
        STACK*nuovo=malloc(sizeof(STACK));
        nuovo->nodo=T;
	   nuovo->next=st;
        st=nuovo;
        return st;
    }

STACK* pop(STACK *st){
       if(st!=NULL){
         STACK*tmp;
         tmp=st;
         st=st->next;
         free(tmp);	        
      }
   return st;
}

void* top(STACK *st){
       if(st!=NULL) return (st->nodo);
       else return NULL; 
}


       
