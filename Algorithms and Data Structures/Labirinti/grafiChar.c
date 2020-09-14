#include"grafiChar.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"Parser.h"

int global = 0;

pos* nameToCoord(cMap* cm, int v){
	pos* p = malloc(sizeof(pos));
	p->j = v % cm->colonne;
	p->i = (v - p->j)/ cm->colonne;
	return p;
}

int coordToName(cMap* cm, pos* p){
	return (p->i*cm->colonne + p->j);
}

pos* setPosizione(int i,int j){
	pos *p = malloc(sizeof(p));
	p->i = i;
	p->j = j;
	return p;
}


int getDimC(void* S){
	cMap* M = S;
	return M->righe*M->colonne;
}


cMap* allocaCharMap(int righe, int colonne){
	int i,j;
	int r = righe, c = colonne;
	cMap* cmap = malloc(sizeof(cMap));
	cmap->map = malloc(r * sizeof(char*));
	
	for(i = 0; i<r; i++)
		cmap->map[i] = malloc(c * sizeof(char));
	
	cmap->righe = r;
	cmap->colonne = c;
	for(i=0; i<cmap->righe; i++){
		for(j=0; j < cmap->colonne; j++){
			cmap->map[i][j] = -1; //metto tutti muri
		}
	}
	return cmap;
	
	
}
//return allocaCharMap(dimC->i,dimC->j);

/*cMap* allocaCharMap(int r, int c){
	cMap* cmap = malloc(sizeof(cMap));
	cmap->map = malloc(r * sizeof(char*));
	int i,j;
	for(i = 0; i<r; i++)
		cmap->map[i] = malloc(c * sizeof(char));
	
	cmap->righe = r;
	cmap->colonne = c;
	for(i=0; i<cmap->righe; i++){
		for(j=0; j < cmap->colonne; j++){
			cmap->map[i][j] = -1; //metto tutti muri
		}
	}
	return cmap;
}
*/
void* inserisciVerticeC(void*S, int v){
	cMap* M = S;
	pos* p = nameToCoord(M,v);
	int i = p->i, j = p->j;
	if( i >= 0 && i < M->righe && j >=0 && j < M->colonne){
		M->map[i][j] = 1; //inserisco vertice e di default metto peso ad 1.
	}
	free(p);
	return M;
}

void* eliminaVerticeC(void* S,int v){
	cMap *M = S;
	pos* p = nameToCoord(M,v);
	int i = p->i, j=p->j;
	if( i >= 0 && i < M->righe && j >=0 && j < M->colonne){
			M->map[i][j] = -1; //inserisco muro.
	}
	free(p);
	return M;
}


void inserisciArcoC(void* S,int a,int b,float p){
	if(p < 1.){
		printf("Non posso avere pesi < 1 nel labirinto\n");
		return;
	}
	cMap *M = S;
	pos* p1 = nameToCoord(M,a);
	pos* p2 = nameToCoord(M,b);
	int i1 = p1->i , j1 = p1->j, i2 = p2->i, j2 = p2->j;
	free(p1);
	free(p2);
	if(M->map[i1][j1] == -1 ) return; // se sorgente e muro non puo avere arco.
	if( ( (i1 == i2) && (j1 == j2-1 || j1 == j2+1) ) || ( (j1 == j2) && (i1 == i2-1 || i1 == i2+1) ) ) //se sono adiacenti nella mappa
		M->map[i2][j2] = p; //assegno peso alla cella di destinazione
}

void eliminaArcoC(void* S,int a,int b){
	cMap *M = S;
	pos* p1 = nameToCoord(M,a);
	pos* p2 = nameToCoord(M,b);
	int i1 = p1->i , j1 = p1->j, i2 = p2->i, j2 = p2->j;
	if(M->map[i1][j1] == -1 ) return; // se sorgente è muro non puo avere arco.
	if( ( (i1 == i2) && (j1 == j2-1 || j1 == j2+1) ) || ( (j1 == j2) && (i1 == i2-1 || i1 == i2+1) ) ) //se sono adiacenti nella mappa
		M->map[i2][j2] = -1; //assegno muro alla cella
}


void freeAdjC(ADJ* l){
	FreeLista(l);
}

 


void deallocaStrutturaC(void*S){
	cMap* M = (cMap*) S;
	int i;
	for (i = 0; i < M->righe; i++){
		free(M->map[i]);
	}
	free(M->map);
	free(M);
}



