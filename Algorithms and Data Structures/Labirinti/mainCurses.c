#include<ncurses.h>
#include"grafiChar.h"
#include"grafi.h"
#include"mystring.h"
#include<stdlib.h>

void engine(WINDOW *win);
void show_maze(WINDOW* win, cMap* cmap);
int init_curses();
void close_curses();
WINDOW *create_boxed_newwin(int height, int width, int starty, int startx);
void engine(WINDOW *win);
void show_message(int x, int y, char* str);

struct Cursor{
    int i;
    int j;
    char character;
};
typedef struct Cursor cursor;


int init_curses() {
	/* Init screen & keyboard input */
	initscr();	/* Start the curses mode */
	//clear();    /* Clear the screen */
	
	keypad(stdscr, TRUE); /* Allow control keys to be read (i.e., function and arrow keys) */
	curs_set(0);/* Hide cursor */
	noecho();    /* Do not echo pressed key on the screen */
	cbreak();   /* Line buffering disabled, pass on everything */
 	 if(!has_colors()) {
		endwin();
		printf("Your terminal does not support colors\n");
		return 0;
	}
	start_color();			/* Start colors */
	/* Set 3 different color pairs <foreground,background> for the text printed on the screen */
	init_pair(1, COLOR_WHITE, COLOR_BLACK); /* Text color pair 1: white on black*/
	init_pair(2, COLOR_WHITE, COLOR_RED);/* Text color pair 2: black on black */
	init_pair(3, COLOR_WHITE, COLOR_WHITE);   /* Text color pair 3: red on white */
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
	//show_message(22,0,"Press SPACE to stop, F to fire, and ESC to quit the game.");
	//refresh(); /* Show everything on the screen*/
	/* ESCDELAY = 20; */ /* Set delay for ESC reaction (default delay is too long) [Linux only] */
	return 1;
}

void close_curses() {
		attroff(COLOR_PAIR(1)); /* Restore screen colors */
		endwin();   /* Close the window */
}


void show_maze(WINDOW* win, cMap* cmap){
	int x,y;
	for (x=0; x < cmap->righe; x++) {
		for (y=0; y < cmap->colonne; y++) {
			wmove(win, x, y);
			if(x == 0 || x == cmap->righe-1 || y == 0 || y == cmap->colonne -1)
                wattron(win,COLOR_PAIR(3));
            else{
                switch(cmap->map[x][y]) {
                    case -1:
                        wattron(win,COLOR_PAIR(2));
                        break;
                    case 1:
                        wattron(win,COLOR_PAIR(1));
                        break;
                }
            }
            waddch(win,' ');
		}
	}
}

cursor* init_cursor(char c){
    cursor* curs = malloc(sizeof(cursor));
    curs->i = 1;
    curs->j = 1;
    curs->character = c;
    return curs;
}


void disegnaCella(WINDOW* win, cMap* cmap, int i,int j){
    if( cmap->map[i][j] == -1)
        wattron(win,COLOR_PAIR(2));
    else
        wattron(win,COLOR_PAIR(1));
    mvwaddch(win,i,j,' ');
}

void setPosCursore(cursor* curs, int i, int j){
    curs->i = i;
    curs->j = j;
}

void showCursore(WINDOW* win, cMap* cmap,cursor* curs){
    if(cmap->map[curs->i][curs->j] == -1){
        wattron(win,COLOR_PAIR(2));
        mvwaddch(win,curs->i,curs->j,curs->character);
    }
    else{
        wattron(win,COLOR_PAIR(1));
        mvwaddch(win,curs->i,curs->j,curs->character);
    }
}

void showCursorePercorso(WINDOW* win, cMap* cmap,cursor* curs,int curr){
    pos *p;
    p = nameToCoord(cmap,curr);
    setPosCursore(curs,p->i,p->j);
    free(p);
    mvwaddch(win,curs->i,curs->j,curs->character);
    wrefresh(win);
    mvwaddch(win,curs->i,curs->j,' ');
}

void showOneStringWindow(WINDOW* win,char* msg){
    wclear(win);
    box(win,0,0);
    mvwaddstr(win,1,2,msg);
    wrefresh(win);
}

