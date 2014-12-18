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