ADJ* adiacentiC(void* S, int v){
	ADJ* l = NULL;
	cMap* M = S;
	pos* p = nameToCoord(M,v), *pt=NULL;
	int j = p->j, i = p->i;
	free(p);
	if( M->map[i][j] == -1) return l;//se è muro non ha adiacenti
	//Devo deallocare le strutture posizioni.
	if( (j-1 >= 0) && M->map[i][j-1] != -1){ //diversi da muro, metto peso 1 per ora.
		p = setPosizione(i,j-1);
		l = InsertTestaL(l,coordToName(M,p),M->map[i][j-1]);
		free(p);
	}
	
	if( (i+1 < M->righe) && M->map[i+1][j] != -1){ 
		p = setPosizione(i+1,j);
		l = InsertTestaL(l,coordToName(M,p),M->map[i+1][j]);
		free(p);
	}
	if( (j+1 < M->colonne) && M->map[i][j+1] != -1){ 
		p = setPosizione(i,j+1);
		l = InsertTestaL(l,coordToName(M,p),M->map[i][j+1]);
		free(p);
	}
	if( (i-1 >= 0) && M->map[i-1][j] != -1){
		p = setPosizione(i-1,j);
		l = InsertTestaL(l,coordToName(M,p),M->map[i-1][j]);
		free(p); 
	}
	return l;
}
	
float hC(void* S,int a, int b){
//da fare.
	cMap *M = S; 
	pos* p1 = nameToCoord(M,a);
	pos* p2 = nameToCoord(M,b);
	int x1 = p1->i ,x2 = p2->i ,y1 = p1->j ,y2 = p2->j;
	free(p1);
	free(p2);
	float res = sqrt( pow(x1 - x2,2) + pow(y1-y2,2) );
	return res;
}
	
	
int verticiC(FILE* fd,cMap* cmap){
	int i=0 , j=0;
	int v = 1,x;
	while (v && !match(fd,FINISH)){
		printf("sto nel while\n");
		if(match(fd,WALL)){
			printf("muro\n");
		}
		
		else if(match(fd,CORRIDOR)){
			cmap->map[i][j] = 1;
		}
		else{
			v = 0;
			printf("Errore simbolo \n");
		}
		if(j == cmap->colonne -1){
			i++;
			j = 0;
			avoidSpace(fd);
		}
		else
			j++;
	}
	return v;
 
}
	
void* parserC(char* file){
	FILE *fd = fopen(file,"r+");
	cMap *cmap = NULL;
	int v,righe,colonne;
	if(fd != NULL){
		if(match(fd,LPAR)){
			if( (v = ParseInt(fd,&righe)) ){
				if( match(fd, COMMA) ){
					if( (v = ParseInt(fd,&colonne)) ){
						if( match(fd,RPAR) ){
							cmap = allocaCharMap(righe,colonne);
							avoidSpace(fd);
							v = verticiC(fd,cmap);
							if(!v){
								deallocaStrutturaC(cmap);
								cmap = NULL;
							}
						}
						else
							syntaxErr(RPAR,ftell(fd));
					}
					else 
						printf("Errore parser intero\n");
				}
				else 
					syntaxErr(COMMA,ftell(fd));	
			}
			else
				printf("Errore parser intero\n");
		}
		else 
			syntaxErr(LPAR,ftell(fd));
		
		fclose(fd);
	}
	return cmap;
}	
	
//stampa
void stampaLab(cMap *cmap){
	int i,j,t;
	for(i = 0;i < cmap->righe; i++){
		for(t = 0; t < 2; t++){
			for(j = 0; j < cmap->colonne; j++){
			
				if(cmap->map[i][j] == -1)
					printf("++");
				else 
					printf("  ");
			
			}
			printf("\n");			
		}
	}

}

//Generazione casuale labirinti
int isVicoloCieco(cMap* cmap,int x,int y){
	int muri = 0;
	
	if(cmap->map[x+1][y] == -1 ) muri++;
	if(cmap->map[x-1][y] == -1 ) muri++;
	if(cmap->map[x][y+1] == -1 ) muri++;
	if(cmap->map[x][y-1] == -1 ) muri++;
	//inutile controllare che nn esca dai limiti, poiche ci sono muri laterali
	return (muri>=3);
}

void EliminaVicoloCieco(cMap *cmap,int x,int y){
	//Elimino un solo muro, che viene scelto in base alla possibilità di essere eliminato.La priorità di eliminazione è (RIGHT,DOWN,LEFT,UP).
	if(y+2 < cmap->colonne-1 && cmap->map[x][y+1] == -1 ) cmap->map[x][y+1] = 1;
	else if(x+2 < cmap->righe -1 && cmap->map[x+1][y] == -1 ) cmap->map[x+1][y] = 1;
	else if(y-2 > 0 && cmap->map[x][y-1] == -1 ) cmap->map[x][y-1] = 1;
	else if(x-2 > 0 && cmap->map[x-1][y] == -1 ) cmap->map[x-1][y] = 1;
}

