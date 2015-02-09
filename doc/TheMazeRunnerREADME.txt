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
	3 clé
	4 téléporteur

- RenderWindow *App est l'instance de la fenêtre d'affichage

- Sprite *maze est le sprite du labyrinthe (fond)

- Sprite walls[] contient les sprites des cases spéciales du labyrinthe (1, 2, 3, 4)

- Le constructeur de Maze permet directement d'instancier les cases selon un schéma prédéfini
  Pour l'instant les schémas de labyrinthe sont dans un fichier à part sous forme de tableaux
  Plus tard les labyrinthes seront lus dans des fichiers



Entity : une entité du labyrinthe (abstraite)

- int x est la position en abscisse

- int y est la position en ordonnée

- Sprite entity est le sprite de l'entité

- int getSquareType(QString directions[]) permet d'obtenir le type d'une des cases proches
  de l'entité en fonction de une ou plusieurs directions, par exemple si l'on veut connaître
  le type se trouvant deux cases au dessus puis une case à droite de l'entité

- void move(QString direction) permet de déplacer une entité sur une case (4 directions possibles)

- Le constructeur instancie une entité à une position (x, y) puis lui assigne un sprite


	Monster : l'entitié est un monstre

	- QString type est le type du monstre (griffeur, sauteur, idiot, etc)

	- void searchPlayer() et void stay() sont des exemples de comportements possibles

	- void monsterAction() définit le comportement du monstre selon son type

	- Le constructeur prend en paramètre le type de monstre


	Player : l'entité est le joueur

	- QString state est l'état actuel du jouer (chercheclé, chercheporte, perdu, alerte, etc)

	- void searchDoor(), void searchKey(), void searchAll() sont des exemples de comportements

	- void controlPlayer permet de contrôler le joueur au clavier

	- void playerAction() définit le comportement du joueur en fonction de son état actuel

	- Le constructeur ne prend que les paramètres de la classe mère