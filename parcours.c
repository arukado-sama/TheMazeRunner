/*
Fichier autosuffisant.
Contient toutes les donnees necessaires pour fonction seul.

problème sur le changement de la variable de direction
dans la fonction avancementsimple
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define labySize 5

void printLaby(int laby[labySize][labySize], int hero[2]);
void move(char c, int hero[2]);// ne verifie pas si les mouvement sont possibles
void scan(int possiblePath[4]); //on commence par identifier les chemins possibles
int testMove(int laby[labySize][labySize], int hero[2], char c);//verifie si le mouvement est possible dans la direction choisi
void fieldMemorize(int coordJoueur[2], int maze[labySize][labySize], int mazeMemory[labySize][labySize]); // depassement de lecture lorsque pres des bords
void avancementsimple(int laby[labySize][labySize], int hero[2], char *c);// parcours main sur le mur

char currentVector='u';

int main(){
	int laby[labySize][labySize]={{1,1,1,1,1},
					{1,0,1,0,1},
					{1,0,0,0,1},
					{1,1,1,0,1},
					{1,1,1,1,1}};
	int mem[labySize][labySize]={{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5}};
	int possiblePath[4]={0, 0, 0, 0}; //u r d l, direction cardinales, utilisees par "void move"
	int hero[2]={2,2};
	char *linkTocurrentVector=&currentVector;
	puts("Le Labyrinthe :");
	printLaby(laby, hero);
	//fieldMemorize(hero, laby, mem);
	

	while(1){
		sleep(1); //pour situer la progression
		avancementsimple(laby,hero,linkTocurrentVector);
		printLaby(laby, hero);
	}

	//puts("Le memo actuel :");
	//printLaby(mem, hero);
	return 0;
}

void printLaby(int laby[labySize][labySize], int hero[2]){
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

void move(char c, int hero[2]){
	if(c=='d'){
		hero[0]=hero[0]+1;
	}
	if(c=='u'){
		hero[0]=hero[0]-1;
	}
	if(c=='r'){
		hero[1]=hero[1]+1;
	}
	if(c=='l'){
		hero[1]=hero[1]-1;
	}
}

void fieldMemorize(int coordJoueur[2], int maze[labySize][labySize], int mazeMemory[labySize][labySize]){ // le joueur scanne les environs depuis sa posistion actuelle et les mets en mémoires
	//s'il ya un mur, il le met en mémoire et ne scanne pas au-délà
	if( maze [coordJoueur[0]+1] [coordJoueur[1]] == 0) mazeMemory[coordJoueur[0]+1] [coordJoueur[1]]=0; else { //coté droit
		mazeMemory[coordJoueur[0]+1] [coordJoueur[1]]=maze [coordJoueur[0]+1] [coordJoueur[1]]; //la case déjà testé dans le if, mais mis en mémoire
		mazeMemory[coordJoueur[0]+1] [coordJoueur[1]+1]=maze[coordJoueur[0]+1] [coordJoueur[1]+1]; //en haut
		mazeMemory[coordJoueur[0]+1] [coordJoueur[1]-1]=maze[coordJoueur[0]+1] [coordJoueur[1]-1]; //en bas
		mazeMemory[coordJoueur[0]+1+1] [coordJoueur[1]]=maze[coordJoueur[0]+1+1] [coordJoueur[1]]; //à droite
	}
	
	if( maze [coordJoueur[0]-1] [coordJoueur[1]] == 0) mazeMemory[coordJoueur[0]-1] [coordJoueur[1]]=0; else { //coté gauche
		mazeMemory[coordJoueur[0]-1] [coordJoueur[1]]=maze [coordJoueur[0]-1] [coordJoueur[1]]; //la case déjà testé dans le if, mais mis en mémoire
		mazeMemory[coordJoueur[0]-1] [coordJoueur[1]+1]=maze[coordJoueur[0]-1] [coordJoueur[1]+1]; //en haut
		mazeMemory[coordJoueur[0]-1] [coordJoueur[1]-1]=maze[coordJoueur[0]-1] [coordJoueur[1]-1]; //en bas
		mazeMemory[coordJoueur[0]-1-1] [coordJoueur[1]]=maze[coordJoueur[0]-1-1] [coordJoueur[1]]; //à gauche
	}
	
	if( maze [coordJoueur[0]] [coordJoueur[1]+1] == 0) mazeMemory[coordJoueur[0]] [coordJoueur[1]+1]=0; else { //coté haut
		mazeMemory[coordJoueur[0]] [coordJoueur[1]+1]=maze [coordJoueur[0]] [coordJoueur[1]+1]; //la case déjà testé dans le if, mais mis en mémoire
		mazeMemory[coordJoueur[0]+1] [coordJoueur[1]+1]=maze[coordJoueur[0]+1] [coordJoueur[1]+1]; //à droite
		mazeMemory[coordJoueur[0]-1] [coordJoueur[1]+1]=maze[coordJoueur[0]-1] [coordJoueur[1]+1]; //à gauche
		mazeMemory[coordJoueur[0]] [coordJoueur[1]+1+1]=maze[coordJoueur[0]] [coordJoueur[1]+1+1]; //en haut
	}
	
	if( maze [coordJoueur[0]] [coordJoueur[1]-1] == 0) mazeMemory[coordJoueur[0]] [coordJoueur[1]-1]=0; else { //coté haut
		mazeMemory[coordJoueur[0]] [coordJoueur[1]-1]=maze [coordJoueur[0]] [coordJoueur[1]-1]; //la case déjà testé dans le if, mais mis en mémoire
		mazeMemory[coordJoueur[0]+1] [coordJoueur[1]-1]=maze[coordJoueur[0]+1] [coordJoueur[1]-1]; //à droite
		mazeMemory[coordJoueur[0]-1] [coordJoueur[1]-1]=maze[coordJoueur[0]-1] [coordJoueur[1]-1]; //à gauche
		mazeMemory[coordJoueur[0]] [coordJoueur[1]-1-1]=maze[coordJoueur[0]] [coordJoueur[1]-1-1]; //en bas
	}
}

void avancementsimple(int laby[labySize][labySize], int hero[2], char *c){ //en suivant u r d l

//problème sur le changement de la variable de direction
	if(testMove(laby, hero, currentVector)){
		move(currentVector, hero);
	} else {
// instructions de changement de direction
		if (c=='u'){
			*c='r';	
		}
		if (c=='r'){
			*c='d';	
		}
		if (c=='d'){
			*c='l';	
		}
		if (c=='l'){
			*c='u';	
		}
	}
}

int testMove(int laby[labySize][labySize], int hero[2], char c){ //en suivant u r d l
//retravailler code qui suit
	if(c=='u'){
		if( laby[hero[0]-1][hero[1]]==0 ){
			return 1;		
		} else return 0;
	}else if(c=='r'){
		if( laby[hero[0]][hero[1]+1]==0 ){
			return 1;		
		} else return 0;
	} else if(c=='d'){
		if( laby[hero[0]+1][hero[1]]==0 ){
			return 1;		
		} else return 0;
	} else
	/*if(c=='l')*/{
		if( laby[hero[0]][hero[1]-1]==0 ){
			return 1;		
		} else return 0;
	}
}