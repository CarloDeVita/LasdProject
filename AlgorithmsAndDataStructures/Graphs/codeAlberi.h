

struct HeapNode{
	struct HeapNode* sx;
	struct HeapNode* dx;
	struct HeapNode* f;
	void* dato;
};

typedef struct HeapNode heap;

struct HeapStructure{
	heap* T;
	heap* last;//ultima foglia.
	int hsize;
};

typedef struct HeapStructure heapS;

void* AllocaStrutturaH();
void* leftH(void*,void*);
void* fatherH(void*,void*);
void* rightH(void*,void*);
int isNodeH(void *S, void *i);
void* getDatoH(void*);
void scambiaH(void*,void*);
void* getMassimoH(void*);
void* getUltimoH(void*);
void* getPunH(void*,int);
void addElemH(void*,void*);
void* deallocaH(void*);
	
