#include<stdio.h>
#include<stdlib.h>
//#include"Lista.h"
#include"grafiMatrice.h"

void* allocaGrafoM(int k){
	float ***M=NULL;
	int i;
	if(k>0){
		M=calloc(k,sizeof(float**));
		for(i=0;i<k;i++)
			M[i]=calloc(k,sizeof(float*));
	}
	return M;
}		


void* inserisciVerticeM(void*A,int k){
	float ***M, ***Mtemp=A;
	int i,j;
	M=(float***)malloc( (k+1)* sizeof(float**));
	for(i=0;i<k+1;i++)
		M[i]=(float**)malloc( (k+1)*sizeof(float*)); //alloco nuova matrice 		
	
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			//M[i][j]=malloc(sizeof(float));
			M[i][j]=Mtemp[i][j];
		}
		free(Mtemp[i]);
		M[i][j]=NULL;
	}
	for (i=0;i<=k;i++)
		M[k][i]=NULL; //metto a 0 tutti gli archi del nuovo vertice	
	A=M; //assegno alla struttura dati del grafo la nuova matrice
	free(Mtemp);	
	return A;
}
	
	
void inserisciArcoM(void*A,int a,int b,float peso){	
	if( ((float***)A)[a][b] == NULL ){
		((float***)A)[a][b]=malloc(sizeof(float));
		*( ((float***)A)[a][b] )=peso;
	}else{
		//printf("Errore Arco gia presente");
	}	
}	 
		
	
	
	//((int**)A)[a][b]=1

void* eliminaVerticeM(void*A,int k,int v){
	float ***M,***Mtemp=A;
	int i,j,x,y;	
	M=malloc( (k-1)*sizeof(float**));
	for(i=0;i<k-1;i++)
		M[i]=malloc( (k-1)*sizeof(float*)); //alloco nuova matrice	
	x=0;
	y=0;		
	for(i=0; i<k; i++){
		if( i != v){
			y=0;
			for( j=0;j<k;j++){
				if( j != v ){
					M[x][y]=Mtemp[i][j];
					y++;
				}else //se c'è l'arco dove devo eliminare
					free(Mtemp[i][j]);				
			}
			x++;
		}else{
			for(j=0;j<k;j++)
				if(Mtemp[i][j] != NULL) free(Mtemp[i][j]);
			free(Mtemp[i]);
		}
	}				         
	A=M;//assegno alla struttura dati del grafo la nuova matrice
	free(Mtemp);
	return A;
}	
	

void eliminaArcoM(void*A,int a,int b){
	if( ((float***)A)[a][b]!= NULL ){
		free ( ((float***)A)[a][b] );
		((float***)A)[a][b]=NULL;
	}
}



ADJ *adiacentiM(void*A,int k,int v){
	int i;
	ADJ *L=NULL;
	float ***M=A;
	for(i=0;i<k;i++){
		if( M[v][i] != NULL)			
			L=InsertTestaL( L,i,*(M[v][i]) );
	}
	return L;
}

void deallocaStrutturaM(void*A,int k){
	int i,j;
	float ***M=A;
	for(i=0; i<k; i++){
		for(j=0; j<k; j++){
			if( M[i][j] != NULL )
				free( M[i][j] );
		}
		free(M[i]);
	}			
	free(M);
}

void freeAdjM(ADJ* list){
	FreeLista(list);
}
			

/*void stampaArchiM(void *A,int k){
	int i,j;
	for(i=0; i<k; i++){
		for(j=0; j<k; j++){
			if( ((float***)A)[i][j] != NULL )
				printf("%d, %d\n",i,j ) ;
		}
	}
}*/						
