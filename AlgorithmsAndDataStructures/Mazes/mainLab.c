#include<stdio.h>
#include"grafiChar.h"
#include"mystring.h"

main(){
	int scelta;
	int v;
	cMap* cmap = NULL;
	printf("\t\tGESTIONE LABIRINTI\n\n");
	srand(time(NULL));
	
	do{
		printf("1) ISPIRATO A PRIM\n");
		printf("2) ISPIRATO A DFS\n");
		printf("3) RECURSIVE MAZE\n");
		printf("4) DIVIDE RECURSIVE MAZE\n");
		printf("5) ESCI\n");
		
		printf("Scelta: ");
		scelta = intControlInterval(1,5);
		switch(scelta){
			case 1:
				cmap = Prim(20,20);
				stampaLab(cmap);
				printf("\n\nEliminare Vicoli ciechi?\n1)SI\n2)NO\nScelta: ");
				v = intControlInterval(1,2);
				if(v == 1){
					EliminaVicoliCiechi(cmap);	
					stampaLab(cmap);
				}
				deallocaStrutturaC(cmap);
				break;
	
			case 2:
				cmap = DfsLab(20,20);
				stampaLab(cmap);
				printf("\n\nEliminare Vicoli ciechi?\n1)SI\n2)NO\nScelta: ");
				v = intControlInterval(1,2);
				if(v == 1){
					EliminaVicoliCiechi(cmap);	
					stampaLab(cmap);
				}
				deallocaStrutturaC(cmap);
				break;
	
			case 3:
				cmap = RecursiveLab(50,50);
				stampaLab(cmap);
				printf("\n\nEliminare Vicoli ciechi?\n1)SI\n2)NO\nScelta: ");
				v = intControlInterval(1,2);
				if(v == 1){
					EliminaVicoliCiechi(cmap);	
					stampaLab(cmap);
				}
				deallocaStrutturaC(cmap);
				break;
			
			case 4:
				cmap = DivideLab(50,50);
				stampaLab(cmap);
				printf("\n\nEliminare Vicoli ciechi?\n1)SI\n2)NO\nScelta: ");
				v = intControlInterval(1,2);
				if(v == 1){
					EliminaVicoliCiechi(cmap);	
					stampaLab(cmap);
				}
				deallocaStrutturaC(cmap);
				break;
			
		}
	}while(scelta != 5);

}
