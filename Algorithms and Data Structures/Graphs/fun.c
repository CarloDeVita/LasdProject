//FUNZIONI 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"codeHash.h"
#include"fun.h"
#include"mystring.h"
//creazione e allocazione
void *creaint(void *k){
   void *tmp=malloc(sizeof(int));
	*((int*)tmp)=*((int*)k);
	return tmp; 
   
   }
void *creafloat(void* k){
     void *tmp=malloc(sizeof(float));
     *((float*)tmp)=*((float*)k);
     return tmp;
    }

void* creastr(void *str){
     void* tmp=allocaString(strlen((char*)str));
     strcpy((char*)tmp,(char*)str);
     return tmp;
     }


void* crearecord(void* rec){
      RECORD *rec1;
      rec1=calloc(1,sizeof(RECORD));
      rec1->intero=((RECORD*)rec)->intero;
      rec1->stringa=allocaString( strlen(((RECORD*)rec)->stringa) );
      strcpy(rec1->stringa,((RECORD*)rec)->stringa);
      return (void*)rec1;
      }

//confronti
int compint(void* a,void* b){
        if(*((int*)a)<*((int*)b)) return -1;
        else if (*((int*)a)>*((int*)b)) return 1;
        else return 0;
}


int compfloat(void* a,void* b){
        if(*((float*)a)<*((float*)b)) return -1;
        else if (*((float*)a)>*((float*)b)) return 1;
        else return 0;
}

int compstr(void*s1,void*s2){
     return strcmp((char*)s1,(char*)s2);
  }

int comprecord(void *rec1,void *rec2){
    int a;
    a=((RECORD*)rec1)->intero - ((RECORD*)rec2)->intero;
    if (a==0)
      a=strcmp( ((RECORD*)rec1)->stringa, ((RECORD*)rec2)->stringa);
    return a;
 }    

//stampe
void stampaint(void* k){
   printf("%d ",*((int*)k));
}

void stampafloat(void* k){
   printf("%f ",*((float*)k));
}

void stampastr(void *s){
   printf("%s ",(char*)s);
}

void stamprecord(void* rec){
    printf("%d,", ((RECORD*)rec)->intero );
    printf("%s ", ((RECORD*)rec)->stringa);
 }
 
//inserimento
void* insintero(void){
      void*a=calloc(1,sizeof(int));
      *((int*)a)=intControl();
      return a;
}

void* insfloat(void){
      void*a=calloc(1,sizeof(float));
      *((int*)a) = floatControl();
      return a;
}

void* insertstr(void){
   return ((void*)insertString(50));
}

void* insertrecord(void){
     printf("\n");
     RECORD*rec=calloc(1,sizeof(RECORD));
     printf("INTERO: ");
     rec->intero=intControl();
     printf("STRINGA: ");
     rec->stringa=insertString(50);
     return (void*)rec;     
     
}

//controllo parita'

int pariint(void *a){
    if( *((int*)a)%2==0 ) return 1;
    else return 0;
}


int parifloat(void *a){ //pari se la parte intera è pari
    float b;
    b=*((float*)a);
    if ( (int)(b)%2==0) return 1;
    else return 0;
}

int paristring(void *a){
    if (strlen((char*)a)%2==0) return 1;
    else return 0;
  }  

int parirecord(void *rec){
   int a= pariint( &((RECORD*)rec)->intero );
   int b= paristring( (void*)((RECORD*)rec)->stringa);
   if(a==1 && b==1) return 1;
   else return 0;
   }  

//valori casuali 
 
void* random_int(void){
    void*x=calloc(1,sizeof(int));
    *((int*)x)=1+(rand()%(9999));
    return x;
}

void* random_float(void){
    void*x=calloc(1,sizeof(float));
    *((float*)x)=1+(rand()%(9999));
    return x;
}


void* random_string(void){
	int i,tipo,len;
	char c;
	char*s;
	len=random_num(1,30);
	s=allocaString(len);
	for(i=0;i<len;i++){ 
		tipo=random_num(1,3);
		if(tipo==1)
			c=random_char(65,90);//MAIUSCOLE
         else if(tipo==2)
            c=random_char(97,122);//MINUSCOLE
         else if(tipo==3)
            c=random_char(48,57);//NUMERI
         s[i]=c;
	}
	s[i]='\0';
	return (void*)s;
}


void* random_record(void){
    RECORD* rec;
    rec=calloc(1,sizeof(RECORD));
    rec->intero=random_num(0,999);
    rec->stringa=casualString(30);
    return (void*)rec;  
 }


//Stampa dell'array
void StmArr(void **A,int n,dfun *fun){
	int i;
	for(i=0;i<n;i++)
		fun->stamp(A[i]);
}



//free del record

void free_rec(void*rec){
    free(((RECORD*)rec)->stringa);
    free(((RECORD*)rec));
}
