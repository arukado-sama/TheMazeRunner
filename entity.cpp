#include "entity.h"

Entity::Entity(int x0, int y0, int type0)
{
    x = x0;
    y = y0;
    type = type0;

    path = QCoreApplication::applicationDirPath ()+"/img";

    switch(type)
    {
        case PLAYER: entity = new Sprite((path+"/player.png").toStdString().c_str()); break;
        case GRIEVER: entity = new Sprite((path+"/griever.png").toStdString().c_str()); break;
        case SENTINEL: entity = new Sprite((path+"/sentinel.png").toStdString().c_str()); break;
        case GUARDIAN: entity = new Sprite((path+"/guardian.png").toStdString().c_str()); break;
    }
}

Entity::~Entity()
{
    delete entity;
}

void Entity::move(int vector)
{
    switch(vector)
    {
        case UP: if(mem[x][y-1]!=WALL) y = y-1; break;
        case DOWN: if(mem[x][y+1]!=WALL) y = y+1; break;
        case LEFT: if(mem[x-1][y]!=WALL) x = x-1; break;
        case RIGHT: if(mem[x+1][y]!=WALL) x = x+1; break;
    }
}
