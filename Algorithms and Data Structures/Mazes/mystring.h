//DE VITA CARLO N86001634

//LIBRERIA STRINGHE OTTIMIZZATA
//Pulisce il buffer per ovviare ad incongruenze
void SvuotaBuffer();

//Inserimento della stringa entro una data lunghezza
char* insertString (int n);

//Generazione numero casuale in un dato intervallo
int random_num(int a,int b);

//Generazione carattere casuale in un dato intervallo
char random_char(int a,int b);

//Generazione stringa casuale data una dimensione
char *casualString(int n);

//Controllo se inserisco un intero
int intControl();

//Controllo se inserisco un intero in un intervallo (a,b)
int intControlInterval(int a, int b);

//Controllo se inserisco un float 
float floatControl();

//Controllo se inserisco un float in un intervallo(a,b)
float floatControlInterval(float a,float b);

//Stampa dell'array di stringhe
void stampArray(char **A,int n);

//Funzione che permette l'allocazione di una stringa di lunghezza n 
char* allocaString(int n);

//deallocazione array stringhe
void deallocArrayStr(char ** A,int n);
