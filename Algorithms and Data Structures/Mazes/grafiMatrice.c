#include<stdio.h>
#include<stdlib.h>
//#include"Lista.h"
#include"grafiMatrice.h"
#include"Parser.h"

void* traspostoM(void* adjmat){
	matAdj* A = adjmat;
	matAdj* S = allocaMatAdj(A->dim);
	int i,j;
	for(i=0 ; i< A->dim ; i++){
		for(j = 0; j< A->dim; j++){
			if(A->M[i][j] != NULL){
				S->M[j][i] = malloc(sizeof(float));
				*(S->M[j][i]) = *(A->M[i][j]); 	
			}
		}
	}
	return S;
}

matAdj* allocaMatAdj(int dim){
	matAdj* A = NULL;
	int k = dim;
	int i;
	if(k>0){
		A = malloc(sizeof(matAdj));
		A->dim = k;
		A->M=calloc(A->dim,sizeof(float**));
		for(i=0;i<k;i++)
			A->M[i]=calloc(k,sizeof(float*));
	}
	return A;
}		

int getDimM(void *E){
	matAdj* A = E;
	return A->dim;
}

void* inserisciVerticeM(void*S,int v){
	matAdj* A = S;
	float ***M2, ***Mtemp=A->M; 
	int i,j;
	A->dim++;
	M2=(float***)malloc( A->dim* sizeof(float**));
	for(i=0;i<A->dim;i++)
		M2[i]=(float**)malloc( (A->dim)*sizeof(float*)); //alloco nuova matrice 		
	
	for(i=0;i<A->dim-1;i++){
		for(j=0;j<A->dim-1;j++){
			//M[i][j]=malloc(sizeof(float));
			M2[i][j]=Mtemp[i][j];
		}
		free(Mtemp[i]);
		M2[i][j]=NULL;
	}
	for (i=0;i<A->dim;i++)
		M2[A->dim-1][i]=NULL; //metto a 0 tutti gli archi del nuovo vertice	
	A->M=M2; //assegno alla struttura dati del grafo la nuova matrice
	free(Mtemp);	
	return A;
}
	
	
void inserisciArcoM(void*S,int a,int b,float peso){	
	matAdj* A = S;
	
	if( A->M[a][b] == NULL ){
		A->M[a][b]=malloc(sizeof(float));
		*(A->M[a][b]) = peso;
	}else{
		//printf("Errore Arco gia presente");
	}	
}	 
		
	
	
	//((int**)A)[a][b]=1

void* eliminaVerticeM(void*S,int v){
	matAdj* A = S;
	A->dim--;
	float ***M2,***Mtemp=A->M;
	int i,j,x,y;	
	M2=malloc( (A->dim)*sizeof(float**));
	for(i=0;i<A->dim;i++)
		M2[i]=malloc( (A->dim)*sizeof(float*)); //alloco nuova matrice	
	x=0;
	y=0;		
	for(i=0; i<A->dim+1; i++){
		if( i != v){
			y=0;
			for( j=0;j<A->dim+1;j++){
				if( j != v ){
					M2[x][y]=Mtemp[i][j];
					y++;
				}else //se c'è l'arco dove devo eliminare
					free(Mtemp[i][j]);				
			}
			free(Mtemp[i]);//
			x++;
		}else{
			for(j=0;j<A->dim+1;j++)
				if(Mtemp[i][j] != NULL) free(Mtemp[i][j]);
			free(Mtemp[i]);
		}
	}				         
	A->M=M2;//assegno alla struttura dati del grafo la nuova matrice
	free(Mtemp);
	return A;
}	
	

void eliminaArcoM(void*S,int a,int b){
	matAdj* A = S;
	
	if( A->M[a][b]!= NULL ){
		free ( A->M[a][b] );
		A->M[a][b]=NULL;
	}
}



ADJ *adiacentiM(void*S,int v){
	int i;
	ADJ *L=NULL;
	matAdj* A = S;
	for(i=0;i<A->dim;i++){
		if( A->M[v][i] != NULL)			
			L=InsertTestaL( L,i,*(A->M[v][i]) );
	}
	return L;
}

void deallocaStrutturaM(void*S){
	int i,j;
	matAdj* A = S;
	for(i=0; i<A->dim; i++){
		for(j=0; j<A->dim; j++){
			if( A->M[i][j] != NULL )
				free( A->M[i][j] );
		}
		free(A->M[i]);
	}			
	free(A->M);
	free(A);
}

void freeAdjM(ADJ* list){
	FreeLista(list);
}
			


float hM(void*S,int a,int b){
	return 0.;

}		


int arcoM(FILE* fd, matAdj* A,int x){
	int v, c, y;
	float p;
	if ( (v = match(fd,LPAR)) ){
		v = ParseInt(fd, &y);
		if (v){
			if(y < A->dim){
				if ( (v = match(fd,COMMA)) ){
					
					if(v = ParseFloat(fd,&p)){
						
						if ( (v = match(fd,RPAR)) )
							inserisciArcoM(A,x,y,p);
						else
							syntaxErr(RPAR,ftell(fd));
					}
					else
						printf("Errore parser float\n");
				}
				else
					syntaxErr(COMMA, ftell(fd));
			}
			else
				printf("Il nodo %d non esiste nel grafo\n",y);
		}		
		else
			printf("Errore parser intero\n");
	}
	else
		syntaxErr(LPAR, ftell(fd));
	
	return v;
}
	
		
		
		

int lista_archiM(matAdj* A,FILE *fd,int x){
	int v=0,c;
	
	do{
		v = arcoM(fd,A,x);
	}while (v && match(fd,COMMA) );
	
	return v;		
}			
		
		
				

int adiacenzeM (matAdj* A, FILE* fd){
	int v,x,c;
	v = ParseInt(fd,&x);
	if(v){	
		if (x < A->dim ){			
			if( match(fd,ARROW) )
				v = lista_archiM(A,fd,x); 
			if ( !(match(fd,SEMICOLON)) ){ 
					v = 0;
					syntaxErr(SEMICOLON,ftell(fd));
				}
		}
		else{
			v = 0;
			printf("Il nodo %d non esiste nel grafo\n",x);
		}
	}else{
		printf("Errore parser intero\n");
	}
	return v;
}



void* parserM(char* file){
	matAdj* A = NULL;
	int v,dim;
	FILE* fd = fopen(file,"r+");
	if(fd != NULL){
		if(match(fd,LPAR)){
			v = ParseInt(fd,&dim);
			if(v){
				if(match(fd,RPAR)){
					A = allocaMatAdj(dim);
					while(v && !match(fd,DOT) )
						v = adiacenzeM(A,fd);					
					if (!v){
						deallocaStrutturaM(A);
						A = NULL;
					}
				}
				else 
					syntaxErr(RPAR,ftell(fd));
			}
			else
				printf("Errore parser intero\n");
		}
		else
			syntaxErr(LPAR,ftell(fd));
	
	fclose(fd);
	}
	return A;
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