int askVisualizeOmino(WINDOW* win){
	int key;
	mvwaddstr(win,5,2,"Visualizzare personaggio in movimento?");
	mvwaddstr(win,7,2,"(S)i");
	mvwaddstr(win,9,2,"(N)o");
	wrefresh(win);
	
	while( (key = wgetch(win) )!= 's' && key != 'n' );
	return key;
}

void stampaOmino(WINDOW* win,WINDOW* win2,cMap* cmap, int* post,int src,int dst){//mettere opzione se mostrare o meno.
    int i = 0;
    int curr = src;
    int key;
    
    key = askVisualizeOmino(win2);
	if(key == 's'){
		cursor* pers = init_cursor('@');
		while(curr != dst){
		    showCursorePercorso(win,cmap,pers,curr);
		    delay_output(200);
		    curr = post[curr];
		}
		showCursorePercorso(win,cmap,pers,curr);
		mvwaddstr(win2,11,2,"Premere un tasto per continuare...");
		wgetch(win2);
		free(pers);
		
	}
}

void infoPercorso(WINDOW* win,int t , int z){
	wclear(win);
	mvwprintw(win,1,2,"Sono stati visitati %d vertici",t);
	mvwprintw(win,3,2,"Fanno parte del percorso %d vertici",z);
	box(win,0,0);
	wrefresh(win);
}

void stampaPercorsoLab(WINDOW* win,WINDOW* win2,cMap* cmap, visita* vis, int src,int dst){
    int curr = dst;
    int tmp;
    int* post = malloc(sizeof(int)*(cmap->righe*cmap->colonne));//lo uso per movimento
    int i = 0;
    int t = 0; //visitati
    int z = 0; //vertici percorso
    int dim = cmap->righe * cmap->colonne;
    pos* p;
    cursor* percorso = init_cursor(' ');
	wattron(win,COLOR_PAIR(5));
	for(i = 0; i< dim; i++){
		if(vis->col[i] != 0){
			showCursorePercorso(win,cmap,percorso,i);
			t++;
		}
	}
	
    wattron(win,COLOR_PAIR(4));
    while(curr != src){
        showCursorePercorso(win,cmap,percorso,curr);
        tmp = curr;
        curr = vis->pred[tmp];
        post[curr] = tmp;
        z++;
    }
	z++;
    showCursorePercorso(win,cmap,percorso,curr);
    free(percorso);
 	infoPercorso(win2,t,z);
    stampaOmino(win,win2,cmap,post,src,dst);
    freeVisita(vis);
    free(post);
}


void move_cursor_only(WINDOW* win,cMap* cmap,cursor* curs){
    int key;
    while( (key = wgetch(win)) != 32){//spazio

        switch(key){
            case KEY_UP:
                curs->i--;
                if(!outLab(cmap,curs->i,curs->j)){
                    showCursore(win,cmap,curs);
                    disegnaCella(win,cmap,curs->i+1,curs->j);
                }
                else
                    curs->i++;

                break;
            case KEY_DOWN:

                curs->i++;
                if(!outLab(cmap,curs->i,curs->j)){
                    showCursore(win,cmap,curs);
                    disegnaCella(win,cmap,curs->i-1,curs->j);
                }
                else
                    curs->i--;

                break;
            case KEY_RIGHT:

                curs->j++;
                if(!outLab(cmap,curs->i,curs->j)){
                    showCursore(win,cmap,curs);
                    disegnaCella(win,cmap,curs->i,curs->j-1);
                }
                else
                    curs->j--;

                break;

            case KEY_LEFT:

                curs->j--;
                if(!outLab(cmap,curs->i,curs->j)){
                    showCursore(win,cmap,curs);
                    disegnaCella(win,cmap,curs->i,curs->j+1);
                }
                else
                    curs->j++;
                break;

        }
        wrefresh(win);
    }
}

