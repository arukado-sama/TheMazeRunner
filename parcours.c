/*
Fichier autosuffisant.
Contient toutes les donnees necessaires pour fonction seul.

notes : //u r d l
up right down left -> haut droite bas gauche
l'ordre est a respecter

avancementsimple fonctionne comme demande, mais l'algorithme ne convient pas
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define labySize 5 //que des matrices carrees, a manipuler avec precautions

void printLaby(int laby[labySize][labySize], int hero[2]);
void move(char c[1], int hero[2]);// ne verifie pas si les mouvement sont possibles
void scan(int possiblePath[4]); //on commence par identifier les chemins possibles
int testMove(int laby[labySize][labySize], int hero[2], char c[1]);//verifie si le mouvement est possible dans la direction choisi
void fieldMemorize(int coordJoueur[2], int maze[labySize][labySize], int mazeMemory[labySize][labySize]); // depassement de lecture lorsque pres des bords
void avancementsimple(int laby[labySize][labySize], int hero[2], char c[1]);// parcours main sur le mur

char currentVector[1]={'u'};

int main(){
	int laby[labySize][labySize]={{1,1,1,1,1},
					{1,0,1,0,1},
					{1,0,0,0,1},
					{1,1,1,0,1},
					{1,1,1,1,1}};
	/*int mem[labySize][labySize]={{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5},
					{5,5,5,5,5}};*/
	//int possiblePath[4]={0, 0, 0, 0}; //u r d l, direction cardinales, utilisees par "void move"
	int hero[2]={2,2};
	puts("Le Labyrinthe :");
	printLaby(laby, hero);
	//fieldMemorize(hero, laby, mem);
	

	while(1){
		sleep(1); //pour situer la progression
		avancementsimple(laby,hero,currentVector);
		//printLaby(laby, hero);
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

void move(char c[1], int hero[2]){
	if(c[0]=='d'){
		hero[0]=hero[0]+1;
	}
	if(c[0]=='u'){
		hero[0]=hero[0]-1;
	}
	if(c[0]=='r'){
		hero[1]=hero[1]+1;
	}
	if(c[0]=='l'){
		hero[1]=hero[1]-1;
	}
}

//inutilise pour le moment
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

void avancementsimple(int laby[labySize][labySize], int hero[2], char c[1]){ //en suivant u r d l
//d'abord tourner, avant de tenter d'avancer ?

	if (c[0]=='u'){
		c[0]='r';
		printf("changement de direction : %c\n",c[0]);	
	}
	else if (c[0]=='r'){
		c[0]='d';
		printf("changement de direction : %c\n",c[0]);
	}
	else if (c[0]=='d'){
		c[0]='l';
		printf("changement de direction : %c\n",c[0]);	
	}
	else /*(c[0]=='l')*/{
		c[0]='u';
		printf("changement de direction : %c\n",c[0]);
	}

	if(testMove(laby, hero, currentVector)){
		move(currentVector, hero);
		printLaby(laby, hero);
	}
// instructions de changement de direction

	
}

int testMove(int laby[labySize][labySize], int hero[2], char c[1]){ //en suivant u r d l
//retravailler code qui suit
	if(c[0]=='u'){
		if( laby[hero[0]-1][hero[1]]==0 ){
			return 1;		
		} else return 0;
	}else if(c[0]=='r'){
		if( laby[hero[0]][hero[1]+1]==0 ){
			return 1;		
		} else return 0;
	} else if(c[0]=='d'){
		if( laby[hero[0]+1][hero[1]]==0 ){
			return 1;		
		} else return 0;
	} else
	/*if(c[0]=='l')*/{
		if( laby[hero[0]][hero[1]-1]==0 ){
			return 1;		
		} else return 0;
	}
}