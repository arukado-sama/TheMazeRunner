#ifndef MAZE_H
#define MAZE_H

/*!
 * \file maze.h
 * \brief Création du labyrinthe.
 * \author arukado-sama
 * \version 1.0
 * \date 19 Décembre 2014
 */


#include "defines.h"


/*! \class Maze
   * \brief Classe qui permet de créer un labyrinthe
*/
class Maze
{
public:

    /*!
             *  \brief Constructeur
             *
             *  Constructeur de la classe Maze.
    */
    Maze();

    /*! Fenêtre de l'application */
        sf::RenderWindow *App;

    /*! Indicateur d'évènement */
        sf::Event Event;

    /*! Chemin des sprites */
        QString path;

    /*! Matrice des cases du labyrinthe */
        int **squares;

    /*! Sprite du labyrinthe */
        Sprite *maze;

    /*! Sprites des murs du labyrinthe */
        Sprite *walls;

    /*! Contrôle du clavier */
        void keyboard();

    /*! Vérifie si le labyrinthe est ouvert */
        bool opened();
};

#endif // MAZE_H