fung* assegnaFunChar(){

	fung* f = malloc(sizeof(fung));
	f->getDim = getDimC; //Viene usata un'altra funzione
	f->inserisciVertice = inserisciVerticeC;
	f->inserisciArco = inserisciArcoC; //Non c'è bisogno di inserire archi
	f->eliminaVertice = eliminaVerticeC;
	f->eliminaArco = NULL; //Non si eliminano nemmeno
	f->adiacenti = adiacentiC;
	f->deallocaStruttura = deallocaStrutturaC;
	f->freeAdj = freeAdjC;
	f->h = hC;
	f->parser = parserC;
	f->tipo = 3;
	return f;
}


void move_cursor(WINDOW* win,WINDOW* win2,grafo* G,cursor* curs, int key){
    cMap* cmap = G->S;
    switch(key){
        case KEY_UP:
            curs->i--;
            if(!outLab(cmap,curs->i,curs->j)){
                showCursore(win,cmap,curs);
                disegnaCella(win,cmap,curs->i+1,curs->j);
            }
            else
                curs->i++;

            break;
        case KEY_DOWN:

            curs->i++;
            if(!outLab(cmap,curs->i,curs->j)){
                showCursore(win,cmap,curs);
                disegnaCella(win,cmap,curs->i-1,curs->j);
            }
            else
                curs->i--;

            break;
        case KEY_RIGHT:

            curs->j++;
            if(!outLab(cmap,curs->i,curs->j)){
                showCursore(win,cmap,curs);
                disegnaCella(win,cmap,curs->i,curs->j-1);
            }
            else
                curs->j--;

            break;

        case KEY_LEFT:

            curs->j--;
            if(!outLab(cmap,curs->i,curs->j)){
                showCursore(win,cmap,curs);
                disegnaCella(win,cmap,curs->i,curs->j+1);
            }
            else
                curs->j++;
            break;

        case 'v':
            EliminaVicoliCiechi(cmap);
            show_maze(win,cmap);
            setPosCursore(curs,1,1);
            showCursore(win,cmap,curs);
            break;

        case 'm':
            setMuro(cmap,curs->i,curs->j);
            disegnaCella(win,cmap,curs->i,curs->j);
            showCursore(win,cmap,curs);
            break;

        case 'c':
            setCorridoio(cmap,curs->i,curs->j);
            disegnaCella(win,cmap,curs->i,curs->j);
            showCursore(win,cmap,curs);

            break;

        case 'p':
            Percorso(win,win2,G,curs);
    }


}



void manage_lab(WINDOW* win,WINDOW* win2,cMap* cmap, cursor* curs){
    int key ;
    fung* f = assegnaFunChar();
    grafo* G = CreaGrafo(f,cmap);

    while( (key = wgetch(win) ) != 'q'){
        move_cursor(win,win2,G,curs,key);
        wrefresh(win);
    }
    wclear(win2);
    wrefresh(win2);
    DeallocaGrafo(G);
    free(f);

}

void defaultCommandsWindow(WINDOW* win){
    wclear(win);
    mvwaddstr(win,1,2,"V per eliminare vicoli ciechi");
    mvwaddstr(win,3,2,"FRECCE per cambiare direzione ");
    mvwaddstr(win,5,2,"M per far diventare muro il vertice selezionato");
    mvwaddstr(win,7,2,"C per far diventare corridoio il vertice selezionato ");
    mvwaddstr(win,9,2,"P per individuare percorsi");
    mvwaddstr(win,11,2,"Q per uscire");
    box(win,0,0);
    wrefresh(win);
}

void defaultLabWindow(WINDOW* win,cMap* cmap, cursor* curs){
    wclear(win);
    show_maze(win,cmap);
    setPosCursore(curs,1,1);
    showCursore(win,cmap,curs);
    wrefresh(win);
}


visita* selectMetodoVisita(WINDOW* win,grafo* G,int src,int dst){
    int key;
    visita* vis = NULL;
    wclear(win);
    box(win,0,0);
    mvwaddstr(win,1,2,"1) PERCORSO TRAMITE DFS");
    mvwaddstr(win,3,2,"2) PERCORSO TRAMITE BFS");
    mvwaddstr(win,5,2,"3) PERCORSO TRAMITE DIJKSTRA");
    mvwaddstr(win,7,2,"4) PERCORSO TRAMITE A_STAR");
    wrefresh(win);
    while( (key = wgetch(win)) < 49 || key >52);
    switch(key){
        case 49:
            vis = PercorsoCasuale(G,src,dst);
            break;
        case 50:
            vis = PercorsoMinimo(G,src,dst);
            break;
        case 51:
            vis = P_Dijkstra(G,src,dst);
            break;
        case 52:
            vis = P_Astar(G,src,dst);
            break;
    }
    return vis;
}