void EliminaVicoliCiechi(cMap* cmap){ //eliminare non quando dopo muro laterale.
	int i,j;
	int muri;
	for(i=1;i<cmap->righe-1;i++){
		for(j=1;j<cmap->colonne-1;j++){
			if(cmap->map[i][j]==1 && isVicoloCieco(cmap,i,j)){
				EliminaVicoloCieco(cmap,i,j);
			}
		}
	}
}



int randomInt(int lim){
	int val;
	val =  rand()% (lim-2) + 1; //escludendo i muri
	return val;
}


int random_cell(cMap* cmap){
	int r = cmap->righe, c = cmap->colonne;
	int x,y;
	int res;
	x = randomInt(r);
	y = randomInt(c);
	pos* p = NULL;
	p = setPosizione(x,y);
	res = coordToName(cmap,p);
	free(p);
	return res;
	/*x = randomInt(r);
	if(x%2 != 0) 
		y = random_odd(c);
	else
		y = random_even(c); 
	
	p = setPosizione(x,y);
	res = coordToName(cmap,p);
	free(p);
	return res;*/
	
}


int randomElement(int* Q,int testa,int coda, int*n ){
	if(coda == 0) return -1;
	int random = rand()%( coda - testa) + testa; //ricordare che coda punta gia al prossimo elemento.
	if(n!=NULL) *n = random;
	return Q[random];
}

int isUnvisited(cMap* cmap,int x,int y){
	int res = 1;
	if(cmap->map[x+1][y] != -1 ) return 0;
	if(cmap->map[x-1][y] != -1 ) return 0;
	if(cmap->map[x][y+1] != -1 ) return 0;
	if(cmap->map[x][y-1] != -1 ) return 0;
	//inutile controllare che nn esca dai limiti, poiche ci sono muri laterali
	return 1;
}

int has_Unvisited_Adjacents(cMap* cmap, int cell){
	pos *p = nameToCoord(cmap,cell);
	int x = p->i , y=p->j;
	int res = 0;
	free(p);
	if( x+2 < cmap->righe - 1){
		res = isUnvisited(cmap,x+2,y);
		if(res == 1) return res;
	}
	if( x-2 > 0){
		res = isUnvisited(cmap,x-2,y);
		if(res == 1) return res;
	}	
	if( y+2 < cmap->colonne-1 ){
		res = isUnvisited(cmap,x,y+2);
		if(res == 1) return res;
	}		 
	if( y-2 > 0 ){
		res = isUnvisited(cmap,x,y-2);
		if(res == 1) return res;
	}
	
	return 0;	
}
	
ADJ* unvisited_Adjacents(cMap* cmap, int cell){
	pos* p = nameToCoord(cmap,cell);
	pos* p1;
	int x = p->i , y=p->j;
	ADJ* adj = NULL;
	if( x+2 < cmap->righe - 1){
		if(	isUnvisited(cmap,x+2,y) ){
			p1 = setPosizione(x+2,y);
			adj = InsertTestaL(adj,coordToName(cmap,p1),1);
			free(p1);
		}
	}
	if( x-2 > 0){
		if(	isUnvisited(cmap,x-2,y) ){
			p1 = setPosizione(x-2,y);
			adj = InsertTestaL(adj,coordToName(cmap,p1),1);
			free(p1);
		}
	}	
	if( y+2 < cmap->colonne-1 ){
		if(	isUnvisited(cmap,x,y+2) ){
			p1 = setPosizione(x,y+2);
			adj = InsertTestaL(adj,coordToName(cmap,p1),1);
			free(p1);
		}
	}		 
	if( y-2 > 0 ){
		if(	isUnvisited(cmap,x,y-2) ){
			p1 = setPosizione(x,y-2);
			adj = InsertTestaL(adj,coordToName(cmap,p1),1);
			free(p1);
		}
	}
	free(p);
	return adj;
}

int randomAdj(ADJ* adj){
	int arr[4];
	ADJ* l = adj;
	int n = 0;
	int res;
	while(l != NULL){
		arr[n] = l->key;
		n++;
		l= l->next;
	}
	res = randomElement(arr,0,n,NULL);
	return res;
}

