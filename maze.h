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

    /*! Matrice des entités présentes */
        Entity **entities;

    /*! Nombre d'entités présentes */
        int nbEntities;

    /*! Chemin des sprites */
        QString path;

    /*! Sprite du labyrinthe */
        Sprite *maze;

    /*! Sprites des murs du labyrinthe */
        Sprite *walls;

        Sprite *wall;

public:

    /*!
             *  \brief Constructeur
             *
             *  Constructeur de la classe Maze.
    */
    Maze();

    /*! Destructeur */
    ~Maze();

    /*! Contrôle du clavier */
        void keyboard();

    /*! Vérifie si le labyrinthe est ouvert */
        bool opened();

    /*! Initialise le labyrinthe */
        void initMaze();

    /*! Initialise le labyrinthe */
        void initSquares();

    /*! Initialise le labyrinthe */
        void initEntities();

    /*! Anime les entités du labyrinthe */
        void animation();

    /*! Calcule les dimensions du labyrinthe */
        void saveSizes();

    /*! Calcule les dimensions du labyrinthe */
        void saveSquares();

    /*! Affiche la matrice du labyrinthe */
        void printMaze();
};

#endif // MAZE_H
