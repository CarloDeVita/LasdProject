

struct heapArr{
	void** A;
	int dim;
	int hsize;
};
typedef struct heapArr heapA;

void* AllocaStrutturaA();
void deallocaStrutturaA(void *S);

void* leftA(void*,void*);
void* fatherA(void*,void*);
void* rightA(void*,void*);
int isNodeA(void *S, void *i);
void* getDatoA(void*);
void scambiaA(void*,void*);
void* getMassimoA(void*);
void* getUltimoA(void*);
void* getPunA(void*,int);
void addElemA(void*,void*);
void freeNodeA(void*);
void* deallocaA(void*);