void dig_to(cMap* cmap,int cell,int newcell){
	pos* p1 = nameToCoord(cmap,cell);
	pos* p2 = nameToCoord(cmap,newcell);
	if(p1->i == p2->i){
		if(p1->j < p2 -> j){
			cmap->map[p1->i][p1->j+1] = 1;
			cmap->map[p1->i][p1->j+2] = 1;
		}else{ 
			cmap->map[p1->i][p1->j-1] = 1;
			cmap->map[p1->i][p1->j-2] = 1;
		}
	}
	else{
		if(p1->i < p2 -> i){
			cmap->map[p1->i+1][p1->j] = 1;
			cmap->map[p1->i+2][p1->j] = 1;
		}else{ 
			cmap->map[p1->i-1][p1->j] = 1;
			cmap->map[p1->i-2][p1->j] = 1;
		}
	}
	free(p1);
	free(p2);
	//printf("Sto collegando %d e %d \n",cell,newcell);
}

void Prim_maze(cMap* cmap){
	int r,c;
	int testa=0,coda=0;
	int cell,newcell,n;
	int* Q = malloc( ((cmap->righe * cmap->colonne) /2  )*sizeof(int));
	ADJ* adj = NULL;;
	int initcell = random_cell(cmap);
	Q[coda++] = initcell;
	pos* p = nameToCoord(cmap,initcell);
	cmap->map[p->i][p->j] = 1;
	free(p);
	
	while(testa < coda ){
		cell = randomElement(Q,testa,coda,&n);
		if(has_Unvisited_Adjacents(cmap,cell)){
			adj = unvisited_Adjacents(cmap,cell);
			newcell = randomAdj(adj);
			dig_to(cmap,cell,newcell);
			Q[coda++] = newcell;
			freeAdjC(adj);
		}
		else{
			Q[n] = Q[testa]; //faccio scambio per eliminare
			testa++;
		}
	}
	free(Q);
}



cMap* Prim(int rows, int cols){
	cMap* cmap = NULL;
	int k;
	if(rows > 2 && cols > 2 ){ //2 sono solo muri
		cmap = allocaCharMap(rows,cols);
		//initCasualLab(cmap);
		Prim_maze(cmap);
			
	}
	return cmap;
}

cMap* Dfs_maze(cMap* cmap){
	int r,c;
	int cell,newcell,n;
	int* S = malloc( ((cmap->righe * cmap->colonne) /2  )*sizeof(int));//array come stack(in posizione 0 c'è la dimensione attuale.
	ADJ* adj = NULL;;
	int initcell = random_cell(cmap);
	pos* p = nameToCoord(cmap,initcell);
	S[1] = initcell;
	S[0] = 1;
	cmap->map[p->i][p->j] = 1;
	free(p);
	while(S[0] > 0 ){
		cell = S[ S[0] ];
		if(has_Unvisited_Adjacents(cmap,cell)){
			adj = unvisited_Adjacents(cmap,cell);
			newcell = randomAdj(adj);
			dig_to(cmap,cell,newcell);
			S[S[0]+1] = newcell;
			S[0] = S[0] + 1;
			freeAdjC(adj);
		}
		else{
			S[0] = S[0] - 1;
		}
	}
	free(S);
}



cMap* DfsLab(int rows, int cols){
	cMap* cmap = NULL;
	int k; //prova.
	if(rows > 2 && cols > 2 ){ //2 sono solo muri
		cmap = allocaCharMap(rows,cols);
		//initCasualLab(cmap);
		Dfs_maze(cmap);
	}
	return cmap;
}

int* RandomDirections(){
	int* dir = malloc(4*sizeof(int));
	int i,j,tmp;
	for(i=0;i<4;i++){
		dir[i] = i;
	}
	for(i=0;i<4;i++){
		j = rand()%(4-i) +i; //numero a caso tra i ed n-1
		tmp = dir[i];
		dir[i] = dir[j];
		dir[j] = tmp;
	}
	return dir;
}

int DigUp(cMap* cmap,int r,int c){
	if(r-2 > 0 && cmap->map[r-2][c] != 1){//se gia ho fatto collegamento basta che controllo se la cella intermedia è un vertice(se faccio cosi pero mi viene sempre la stessa figura.
		cmap->map[r-2][c]=1;
		cmap->map[r-1][c]=1;
		return 1;
	}
	else 
		return 0;
}

int DigDown(cMap* cmap,int r,int c){
	if(r+2 < cmap->righe - 1 && cmap->map[r+2][c] != 1){
		cmap->map[r+2][c]=1;
		cmap->map[r+1][c]=1;
		return 1;
	}
	else 
		return 0;
}

