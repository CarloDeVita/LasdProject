#ifndef Lista_H
#define Lista_H

struct listaAD{
	int key;
	float p;
	struct listaAD *next;
};
typedef struct listaAD ADJ;

ADJ* InsertL(ADJ* adj, int v,float peso);
ADJ* InsertTestaL(ADJ* adj,int v, float peso);
ADJ* DeleteL(ADJ *adj,int v);
int InLista(ADJ *adj, int v);
void FreeLista(ADJ* adj);



#endif
