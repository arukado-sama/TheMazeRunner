#ifndef MAZE_H
#define MAZE_H

/*!
 * \file maze.h
 * \brief Création du labyrinthe.
 * \author arukado-sama
 * \version 1.0
 * \date 19 Décembre 2014
 */

#include <QApplication>
#include "defines.h"
#include "entity.h"



/*! \class Maze
   * \brief Classe qui permet de créer un labyrinthe
*/
class Maze
{

private:


public:

    /*!
             *  \brief Constructeur
             *
             *  Constructeur de la classe Maze.
    */
    Maze();

    /*! Destructeur */
    ~Maze();



    /*! Fenêtre de l'application */
        sf::RenderWindow *App;

    /*! Indicateur d'évènement */
        sf::Event Event;

    /*! Matrice des cases du labyrinthe */
        int **squares;

    /*! Tailles pour la matrice labyrinthe */
        int size1;
        int size2;

    /*! Dimensions de la fenêtre */
        int WINDOW_HEIGHT;
        int WINDOW_WIDTH;

    /*! Matrice des entités présentes (monstres)*/
        Entity **entities;

    /*! Nombre d'entités présentes (monstres)*/
        int nbEntities;

    /*! Emplacement du joueur dans le tableau des entités */
        int player;

    /*! Emplacement du gardien dans le tableau des entités */
        int guardian;

    /*! Chemin des sprites */
        QString path;

    /*! Sprite du labyrinthe */
        Sprite *maze;

    /*! Sprites des murs du labyrinthe */
        Sprite *walls;

    /*! Le joueur a la clé */
        bool playerHasKey;

    /*! Le joueur a trouvé la porte */
        bool playerHasDoor;


    /*! Contrôle du clavier */
        void keyboard();

    /*! Vérifie si le labyrinthe est ouvert */
        bool opened();

    /*! Initialise le labyrinthe */
        void initMaze();

    /*! Initialise les cases du labyrinthe */
        void initSquares();

    /*! Initialise le labyrinthe */
        void initEntities();

    /*! Initialise les mémoires des entités */
        void initMemEntities();

    /*! Initialise les cases visitées par les entitées */
        void initVisitedSquares();

    /*! Anime les entités du labyrinthe */
        void animation();

    /*! Calcule les dimensions du labyrinthe */
        void saveSizes();

    /*! Enregistre les cases du labyrinthe */
        void saveSquares();

    /*! Calcule le nombre d'entités */
        void saveNbEntities();

    /*! Enregistre les entités du labyrinthe */
        void saveEntities();

    /*! Initialisation des mémoires des monstres */
        void saveMonstersMem();

    /*! Affiche la matrice du labyrinthe */
        void printMaze();

    /*! Dessine les murs, la clé et la porte */
        void drawWalls();

    /*! Vision du joueur */
        void playerVision();

    /*! Affiche la mémoire de l'entité */
        void printMemPlayer();

    /*! Le joueur cherche la sortie */
        bool search(int X, int Y);

    /*! Le joueur peut bouger dans la direction */
        bool canMove(int X, int Y, int vector);

    /*! Le joueur a la clé et sait où est la porte */
        node dijkstra(int X, int Y);
};

#endif // MAZE_H
