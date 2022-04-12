//DE VITA CARLO N86001634

//IMPLEMENTAZIONE DELLE FUNZIONI DELLA LIBRERIA STRINGHE OTTIMIZZATA
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mystring.h"

//alloca stringa
char* allocaString(int n){
	char*s;	
	s=(char*)malloc((n+1)*sizeof(char));
	return s;
}

//Inserimento stringa controllato
char* insertString(int n){
	int i;
	char *s;
 	char c;
 	s=allocaString(n);
	for(i=0;(i<n && (c=getchar())!='\n' && c!=EOF);i++){
		s[i]=c; 
	}
	s[i]='\0';
	return s;
}



//Pulizia buffer
void SvuotaBuffer(){
	char c;
	while ((c=getchar()) != '\n' && c != EOF);
}


//Generazione numero casuale
int random_num(int a,int b){
    int x;
    x=a+(rand()%(b-a+1));
    return x;
}


//Generazione carattere casuale
char random_char(int a,int b){
    char x;
    x=a+(rand()%(b-a+1));
    return x;
}


//Generazione stringa casuale
char *casualString(int n){
	int i,tipo,len;
	char c,*s;
	len=random_num(1,n);
	s=allocaString(n);
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
	return s;
}

//deallocazione array stringhe
void deallocArrayStr(char ** A,int n){
    int j;
    for(j=0;j<n;j++) free(A[j]);
    free(A);
}


//Inserisce e controlla che il valore inserito sia un intero 
int intControl(){
	int i;
	char *s;
	do{  
		s=insertString(50);
		i=0;
    	while(s[i]>=48 && s[i]<=57 && s[i]!='\0'){
   	 		i++;
    	}
    	if (s[i]!='\0')
			printf("VALORE INSERITO NON CONSENTITO(DEVE ESSERE UN NUMERO INTERO).REINSERIRE: ");
  	}while(s[i]!='\0');    
 	return atoi(s);
}

//Inserisce e controlla che il valore inserito sia un intero compreso tra due numeri
int intControlInterval(int a, int b){
    int s;
	do{
   		s=intControl();
       	if(s>b || s<a) printf("VALORE NON CONSENTITO. REINSERIRE: ");
    }while(s>b || s<a);
	
	return s;
}
            
//Inserisce e controlla che il valore inserito sia un float     
float floatControl(){
	int i;
	char *s;
	do{
		s = insertString(50);
		i = 0;
		while (s[i] >= 48 && s[i] <= 57 && s[i]!='\0') 
			i++;
		if (s[i] == '.'){
			i++;
			while (s[i] >= 48 && s[i] <= 57 && s[i]!='\0') 
				i++;
			if (s[i] != '\0') printf("VALORE NON CONSENTITO. REINSERIRE: ");	
		}
		else if (s[i] != '\0') printf("VALORE NON CONSENTITO. REINSERIRE: ");	
	}while(s[i] != '\0');	
	return atof(s);
}

//Inserisce e controlla che il valore inserito sia un float compreso tra due numeri
float floatControlInterval(float a, float b){
    float s;
    do{
       	s=floatControl();
       	if(s>b || s<a) printf("VALORE NON CONSENTITO. REINSERIRE: ");
    }while(s>b || s<a);
	
	return s;
}

//Stampa un array di stringhe
void stampArray(char **A,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%s ",A[i]);
	}
}
