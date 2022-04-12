 #include"Lista.h"
#include"posizione.h"

struct charMap{
	int righe;
	int colonne;
	char** map;
};
typedef struct charMap cMap;




cMap* allocaCharMap(int righe, int colonne);
int getDimC(void* E);
ADJ* adiacentiC(void* E,int v);
void freeAdjC(ADJ* l);
void* eliminaVerticeC(void* S,int v);
void* inserisciVerticeC(void*S, int v);
void inserisciArcoC(void*S,int a,int b,float p);
void* allocaGrafoC(void* dim);
void deallocaStrutturaC(void*S);
float hC(void*,int,int);
void* parserC(char* file);
cMap* Prim(int rows, int cols);
cMap* DfsLab(int rows, int cols);
cMap* RecursiveLab(int rows,int cols);
cMap* DivideLab(int rows, int cols);



		
		
