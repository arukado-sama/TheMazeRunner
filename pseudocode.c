void carte(){ //prend un fichier ? renvoie la carte sous quel forme ?

	lirefichier(file); //si lecture de fichier
	random(); //si générateur aléatoire de carte existe
	afficheCarte(); //affiche la carte avec monstre(s) et protagoniste
	testMap(); //test si le labyrinthe peut être résolu
}


//peut être généraliser pour toutes les entités
int searchPlayer(int PlayerLocation[2], int MonsterLocation[2], int DetectionRange){
	int Distance, vector[2];
	
	vector = { PlayerLocation[0]-MonsterLocation[0] ) , fabs( PlayerLocation[1]-MonsterLocation[1] }
	
	Distance = fabs( PlayerLocation[0]+MonsterLocation[0] ) + fabs( PlayerLocation[1]+MonsterLocation[1] );
	
	Distance = fabs(vector[0])+fabs(vector[1]);
	
	//Penser à optimiser : d'abord calculer la distance pour test ?
	//Ou calculer le vector pour diminuer temps d'execution en cas de détection fréquente ?
	if(Distance>DetetionRange){
		return [0,0];
	} else {
		return vector;
	}
}
/*
nécéssite un tableau d'entier pour les vecteurs, conjugué de l'emploi d'un modulo
*/


//peut aussi marcher sur les statues de gardes, sauf immobilité sans détections
var simpleMonsterMove(){
	if(DetectPlayer){
		moveTowardsPlayer();
	} else {
		moveRandom();
	}
}

var guardianMove(){
	//poursuit le joueur quand ce dernier à obtenu la clé
	//poursuit quelque soit la distance
}

var sentinelMove(DefaultMove, vector, sentinelPlace){ //Ce monstre est un automate se contentant de se coller sur un mur, DefaultMove étant par rapport a son vecteur de déplacement d'origine.
	//DefaultMove est gauche ou droite
	//doit commencer à côté d'un mur (pour simplier l'ia)
	//tourne toujours sur sa droite ou sur sa gauche (au choix)
	//PAS DE CASES ENCLAVéES
	//nécésiterait un tableau et un modulo pour faire le tour des directions

	if(movePossible(DefaultMove x vector)){
		move DefaultMove;
	} else if (movePossible(DefaultMove x DefaultMove x vector)){
		move DefaultMove x DefaultMove;
	} else if (movePossible(DefaultMove x DefaultMove x DefaultMove x vector)){
		move DefaultMove x DefaultMove x DefaultMove;
	} else {
		move DefaultMove x DefaultMove x DefaultMove x DefaultMove;
	}

	return vector; //doit changer le vecteur de la sentinelle en cas de changement
}

var sentinelBasicBeastMove(state, sentinelPlace, range){ //Ce monstre se déplace aléatoirement s'il ne détecte pas le joueur, sinon, il le poursuivera.
}

var pursuit(){ //joueur détecté, poursuite entamée
	patchfind();
	move();
}

var fieldMemorize(int coordJoueur[2], int maze[][], int mazeMemory[][]){ // le joueur scanne les environs depuis sa posistion actuelle et les mets en mémoires
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

void search(int vector){ //algo IA de base, fonction d'initilization préalable nécéssaire, initialisée avec un vecteur au départ, en paramètre ou au début de l'algorithme
	while (DoorAndKey not found){
		ScanAndGrabIfKey(); //Scanne la zone est la mets en mémoire, prend la clé si elle y est
		if (dead end) backtrack();
		else if (crossroad) chooseAndSetVector(); move(); //le choix sera doute complexe en prenant en compte de nombreux paramètres comme la mémoire
		else moveForward(); //chemin unique, prend en compte les changements de directions
	}
	// après, courir vers la sortie
	runToExit();
}