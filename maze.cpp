#include "maze.h"

Maze::Maze()
{
    int k=0;

    App = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Maze Runner");

    App->setFramerateLimit(60);

    path = QCoreApplication::applicationDirPath ()+"/img";

    maze = new Sprite((path+"/maze.png").toStdString().c_str());

    for(int i=0; i!='\0'; i++)
        for(int j=0; j!='\0'; j++)
        {
            squares[i][j] = 0;

            if((squares[i][j])==1)
            {
                Sprite *wall = new Sprite((path+"/wall.png").toStdString().c_str());
                walls[k] = *wall;
                k++;


            }
        }


    maze->setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    App->draw(*maze);

    App->display();
}


void Maze::keyboard()
{
    while (App->pollEvent(Event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) App->close();
    }
}


bool Maze::opened()
{
    if(App->isOpen()) return true;

    else return false;
}
