/*
pour dijkstra, tester en unidimensionnel (ou pas)

problème sur la récursivité : le paramètre de retour
l'astuce : cumuler des chiffres, puis les retraduire en lettre
mais cela ne permet que de travailler sur de petits labyrinthes car le nombre devient très long

faire une liste chainée ? rique d'ếtre multiple, on tombre dans  la construction d'un arbre,
mais c'est probablement la solution la plus élégante,
mais il faudra faire une fonction de lecture d'arbre, et récupérer la solution
comme dans le knapsack
*/

//u 1
//r 2
//d 3
//l 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define labySize 5 //que des matrices carrees, a manipuler avec precautions

struct CaseSuivante { //peut être plus de variable que nécéssaires
    int distance;
    char direction; //direction d'origine
    int Case[2];
    struct CaseSuivante * Us; //suivant haut
    struct CaseSuivante * Rs; //suivant droit
    struct CaseSuivante * Ds; //suivant bas
    struct CaseSuivante * Ls; //suivant gauche
};
typedef struct CaseSuivante * Chemin;

void printLaby(int laby[labySize][labySize], int hero[2], int end[2]);
int dijkstra(int laby[labySize][labySize], int mem[labySize][labySize], int depart[2], int end[2], int vector, int iteration, int level);
//depart est a l'origine la position du hero, change a chaque appel.
//vector est la direction d'ou venait la case depart, donc faire un contraire pour ne pas revenir en arriere, non-initialisé au départ
//algorithme recursif a quatre dimension ? complication pour récupérer la réponse ?

int main(){
	char path[9]=""; //chemin
	int laby[labySize][labySize]={{1,1,1,1,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,0,1,0,1},
								{1,1,1,1,1}};
	int mem[labySize][labySize]={{1,1,1,1,1},
								{1,0,0,0,1},
								{1,0,0,0,1},
								{1,0,1,0,1},
								{1,1,1,1,1}};
	int hero[2]={1,1};
	int end[2]={2,3};
	puts("\nTest algo Dijkstra");
	printLaby(laby,hero,end);
	//while(hero[0]==end[0] && hero[1]==end[1]){}
	
	printf("%d iterations\n",dijkstra(laby, mem, hero, end, 0, 0, 1));
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

int dijkstra(int laby[labySize][labySize], int mem[labySize][labySize], int depart[2], int end[2], int vector, int iteration, int level){ //incomplet, n'a pas la liste chainée. Mais fonctionne, mais pas le bon résultat, plante parfois
	//condition d'arret, sortie trouver
	if(depart[0]==end[0] && depart[1]==end[1]){ return 6*level; }
	
	//progression, relancement
	else if(mem[depart[0]-1][depart[1]]==0 && vector!=3){//u 1
		depart[0]--;
		return 1*level+dijkstra(laby, mem, depart, end, 3, iteration++, level++);
	}
	
	else if(mem[depart[0]][depart[1]+1]==0 && vector!=4){//r 2
		depart[1]++;
		return 2*level+dijkstra(laby, mem, depart, end, 4, iteration++, level++);
	}
	
	else if(mem[depart[0]+1][depart[1]]==0 && vector!=1){//d 3
		depart[0]++;
		return 3*level+dijkstra(laby, mem, depart, end, 1, iteration++, level++);
	}
	
	else if(mem[depart[0]][depart[1]-1]==0 && vector!=2){//l 4
		depart[1]--;
		return 4*level+dijkstra(laby, mem, depart, end, 2, iteration++, level++);
	}
	
	//condition d'arret, mur
	
	/*(laby[depart[0]][depart[1]])*/
	else { return 5*level; }
}