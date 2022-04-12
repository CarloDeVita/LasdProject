//PARSER	



typedef enum {LPAR, RPAR, ARROW, COMMA, SEMICOLON, DOT} symbols;

void avoidSpace (FILE* fd){
	int c;
	while (   ((c=fgetc(fd))==' ') || (c=='\n') || (c=='\t') ) printf("c = %c\n",(char)c);
	ungetc(c,fd); //rimetti il carattere dentro perchè va bene
}


int matchS (FILE *fd, symbols sym){
	avoidSpace(fd);
	switch(sym)




int ParseInt(FILE *fd, int *num){
	int v=0,i=0,c;
	char buf[100];
	avoidSpace(fd);
	while ( (c=fgetc(fd)) >= 48 && (c <= 57) ){
		buf[i] = (char)c;
		i++;
	}
	ungetc(c,fd);
	if(i!=0){
		v=1;
		buf[i]='\0';
		*num = atoi(buf);
	}
	return v;
}


int ParseFloat(FILE *fd, float *num){
	int v=0,i=0,c;
	char buf[100];
	avoidSpace(fd);
	while ( (c=fgetc(fd))>= 48 && (c <= 57) ){
		buf[i++] = (char)c;
	}
	if (c == '.'){
		buf[i++] = c;
		while ( (c=fgetc(fd))>= 48 && (c <= 57) )
			buf[i++] = (char)c;
	}
	ungetc(c,fd);
	if(i!=0){
		v=1;
		buf[i]='\0';
		*num = atof(buf);
	}
	return v;
}



int arco(FILE* fd, grafo* G,int x){
	int v, c, y;
	float p;
	avoidSpace(fd);
	c = fgetc(fd);
	printf("ciaooo c=%c\n",(char)c);
	if ( c == '(' ){
		avoidSpace(fd);
		v = ParseInt(fd, &y);
		printf("ciaooo v=%d e y=%d\n",v,y);
		if (v){
			if(y < G->size){
				avoidSpace(fd);
				c = fgetc(fd);
				printf("ciaooo,, c=%c\n",(char)c);
				if ( c==',' ){
					avoidSpace(fd);
					v = ParseFloat(fd,&p);
					printf("ciaooo v=%d e p=%f\n",v,p);
					avoidSpace(fd);
					if(v){
						if (fgetc(fd) == ')' ){
							printf("Inserisco l'arco %d,%d,%f\n",x,y,p);
							InserimentoArco(G,x,y,p);
						}
						else{
							v = 0;
							//errore par chiusa
						}
					}
					else{
						//errore float
					}
				}
				else{
					v = 0;
					//errore virgola
				}
			}
			else{
				v = 0;
				//errore numero nodo
			}
		}		
		else{
			//errore intero
		}
	}
	else{
		v = 0;
		//errore parentesi aperta
	}
	return v;
}
	
		
		
		

int lista_archi(grafo *G,FILE *fd,int x){
	int v=0,c;
	avoidSpace(fd);
	v = arco(fd,G,x);
	avoidSpace(fd);
	while (v && (c=fgetc(fd)) == ','){
		v = arco(fd,G,x);
		avoidSpace(fd);
	}
	if (v) 	//se sono uscito perche nn trovo la virgola va bene
		ungetc(c,fd);
	return v;		
}			


int adiacenze (grafo* G, FILE* fd){
	int v,x,c;
	avoidSpace(fd);
	v = ParseInt(fd,&x);
	//printf("il valore di x %d e v %d\n",x,v);
	if(v){	
		if (x < G->size ){			
			avoidSpace(fd);
			if( (c=fgetc(fd))=='-' && (c=fgetc(fd))=='>' ){
				printf("sto qua\n");
				v = lista_archi(G,fd,x); 
				if ( !(c=fgetc(fd))==';'){ 
					v = 0;
					//errore punto e virgola
				}
			}		
			else{
				v = 0;
				//errore freccia
			}
		}
		else{
			v = 0;
			//errore numero vertice
		}
	}else{
		//errore intero
	}
	return v;
}


grafo* GrafoParser(char* namef, fun* f){
	grafo *G = NULL;
	FILE *fd = fopen(namef,"r+");
	int dim, v;
	int c;
	if(fd != NULL){ 
		avoidSpace(fd);
		c=fgetc(fd);
		printf("ciao1 c=%c\n",(char)c);
		if ( c == '(' ){
			v = ParseInt(fd,&dim);
			printf("il valore di dim è: %d, v è %d\n",dim,v);
			if(v){
				avoidSpace(fd);
				c = fgetc(fd);
				printf("ciao2 c=%c\n",(char)c);
				if( c == ')' ){
					G = CreaGrafo(f,dim);
					printf("ho creato il grafo.\n");
					stampaArchi(G);
					printf("\nHo stampato gli archi\n");
					avoidSpace(fd);
					v = adiacenze(G,fd);
					
					printf("ciao3 c=%c\n",(char)c);
					while ( v && (c = fgetc(fd))!='.') { //(c = fgetc(fd))!= EOF && c != '.' ) 
						ungetc(c,fd);
						v = adiacenze(G,fd);
						avoidSpace(fd);
					}
					if (!v){
						printf("errore pv\n");
						DeallocaGrafo(G);
						G = NULL;
					}
				}
				else{
					//errore parentesi chiusa	
				}
			}
			else{
				//errore intero
			}
		}
		else{
			//errore parentesi aperta
		}
		close(fd);
	}	
	return G;
}	
		


