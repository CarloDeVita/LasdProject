#include<stdio.h>
#include<stdlib.h>
#include"Lista.h"

ADJ* InsertL(ADJ* adj, int v,float peso){
	if(adj!=NULL){
		if(adj->key!=v)
			adj->next = InsertL(adj->next,v,peso);
	}else{
		adj=malloc(sizeof(ADJ));		
		adj->key=v;
		adj->p=peso;
		adj->next=NULL;
	}
	return adj;
}	

ADJ* InsertTestaL(ADJ* adj, int v,float peso){
	ADJ*nuovo=malloc(sizeof(ADJ));
	nuovo->key=v;
	nuovo->p=peso;
	nuovo->next=adj;
	adj=nuovo;
	return adj;
}	 

int InLista(ADJ *adj, int v){
	if(adj!=NULL){
		if(adj->key != v)
			return InLista(adj->next,v);
		else
			return 1;
	}
	return 0;
}				
			

ADJ* DeleteL(ADJ *adj,int v){
	if(adj!=NULL){
		if(adj->key != v)
			adj->next=DeleteL(adj->next,v);
		else{
			ADJ*tmp=adj;
			adj=adj->next;
			free(tmp);
		}		
	}
	return adj;
}

void FreeLista(ADJ* adj){
	if(adj!=NULL){
		FreeLista(adj->next);
		free(adj);
	}
}	

