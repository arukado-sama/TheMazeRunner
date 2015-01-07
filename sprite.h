#ifndef SPRITE_H
#define SPRITE_H

/*!
 * \file sprite.h
 * \brief Création de sprites.
 * \author arukado-sama
 * \version 1.0
 * \date 3 Juin 2014
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

/*! \class Sprite
   * \brief Classe qui gère la création d'un sprite à partir d'une image.
*/
class Sprite : public sf::Sprite
{

public:

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe spite, créé un sprite à partir d'une image.
         *
         * \param ImageFileName : chemin de l'image à utiliser
    */
    Sprite(const char* ImageFileName);


private:

    /*! Texture d'affichage du sprite */
    sf::Texture objImage;
};

#endif // SPRITE_H
