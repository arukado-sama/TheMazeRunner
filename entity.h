#ifndef ENTITY_H
#define ENTITY_H

#include "maze.h"

class Entity
{
public:

    Entity(int x0, int y0);

    int x;

    int y;

    /*! Chemin des sprites */
    QString path;

    Sprite *entity;

    void move(int vector);

};

#endif // ENTITY_H
