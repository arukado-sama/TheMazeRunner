#include "maze.h"

Maze::Maze()
{
    initMaze();

    initSquares();

    initEntities();
}


Maze::~Maze()
{
    for(int i=0; i<size2; i++) free(squares[i]);
    free(squares);
    free(walls);
    free(entities);
}

void Maze::initMaze()
{
    saveSizes();

    App = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Maze Runner");

    App->setFramerateLimit(60);

    path = QCoreApplication::applicationDirPath ()+"/img";

    maze = new Sprite((path+"/maze.png").toStdString().c_str());

    maze->setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    App->draw(*maze);
}


void Maze::initSquares()
{
    //allocations des cases du labyrinthe
    squares = (int**)malloc(size1*sizeof(*squares));
    for(int i=0 ; i<size1; i++) squares[i] = (int*)malloc(size2*sizeof(**squares));

    //initialisation des cases du labyrinthe
    for(int i=0; i<size1; i++)
        for(int j=0; j<size2; j++)
            squares[i][j] = 0;

    //allocations des sprites des murs
    walls = (Sprite*)calloc(size1*size2, sizeof(Sprite));

    saveSquares();

    drawWalls();
}


void Maze::initEntities()
{
    saveNbEntities();

    //allocations des entités
    entities = (Entity**)malloc(nbEntities*sizeof(*entities));
    for(int i=0 ; i<nbEntities; i++) entities[i] = (Entity*)malloc(sizeof(**entities));

    saveEntities();

    initMemEntities();
}


void Maze::initMemEntities()
{
    for(int k=0; k<nbEntities; k++)
    {
        //allocations des cases de la mémoire de l'entité
        entities[k]->mem = (int**)malloc(size1*sizeof(*entities[k]->mem));
        for(int i=0 ; i<size1; i++) entities[k]->mem[i] = (int*)malloc(size2*sizeof(**entities[k]->mem));

        //initialisation des cases de la mémoire de l'entité
        for(int i=0; i<size1; i++)
            for(int j=0; j<size2; j++)
                entities[k]->mem[i][j] = 0;
    }
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


void Maze::animation()
{
    for(int i=0; i<nbEntities; i++)
    {
        entities[i]->entity->setPosition(entities[i]->x*40+20, entities[i]->y*40+20);

        App->draw(*(entities[i]->entity));
    }

    App->display();
}


void Maze::drawWalls()
{
    int k = 0;

    Sprite *wall = new Sprite((path+"/wall.png").toStdString().c_str());
    Sprite *key = new Sprite((path+"/key.png").toStdString().c_str());
    Sprite *door = new Sprite((path+"/door.png").toStdString().c_str());

    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            switch(squares[i][j])
            {
                case WALL: walls[k] = *wall; break;
                case KEY: walls[k] = *key; break;
                case DOOR: walls[k] = *door; break;
            }

            walls[k].setPosition(j*40+20, i*40+20);

            App->draw((Sprite)walls[k]);

            k++;
        }
    }

    App->display();
}


void Maze::saveSizes()
{
    char c = 0;
    int s1 = 0;
    int s2 = 0;

    FILE *data;

    //ouverture du fichier
    if((data = fopen("maze.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            s1++;
        }
    }

    rewind(data);
    c = 0;

    while(c!='\n')
    {
        c=fgetc(data);

        if(isdigit(c)) s2++;
    }

    fclose(data);

    size1 = s1;
    size2 = s2;

    WINDOW_HEIGHT = (size1)*40;
    WINDOW_WIDTH = (size2)*40;

    qDebug("%d %d", size1, size2);
}


void Maze::saveSquares()
{
    FILE *data;
    //ouverture du fichier
    if((data = fopen("maze.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    int s1=0, s2=0; //indices matrice
    char c;

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            s1++;
            s2=0;
        }

        if(c!='\n')
        {
            if(isdigit(c))
            {
                squares[s1][s2] = atoi(&c);

                s2++;
            }
        }

    }

    fclose(data);
}


void Maze::saveNbEntities()
{
    char c = 0;
    int nb = 0;

    FILE *data;

    //ouverture du fichier
    if((data = fopen("entities.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(data);

        if(c=='\n')
        {
            nb++;
        }
    }

    fclose(data);

    nbEntities = nb;
}


void Maze::saveEntities()
{
    FILE *data;
    //ouverture du fichier
    if((data = fopen("entities.txt","r")) == NULL) {
        fprintf(stderr, "Echec ouverture fichier. Fin de programme.\n");
        exit(1);
    }

    char c;
    int n = 0;
    int x;
    int y;
    char ctype[8];
    int type = 0;

    while(c=fgetc(data)!=EOF)
    {
        fseek(data, -1, SEEK_CUR);

        fscanf(data, "%d %d %s", &x, &y, ctype);

        if(!strcmp(ctype, "PLAYER")) type = PLAYER;
        if(!strcmp(ctype, "GRIEVER")) type = GRIEVER;
        if(!strcmp(ctype, "SENTINEL")) type = SENTINEL;
        if(!strcmp(ctype, "GUARDIAN")) type = GUARDIAN;

        Entity *e = new Entity(x, y, type);

        entities[n] = e;

        n++;

        fseek(data, 1, SEEK_CUR);
    }

    fclose(data);
}


void Maze::printMaze()
{
    for(int i=0;i<size1;i++)
    {
        printf("|");

        for(int j=0;j<size2;j++)
        {
            printf(" %d", squares[i][j]);
        }

        puts(" |");
    }
}


int Maze::pathFinding(Entity *e, int xe, int ye, int goal)
{
    int x=0, y=0;

    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size2;j++)
        {
            if(squares[i][j]==goal)
            {
                x = i;
                y = j;
            }
        }
    }

    //hors labyrinthe
    if((xe < 0) || (xe >= size1) || (ye < 0) || (ye >= size2)) return 0;

    //mémoire entité
    if(e->mem[xe][ye] == 1) return 0;

    if((xe == x) && (ye == y)) return 1;

    e->mem[xe][ye] = 1;

    return (pathFinding(e, xe+1, ye, goal) || pathFinding(e, xe-1, ye, goal) || pathFinding(e, xe, ye+1, goal) || pathFinding(e, xe, ye-1, goal));
}
