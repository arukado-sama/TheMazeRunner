--------------------------
| THE MAZE RUNNER README |
--------------------------



CLASSES
_______



Maze : une instance de Maze permet la construction d'un labyrinthe

- int squares[] contient les cases du labyrinthe selon leurs types
	
	0 case vide
	1 mur
	2 porte
	3 cl�
	4 t�l�porteur

- RenderWindow *App est l'instance de la fen�tre d'affichage

- Sprite *maze est le sprite du labyrinthe (fond)

- Sprite walls[] contient les sprites des cases sp�ciales du labyrinthe (1, 2, 3, 4)

- Le constructeur de Maze permet directement d'instancier les cases selon un sch�ma pr�d�fini
  Pour l'instant les sch�mas de labyrinthe sont dans un fichier � part sous forme de tableaux
  Plus tard les labyrinthes seront lus dans des fichiers



Entity : une entit� du labyrinthe (abstraite)

- int x est la position en abscisse

- int y est la position en ordonn�e

- Sprite entity est le sprite de l'entit�

- int getSquareType(QString directions[]) permet d'obtenir le type d'une des cases proches
  de l'entit� en fonction de une ou plusieurs directions, par exemple si l'on veut conna�tre
  le type se trouvant deux cases au dessus puis une case � droite de l'entit�

- void move(QString direction) permet de d�placer une entit� sur une case (4 directions possibles)

- Le constructeur instancie une entit� � une position (x, y) puis lui assigne un sprite


	Monster : l'entiti� est un monstre

	- QString type est le type du monstre (griffeur, sauteur, idiot, etc)

	- void searchPlayer() et void stay() sont des exemples de comportements possibles

	- void monsterAction() d�finit le comportement du monstre selon son type

	- Le constructeur prend en param�tre le type de monstre


	Player : l'entit� est le joueur

	- QString state est l'�tat actuel du jouer (cherchecl�, chercheporte, perdu, alerte, etc)

	- void searchDoor(), void searchKey(), void searchAll() sont des exemples de comportements

	- void controlPlayer permet de contr�ler le joueur au clavier

	- void playerAction() d�finit le comportement du joueur en fonction de son �tat actuel

	- Le constructeur ne prend que les param�tres de la classe m�re