int DigRight(cMap* cmap,int r,int c){
	if(c+2 < cmap->colonne - 1 && cmap->map[r][c+2] != 1){
		cmap->map[r][c+2]=1;
		cmap->map[r][c+1]=1;
		return 1;
	}
	else 
		return 0;
}

int DigLeft(cMap* cmap,int r,int c){
	if(c-2 > 0 && cmap->map[r][c-2] != 1){
		cmap->map[r][c-2]=1;
		cmap->map[r][c-1]=1;
		return 1;
	}
	else 
		return 0;
}

void Recursive_Maze(cMap* cmap,int r,int c){
	
	int* dir = RandomDirections();
	int i;
	int k=10;//prova
	int scelta;
	/*for(i=0;i<4;i++)
		printf("%d\t",dir[i]);
	printf("\n");*/
	
	for(i=0;i<4;i++){
		scelta = dir[i];
		switch(scelta){
				
			case 0: //up
				if(DigUp(cmap,r,c)) {
			 		Recursive_Maze(cmap,r-2,c);
			 		k = 0;
		 		}
				break;
			
			case 1: //down
				if(DigDown(cmap,r,c)){
			 		Recursive_Maze(cmap,r+2,c);
					k = 1;
				}
				break;
				
			case 2: //right
				if(DigRight(cmap,r,c)){
			 		Recursive_Maze(cmap,r,c+2);
					k = 2;
				}
				break;
		
			case 3: //left
				if(DigLeft(cmap,r,c)){
			 		Recursive_Maze(cmap,r,c-2);
			 		k = 3;
		 		}
				break;
		}
		//printf("ciaooo %d\n",k);
		
	}
	free(dir);
	
}


cMap* RecursiveLab(int rows, int cols){
	cMap* cmap = NULL;
	if(rows > 2 && cols > 2){
		cmap = allocaCharMap(rows,cols);
		cmap->map[rows-2][cols-2]=1;
		Recursive_Maze(cmap,rows-2,cols-2);
	
	}
	return cmap;		

}


int random_even(int lim){
	int val;
	val =  rand()% lim; 
	if(val%2 != 0){
		if(val + 1 == lim) 
			val = val - 1;
		else 
			val = val + 1; //è per forza maggiore uguale di 1.
	}
	return val;
}

int random_odd(int lim){
	int val;
	val =  rand()% lim; //escludendo i muri
	if(val%2 == 0){
		if(val + 1 == lim)
			val = val - 1; //è per forza maggiore uguale di 1.
		else
			val = val + 1;
	}
	return val;
}

void Divide_maze(cMap* cmap,int x,int y, int r, int c);

void Divide_horizontal(cMap* cmap,int x,int y,int r,int c){
	
	int w = random_even(r);
	int door = random_odd(c);
	int i;
	printf("r = %d, c = %d ,x = %d , y = %d,door = %d, w = %d  HORIZONTAL\n",r,c,x,y,door,w);
	for(i=0;i<c;i++){
		if(i!=door)
			cmap->map[x+w][y+i] = -1;
	}
	Divide_maze(cmap,x,y,w,c);
	Divide_maze(cmap,x+w+1,y,r-w-1,c);			
}	

void Divide_vertical(cMap* cmap,int x,int y,int r,int c){
	
	int w = random_even(c);
	int door = random_odd(r);
	int i;
	printf("r = %d, c = %d ,x = %d , y = %d,door = %d, w = %d  VERTICAL\n",r,c,x,y,door,w);
	for(i=0;i<r;i++){
		if(i!=door)
			cmap->map[x+i][y+w] = -1;
	}
	Divide_maze(cmap,x,y,r,w);
	Divide_maze(cmap,x,y+w+1,r,c-w-1);			
}

//x,y coordinate stanza || r,c dimensioni stanza
void Divide_maze(cMap* cmap,int x,int y, int r, int c){
	int a;
	printf("r = %d, c = %d ,x = %d , y = %d\n",r,c,x,y);
	if(r > 1 && c > 1){
		if(r > c)
			Divide_horizontal(cmap,x,y,r,c);
		else
			Divide_vertical(cmap,x,y,r,c);
	}
}

void labVuoto(cMap* cmap){
	int i,j;
	for(i=1;i<cmap->righe-1;i++){
		for(j=1;j<cmap->colonne-1;j++){
			cmap->map[i][j] = 1;	
		}
	}
}

cMap* DivideLab(int rows, int cols){
	cMap* cmap = NULL;
	int a;
	if(rows > 2 && cols > 2){
		cmap = allocaCharMap(rows,cols);
		labVuoto(cmap);
		Divide_maze(cmap,1,1,rows-2,cols-2);
	}
	return cmap;
}


