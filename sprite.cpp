/*!
 * \file sprite.cpp
 * \brief Création de sprites.
 * \author arukado-sama
 * \version 1.0
 * \date 3 Juin 2014
 *
 * Implémentation des méthodes de la classe Sprite
 *
 */

#include "sprite.h"

Sprite::Sprite(const char* ImageFileName)
{
    if (!objImage.loadFromFile(ImageFileName))
        std::cerr << "Error while loading image, check file name." << std::endl;
    this->setTexture(objImage);
    this->setOrigin(this->getGlobalBounds().width/2 , this->getGlobalBounds().height/2);
}
