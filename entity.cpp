#include "entity.h"

Entity::Entity(int x0, int y0)
{
    x = x0;
    y = y0;
}

void Entity::move(int vector)
{
    switch(vector)
    {
        case UP: y = y+1; break;
        case DOWN: y = y-1; break;
        case LEFT: x = x-1; break;
        case RIGHT: x = x+1; break;
    }
}
