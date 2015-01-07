#include "maze.h"

Maze::Maze()
{
    int k=0;

    App = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Maze Runner");

    App->setFramerateLimit(60);

    path = QCoreApplication::applicationDirPath ()+"/img";

    maze = new Sprite((path+"/maze.png").toStdString().c_str());
    wall = new Sprite((path+"/wall.png").toStdString().c_str());

    maze->setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    App->draw(*maze);


    //tailles du labyrinthe (à modifier)
    size1=5;
    size2=10;

    //allocations des cases du labyrinthe
    squares = (int**)malloc(size1*sizeof(*squares));
    for(int i=0 ; i<size2; i++) squares[i] = (int*)malloc(size2*sizeof(**squares));

    //allocations des sprites des murs
    walls = (Sprite*)calloc(size1*size2, sizeof(Sprite));

    squares[0][0] = 1;
    squares[1][1] = 1;
    squares[1][0] = 1;
    squares[0][10] = 1;

    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            if((squares[i][j])==1)
            {
                walls[k] = *wall;

                walls[k].setPosition(i*40+20, WINDOW_HEIGHT-j*40-20);

                App->draw((Sprite)walls[k]);

                k++;
            }
        }
    }

    App->display();
}


Maze::~Maze()
{
    for(int i=0; i<size2; i++) free(squares[i]);
    free(squares);
    free(walls);
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
