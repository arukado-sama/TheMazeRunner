#ifndef ENTITY_H
#define ENTITY_H

#include <QApplication>
#include "defines.h"

class Entity
{
public:

    /*! Constructeur */
    Entity(int x0, int y0, int type0);

    /*! Destructeur */
    ~Entity();

    /*! Abscisse de l'entité */
    int x;

    /*! Ordonnée de l'entité */
    int y;

    /*! type de l'entité */
    int type;

    /*! Matrice mémoire de l'entité */
    int **mem;

    /*! Matrice des cases visitées */
    int **visited;

    /*! Chemin des sprites */
    QString path;

    /*! Sprite de l'entité */
    Sprite *entity;

    /*! Déplacement de l'entité */
    void move(int vector);
};

#endif // ENTITY_H
