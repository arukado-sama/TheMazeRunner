/*
pour dijkstra, tester en unidimensionnel (ou pas)

problème sur la récursivité : le paramètre de retour
l'astuce : cumuler des chiffres, puis les retraduire en lettre
mais cela ne permet que de travailler sur de petits labyrinthes
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define labySize 5 //que des matrices carrees, a manipuler avec precautions

void printLaby(int laby[labySize][labySize], int hero[2], int end[2]);
int dijkstra(int laby[labySize][labySize], int mem[labySize][labySize], int depart[2], int end[2], char vector, int iteration);
//depart est a l'origine la position du hero, change a chaque appel.
//vector est la direction d'ou venait la case depart, donc faire un contraire pour ne pas revenir en arriere, non-initialisé au départ
int rectest(int i, int lim, int level);

int main(){
	char path[9]=""; //chemin
	int laby[labySize][labySize]={{1,1,1,1,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,1,1,1,1}};
	int mem[labySize][labySize]={{1,1,1,1,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,1,1,1,1}};
	int hero[2]={2,2};
	int end[2]={2,3};
	puts("Test algo Dijkstra");
	printLaby(laby,hero,end);
	//printf("%d\n",rectest(1,6,1));
	//while(hero[0]==end[0] && hero[1]==end[1]){}
	return 0;
}

void printLaby(int laby[labySize][labySize], int hero[2], int end[2]){
	int i, j;
	printf("\nx");
	for(i=0;i<labySize;i++){
		printf("--");
	}
	printf("-x\n");
	for(i=0;i<labySize;i++){
	printf("|");
		for(j=0;j<labySize;j++){//paragraphe aux operations
			if(i==hero[0] && j==hero[1] && laby[i][j]!=1){
				printf(" H");
			} else if(i==end[0] && j==end[1] && laby[i][j]!=1){
				printf(" E");
			} else if(laby[i][j]==0){
				printf(" _");
			} else if(laby[i][j]==1){
				printf(" X");	
			} else {
				printf(" ?");			
			}
		}
		puts(" |");
	}
	printf("x");
	for(i=0;i<labySize;i++){
		printf("--");
	}
	printf("-x\n\n");
}

int dijkstra(int laby[labySize][labySize], int mem[labySize][labySize], int depart[2], int end[2], char vector, int iteration){ //incomplet
	//condition d'arret, sortie trouver
	if(depart[0]==end[0] && depart[1]==end[1]){ return 6*level; };
	
	
	
	//condition d'arret, mur
	else /*(laby[depart[0]][depart[1]])*/{ return 5*level; };
}

int rectest(int i, int lim, int level){ //juste test de fonction recursive
	if(i<lim){
		return 1*level + rectest(i+1, lim, level*10); //pour int
	} else {
		return 6*level;
	}
}