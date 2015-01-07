#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//postulats : il y aura plus de 1 ligne et plus de 1 colone, sinon il n'y a pas de labyrinthe

void printMat(int **tab, int lenght, int height);

int labySize(int tab[2]){ //détermine la taille du labyrinthe, marche
	char c;
	tab[0]=0;
	tab[1]=0;
	FILE *data;
    //ouverture du fichier
    if((data = fopen("laby.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }
    
    while((c=fgetc(data))!=EOF){ //calcule nombre de lignes
    	if((c=fgetc(data))=='\n'){ tab[0]++; }
    }
    rewind(data); //retour au début
    
    
    while((c=fgetc(data))!='\n'){
    	fseek(data, -1, SEEK_CUR); //replace le curseur 1 fois vers l'arriere, à cause de la lecture du premier caractere
    	if( isdigit(c=fgetc(data)) ){ tab[1]++; }
    }
    
    fclose(data);
    return tab;
}

void readLaby(int lenght, int height){ //marche pas encore
	int Laby[lenght][height];
 	FILE *data;
    //ouverture du fichier
    if((data = fopen("laby.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }
    
    int i=0, j=0; //indices pour les matrices
    
    char c;
    while((c=fgetc(data))!=EOF){
        fseek(data, -1, SEEK_CUR); //replace le curseur 1 fois vers l'arriere, à cause de la lecture du premier caractere
        if(c=='\n'){ j++; }
	    if(isalpha(c=fgetc(data))){
	    	Laby[i][j]=atoi(c);
	    	i++;
	    }

    }
    fclose(data);
    printMat(Laby, lenght, height);
}

void printMat(int **tab, int lenght, int height){
	int i, j;
	for(i=0;i<lenght;i++){
	printf("| ");
		for(j=0;j<height;j++){
			printf(" %d",tab[i][j]);
		}
		puts(" |");
	}
}

int main(){
	int tab[2];
	labySize(tab);
	printf("Labyrinthe de taille %d %d\n", tab[0], tab[1]);
	readLaby(tab[0], tab[1]);
	
	return 0;
}