Percorso_lab(WINDOW* win,WINDOW* win2, grafo* G, int src, int dst)   {
	cMap* cmap = G->S;
	visita* vis = selectMetodoVisita(win2,G,src,dst);
    stampaPercorsoLab(win,win2,cmap,vis,src,dst);
}

Percorso(WINDOW* win,WINDOW* win2,grafo* G,cursor* curs){
    int key;
    int i1,i2,j1,j2;
    int src,dst;
    cMap* cmap = G->S;
    showOneStringWindow(win2,"Scegliere SORGENTE (corridoio) e premere SPAZIO");
    do{
        move_cursor_only(win,cmap,curs);
        i1 = curs->i;
        j1 = curs->j;
    }while(isMuro(cmap,i1,j1));
    showOneStringWindow(win2,"Scegliere DESTINAZIONE (corridorio) e premere SPAZIO");
    do{
        move_cursor_only(win,cmap,curs);
        i2 = curs->i;
        j2 = curs->j;
    }while(isMuro(cmap,i2,j2));
    src = coordToName2(cmap,i1,j1);
    dst = coordToName2(cmap,i2,j2);
    Percorso_lab(win,win2,G,src,dst);
    defaultCommandsWindow(win2);
    defaultLabWindow(win,cmap,curs);


}

int startWindow(WINDOW* win){
    wclear(win);//clear
    wattron(win,COLOR_PAIR(1));
    mvwaddstr(win,1,1,"\t\tGESTIONE LABIRINTI");
    mvwaddstr(win,2,1,"1) ISPIRATO A PRIM");
    mvwaddstr(win,3,1,"2) ISPIRATO A DFS");
    mvwaddstr(win,4,1,"3) RECURSIVE MAZE");
    mvwaddstr(win,5,1,"4) DIVIDE RECURSIVE MAZE");
    mvwaddstr(win,6,1,"5) ESCI");

    wrefresh(win);
    int scelta = wgetch(win);
    return scelta;
}



void engine(WINDOW *win){
	int scelta;
	int v;
	cMap* cmap = NULL;
	cursor* curs = NULL;
	WINDOW* localWin = newwin(20,60,5,70);;
    srand(time(NULL));


	do{

		scelta = startWindow(win);
		switch(scelta){
			case '1':
				cmap = Prim(30,50);
				curs = init_cursor('C');
                defaultLabWindow(win,cmap,curs);
                defaultCommandsWindow(localWin);
                manage_lab(win,localWin,cmap,curs);
                free(curs);
				break;

			case '2':
				cmap = DfsLab(30,50);
				curs = init_cursor('C');
                defaultLabWindow(win,cmap,curs);
                defaultCommandsWindow(localWin);
                manage_lab(win,localWin,cmap,curs);
                free(curs);
				break;

			case '3':
				cmap = RecursiveLab(30,50);
				curs = init_cursor('C');
                defaultLabWindow(win,cmap,curs);
                defaultCommandsWindow(localWin);
                manage_lab(win,localWin,cmap,curs);
                free(curs);
				break;

			case '4':
				cmap = DivideLab(30,50);
				curs = init_cursor('C');
                defaultLabWindow(win,cmap,curs);
                defaultCommandsWindow(localWin);
                manage_lab(win,localWin,cmap,curs);
                free(curs);
				break;

		}
	}while(scelta != '5');
	delwin(localWin);

}

int main() {
	WINDOW *win; /* Pointer to a window structure */

	if  (init_curses()) { /* if ncurses intialization was successful ... */
		//win = create_boxed_newwin(40,120,0,0); /* create the game area on the screen */
		win = newwin(40,60,0,0);

		keypad(win, TRUE);
		
		if (win){	 /*if the game area was successfully created, then start the game */
			engine(win);
            delwin(win);
		}
		close_curses(); /* close ncurses */
	}
	return 0;
}

