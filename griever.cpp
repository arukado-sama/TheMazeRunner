#include "griever.h"

Griever::Griever(int x0, int y0):Monster(x, y)
{
    Monster(x0, y0);

    entity = new Sprite((path+"/griever.png").toStdString().c_str());

    entity->setPosition(x*40+20, WINDOW_HEIGHT-(y*40+20));
}
